#include <iostream>
#include <vector>

using namespace std;

#define MAXSIZE 20

static int cumulativeSum[MAXSIZE];
static vector<int> maxNumbers;
static int maxSumResult;

// returns C(n,k)
int getCombinationCount(int n, int k)
{
    if(n < k)
        return 0;

    int t = min(n-k, k);
    int c = 1;

    for(int i = 0; i < t; ++i)
    {
        c *= (n-i);
        c /= (i + 1);
    }
    return c;
}

// sets next k combination in comb
void setNextCombination(int comb[], int k, int n)
{
    int i = k - 1;
    while(i > 0 && comb[i] == n - k + i)
    {
        --i;
    }
    ++comb[i];

    for(i = i + 1; i < k; ++i)
    {
        comb[i] = comb[i-1] + 1;
    }
}

// When a new number is calculated as if it satisfies the sum of every k number 
// with the vals vector elements, every k-1 number combination + newNumber has to be
// false in the sumCheck array. If not, then there is a k combination that sums to that
// number in vals already, so newNumber cannot be added to vals array
bool* checkPairSums( vector<int> vals, bool sumCheck[], int newNumber, int max, int k ) {

    bool localSumCheck[max * k];

    for(int i = 0; i < max * k; ++i)
        localSumCheck[i] = sumCheck[i];

    int comb[k - 1];
    for(int i = 0; i < k - 1; ++i)
        comb[i] = i;

    for(int i = 0; i < getCombinationCount(vals.size(), k - 1); ++i)
    {
        int cSum = 0;
        for(int j = 0; j < k - 1; ++j)
            cSum += vals[comb[j]];

        if(localSumCheck[cSum + newNumber] == true)
            return NULL;

        localSumCheck[cSum + newNumber] = true;
        setNextCombination(comb, k - 1, vals.size());
    }
    for(int i = 0; i < max * k; ++i)
        sumCheck[i] = localSumCheck[i];
    return sumCheck;
}

// every sum of k elements are set to true in newCheckSum array
void setPairSums( vector<int> values, bool newCheckSum[], int max, int k ) {
    for (int i = 0; i < max * k; i++)
        newCheckSum[i] = false;

    int comb[k];
    for(int i = 0; i < k; ++i)
        comb[i] = i;

    for(int i = 0; i < getCombinationCount(values.size(), k); ++i)
    {
        int cSum = 0;
        for(int j = 0; j < k; ++j)
            cSum += values[comb[j]];

        newCheckSum[cSum] = true;
        setNextCombination(comb, k, values.size());
    }
}

// Find initial values that satisfies distinct k sum rule
// Then in findMaxResult, this initial values will be modified to
// find larger sum of elements which also satisfies the rule
vector<int> getInitialValues(int max, int k)
{
    bool sumCheck[max * k];
    for (int i = 0; i < MAXSIZE; ++i)
        cumulativeSum[i] = 0;

    for (int i = 0; i < max * k; ++i)
        sumCheck[i] = false;

    vector<int> initialValues;

    int s = 0;

    for (int i = max; i > 0; --i) {

        if (initialValues.empty()) {
            initialValues.push_back( i );
            cumulativeSum[s++] = i;
        } else {
            bool* newSumCheck = checkPairSums( initialValues, sumCheck, i, max, k );
            if (newSumCheck != NULL) {
                initialValues.push_back( i );
                cumulativeSum[s] = cumulativeSum[s - 1] + i;
                s++;
            }
        }
    }
    return initialValues;
}

// Recursive algorithm
// Main idea is implemented through this function
void findMaxResult( vector<int> vals, int max, int k, int index ) {
    if (index == 0 || vals[index] == 1)
        return;

    vector<int> values;
    for (int i = 0; i < index; ++i) {
            values.push_back(vals[i]);
    }

    bool valuesCheckSum[max * k];
    setPairSums( values, valuesCheckSum, max, k );

    for (int num = vals[index] - 1; num > 0; --num) {
        bool * newSumCheck = checkPairSums( values, valuesCheckSum, num, max, k );
        if (newSumCheck != NULL) {
            values.push_back( num );
            cumulativeSum[values.size() - 1] = cumulativeSum[values.size() - 2] + num;

            if (maxSumResult < cumulativeSum[values.size() - 1]) {
                maxSumResult = cumulativeSum[values.size() - 1];
                maxNumbers = values;
            }

        }
    }
    for (int i = values.size() - 1; i > index - 1; --i)
        findMaxResult( values, max, k, i );
}

// First there elements are n, n-1 and n-2 so 
// instead of i > 0, i > 2 is written. 
void findResult( vector<int> vals, int max, int k ) {
    for (int i = vals.size() - 1; i > 2; --i) {
        findMaxResult( vals, max, k, i );
    }
}

int main()
{
    int k;
    cout << "Enter k value : " << endl;
    cin >> k;

    for (int i = 10; i < 75; i++) {

        vector<int> vals = getInitialValues( i, k );
        maxNumbers = vals;
        maxSumResult = cumulativeSum[vals.size() - 1];

        findResult( vals, i, k );

        cout << i << " | " << k << " | " << maxNumbers.size() << " | ";
        for (auto iter = maxNumbers.begin(); iter != maxNumbers.end(); iter++)
            cout << *iter << " ";

        cout << " ||| " << maxSumResult << endl;
    }

    cout << "End of program" << endl;
    return 0;
}
