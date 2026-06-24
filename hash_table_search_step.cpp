// *********************************************************
// Program: hash_table_search_step.cpp
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

    void searchStep(long long target, ofstream& out) const {
        int index = hashFunction(target);
        Node* current = table[index];

        out << "target = " << target << "\n";
        out << "hash index = " << target << " % " << tableSize << " = " << index << "\n";
        out << "search path: ";

        bool first = true;

        while (current != NULL) {
            if (first == false) {
                out << " -> ";
            }

            out << current->data.key << "/" << current->data.word;
            first = false;

            if (current->data.key == target) {
                out << "\n";
                out << target << " = " << current->data.key << "/" << current->data.word << "\n";
                return;
            }

            current = current->next;
        }

        if (first == true) {
            out << "empty bucket";
        }

        out << "\n";
        out << "-1 != " << target << "\n";
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
    long long target;

    cout << "Enter dataset filename: ";
    cin >> filename;

    cout << "Enter target integer: ";
    cin >> target;

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

    string sizeText = getSizeText(filename, n);
    string outName = "dataset_" + sizeText + "_hash_table_search_step_" + to_string(target) + ".txt";

    ofstream out(outName.c_str());

    ht.searchStep(target, out);

    cout << "Step output written to " << outName << endl;

    return 0;
}
