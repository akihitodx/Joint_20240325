//
// Created by DELL on 2024/1/3.
//

#include <string>
#include <iostream>
#include <fstream>
#include "Graph.h"

bool Graph:: ReadInFile(const string &FileName) {
    char ve;
    int vNum, eNum;
    int n1, n2, n3;
    //���ļ���ȡͼ
    ifstream infile;
    cout << "��ȡ�ļ���" << FileName << endl;
    infile.open(FileName, ios::in);
    if (!infile.is_open()) {
        cout << "�ļ���ʧ��" << endl;
        return false;
    }
    //��ȡ��ͱߵĸ���
    infile >> ve >> vNum >> eNum;
    q_h_node.resize(vNum, -1);
    q_h_label.resize(vNum, -1);
    q_h_du.resize(vNum, -1);
    originalId.resize(vNum, -1);
    int adjNumber = 0;
    int minDu = vNum;
    //int minDuV = 0;
    //��ȡ��
    for (int i = 0; i < vNum; i++) {
        infile >> ve >> n1 >> n2 >> n3;
        originalId[i] = i;
        q_h_node[n1] = adjNumber;
        q_h_label[n1] = n2;
        q_h_du[n1] = n3;
        adjNumber += n3;
        if (minDu > n3) {
            minDu = n3;
            //minDuV = n1;
        }

    }
    //��ȡ��
    q_h_adj.resize(adjNumber, -1);
    for (int i = 0; i < eNum; i++) {
        infile >> ve >> n1 >> n2 >> n3;
        int index = q_h_node[n1];
        while (q_h_adj[index] != -1) {
            index++;
        }
        q_h_adj[index] = n2;

        index = q_h_node[n2];
        while (q_h_adj[index] != -1) {
            index++;
        }
        q_h_adj[index] = n1;
    }

    cout << "��ȡ���" << endl;
    print();

    cutStep = 0;
    midNode = vector<vector<int>>(q_h_label.size(), vector<int>());
    midNodeNum = vector<vector<int>>(q_h_label.size(), vector<int>());
    singNodeArray = vector<vector<int>>(q_h_label.size(), vector<int>());
    return true;
}

void Graph::print() {
    cout << "=============================================" << endl;
    cout << setw(12) << "�ڵ����飺";

    for (int i = 0; i < q_h_node.size(); i++)
        cout << setw(3) << q_h_node[i];
    cout << endl;
    cout << setw(12) << "��ǩ���飺";
    for (int i = 0; i < q_h_label.size(); i++)
        cout << setw(3) << q_h_label[i];
    cout << endl;
    cout << setw(12) << "ԭʼID���飺";
    for (int i = 0; i < originalId.size(); i++)
        cout << setw(3) << originalId[i];
    cout << endl;
    cout << setw(10) << "�ڵ�����飺";
    for (int i = 0; i < q_h_du.size(); i++)
        cout << setw(3) << q_h_du[i];
    cout << endl;
    cout << setw(10) << "�ٽӵ����飺";
    for (int i = 0; i < q_h_adj.size(); i++)
        cout << setw(3) << q_h_adj[i];
    cout << endl;
    cout << setw(12) << "�ָ����飺";
    for (int i = 0; i < q_h_adj_chai.size(); i++)
        cout << setw(3) << q_h_adj_chai[i];
    cout << endl;
    cout << setw(12) << "�ָ�㣺";
    for (int i = 0; i < split_node.size(); i++)
        cout << setw(3) << split_node[i];
    cout << endl;
    cout << "=============================================" << endl;
}

bool Graph::calcLevelId() {
    //�ҵ�����С�Ľڵ�
    int minDu = q_h_node.size();
    for (int i = 0; i < q_h_node.size(); i++) {
        if (minDu > q_h_du[i]) {
            minDu = q_h_du[i];
            minLevelId = i;
        }
    }
    vector<int> q_h_level(q_h_node.size(), -1);
    q_h_level[minLevelId] = 0;
    //���ڵ�ּ�
    GuangDu(q_h_level, q_h_node, q_h_adj, 1, minLevelId);
    cout << "�������level��";
    int max = 0;
    for (int i = 0; i <= q_h_level.size() - 1; i++) {
        cout << q_h_level[i] << ",";
        if (max < q_h_level[i]) {
            max = q_h_level[i];
            maxLevelId = i;
        }
    }
    cout << endl;
    cout << "����С�ڵ���Զ�ڵ㣺" << maxLevelId << endl;
    return true;
}

