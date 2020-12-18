#include <cstdio>
#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

bool is_member(int elem, vector<int> all)
{
   return find(all.begin(), all.end(), elem)!= all.end();   
}

struct edge
{
    int equipment, time, to; 
};


vector<edge> g[int(1e5)];
int equipment[int(1e5)];
int t[int(1e5)];


void all_paths_aux(int current_node, int goal_node, vector<int>& current_path, vector<int>& paths, int& record)
{
    current_path.push_back(current_node);

    if(current_node == goal_node )
    {
        paths.push_back(equipment[current_node]);
    }

    for (edge neib: g[current_node])
    {
        if(!is_member(neib.to, current_path))
        { 
            equipment[neib.to] = max(neib.equipment, equipment[current_node]);
            t[neib.to] = neib.time + t[current_node];
            if(t[neib.to]<=record)
                all_paths_aux(neib.to, goal_node, current_path, paths, record);
        }
    }

    current_path.pop_back();
}

vector<int> all_paths(int start, int end, int record)
{
    vector<int> current_path;
    vector<int> paths;
    equipment[start]=0;
    t[start]=0;
    all_paths_aux(start, end, current_path, paths, record);
    return paths;
}



int get_min(vector<int> v)
{
    if(v.empty())
        return -1;
    
    int min_el = v[0];
    for(int i=1; i<v.size(); ++i)
    {
        min_el = min(min_el, v[i]);
    }

    return min_el;
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
        g[start].push_back(new_edge);
    }

    printf("%d",get_min(all_paths(1, rocks_number, record)));
    
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