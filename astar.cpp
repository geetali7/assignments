#include <bits/stdc++.h>
using namespace std;
#define N 3

class Node
{
public:
    Node *parent;
    int **mat;
    int x, y, r, c;

    int cost;
    int level;

    Node(int a, int b)
    {
        r = a;
        c = b;
        mat = new int *[r];
        for (int i = 0; i < r; i++)
        {
            mat[i] = new int[c];
        }
    }
};
void printMatrix(int **mat, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

Node *newNode(int **mat, int x, int y, int newX,
              int newY, int level, Node *parent, int r, int c)
{
    Node *node = new Node(r, c);
    node->parent = parent;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            node->mat[i][j] = mat[i][j];
        }
    }
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;

    return node;
}

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

int calculateCost(int **initial, int **final, int r, int c)
{
    int count = 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (initial[i][j] && initial[i][j] != final[i][j])
                count++;
    return count;
}
int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}
void printPath(Node *root, int r, int c)
{
    if (root == NULL)
        return;
    printPath(root->parent, r, c);
    printMatrix(root->mat, r, c);

    printf("\n");
}
struct comp
{
    bool operator()(const Node *lhs, const Node *rhs) const
    {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};
void solve(int **initial, int x, int y,
           int **final, int r, int c)
{

    priority_queue<Node *, std::vector<Node *>, comp> pq;

    Node *root = newNode(initial, x, y, x, y, 0, NULL, r, c);
    root->cost = calculateCost(initial, final, r, c);
    pq.push(root);
    while (!pq.empty())
    {

        Node *min = pq.top();
        cout << "\n\nParent Matrix : \n";
        printMatrix(min->mat, r, c);
        cout << "********************\n";
        cout << " h(n) : " << min->cost << endl;
        cout << " g(n) : " << min->level << endl;
        cout << " f(n) : " << min->cost + min->level << "\n";
        pq.pop();
        if (min->cost == 0)
        {
            cout << endl;
            cout << "Path form start to Final State" << endl;
            printPath(min, r, c);

            return;
        }
        for (int i = 0; i < 4; i++)
        {
            if (isSafe(min->x + row[i], min->y + col[i]))
            {
                Node *child = newNode(min->mat, min->x,
                                      min->y, min->x + row[i],
                                      min->y + col[i],
                                      min->level + 1, min, r, c);
                child->cost = calculateCost(child->mat, final, r, c);
                cout << "Child Matrix : " << child->cost << endl;
                printMatrix(child->mat, r, c);
                cout << "\n";
                cout << " h(n) : " << child->cost << endl;
                cout << " g(n) : " << child->level << endl;
                cout << " f(n) : " << child->cost + child->level << "\n";
                pq.push(child);
            }
        }
    }
}
int main()
{

    cout << "Enter Number of rows and colums" << endl;
    int r, c;
    cin >> r >> c;

    int **start = new int *[r], ** final = new int *[r];
    for (int i = 0; i < r; i++)
    {
        start[i] = new int[c];
        final[i] = new int[c];
    }
    cout << "Enter Start Matrix" << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> start[i][j];
        }
    }
    cout << "Enter Final Matrix" << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> final[i][j];
        }
    }
    int x = -1, y = -1;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (start[i][j] == 0)
            {
                x = i;
                y = j;
                break;
            }
        }
    }
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            sum1 += start[i][j];
        }
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            sum2 += final[i][j];
        }
    }
    if (sum1 != sum2)
    {
        cout << "Unsolvable case." << endl;
    }
    else
        solve(start, x, y, final, r, c);

    return 0;
}