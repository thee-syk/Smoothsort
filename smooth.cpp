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