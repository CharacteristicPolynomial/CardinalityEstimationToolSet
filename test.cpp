#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
#include "CETS.h"
using namespace std;

int main() {
    int m = 1000;
    MQCounter mq(m,2);
    for(int j=0; j<1; j++) {
        mq.init();
        mq.add(1e8);
        for(int i=0; i<m; i++) {
            // cout << mq.x[i] << "\t";
        }
        cout << mq.mle_bs() << " | hll: " << mq.hll();
        cout << endl;
    }
    return 0;
}