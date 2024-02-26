#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<string.h>
#include<cstring>
#include<queue>
#include<cmath>
#include"CCA.h"
#include<fstream>
#include<iomanip>
#include <thread>
#include <chrono>
#define ll long long
#define maxn 10000000
#define MTCSXS 0.1
#define maxjs 3
using namespace std;
int shichang = 5;
int COUNT;
struct dian {//白棋1;黑棋-1;
    int x, y; double value, gz1, gz2;
    dian(int x, int y, double value, double gz1, double gz2) :x(x), y(y), value(value), gz1(gz1), gz2(gz2) {}
};
struct cmp {
    bool operator()(dian u, dian v) { return u.value < v.value; }
};
struct cjd {
    Game now;
    int ALLOW_TYPE_NUM[2];//多少个可用行动
    int EXPANDED_NUM[2];
    vector<int>ALLOW_TYPE[2];//0是我们训练的AI，1是随机的
    vector<pair<int, double>>ALLOW_TYPE_HISTORY[2];
    int fa;
    int bh;
}CJD[100010];
int CJDCNT;

cjd xj(Game U, int father) {
    cjd tmp;
    tmp.now = U;
    tmp.ALLOW_TYPE[0] = U.Get_allowed_actions(0); tmp.ALLOW_TYPE_NUM[0] = tmp.ALLOW_TYPE[0].size(); tmp.EXPANDED_NUM[0] = 0;
    tmp.ALLOW_TYPE[1] = U.Get_allowed_actions(1); tmp.ALLOW_TYPE_NUM[1] = tmp.ALLOW_TYPE[1].size(); tmp.EXPANDED_NUM[1] = 0;
    for (int i = 0; i < U.num; i++) {
        tmp.ALLOW_TYPE_HISTORY[i].clear();
        for (int j = 0; j < tmp.ALLOW_TYPE_NUM[i]; j++) {
            tmp.ALLOW_TYPE_HISTORY[i].push_back(make_pair(0, 0));
        }
    }
    tmp.fa = father;
    CJD[++CJDCNT] = tmp; CJD[CJDCNT].bh = CJDCNT;
    return CJD[CJDCNT];
}
int renew(cjd* tmp) {
    if (tmp->now.end())return -1;
    for (int i = 0; i < maxjs; i++) {
        tmp->ALLOW_TYPE[i] = tmp->now.Get_allowed_actions(i); tmp->ALLOW_TYPE_NUM[i] = tmp->ALLOW_TYPE[i].size(); tmp->EXPANDED_NUM[i] = 0;
        tmp->now.now_action[i].type = tmp->ALLOW_TYPE[i][rand() % tmp->ALLOW_TYPE_NUM[i]];
    }
    return 0;
}
pair<int,double> EXPAND(cjd& root,int lunshu,int js) {
    int bestson = 0;
    if (root.ALLOW_TYPE_NUM[js] == 0)return make_pair(- 1, 0);
    int now_type;
    if (root.EXPANDED_NUM[js] <root.ALLOW_TYPE_NUM[js]) {
        now_type = root.ALLOW_TYPE[js][root.EXPANDED_NUM[js]];
        root.EXPANDED_NUM[js]++;
    }
    else {
        double maxUTB = -1000000; bool IFFIRST = true;
        double now_UTB;
        for (int i = 0; i < root.ALLOW_TYPE_NUM[js]; i++) {
            if (root.ALLOW_TYPE_HISTORY[js][i].first == 0)now_UTB = 10000000;
            else now_UTB = (root.ALLOW_TYPE_HISTORY[js][i].second / root.ALLOW_TYPE_HISTORY[js][i].first) + sqrt(MTCSXS * log(COUNT) / root.ALLOW_TYPE_HISTORY[js][i].first);
            if (now_UTB > maxUTB)bestson = i, maxUTB = now_UTB;
        }
        now_type = root.ALLOW_TYPE[js][bestson];
    }
    cjd tmpp = root;
    ////////!!!!!

    for (int i = 0; i <root.now.num; i++) {
        if (i == js)tmpp.now.now_action[i].type = now_type;
        else tmpp.now.now_action[i].type = tmpp.ALLOW_TYPE[i][rand() % tmpp.ALLOW_TYPE_NUM[i]];
    }

    while (lunshu) {
        lunshu--;
        tmpp.now.step();
        if (renew(&tmpp) == -1) {
            break;
        }
    }
    root.ALLOW_TYPE_HISTORY[js][bestson].first++;
    double ss= tmpp.now.get_value(js);
    root.ALLOW_TYPE_HISTORY[js][bestson].second += ss;
    //////!!!!!!
    return make_pair(now_type, ss);
}
int AI2(int bs,int js) {
    fill(CJD + 1, CJD + 100000, cjd{});
    CJDCNT = 0;
    COUNT = 0;
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    cjd Root = xj(Initial, 0);
    while ((end - start) / 1ms < shichang) {
        COUNT++;
        int lunshu = 10 + rand() % 5;
        int ttmm = EXPAND(Root,lunshu,js).second;
        end = std::chrono::system_clock::now();
    }
    printf("第%d步共耗时%dms,拓展%d次,平均用时%lfms,用了%d个CJD\n", bs, (end - start) / 1ms, COUNT, ((end - start) / 1ms) * 1.0 / COUNT, CJDCNT);
    int final_choice= EXPAND(Root, 0, js).first;
    return final_choice;
}
int main() {
    
    return 0;
}