#include <iostream>
#include "alg.h"
#include "unordered_map"

void del_edge(Graph &graph){
    vector<unordered_set<VertexID>> new_q_h_adj(graph.q_h_node.size());
    unordered_set<VertexID> list;
    VertexID maxDegreeID = 0;
    for(int k = 0 ; k <graph.q_h_node.size(); ++k){
        for(int i = graph.q_h_node[k] ; i <graph.q_h_node[k] + graph.q_h_du[k]; ++i){
            new_q_h_adj[k].insert(graph.q_h_adj[i]);
        }
        list.insert(k);
        if(graph.q_h_du[k]>graph.q_h_du[maxDegreeID])
            maxDegreeID = k;
    }
    vector<VertexDegree> degree_list = graph.q_h_du;
    unordered_set<VertexID> path_node;
    unordered_set<VertexID> others;
    unordered_set<VertexID> choice;


    while(!list.empty()){
        path_node.insert(maxDegreeID);
        list.erase(maxDegreeID);
        VertexDegree new_max_degree = 0;
        unordered_set<VertexID> need_update;
        for(auto i: new_q_h_adj[maxDegreeID]){
            if(path_node.count(i) > 0){
                need_update.insert(i);
                continue;
            }
            --degree_list[i];
            if(degree_list[i] == 0){
                list.erase(i);
                choice.erase(i);
                others.insert(i);
                continue;
            }
            choice.insert(i);
        }
        while(need_update.size() > 1){
            VertexID maxD = *need_update.begin();
            for(auto i : need_update){
                if(degree_list[i] > degree_list[maxD]){
                    maxD  = i;
                }
            }
            graph.del_edge.push_back(maxDegreeID);
            --graph.q_h_du[maxDegreeID];
            graph.del_edge.push_back(maxD);
            --graph.q_h_du[maxD];
            new_q_h_adj[maxD].erase(maxDegreeID);
            new_q_h_adj[maxDegreeID].erase(maxD);
            --degree_list[maxD];
            --degree_list[maxDegreeID];
            need_update.erase(maxD);
        }
        for(auto i : choice){
            if(degree_list[i] > new_max_degree){
                new_max_degree = degree_list[i];
                maxDegreeID = i;
            }
        }
        choice.erase(maxDegreeID);
    }
    unordered_map<VertexID,VertexDegree> path_other;
    for(auto i : path_node){
        path_other[i] = 0;
        for(auto j : new_q_h_adj[i]){
            if(others.count(j) > 0 ) ++path_other[i];
        }
    }
    for(auto i: others){
        priority_queue<pair<VertexDegree,VertexID>,vector<pair<int, int>>,ComparePairFirst> qqq;
        for(auto p : new_q_h_adj[i]){
            qqq.emplace(path_other[p],p);
        }

        while(qqq.size()>1){
            auto max = qqq.top();
            qqq.pop();
            --path_other[max.second];
            graph.del_edge.push_back(i);
            --graph.q_h_du[i];
            graph.del_edge.push_back(max.second);
            --graph.q_h_du[max.second];
            --degree_list[max.second];
            --degree_list[i];
            if(degree_list[max.second] == 0) list.erase(max.second);
            new_q_h_adj[max.second].erase(i);
            new_q_h_adj[i].erase(max.second);
        }

    }
    vector<int> update_adj;
    for(auto i : new_q_h_adj){
        update_adj.insert(update_adj.end(),i.begin(), i.end());
    }
    graph.q_h_adj = update_adj;
    int count  = 0;
    for(int i = 0; i < graph.q_h_node.size(); ++i){
        graph.q_h_node[i] = count;
        count += graph.q_h_du[i];
    }

    cout<<"=======去环完成========"<<endl;
    cout<<"路径节点: ";
    for(auto i : path_node){
        cout<<i <<" ";
    }
    cout<<endl;
    cout<<"删除边：";
    for(int i = 0 ; i < graph.del_edge.size(); i+=2){
        cout<<"("<<graph.del_edge[i]<<","<<graph.del_edge[i+1]<<") ";
    }
    cout<<endl;
    graph.print();
}