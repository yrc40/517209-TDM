#include <iostream>
#include<set>
#include "gurobi_c++.h"
using namespace std;
int main()
{
	GRBEnv env = GRBEnv();
	GRBModel model = GRBModel(env);
	model.optimize();
}
