#include<iostream>
using namespace std;


class Graph
{
    private:
        static const int MAX = 10;
        int adjacency[MAX][MAX];
        bool visited[MAX];
        int vertices;

        // -----------------------------------------
        // DFS RECURSIVE HELPER
        // -----------------------------------------

        void DFSRecursive(int current)
        {
            visited[current] = true;
            cout << current << " ";

            for(int i = 0; i < vertices; i++)
            {
                if(adjacency[current][i] == 1 && visited[i] == false)
                {
                    DFSRecursive(i);
                }
            }
        }

    public:
        Graph(int pVertices)
        {
            vertices = pVertices;

            for(int i = 0; i < vertices; i++)
            {
                visited[i] = false;

                for(int j = 0; j < vertices; j++)
                {
                    adjacency[i][j] = 0;
                }
            }
        }

        void AddEdge(int source, int destination)
        {
            adjacency[source][destination] = 1;
            adjacency[destination][source] = 1;
        }

        void BFS(int start)
        {
            int queue[MAX];
            int front = 0;
            int rear = 0;

            for(int i = 0; i < vertices; i++)
            {
                visited[i] = false;
            }

            visited[start] = true;
            queue[rear] = start;
            rear++;

            while(front < rear)
            {
                int current = queue[front];
                front++;
                cout << current << " ";
				
                for(int i = 0; i < vertices; i++)
                {
                    if(adjacency[current][i] == 1 && visited[i] == false)
                    {
                        visited[i] = true;
                        queue[rear] = i;
                        rear++;
                    }
                }
            }
        }

        void DFS(int start)
        {
            for(int i = 0; i < vertices; i++)
            {
                visited[i] = false;
            }

            DFSRecursive(start);
        }
};

int main()
{
    Graph graph(6);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 4);
    graph.AddEdge(2, 5);

    cout << endl
         << "BFS Traversal: ";

    graph.BFS(0);

    cout << endl
         << "DFS Traversal: ";

    graph.DFS(0);

    return 0;
}