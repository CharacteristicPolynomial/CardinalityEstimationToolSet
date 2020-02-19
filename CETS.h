#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;

double entropy(double q) {
    double k = 3;
    double n = 1e5;
    double ce = log(n)/log(q);
    int c = int(ce/k);
    double ent = 0;
    cout << c << " " << ce << endl;
    while (c < ce*k) {
        double qt = pow(q, c);
        double qt1 = qt * q;
        double p = exp(-n/qt1)-exp(-n/qt);
        if (p!=0)
            ent += -p*log2(p);
        // cout << qt << " " << qt1 << " p:" << p << " | ent: " << ent << endl;
        c ++;
    }
    return ent;
}

class MQCounter {
    public:
    MQCounter(int m_, double q_) {
        m = m_;
        q = q_;
        x.resize(m);
        unsigned d = chrono::high_resolution_clock::now().time_since_epoch().count();
        gen.seed(d);
        dist.param(geometric_distribution<int>::param_type(1.0-1.0/q));

        srand(time(NULL));
    }
    void add(long n) {
        for (long i=0; i<n; i++) {
            if(i*100 % n == 0) {
                // cout << (double)i*100.0/n << "\%" << endl;
            }
            int c = rand() % m;
            int temp = dist(gen);
            if (x[c] < temp)
                x[c] = temp;
        }
    }
    void init() {
        x.clear();
        x.resize(m);
    }
    void init(int m_) {
        m = m_;
        x.clear();
        x.resize(m);        
    }
    int m;
    double q;
    vector<int> x;
    geometric_distribution<int> dist;
    default_random_engine gen;

    void setxi(int i, int v) {
        x[i] = v;
    }

    // MSPE
    double mspe() {
        // hope it work
        double har = 0; // the part using harmonic sum as the statistic
        for(int j=0; j<m; j++) {
            har += pow(1.0/q, x[j]+1);
        }
        double temp = m;
        har = temp * (temp-1) *(q-1.0) / har / q;
        
        // the shape part
        // first construct a categarical random variable
        vector<double> ths(m); // so if a random number is between ths[m] and ths[m+1], then it is categray m
        vector<double> tempv(m);
        double xmax=0;
        for(int j=0; j<m; j++) {
            if(xmax < x[j]) 
                xmax = x[j];
        }
        double temp2 = 0;
        for(int j=0; j<m; j++) {
            temp2 += pow(q, xmax-x[j]);
            tempv[j] = temp2;
        }
        for(int j=0; j<m; j++) {
            ths[j] = tempv[j]/temp2*RAND_MAX;
        }

        int ne = 10000; // number of experiment
        int mb = 2*m; // number of summations
        double nomin =0;
        double denomin = 0;
        vector<double> ex(m); // x for experiment
        for(int i=0; i<ne; i++) {
            // cout << i << endl;
            double qk = 1;
            double mk1 = 1;
            double mk2 = 1;
            double phik = 1;
            fill(ex.begin(), ex.end(), 0);
            for (int k=0; k<mb; k++) {
                // qk for 1/q^k
                // mk1 for {m+k-1 \choose k}
                // mk2 for {m+k-2 \choose k}
                // phik for \phi(k;p)
                nomin += qk * mk1 * phik;
                denomin += qk * mk2 * phik;

                double draw = rand(); // draw your card!
                int di=-1;
                for(int j=0; j<m; j++) {
                    if(draw < ths[j]) {
                        di = j;
                        break;
                    }
                }
                if(di == -1) {
                    // cerr << "what?" << endl;
                    // exit(-1);
                    di = m-1;
                }

                // update
                qk *= (q-1.0) / q;
                mk1 *= (double)(m+k)/(k+1);
                mk2 *= (double)(m+k-1)/(k+1);
                phik *= (double)(ex[di]+1)/(ex[di]+2);
                ex[di] += 1;
            }
        }
        cout << nomin / denomin << endl;
        return har * nomin / denomin;
    }


