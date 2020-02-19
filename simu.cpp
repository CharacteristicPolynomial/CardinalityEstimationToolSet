#include <iostream>
#include "CETS.h"
#include "list.h"
using namespace std;

int main() {
    int m = 128;
    int n = 800000;
    int k = 50000;
    vector<double> hr;
    vector<double> mser;
    vector<double> msewr;

    MQCounter mq(m,2);
    for(int j=0; j<k; j++) {
        cout << j << endl;
        mq.init();
        mq.add(n);
        hr.push_back(mq.hll());
        mser.push_back(mq.mspe());
        msewr.push_back(mq.mspew());
        cout << "hll: " << hr.back() << " | " << "mse: " << mser.back() << " | " << "msew: " << msewr.back() << endl;
    }
    string hname = "hll"+to_string(n)+".list";
    string mname = "mse"+to_string(n)+".list";
    string mwname = "msew"+to_string(n)+".list";
    list_write(hr, hname.c_str());
    list_write(mser, mname.c_str());
    list_write(msewr, mwname.c_str());
    return 0;
}