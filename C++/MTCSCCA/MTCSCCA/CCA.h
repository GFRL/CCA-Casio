#pragma once
#define type_num 20
#include<vector>
using namespace std;
struct Action {
	int from, to, type;
};
struct Game {
	int num;
	int bullet[2];
	int HP[2];
	int sword[2];
	int next_sword[2];
	Action now_action[2];
	vector<int> Get_allowed_actions(int u) {
		return vector<int>{};
	}
	void step() {
		return;
	}
	bool end() {
		return false;
	}
	double get_value(int js) {
		return 1;
	}
}Initial;