bool Graph::division(int count) {
    cout << "��ʼ�ָ�" << endl;
    print();


    q_h_adj_chai.resize(q_h_adj.size(), -1);
    queue<int> leftQueue;
    queue<int> rightQueue;
    //���Ҷ��з���Ԫ��
    leftQueue.push(maxLevelId);
    rightQueue.push(minLevelId);
    while (!(leftQueue.empty() && rightQueue.empty())) {
        int checkV = -1;
        int searchV = -1;
        while (!leftQueue.empty() && checkV == -1) {
            //��left����ȡ����һ��
            searchV = leftQueue.front();
            //�ж���û�п�ȡ��,����ѡȡһ����
            for (int i = q_h_node[searchV]; i < q_h_node[searchV] + q_h_du[searchV]; i++) {
                if (q_h_adj_chai[i] == -1) {
                    //�ҵ���ȡ�㣬����checkVΪѡ�е�id����this_chai�����λ������Ϊ��ǰ���time
                    checkV = q_h_adj[i];
                    leftQueue.push(checkV);
                    q_h_adj_chai[i] = 0;
                    break;
                }
            }
            //û�п�ȡ��,���е���
            if (checkV == -1) {
                leftQueue.pop();
            }
        }
        //�ҵ���һ����
        if (checkV != -1 && searchV != -1) {
            for (int i = q_h_node[checkV]; i < q_h_node[checkV] + q_h_du[checkV]; i++) {
                if (q_h_adj[i] == searchV) {
                    q_h_adj_chai[i] = 0;
                    break;
                }
            }
        }
        checkV = -1;
        searchV = -1;
        while (!rightQueue.empty() && checkV == -1) {
            //��left����ȡ����һ��
            searchV = rightQueue.front();
            //�ж���û�п�ȡ��,����ѡȡһ����
            for (int i = q_h_node[searchV]; i < q_h_node[searchV] + q_h_du[searchV]; i++) {
                if (q_h_adj_chai[i] == -1) {
                    //�ҵ���ȡ�㣬����checkVΪѡ�е�id����this_chai�����λ������Ϊ��ǰ���time
                    checkV = q_h_adj[i];
                    rightQueue.push(checkV);
                    q_h_adj_chai[i] = 1;
                    break;
                }
            }
            //û�п�ȡ��,���е���
            if (checkV == -1) {
                rightQueue.pop();
            }
        }
        //�ҵ���һ����
        if (checkV != -1 && searchV != -1) {
            for (int i = q_h_node[checkV]; i < q_h_node[checkV] + q_h_du[checkV]; i++) {
                if (q_h_adj[i] == searchV) {
                    q_h_adj_chai[i] = 1;
                    break;
                }
            }
        }
    }
    //ɨ��ָ��

    for (int i = 0; i < q_h_node.size(); i++) {
        for (int j = q_h_node[i]; j < q_h_node[i] + q_h_du[i] - 1; j++) {
            if (q_h_adj_chai[j] != q_h_adj_chai[j + 1]) {
                split_node.push_back(originalId[i]);
                midNode[count].emplace_back(originalId[i]);
                break;
            }
        }
    }
    midNodeNum[count].emplace_back(split_node.size());

    cout << "�ָ����" << endl;
    print();

    vector<int> leftQMap;//ƫ��������
    vector<int> rightQMap;
    vector<int> leftLabelMap;//��ǩ����
    vector<int> rightLabelMap;
    vector<int> leftAdjMap;//�ٽӵ�����
    vector<int> rightAdjMap;

    vector<int> leftOldQMap;
    vector<int> rightOldQMap;
    vector<int> leftOldQMapOri;
    vector<int> rightOldQMapOri;
    vector<int> leftDuMap;//��һ����id
    vector<int> rightDuMap;
    //������������GSI
    for (int i = 0; i < q_h_node.size(); i++) {
        bool isLeftPush = false;
        bool isRightPush = false;
        int thisLeftQ = leftAdjMap.size();
        int thisRightQ = rightAdjMap.size();
        for (int j = q_h_node[i]; j < q_h_node[i] + q_h_du[i]; j++) {
            if (q_h_adj_chai[j] == 0) {
                leftAdjMap.push_back(q_h_adj[j]);
                isLeftPush = true;
            }
            if (q_h_adj_chai[j] == 1) {
                rightAdjMap.push_back(q_h_adj[j]);
                isRightPush = true;
            }
        }
        if (isLeftPush) {
            leftQMap.push_back(thisLeftQ);
            leftOldQMap.push_back(i);
            leftOldQMapOri.push_back(originalId[i]);
            leftLabelMap.push_back(q_h_label[i]);
        }
        if (isRightPush) {
            rightQMap.push_back(thisRightQ);
            rightOldQMap.push_back(i);
            rightOldQMapOri.push_back(originalId[i]);
            rightLabelMap.push_back(q_h_label[i]);
        }
    }
    //�ڽӵ�idתΪ��ͼid
    for (int i = 0; i < leftAdjMap.size(); i++) {
        for (int j = 0; j < leftOldQMap.size(); j++) {
            if (leftAdjMap[i] == leftOldQMap[j]) {
                leftAdjMap[i] = j;
                break;
            }
        }
    }
    for (int i = 0; i < rightAdjMap.size(); i++) {
        for (int j = 0; j < rightOldQMap.size(); j++) {
            if (rightAdjMap[i] == rightOldQMap[j]) {
                rightAdjMap[i] = j;
                break;
            }
        }
    }
    //������ͼ�Ķ�����
    for (int i = 0; i < leftQMap.size(); i++) {
        if (i < leftQMap.size() - 1) {
            leftDuMap.push_back(leftQMap[i + 1] - leftQMap[i]);
        }
        else {
            leftDuMap.push_back(leftAdjMap.size() - leftQMap[i]);
        }
    }
    for (int i = 0; i < rightQMap.size(); i++) {
        if (i < rightQMap.size() - 1) {
            rightDuMap.push_back(rightQMap[i + 1] - rightQMap[i]);
        }
        else {
            rightDuMap.push_back(rightAdjMap.size() - rightQMap[i]);
        }
    }

    //���������ָ����ͼ������
    Graph left = Graph();
    Graph right = Graph();
    left.q_h_node.assign(leftQMap.begin(), leftQMap.end());
    left.q_h_label.assign(leftLabelMap.begin(), leftLabelMap.end());
    left.q_h_du.assign(leftDuMap.begin(), leftDuMap.end());
    left.q_h_adj.assign(leftAdjMap.begin(), leftAdjMap.end());
    left.originalId.assign(leftOldQMapOri.begin(), leftOldQMapOri.end());
    this->leftChild = &left;
    left.father = this;

    right.q_h_node.assign(rightQMap.begin(), rightQMap.end());
    right.q_h_label.assign(rightLabelMap.begin(), rightLabelMap.end());
    right.q_h_du.assign(rightDuMap.begin(), rightDuMap.end());
    right.q_h_adj.assign(rightAdjMap.begin(), rightAdjMap.end());
    right.originalId.assign(rightOldQMapOri.begin(), rightOldQMapOri.end());
    this->rightChild = &right;
    right.father = this;
    cout << "������" << endl;
    cout << "����ͼ" << endl;
    left.print();
    cout << "����ͼ" << endl;
    right.print();
    //�����ֺ����ͼ�ڵ�ĸ�������2�Ļ����ݹ������һ�ηָ�
    if (left.q_h_node.size() > 2) {
        left.calcLevelId();
        left.division(count + 1);
    }
    else {
        for (int k = 0; k < left.originalId.size(); ++k) {
            singNodeArray[count].emplace_back(left.originalId[k]);
        }
        midNode[count + 1].push_back(-1);
    }
    if (right.q_h_node.size() > 2) {
        right.calcLevelId();
        right.division(count + 1);
    }
    else {
        for (int k = 0; k < right.originalId.size(); ++k) {
            singNodeArray[count].emplace_back(right.originalId[k]);
        }
        midNode[count + 1].push_back(-1);
    }
    if (cutStep < count) {
        cutStep = count;
    }
    return true;

}

