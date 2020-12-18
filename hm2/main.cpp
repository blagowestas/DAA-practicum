#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool is_member(int elem, vector<int> all)
{
    for(auto x: all)
        if(x==elem)
        return true;

    return false;
}

struct edge
{
    int equipment, time, to; 
};


vector<edge> g[int(1e6)+5];
int used[int(1e6)+5];
int parrent[int(1e6)+5];
int equipment[int(1e6)+5];
int t[int(1e6)+5];


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

    int rocks_number, bridges_number, record;
    
    cin>> rocks_number >> bridges_number >> record;

    int start;
    edge new_edge;

    for(int i=0; i<bridges_number; ++i)
    {
        cin >> start >> new_edge.to >> new_edge.equipment >> new_edge.time;       
        g[start].push_back(new_edge);
    }

    cout << get_min(all_paths(1, rocks_number, record));
    
    return 0;

}