    // MSPEw weighted version of min square error
    double mspew() {
        double har = 0; // the part using harmonic sum as the statistic
        for(int j=0; j<m; j++) {
            har += pow(1.0/q, x[j]+1);
        }
        double temp = m;
        har = temp * (temp-2) *(q-1.0)  / har / q;
        
        // the shape part
        // first construct a categarical random variable
        vector<double> ths(m); // so if a random number is between ths[m] and ths[m+1], then it is categray m
        vector<double> tempv(m);
        double xmax=0;
        for(int j=0; j<m; j++) {
            if(xmax < x[j]) 
                xmax = x[j];
        }
        double temp2 = 0;
        for(int j=0; j<m; j++) {
            temp2 += pow(q, xmax-x[j]);
            tempv[j] = temp2;
        }
        for(int j=0; j<m; j++) {
            ths[j] = tempv[j]/temp2*RAND_MAX;
        }

        int ne = 10000; // number of experiment
        int mb = 2*m; // number of summations
        double nomin =0;
        double denomin = 0;
        vector<double> ex(m); // x for experiment
        for(int i=0; i<ne; i++) {
            // cout << i << endl;
            double qk = 1;
            double mk2 = 1;
            double mk3 = 1;
            double phik = 1;
            fill(ex.begin(), ex.end(), 0);
            for (int k=0; k<mb; k++) {
                // qk for (q-1)^k/q^k
                // mk1 for {m+k-1 \choose k}
                // mk2 for {m+k-2 \choose k}
                // phik for \phi(k;p)
                nomin += qk * mk2 * phik;
                denomin += qk * mk3 * phik;

                double draw = rand(); // draw your card!
                int di=-1;
                for(int j=0; j<m; j++) {
                    if(draw < ths[j]) {
                        di = j;
                        break;
                    }
                }
                if(di == -1) {
                    // cerr << "what?" << endl;
                    // exit(-1);
                    di = m-1;
                }

                // update
                qk *= (q-1.0) / q;
                mk2 *= (double)(m+k-1)/(k+1);
                mk3 *= (double)(m+k-2)/(k+1);
                phik *= (double)(ex[di]+1)/(ex[di]+2);
                ex[di] += 1;
            }
        }
        cout << nomin / denomin << endl;
        return har * nomin / denomin;
    }
    // HyperLoglog
    double hll() {
        // only for q = 2 and m >= 128
        double am = 0.7213/(1+1.079/m);
        double temp = 0;
        for(int j=0; j<m; j++) {
            temp += pow(0.5, x[j]);
        }
        return 2*am * m * m / temp;
    }
    // MLE
    double mle_bs() {
        // binary search
        double rr = rough()/m; // initial guess, often being large
        double lr = 0;
        double mr;
        double ml1, rl1, ll1;
        double e = 0.1/m;
        rl1 = loglikelihood1(rr);
        ll1 = loglikelihood1(lr);
        while (rl1 > 0) {
            rr *= 2;
            rl1 = loglikelihood1(rr);
        }
        if (ll1 < 0) {
            cout << "initial left derivative smaller than 0" << endl;
            return lr;
        }
        while(true) {
            mr = (rr + lr)/2.0;
            ml1 = loglikelihood1(mr);
            if (ml1 <0) {
                rr = mr;
            } else {
                lr = mr;
            }
            // cout << lr << " " << ll1 << " | " << rr << " " << rl1 << endl; 
            if (rr - lr < e) 
                break;
            rl1 = loglikelihood1(rr);
            ll1 = loglikelihood1(lr);
        }
        return (rr + lr)/2.0 * m;
    }

    double loglikelihood1(double r) {
        double l1 = 0;
        for (int i=0; i<m; i++) {
            double qt = pow(q, x[i]);
            double qt1 = qt * q;
            l1 += -exp(-r/qt1)/qt1 +exp(-r/qt)/qt;
        }
        return l1;
    }

    double mle_newton() {
        // doesn't work
        double r = rough()/m; // initial guess
        vector<double> g(m); // ordinary
        vector<double> g1(m); // 1st derivative
        vector<double> g2(m); // 2nd derivative
        double l1;
        double l2;
        double diff;
        double e = 0.1;
        while(true) {
            fill(g.begin(), g.end(), 0);
            fill(g.begin(), g1.end(), 0);
            fill(g.begin(), g2.end(), 0);
            for (int i=0; i<m; i++) {
                double qt = pow(q, x[i]);
                double qt1 = qt * q;
                g[i] = exp(-r/qt1)-exp(-r/qt);
                g1[i] = -exp(-r/qt1)/qt1 +exp(-r/qt)/qt;
                g2[i] = exp(-r/qt1)/qt1/qt1 -exp(-r/qt)/qt/qt;
            }
            l1 = 0;
            l2 = 0;
            for(int i=0; i<m; i++) {
                l1 += g1[i]/g[i];
                l2 += (g2[i]*g[i]-g1[i]*g1[i])/g[i]/g[i];
            }
            diff = l1/l2;
            cout << l1 << " " << l2 << " " << diff << " " << r << endl;
            cout << diff << endl;
            r -= diff;
            if(diff < e)
                break;
        }
        return r * m;
    }

    double rough() {
        double s = 0;
        for(int i=0; i<m; i++) {
            s += pow(q, x[i]);
        }
        return s;
    }
};