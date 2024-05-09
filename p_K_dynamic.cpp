#include <iostream>
#include <vector>
#include <string>
using namespace std;

class PrimsMST {
    vector<vector<int>> a; // Vector for graph adjacency matrix
    vector<vector<int>> b; // Vector for MST adjacency matrix
    vector<string> name; // Vector to store landmark names

public:
    PrimsMST(int ver) {
        // Initialize vectors with size ver
        a.resize(ver, vector<int>(ver, 0));
        b.resize(ver, vector<int>(ver, 0));
        // Resize vector for landmark names
        name.resize(ver);
    }

    void read(int ver, int e);
    void add_edge(int, int, int);
    void prims(int);
    void display(int);
    void kruskals(int);
};

void PrimsMST::read(int ver, int e)
{
    int u, v, w;
    string n1, n2;
    cout << "Enter Name of Landmarks: ";
    for (int i = 0; i < ver; i++)
    {
        cin >> name[i];
    }
    for (int i = 0; i < e; i++)
    {
        cout << "Enter enter source, destination and its weight: ";
        cin >> n1 >> n2 >> w;
        for (int i = 0; i < ver; i++)
        {
            if (n1 == name[i])
            {
                u = i;
                break;
            }
        }
        for (int i = 0; i < ver; i++)
        {
            if (n2 == name[i])
            {
                v = i;
                break;
            }
        }
        add_edge(u, v, w);
    }
}

void PrimsMST::add_edge(int u, int v, int w)
{
    a[u][v] = w;
    a[v][u] = w;
}

void PrimsMST::display(int v)
{
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void PrimsMST::prims(int ver)
{
    int inf = 9999999;
    int cost = 0;
    vector<bool> selected(ver, false);
    int no_edge = 0;
    int x, y;
    selected[0] = true;
    while (no_edge < (ver - 1))
    {
        int min = inf;
        x = 0;
        y = 0;
        for (int i = 0; i < ver; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < ver; j++)
                {
                    if (!selected[j] && a[i][j])
                    {
                        if (min > a[i][j])
                        {
                            min = a[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        cout << name[x] << " - " << name[y] << " : " << a[x][y];
        b[x][y] = a[x][y];
        b[y][x] = a[x][y];
        cost = cost + a[x][y];
        cout << endl << endl;
        selected[y] = true;
        no_edge++;
    }
    cout << "MINIMUM SPANNING TREE:- " << endl;
    for (int i = 0; i < ver; i++)
    {
        for (int j = 0; j < ver; j++)
        {
            cout << b[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Minimum cost by Prims Algorithm: " << cost << endl;
}

void PrimsMST::kruskals(int ver)
{
    int count = 0;
    vector<int> father(ver, -1);
    int wt = 0;
    vector<vector<int>> res(ver, vector<int>(ver, 0));

    while (count < ver - 1)
    {
        long int min = 9999;
        int t1, t2, temp1, temp2, root_temp1, root_temp2;

        for (int v1 = 0; v1 < ver; v1++)
        {
            for (int v2 = 0; v2 < ver; v2++)
            {
                if (a[v1][v2] != 0 && a[v1][v2] < min)
                {
                    min = a[v1][v2];
                    t1 = v1;
                    t2 = v2;
                }
            }
        }

        temp1 = t1;
        temp2 = t2;
        a[t1][t2] = a[t2][t1] = 0;

        while (t1 >= 0)
        {
            root_temp1 = t1;
            t1 = father[t1];
        }
        while (t2 >= 0)
        {
            root_temp2 = t2;
            t2 = father[t2];
        }

        if (root_temp1 != root_temp2)
        {
            res[temp1][temp2] = res[temp2][temp1] = min;
            wt = wt + res[temp1][temp2];
            father[root_temp2] = root_temp1;
            count++;
        }
    }
    cout << "Minimum cost by Kruskals Algorithm: " << wt << endl;
}

int main()
{
    int ver, e;
    cout << "Enter no. of vertices: " << endl;
    cin >> ver;
    cout << "Enter no. of edges: " << endl;
    cin >> e;
    PrimsMST p(ver);

    int ch;
    while (true)
    {
        cout << "\n----------Menu----------" << endl;
        cout << "1.Read the Graph" << endl;
        cout << "2.Display the graph" << endl;
        cout << "3.Minimum Cost using Prims Algorithm" << endl;
        cout << "4.Minimum Cost using Kruskals Algorithm" << endl;
        cout << "5.Exit " << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            p.read(ver, e);
            break;
        case 2:
            p.display(ver);
            break;
        case 3:
            p.prims(ver);
            break;
        case 4:
            p.kruskals(ver);
            break;
        case 5:
            cout << "Code Exited" << endl;
            exit(0);
        default:
            cout << "\nEnter correct choice!!" << endl;
            break;
        }
    }
    return 0;
}
