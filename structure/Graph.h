//
// Created by DELL on 2024/1/3.
//

#ifndef KCM_GRAPH_H
#define KCM_GRAPH_H
#include <vector>
#include <unordered_set>
#include <set>
#include <queue>
#include<iomanip>

using namespace std;

extern int cutStep; //几步分割
extern vector<vector<int>> midNodeNum; //每一部连接点的个数
extern vector<vector<int>> midNode; //连接点
extern vector<vector<int>> singNodeArray; //无连接点节点数组

class Graph {
public:
    int id;
    vector<int> q_h_node;
    vector<int> q_h_label;
    vector<int> q_h_adj;
    vector<int> q_h_du;
    vector<int> q_h_adj_chai;
    int maxLevelId = -1;
    int minLevelId = -1;

    vector<int> del_edge;
    vector<int> split_node;
    vector<int> originalId;

    Graph *father;
    Graph *leftChild;
    Graph *rightChild;

    bool ReadInFile(const string &FileName);
    void print();
    bool calcLevelId();
    bool division(int count);
    void fuzhi(vector<int>& singleNodeNum, vector<int>& singleNode);

};

void GuangDu(vector<int>& q_h_level, vector<int>& q_h_node, vector<int>& q_h_adj, int level, int vId);

#endif //KCM_GRAPH_H
