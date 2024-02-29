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
#include<vector>
#include<random>
#include<map>
#define ll long long
#define maxn 10000000
#define MTCSXS 0.1
#define type_num 20
#define maxjs 2
using namespace std;
int shichang = 100;
int COUNT;


//实验：1 补 2拔 3枪 4双枪 5刺 6砍 7挡 8双档 9重挡 
struct Action {
    int from, to, type;
};
map<int, int>Q{{1, 0}, { 2,0 }, { 3,3 }, { 4,3 }, { 5,1 }, { 6,2 }, { 7,0 }, { 8,0 }, { 9,0 }};
map<int, int>Qb{{1, 0}, { 2,0 }, { 3,1 }, { 4,2 }, { 5,0 }, { 6,0 }, { 7,0 }, { 8,0 }, { 9,0 }};
map<int, int>Qs{{1, 0}, { 2,0 }, { 3,0 }, { 4,0 }, { 5,1 }, { 6,2 }, { 7,0 }, { 8,0 }, { 9,0 }};
map<int, int>Qv{{1, 0}, { 2,0 }, { 3,1 }, { 4,1 }, { 5,1 }, { 6,1 }, { 7,0 }, { 8,0 }, { 9,0 }};
map<int, string>Name{{1, "补"}, { 2,"拔" }, { 3,"枪" }, { 4,"双枪" }, { 5,"刺" }, { 6,"砍" }, { 7, "挡" } ,{8, "双档"}, { 9,"重挡" }};
struct Game {
    int num=2;
    int bullet[2];
    int HP[2];
    int sword[2];
    int next_sword[2];
    Action now_action[2];
    vector<int> Get_allowed_actions(int u) {
        vector<int>A;
        A.push_back(1);
        A.push_back(2);
        if (bullet[u] > 0)A.push_back(3);
        if (bullet[u] > 1)A.push_back(4);
        if (next_sword[u] > 0)A.push_back(5);
        if (next_sword[u] > 1)A.push_back(6);
        A.push_back(7);
        A.push_back(8);
        A.push_back(9);
        return A;
    }
    void step(int real = 0) {
        int Atype = now_action[0].type, Btype = now_action[1].type;
        if (Q[Atype] > 0) {
            if (Q[Btype] > 0) {
                if (Q[Atype] > Q[Btype]) {
                    HP[1] -= Qv[Atype];

                }
            }
            else {
                if ((Btype == 7 && Atype == 3) || (Btype == 7 && Atype == 5)
                    || (Btype == 8 && Atype == 4) || (Btype == 9 && Atype == 6)) {
                    int a = 1;
                }
                else {
                    HP[1] -= Qv[Atype];
                }
            }
            bullet[0] -= Qb[Atype];
            next_sword[0] -= Qs[Atype];
        }
        else {
            
            if (Atype == 1) {
                bullet[0]++;
            }
            else if (Atype == 2) {
                sword[0]++;
            }
            next_sword[0] = sword[0];
        }
        swap(Atype, Btype);
        if (Q[Atype] > 0) {
            if (Q[Btype] > 0) {
                if (Q[Atype] > Q[Btype]) {
                    HP[0] -= Qv[Atype];

                }
            }
            else {
                if ((Btype == 7 && Atype == 3) || (Btype == 7 && Atype == 5)
                    || (Btype == 8 && Atype == 4) || (Btype == 9 && Atype == 6)) {
                    int a = 1;
                }
                else {
                    HP[0] -= Qv[Atype];
                }
            }
            bullet[1] -= Qb[Atype];
            next_sword[1] -= Qs[Atype];
        }
        else {

            if (Atype == 1) {
                bullet[1]++;
            }
            else if (Atype == 2) {
                sword[1]++;
            }
            next_sword[1] = sword[1];
        }
        if (real) {
            printf("A使用了%d(%s),B使用了%d(%s)\n", Btype,Name[Btype], Atype,Name[Atype] );
            printf("A:bullet:  %d  sword:%d/%d  ,HP:%d\n", bullet[0], next_sword[0], sword[0], HP[0]);
            printf("B:bullet:  %d  sword:%d/%d  ,HP:%d\n", bullet[1], next_sword[1], sword[1], HP[1]);
        }
        return;
    }
    void output(int js) {
        printf("A:bullet:  %d  sword:%d/%d  ,HP:%d\n", bullet[0], next_sword[0], sword[0], HP[0]);
        printf("B:bullet:  %d  sword:%d/%d  ,HP:%d\n", bullet[1], next_sword[1], sword[1], HP[1]);
        auto AA = Get_allowed_actions(js);
        int s = AA.size();
        cout << "Allowed action\n";
        cout << "1 补 2拔 3枪 4双枪 5刺 6砍 7挡 8双档 9重挡\n ";
        for (int i = 0; i < s; i++) {
            cout << AA[i] << " ";
        }
        cout << endl;
    }
    bool end() {
        return HP[0] <= 0 || HP[1] <= 0;
    }
    double tmp_value(int js,int type) {
        
        if (type == 1) {
            if (end()) {
                return HP[js] > 0 ? 1000 : -1000;
            }
            else  return (log(bullet[js]+1) * 3 + log(sword[js]+1) * 4 + log(next_sword[js]+1) + log(HP[js]+1) * 8);
        }
        else if (type == 2) {//阿绿
            return (sqrt(bullet[js]) * 3 + sqrt(sword[js]) * 4 + sqrt(next_sword[js]) + sqrt(HP[js]) * 8);
        }
        else {
            if (end()) {
                return HP[js] > 0 ? 1000 : -1000;
            }
            else  return (bullet[js] * 5 + sword[js] * 2 + next_sword[js] + HP[js] * 8);

        }
    }
    double get_value(int js,int type) {
        return tmp_value(js,type) - tmp_value(1 - js,type);
    }
}Initial;



