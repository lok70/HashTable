#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include "HashTableV9.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    const int numElements = 100000;
    const int capacity    = 200000;
    std::vector<std::string> keys;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 10000);

    
    // ��������� ��������� ������
    for (int i = 0; i < numElements; ++i)
    {
        keys.push_back(std::to_string(distribution(generator)));
    }

    HashTable hashTable(capacity);
    std::unordered_set<std::string> unorderedSet;
    std::set<std::string> balancedTree;

    // ������������ �������
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys)
    {
        hashTable.insert(key, 1);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> hashTableInsertTime = end - start;
    std::cout << "����� ������� � HashTable: " << hashTableInsertTime.count() << "�\n";

    start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys)
    {
        unorderedSet.insert(key);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> unorderedSetInsertTime = end - start;
    std::cout << "����� ������� � Unordered Set: " << unorderedSetInsertTime.count() << "�\n";

    start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys)
    {
        balancedTree.insert(key);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> balancedTreeInsertTime = end - start;
    std::cout << "����� ������� � Balanced Tree: " << balancedTreeInsertTime.count() << "�\n";

    // ������������ ������
    start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys)
    {
        hashTable.contains(key);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> hashTableSearchTime = end - start;
    std::cout << "����� ������ � HashTable: " << hashTableSearchTime.count() << "�\n";

    start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys)
    {
        unorderedSet.find(key);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> unorderedSetSearchTime = end - start;
    std::cout << "����� ������ � Unordered Set: " << unorderedSetSearchTime.count() << "�\n";

    start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys)
    {
        balancedTree.find(key);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> balancedTreeSearchTime = end - start;
    std::cout << "����� ������ � Balanced Tree: " << balancedTreeSearchTime.count() << "�\n";

    // ������������ ����������
    start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys)
    {
        hashTable.update(key, 1);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> hashTableUpdateTime = end - start;
    std::cout << "����� ���������� � HashTable: " << hashTableUpdateTime.count() << "�\n";

    // ������������ ��������
    start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys)
    {
        hashTable.erase(key);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> hashTableEraseTime = end - start;
    std::cout << "����� �������� �� HashTable: " << hashTableEraseTime.count() << "�\n";

    // ����� ��������� ��������� ���-�������
    std::cout << hashTable;

    return 0;
}
