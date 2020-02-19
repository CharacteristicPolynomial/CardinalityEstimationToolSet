#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
#include "CETS.h"
using namespace std;

int main() {
    int m = 50;
    int n = 800000;
    int k = 500;
    
    MQCounter mq(m,2);
    for(m = 64; m < 200; m++) {
        mq.init(m);
        for(int i=0; i<m; i++) {
            mq.setxi(i, 14);
        }
        for(int i=m/2; i<m; i++) {
            mq.setxi(i, 17);
        }
        cout << m << endl;
        mq.mspe();
    }
    return 0;
}