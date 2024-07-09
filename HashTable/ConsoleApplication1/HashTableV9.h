#ifndef HASHTABLEV9_H
#define HASHTABLEV9_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class HashTable
{
private:
    struct Entry
    {
        std::string key;
        int value;
        bool occupied;
        bool wasoccupied;

        Entry() : key(""), value(0), occupied(false), wasoccupied(false) {}
    };

    std::vector<Entry> table;
    int capacity;
    int size;
    int collisionCount;

    size_t hashFunction(const std::string& key) const
    {
        const size_t prime = 2654435769; // Простое число для умножения
        size_t hash = 0;
        for (char c : key)
        {
            hash = hash * prime + c;
        }
        return hash;
    }

    size_t probe(size_t hash, int i) const
    {
        return (hash + i * i) % capacity;
    }

public:
    HashTable(int capacity = 2000) : capacity(capacity), size(0), collisionCount(0)
    {
        table.resize(capacity);
    }

    bool insert(const std::string& key, int value)
    {
        size_t hash = hashFunction(key);
        for (int i = 0; i < capacity; ++i)
        {
            size_t idx = probe(hash, i);
            if (!table[idx].occupied)
            {
                table[idx].key = key;
                table[idx].value = value;
                table[idx].occupied = true;
                ++size;
                table[idx].wasoccupied = true;
                return true;
            }
            //else if (table[idx].key == key)
            //{
            //    return false; // Дубликат ключа
            //}
            else
            {
                ++collisionCount;
            }
        }
        return false; // Таблица заполнена
    }

    bool update(const std::string& key, int value)
    {
        size_t hash = hashFunction(key);
        for (int i = 0; i < capacity; ++i)
        {
            size_t idx = probe(hash, i);
            if (table[idx].occupied && table[idx].key == key)
            {
                table[idx].value = value;
                return true;
            }
            else if (!table[idx].occupied)
            {
                return false;
            }
        }
        return false;
    }

    bool contains(const std::string& key) const
    {
        size_t hash = hashFunction(key);
        for (int i = 0; i < capacity; ++i)
        {
            size_t idx = probe(hash, i);
            if (table[idx].occupied && table[idx].key == key)
            {
                return true;
            }
            else if (!table[idx].wasoccupied)
            {
                return false;
            }
        }
        return false;
    }

    bool erase(const std::string& key)
    {
        size_t hash = hashFunction(key);
        for (int i = 0; i < capacity; ++i)
        {
            size_t idx = probe(hash, i);
            if (table[idx].occupied && table[idx].key == key)
            {
                table[idx].occupied = false;
                --size;
                return true;
            }
            else if (!table[idx].wasoccupied)
            {
                return false;
            }
        }
        return false;
    }

    int get(const std::string& key) const
    {
        size_t hash = hashFunction(key);
        for (int i = 0; i < capacity; ++i)
        {
            size_t idx = probe(hash, i);
            if (table[idx].occupied && table[idx].key == key)
            {
                return table[idx].value;
            }
            else if (!table[idx].occupied)
            {
                throw std::runtime_error("Ключ не найден");
            }
        }
        throw std::runtime_error("Ключ не найден");
    }

    void clear()
    {
        for (auto& entry : table)
        {
            entry.occupied = false;
        }
        size = 0;
        collisionCount = 0;
    }

    int getCollisionCount() const
    {
        return collisionCount;
    }

    int getSize() const
    {
        return size;
    }

    int getCapacity() const
    {
        return capacity;
    }

    void display() const
    {
        for (int i = 0; i < capacity; ++i)
        {
            if (table[i].occupied)
            {
                std::cout << "Индекс: " << i << ", Хеш: " << hashFunction(table[i].key)
                    << ", Ключ: " << table[i].key << ", Значение: " << table[i].value << std::endl;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const HashTable& ht)
    {
        for (int i = 0; i < ht.capacity; ++i)
        {
            if (ht.table[i].occupied)
            {
                os << "Индекс: " << i << ", Хеш: " << ht.hashFunction(ht.table[i].key)
                    << ", Ключ: " << ht.table[i].key << ", Значение: " << ht.table[i].value << std::endl;
            }
        }
        return os;
    }
};

#endif // HASHTABLEV9_H
