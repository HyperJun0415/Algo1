// *********************************************************
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC3L
// Tutorial Class: TT9L
// Trimester: 2610
// Member_1: 242UC244PB | LEM JOE ERN | lem.joe.ern@student.mmu.edu.my | 0162237965
// Member_2: 251UC250J5 | LEE JUN YAN | lee.jun.yan@student.mmu.edu.my | 0128500415
// Member_3: 251UC25141 | SHAWN GOH XUN SHEN | shawn.goh.xun@student.mmu.edu.my | 0199906601
// Member_4: 242UC244KV | KOH HUI WEN | koh.hui.wen@student.mmu.edu.my | 0129817286
// *******************
// Task Distribution
// Member_1: Dataset Generator
// Member_2: Radix Sort
// Member_3: Heap Sort
// Member_4: Hash Table Search
// *******************

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;

struct Record
{
    long long key;
    string word;
};

long long power10(int p)
{
    long long ans = 1;

    for (int i = 0; i < p; i++)
    {
        ans = ans * 10;
    }

    return ans;
}

int getDigit(long long value, int pos)
{
    return (value / power10(pos)) % 10;
}

vector<Record> readDataset(const string &filename)
{
    vector<Record> a;
    ifstream inFile(filename.c_str());
    string line;

    while (getline(inFile, line))
    {
        if (line == "")
            continue;

        stringstream ss(line);
        string left, right;

        if (getline(ss, left, ',') && getline(ss, right))
        {
            Record r;
            r.key = stoll(left);
            r.word = right;
            a.push_back(r);
        }
    }

    return a;
}

string getSizeText(const string &filename, int n)
{
    string text = "";

    for (int i = 0; i < filename.length(); i++)
    {
        if (filename[i] >= '0' && filename[i] <= '9')
        {
            text = text + filename[i];
        }
    }

    if (text == "")
    {
        text = to_string(n);
    }

    return text;
}

void countingSortByDigit(vector<Record> &a, int pos)
{
    int n = a.size();
    vector<Record> output(n);
    int count[10];

    for (int i = 0; i < 10; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int d = getDigit(a[i].key, pos);
        count[d]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int d = getDigit(a[i].key, pos);
        output[count[d] - 1] = a[i];
        count[d]--;
    }

    for (int i = 0; i < n; i++)
    {
        a[i] = output[i];
    }
}

void radixSort(vector<Record> &a)
{
    for (int p = 0; p < 10; p++)
    {
        countingSortByDigit(a, p);
    }
}

int main()
{
    string filename;

    cout << "Enter dataset filename: ";
    cin >> filename;

    vector<Record> a = readDataset(filename);
    int n = a.size();

    if (n == 0)
    {
        cout << "No data loaded." << endl;
        return 1;
    }

    auto start = chrono::high_resolution_clock::now();
    radixSort(a);
    auto stop = chrono::high_resolution_clock::now();

    double seconds = chrono::duration<double>(stop - start).count();

    string sizeText = getSizeText(filename, n);
    string outName = "radix_sorted_dataset_" + sizeText + ".csv";

    ofstream outFile(outName.c_str());

    for (int i = 0; i < n; i++)
    {
        outFile << a[i].key << "," << a[i].word << "\n";
    }

    outFile << "Running time: " << fixed << setprecision(9) << seconds << " seconds\n";

    cout << fixed << setprecision(9);
    cout << "Radix sort running time: " << seconds << " seconds" << endl;
    cout << "Output written to " << outName << endl;

    return 0;
}
