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

int getDigit(long long value, int posFromRight)
{
    int digit = (value / power10(posFromRight)) % 10;
    return digit;
}

vector<Record> readDataset(const string &filename)
{
    vector<Record> a;
    ifstream inFile(filename.c_str());
    string line;

    while (getline(inFile, line))
    {
        if (line != "")
        {
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
    }

    return a;
}

string getSizeText(const string &filename, int n)
{
    string text = "";

    for (int i = 0; i < (int)filename.length(); i++)
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

void printArray(ofstream &out, const vector<Record> &a, const string &label)
{
    out << "[";

    for (int i = 0; i < (int)a.size(); i++)
    {
        out << a[i].key << "/" << a[i].word;

        if (i != (int)a.size() - 1)
        {
            out << ", ";
        }
    }

    out << "] " << label << "\n";
}

void countingSortByDigit(vector<Record> &a, int posFromRight)
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
        int d = getDigit(a[i].key, posFromRight);
        count[d]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int d = getDigit(a[i].key, posFromRight);
        output[count[d] - 1] = a[i];
        count[d]--;
    }

    for (int i = 0; i < n; i++)
    {
        a[i] = output[i];
    }
}

int main()
{
    string filename;
    int startRow;
    int endRow;

    cout << "Enter dataset filename: ";
    cin >> filename;

    cout << "Enter start row: ";
    cin >> startRow;

    cout << "Enter end row: ";
    cin >> endRow;

    vector<Record> all = readDataset(filename);

    if (startRow < 1)
    {
        startRow = 1;
    }

    if (endRow > (int)all.size())
    {
        endRow = all.size();
    }

    if (startRow > endRow)
    {
        cout << "Invalid row range." << endl;
        return 1;
    }

    vector<Record> a;

    for (int i = startRow - 1; i <= endRow - 1; i++)
    {
        a.push_back(all[i]);
    }

    string sizeText = getSizeText(filename, all.size());
    string outName = "dataset_" + sizeText + "_radix_sorted_step_" + to_string(startRow) + "_" + to_string(endRow) + ".txt";

    ofstream out(outName.c_str());

    printArray(out, a, "original");

    long long maxKey = 0;
    for (int i = 0; i < (int)a.size(); i++)
    {
        if (a[i].key > maxKey)
        {
            maxKey = a[i].key;
        }
    }

    // Dynamic Digit Scan: Instead of hardcoding 10 passes like the main file,
    // we calculate the maximum number of digits present within this specific row range.
    // This stops us from running empty, redundant passes over smaller numbers.

    int maxDigits = 0;
    long long temp = maxKey;
    while (temp > 0)
    {
        maxDigits++;
        temp /= 10;
    }
    if (maxDigits == 0)
        maxDigits = 1;

    // Loop through each digit position, moving right-to-left (Least Significant Digit first).

    for (int p = 0; p < maxDigits; p++)
    {
        countingSortByDigit(a, p);

        // The label calculation 'maxDigits - p' converts the index
        // into an explicit tracking descriptor (e.g., d=10 down to d=1)
        // to directly match the formatting required in our report submission.

        int dLabel = maxDigits - p;
        printArray(out, a, "d=" + to_string(dLabel));
    }

    cout << "Step output written to " << outName << endl;

    return 0;
}