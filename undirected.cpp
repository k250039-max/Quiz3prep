#include<iostream>
#include<list>
#include<queue>
#include<vector>
#include<stack>
using namespace std;

class Graph
{
    int V;
    list<int>* L;
    void DFSHelper(int u,vector<bool>&vis)
    {
        cout<<u<<" ";
        vis[u]=true;
        for(int v:L[u])
        {
            if(!vis[v]) DFSHelper(v,vis);
        }
    }
    bool isCycleUndirDFS(int src,int par,vector<bool>&vis)
    {
        vis[src]=true;
        list<int> neighbours = L[src];
        for(int v:neighbours)
        {
            if(!vis[v]) if(isCycleUndirDFS(v,src,vis)) return true;
            else if(v!=par) return true;
        }
        return false;

    }
    bool isCycleUndirBFS(int src,vector<bool>&vis)
    {
        queue<pair<int,int>> q;
        vis[src]=true;
        q.push({src,-1});
        while(q.size()>0)
        {
            int u=q.front().first;
            int parent=q.front().second;
            q.pop();
            list<int> neighbours=L[u];
            for(int v:neighbours)
            {
                if(!vis[v])
                {
                    q.push({u,v});
                    vis[v]=true;
                }
                else if(v!=parent) return true;

            }
        }
        return false;
    }
    void toposorthelper(int curr,vector<bool> &vis,stack<int> &s)
    {
        vis[curr]=true;
        for(int v:L[curr])
        {
            if(!vis[v]) toposorthelper(v,vis,s);
        }
        s.push(curr);
    }
    public:
    Graph(int val):V(val)
    {
        L = new list<int>[V];
    }

    void addedge(int u,int v)
    {
        L[u].push_back(v);
        L[v].push_back(u);
    }
    void printADJlist()
    {
        for(int i=0;i<V;i++)
        {
            cout<<i<<":";
            for(int neigh:L[i])
            {
                cout<<neigh<<" ";
            }
            cout<<endl;
        }
    }
    void bfs()
    {
        queue<int> Q;
        vector<int> vis(V,false);
        Q.push(0);
        vis[0]=true;
        while(Q.size()>0)
        {
            int u=Q.front();
            cout<<u<<" ";
            Q.pop();
            for(int v:L[u])
            {
                if(!vis[v])
                {
                    vis[v]=true;
                    Q.push(v);
                }
                
            }

        }
        cout<<endl;
    }
    void dfs()
    {
        int u=0;
        vector<bool> vis(V,false);
        DFSHelper(u,vis);
    }
    bool iscycledfs()
    {
        vector<bool> vis(V,false);
        for(int i=0;i<V;i++)
        {
            if(!vis[i]) 
            {
                if(isCycleUndirDFS(i,-1,vis)) return true;
            }
        }
        return false;
    }
    bool iscyclebfs()
    {
        vector<bool> vis(V,false);
        for(int i=0;i<V;i++)
        {
            if(!vis[i]) if(isCycleUndirBFS(i,vis)) return true;
        }
        return false;
    }

    void topologicalsort()
    {
        vector<bool> vis(V,false);
        stack<int>s;
        for(int i=0;i<V;i++) if(!vis[i]) toposorthelper(i,vis,s);
        
        while(s.size()>0)
        {
            int curr=s.top();
            s.pop();
            cout<<curr<<" ";
        }
    }
};


int main()
{
    Graph g(5);
    g.addedge(0,1);
    g.addedge(0,2);
    g.addedge(0,3);
    g.addedge(1,2);
    g.addedge(3,4);
    g.printADJlist();
    g.bfs();
    g.dfs();
    cout<<endl;
    cout<<g.iscycledfs();
}