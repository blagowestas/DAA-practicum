#include <cstdio>
#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

const int MAX_EQUIPMENT = int(1e6);

struct edge
{
    int equipment, time, to; 
};

vector<edge> g[int(1e5)];
int equipment[int(1e5)];
int t[int(1e5)];
bool used[int(1e5)];


void all_paths_aux(int current_node, int& goal_node, int& result, int& record)
{
   used[current_node]=true;

    if(current_node == goal_node )
    {
        result = min(result, equipment[current_node]);
    }

    for (edge neib: g[current_node])
    {
        if(!used[neib.to])
        { 
            equipment[neib.to] = max(neib.equipment, equipment[current_node]);
            t[neib.to] = neib.time + t[current_node];
            if(t[neib.to]<=record && equipment[neib.to]<=result)
                all_paths_aux(neib.to, goal_node, result, record);
        }
    }

    used[current_node]=false;
}

int all_paths(int start, int end, int record)
{
    vector<int> current_path;
    int result=MAX_EQUIPMENT;
    equipment[start]=0;
    t[start]=0;
    all_paths_aux(start, end, result, record);
    
    if(result==MAX_EQUIPMENT)
        return -1;
     return result;
}


int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int rocks_number, bridges_number, record;
    
    scanf("%d %d %d",&rocks_number,&bridges_number,&record);

    int start;
    edge new_edge;

    for(int i=0; i<bridges_number; ++i)
    {
        scanf("%d %d %d %d",&start,&new_edge.to,&new_edge.equipment,&new_edge.time);    
        if(new_edge.time <= record)
            g[start].push_back(new_edge);
    }

    printf("%d", all_paths(1, rocks_number, record));
    
    return 0;
}

// 7 11 42
// 1 3 7 11
// 3 1 7 13
// 1 2 3 3
// 1 4 13 1
// 6 1 14 8
// 4 6 1 7
// 2 4 1 13
// 2 6 4 20
// 3 5 2 5
// 5 6 6 4
// 6 7 5 20

// 2 2 3
// 1 2 3 5
// 1 2 1 9