#include <iostream>
#include "structure/Graph.h"
#include "alg/alg.h"

using namespace std;

int cutStep; //�����ָ�
vector<vector<int>> midNodeNum; //ÿһ�����ӵ�ĸ���
vector<vector<int>> midNode; //���ӵ�
vector<vector<int>> singNodeArray; //�����ӵ�ڵ�����

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
