// *********************************************************
// Program: hash_table_search.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC3L
// Tutorial Class: TT9L
// Trimester: 2610
// Member_1: 242UC244PB | LEM JOE ERN | lem.joe.ern@student.mmu.edu.my | 0162237965
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: 242UC244KV | KOH HUI WEN | koh.hui.wen@student.mmu.edu.my | 0129817286
// *********************************************************
// Task Distribution
// Member_1: Dataset Generator
// Member_2: Radix Sort
// Member_3: Heap Sort
// Member_4: Hash Table Search
// *********************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;

struct Record {
    long long key;
    string word;
};

struct Node {
    Record data;
    Node* next;
};

class HashTable {
private:
    vector<Node*> table;
    int tableSize;

public:
    HashTable(int size) {
        tableSize = size;
        table.assign(tableSize, NULL);
    }

    ~HashTable() {
        clear();
    }

    int hashFunction(long long key) const {
        return key % tableSize;
    }

    void insert(Record r) {
        int index = hashFunction(r.key);

        Node* newNode = new Node;
        newNode->data = r;
        newNode->next = table[index];

        table[index] = newNode;
    }

    bool search(long long target, Record& found) const {
        int index = hashFunction(target);
        Node* current = table[index];

        while (current != NULL) {
            if (current->data.key == target) {
                found = current->data;
                return true;
            }

            current = current->next;
        }

        return false;
    }

    long long firstKeyInTable() const {
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != NULL) {
                return table[i]->data.key;
            }
        }

        return -1;
    }

    long long missingKeyForLongestChain() const {
        int longestIndex = 0;
        int longest = -1;

        for (int i = 0; i < tableSize; i++) {
            int count = 0;
            Node* current = table[i];

            while (current != NULL) {
                count++;
                current = current->next;
            }

            if (count > longest) {
                longest = count;
                longestIndex = i;
            }
        }

        long long target = 10000000000LL + longestIndex;

        while (target % tableSize != longestIndex) {
            target++;
        }

        return target;
    }

    void clear() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];

            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }

            table[i] = NULL;
        }
    }
};

vector<Record> readDataset(const string& filename) {
    vector<Record> a;
    ifstream inFile(filename.c_str());
    string line;

    while (getline(inFile, line)) {
        if (line != "") {
            stringstream ss(line);
            string left;
            string right;

            if (getline(ss, left, ',') && getline(ss, right)) {
                Record r;
                r.key = stoll(left);
                r.word = right;
                a.push_back(r);
            }
        }
    }

    return a;
}

string getSizeText(const string& filename, int n) {
    string text = "";

    for (int i = 0; i < (int)filename.length(); i++) {
        if (filename[i] >= '0' && filename[i] <= '9') {
            text = text + filename[i];
        }
    }

    if (text == "") {
        text = to_string(n);
    }

    return text;
}

int main() {
    string filename;

    cout << "Enter dataset filename: ";
    cin >> filename;

    vector<Record> records = readDataset(filename);
    int n = records.size();

    if (n == 0) {
        cout << "No data loaded." << endl;
        return 1;
    }

    int tableSize = n / 10 + 1;

    HashTable ht(tableSize);

    for (int i = 0; i < n; i++) {
        ht.insert(records[i]);
    }

    Record found;
    volatile long long check = 0;

    long long bestTarget = ht.firstKeyInTable();
    long long worstTarget = ht.missingKeyForLongestChain();

    auto startBest = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        if (ht.search(bestTarget, found)) {
            check = check + found.key;
        }
    }

    auto stopBest = chrono::high_resolution_clock::now();

    auto startAverage = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        if (ht.search(records[i].key, found)) {
            check = check + found.key;
        }
    }

    auto stopAverage = chrono::high_resolution_clock::now();

    auto startWorst = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        if (ht.search(worstTarget, found)) {
            check = check + found.key;
        }
    }

    auto stopWorst = chrono::high_resolution_clock::now();

    double bestTime = chrono::duration<double>(stopBest - startBest).count();
    double averageTime = chrono::duration<double>(stopAverage - startAverage).count();
    double worstTime = chrono::duration<double>(stopWorst - startWorst).count();

    string sizeText = getSizeText(filename, n);
    string outName = "hash_table_search_dataset_" + sizeText + ".txt";

    ofstream outFile(outName.c_str());

    outFile << fixed << setprecision(9);
    outFile << "Best case time: " << bestTime << " seconds\n";
    outFile << "Average case time: " << averageTime << " seconds\n";
    outFile << "Worst case time: " << worstTime << " seconds\n";
    outFile << "Number of searches per case: " << n << "\n";
    outFile << "Hash table size: " << tableSize << "\n";
    outFile << "Check value: " << check << "\n";

    cout << fixed << setprecision(9);
    cout << "Best case time: " << bestTime << " seconds" << endl;
    cout << "Average case time: " << averageTime << " seconds" << endl;
    cout << "Worst case time: " << worstTime << " seconds" << endl;
    cout << "Output written to " << outName << endl;

    return 0;
}
