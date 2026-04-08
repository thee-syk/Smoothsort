#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//this is the leonardo numbers and we used 46 since it can hold a big array in a tree
long long L[46];
void buildLeo() {
    L[0] = 1; L[1] = 1;
    for (int i = 2; i < 46; i++)
        L[i] = L[i-1] + L[i-2] + 1;
}
//fixes one tree's heap..,hence satisfying every parent to be greater than or equal to child
//it swaps until root is greater than child then stops
void sift(vector<int>& a, int root, int order) {
    while (order >= 2) {
        int right = root - 1;
        int left  = root - 1 - (int)L[order - 1];
        if (a[root] >= a[left] && a[root] >= a[right]) break;
        if (a[left] >= a[right]) {
            swap(a[root], a[left]);
            root = left; order -= 2;
        } else {
            swap(a[root], a[right]);
            root = right; order -= 1;
        }
    }
}
//fixes ordering across trees by swaping until each root is smaller than root in right
void trinkle(vector<int>& a, int root, int order,
             vector<int>& ordStack, int stackTop) {
    while (stackTop > 0) {
        int prevRoot = root - (int)L[order];
        if (a[prevRoot] <= a[root]) break;
        if (order >= 2) {
            int right = root - 1;
            int left  = root - 1 - (int)L[order - 1];
            if (a[prevRoot] < a[right] || a[prevRoot] < a[left]) break;
        }
        swap(a[prevRoot], a[root]);
        root = prevRoot;
        stackTop--;
        order = ordStack[stackTop];
    }
    sift(a, root, order);
}
//it tracks the order of each active tree from left to right
void smoothSort(vector<int>& a) {
    int n = (int)a.size();
    if (n <= 1) return;

    vector<int> orders;

    //  Builds
    for (int i = 0; i < n; i++) {
        int sz = (int)orders.size();
        if (sz >= 2 && orders[sz-2] == orders[sz-1] + 1) {
            orders.pop_back();
            orders.back() += 1;
        } else if (sz >= 1 && orders.back() == 1) {
            orders.push_back(0);
        } else {
            orders.push_back(1);
        }
        int top = (int)orders.size() - 1;
        trinkle(a, i, orders[top], orders, top);
    }

    //  Extracts
    for (int i = n - 1; i >= 0; i--) {
        int ord = orders.back();
        orders.pop_back();
        if (ord >= 2) {
            int rightRoot = i - 1;
            int leftRoot  = i - 1 - (int)L[ord - 1];
            orders.push_back(ord - 2);
            orders.push_back(ord - 1);
            int leftTop  = (int)orders.size() - 2;
            int rightTop = (int)orders.size() - 1;
            trinkle(a, leftRoot,  ord - 2, orders, leftTop);
            trinkle(a, rightRoot, ord - 1, orders, rightTop);
        }
    }
}
//this displays the array
void printArray(const vector<int>& a) {
    for (int i = 0; i < (int)a.size(); i++) {
        cout << a[i];
        if (i < (int)a.size() - 1) cout << "  ";
    }
    cout << "\n";
}
//read int-reads all user input to ensure user enters correct data type..,and it catches the error if wrong data type is iputed

bool readInt(int& val) {
    cin >> val;
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); return false; }
    return true;
}
//
int main() {
    buildLeo();
    const int LIMIT = 50;//set max number in input
    //checks condition using while loop to ensure limit is not passed
    int n = 0;
    while (true) {
        cout << "\nHow many numbers do you want to sort? ";
        if (readInt(n) && n >= 1 && n <=50) break;
        cout <<"Enter a number between 1 and "<<LIMIT<<endl;
 
    }
    //  Enter the elements
    vector<int> arr(n);
    cout << "Enter " << n << " integer(s), one per line:\n";
    for (int i = 0; i < n; i++) {
        while (true) {
            cout << "  [" << (i+1) << "] ";
            if (readInt(arr[i])) break;
            cout << "  [!] Invalid. Please enter an integer.\n";
        }
    }
    //Shows original inputs
    cout << "\n";
    cout << "Original array:\n  ";
    printArray(arr);
    //Sorts the array
    smoothSort(arr);
    //Shows the sorted iput
    cout << "\nSorted array (ascending):\n  ";
    printArray(arr);
        return 0;
}