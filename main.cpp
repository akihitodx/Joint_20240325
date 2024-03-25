#include <iostream>
#include "structure/Graph.h"
#include "alg/alg.h"

using namespace std;

int cutStep; //几步分割
vector<vector<int>> midNodeNum; //每一部连接点的个数
vector<vector<int>> midNode; //连接点
vector<vector<int>> singNodeArray; //无连接点节点数组

int main() {


    string query_path = "../test/query";
    string data_path = "../test/data";

    auto* query = new Graph();
    auto* data = new Graph();

    query->ReadInFile(query_path);
    data->ReadInFile(data_path);

    del_edge(*query);
    query->calcLevelId();
    query->division(0);
    vector<int> singleNodeNum;
    vector<int> h_singleNode;
    query->fuzhi(singleNodeNum, h_singleNode);


    return 0;

}