struct cjd {
    Game now;
    int ALLOW_TYPE_NUM[2];//多少个可用行动
    int EXPANDED_NUM[2];
    vector<int>ALLOW_TYPE[2];//0是我们训练的AI，1是随机的
    vector<pair<int, double>>ALLOW_TYPE_HISTORY[2];
    int fa;
    int bh;
}CJD[10000];
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
pair<int,double> EXPAND(cjd& root,int lunshu,int js,int type) {
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
    double ss= tmpp.now.get_value(js,type);
    root.ALLOW_TYPE_HISTORY[js][bestson].second += ss;
    //////!!!!!!
    return make_pair(now_type, ss);
}
int AI2(int bs,int js,int type) {
    CJDCNT = 0;
    COUNT = 0;
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    cjd Root = xj(Initial, 0);
    while ((end - start) / 1ms < shichang) {
        COUNT++;
        int lunshu = 10 + rand() % 5;
        int ttmm = EXPAND(Root,lunshu,js,type).second;
        end = std::chrono::system_clock::now();
    }
    printf("第%d步共耗时%dms,拓展%d次,平均用时%lfms,用了%d个CJD\n", bs, (end - start) / 1ms, COUNT, ((end - start) / 1ms) * 1.0 / COUNT, CJDCNT);
    int final_choice= EXPAND(Root, 0, js,type).first;
    return final_choice;
}
int main() {
    printf("输入HP1,HP2\n");
    srand((unsigned)time(NULL));
    cin >> Initial.HP[0] >> Initial.HP[1];
    int count=0;
    Initial.output(1);
    while (!Initial.end()) {
        int s1 = AI2(++count, 0,1);
        int s2 = AI2(count, 1,2);
        /*while (1)
        {
            cin >> s2;
            auto AA = Initial.Get_allowed_actions(1);
            int s = AA.size();
            bool check = false;
            for (int i = 0; i < s; i++) {
                if (AA[i] == s2)check = true;
            }
            if (!check) {
                cout << "WRONG!\n";
            }
            else {
                break;
            }
        }*/
        Initial.now_action[0].type = s1, Initial.now_action[1].type = s2;
        Initial.step(1);
    }
    return 0;
}