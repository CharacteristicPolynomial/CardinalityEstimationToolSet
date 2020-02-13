#include <iostream>
#include "CETS.h"
#include "list.h"
using namespace std;

int main() {
    int m = 100;
    int n = 1e6;
    int k = 10000;
    vector<double> hr;
    vector<double> mr;

    MQCounter mq(m,2);
    for(int j=0; j<k; j++) {
        cout << j << endl;
        mq.init();
        mq.add(n);
        hr.push_back(mq.hll());
        mr.push_back(mq.mle_bs());
    }
    string hname = "hll"+to_string(n)+".list";
    string mname = "mle"+to_string(n)+".list";
    list_write(hr, hname.c_str());
    list_write(mr, mname.c_str());
    return 0;
}