#include <iostream>
#include "CETS.h"
#include "list.h"
using namespace std;

int main() {
    vector<double> blist;
    vector<double> eblist;
    double n = 100;
    double l = 1+1/n;
    double r = 3;

    for(int j=0; j/n+l<r; j++) {
        double b = j/n+l;
        cout << b << endl;
        blist.push_back(b);
        eblist.push_back(entropy(b));
    }
    string bname = "b.list";
    string ebname = "eb.list";
    list_write(blist, bname.c_str());
    list_write(eblist, ebname.c_str());
    return 0;
}