void Graph::fuzhi(vector<int>& singleNodeNum, vector<int>& singleNode) {
    cout << "CutStep:" << cutStep << endl;
    midNode.resize(cutStep + 1);
    midNodeNum.resize(cutStep + 1);
    singNodeArray.resize(cutStep + 1);
    cout << "midNode:" << endl;
    for (int i = 0; i <= cutStep; ++i) {
        for (int j = 0; j < midNode[i].size(); ++j) {
            cout << midNode[i][j] << " ";
        }
        cout << endl;
    }
    cout << "midNodeNum:" << endl;
    for (int i = 0; i <= cutStep; ++i) {
        for (int j = 0; j < midNodeNum[i].size(); ++j) {
            cout << midNodeNum[i][j] << " ";
        }
        cout << endl;
    }
    cout << "singNodeArray:" << endl;
    for (int i = 0; i <= cutStep; ++i) {
        for (int j = 0; j < singNodeArray[i].size(); ++j) {
            cout << singNodeArray[i][j] << " ";
        }
        cout << endl;
    }
    singleNodeNum.emplace_back(0);
    for (int i = cutStep; i >= 0; --i) {
        for (int j = 0; j < singNodeArray[i].size(); ++j) {
            singleNode.emplace_back(singNodeArray[i][j]);
        }
        if (singNodeArray[i].size() > 0) {
            singleNodeNum.emplace_back(singleNodeNum.back() + (singNodeArray[i].size()/2));
        }
    }
}

void GuangDu(vector<int>& q_h_level, vector<int>& q_h_node, vector<int>& q_h_adj, int level, int vId) {
    int next;
    if (vId < q_h_node.size() - 1) {
        next = q_h_node[vId + 1];
    }
    else {
        next = q_h_adj.size();
    }
    bool isAllNotFu1 = true;
    for (int i = q_h_node[vId]; i < next; i++) {
        if (q_h_level[q_h_adj[i]] == -1) {
            q_h_level[q_h_adj[i]] = level;
            isAllNotFu1 = false;
        }
    }
    if (isAllNotFu1) {
        return;
    }
    else {
        for (int i = q_h_node[vId]; i < next; i++) {
            GuangDu(q_h_level, q_h_node, q_h_adj, level + 1, q_h_adj[i]);
        }
    }
}