#ifndef KCM_REBUILD_TYPE_H
#define KCM_REBUILD_TYPE_H

#include <bitset>

//����querySize ������������
typedef unsigned int unsigned_key;
typedef int VertexID ;
typedef int VertexDegree;
typedef int VertexLabel;



//struct VectorHash {
//    size_t operator()(const std::vector<int>& v) const {
//        std::hash<int> hasher;
//        size_t seed = 0;
//        for (int i : v) {
//            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
//        }
//        return seed;
//    }
//};

struct ComparePairFirst {
    bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        // �Եڶ���Ԫ�ؽ�������
        return p1.first < p2.first;
    }
};

struct CompareByBitCount {
    bool operator()(unsigned_key a,unsigned_key b) const {
        // ����a��b�е�1��λ��
        int countA = std::bitset<sizeof(unsigned_key) * 8>(a).count();
        int countB = std::bitset<sizeof(unsigned_key) * 8>(b).count();

        // �Ƚ�Ԫ���е�1��λ��
        if (countA != countB) {
            return countA < countB;
        } else {
            return a < b;
        }
    }
};

#endif //KCM_REBUILD_TYPE_H
