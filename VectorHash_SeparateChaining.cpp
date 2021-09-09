//
// Created by jcasiano on 4/7/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

template <class T>
struct Hash {
private:
    int mod;

public:
    Hash() = default;

    Hash(int m): mod(m) {} //dividendo

    int operator()(T x) {
        return (T) x % mod;
    }
};

template <class Key, int N>
struct HashTable {
private:
    Hash<Key> hash;
    array<vector<Key>, N> list;

public:
    HashTable(): hash(N) {};

    void insert(Key k) {
        int hk = hash(k);

        auto it = std::find(list[hk].begin(), list[hk].end(), k);
        if (it == list[hk].end())
            list[hk].push_back(k);
    }

    void erase(Key k) {
        int hk = hash(k);

        auto it = std::find(list[hk].begin(), list[hk].end(), k);
        if (it != list[hk].end())
            list[hk].erase(it);
    }

    bool find(Key k) {
        int hk = hash(k);

        auto it = std::find(list[hk].begin(), list[hk].end(), k);
        return it != list[hk].end();
    }
};

int main() {
    HashTable<long long, 10000> htable;

    htable.insert(10);
    htable.insert(1111);
    htable.insert(1341234351532);

    cout << htable.find(10) << endl;
    cout << htable.find(1111) << endl;
    cout << htable.find(1341234351532) << endl;
    cout << htable.find(1341534351532) << endl;

    return 0;
}
