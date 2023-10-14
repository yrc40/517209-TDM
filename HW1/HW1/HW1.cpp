#include <iostream>
#include <fstream>
#include<set>
#include<utility>
#include<algorithm>
#include<string>
#include "gurobi_c++.h"
using namespace std;
int main() {

	int item;

	fstream fin;
	fin.open("C:/Users/User/Desktop/param.txt", ios::in);
	if (!fin) {
		cerr << "Can't open file!\n";
		system("pause");
		exit(1);
	}
	else
		cout << "File open successfully!\n";

	int v;
	fin >> v;

	/*Sets*/
	set<int> V;
	for (int i = 0; i <= v + 1; i++) {
		V.insert(i);
	}

	set<pair<int, int> > A;
	for (int i = 0; i <= v; i++) {
		for (int j = 1; j <= v + 1; j++) {
			if (i != j && !(i == 0 && j == 6))//
				A.insert(make_pair(i, j));
		}
	}

	set<int> C1;
	for (int i = 0; i <= v + 1; i++) {
		fin >> item;
		if (item)
			C1.insert(i);
	}

	set<int> C2;
	for (int i = 0; i <= v + 1; i++) {
		fin >> item;
		if (item)
			C2.insert(i);
	}

	set<int> C;
	for (int i = 1; i <= v; i++) {
		C.insert(i);
	}

	set<int> V1;
	set_difference(C.begin(), C.end(), C2.begin(), C2.end(), inserter(V1, V1.end()));
	V1.insert(0);
	V1.insert(v + 1);


	set<int> V2 = V;

	set<pair<int, int> > A1;
	for (auto& i : A) {
		if (C2.find(i.first) == C2.end() && C2.find(i.second) == C2.end() && i.first != v + 1)
			A1.insert(i);
	}

	set<pair<int, int> > A2 = A;

	set<int> deltaPlus1[7], deltaMinus1[7];
	for (auto& i : A1) {
		deltaPlus1[i.first].insert(i.second);
		deltaMinus1[i.second].insert(i.first);
	}

	set<int> deltaPlus2[7], deltaMinus2[7];
	for (auto& i : A2) {
		deltaPlus2[i.first].insert(i.second);
		deltaMinus2[i.second].insert(i.first);
	}

	/*Parameters*/
	double d[7][7], r[7][7], c[7][7], e[7][7];
	int s1[7] = { 0 }, s2[7] = { 0 }, a[7], b[7], T, M;
	double item2;

	for (int i = 0; i <= v + 1; i++) {
		for (int j = 0; j <= v + 1; j++) {
			fin >> item2;
			d[i][j] = item2;
			r[i][j] = item2;
			c[i][j] = item2;
			e[i][j] = item2;
		}
	}

	for (int i = 0; i <= v + 1; i++) {
		fin >> item;
		s1[i] = item;
		s2[i] = item;
	}

	for (int i = 0; i <= v + 1; i++) {
		fin >> a[i];
	}

	for (int i = 0; i <= v + 1; i++) {
		fin >> b[i];
	}

	fin >> T;
	fin >> M;

	fin.close();

	/*Gurobi*/
	try {
		GRBEnv env = GRBEnv();
		GRBModel model = GRBModel(env);
		string name;

		/*Variables*/
		//cout << "xi_j\n";
		GRBVar x[7][7];
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				if (A1.find(make_pair(i, j)) != A1.end()) {
					name = "x" + to_string(i) + "_" + to_string(j);
					x[i][j] = model.addVar(0, 1, 0, GRB_BINARY, name);
				}
				else {
					name = "x" + to_string(i) + "_" + to_string(j);
					x[i][j] = model.addVar(0, 0, 0, GRB_BINARY, name);
				}
				//name = "x" + to_string(i) + "_" + to_string(j);
				//x[i][j] = model.addVar(0, 1, 0, GRB_BINARY, name);
			}
		}

		//cout << "yi_j\n";
		GRBVar y[7][7];
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				if (A2.find(make_pair(i, j)) != A2.end()) {
					name = "y" + to_string(i) + "_" + to_string(j);
					y[i][j] = model.addVar(0, 1, 0, GRB_BINARY, name);
				}
				else {
					name = "y" + to_string(i) + "_" + to_string(j);
					y[i][j] = model.addVar(0, 0, 0, GRB_BINARY, name);
				}
			}
		}

		//cout << "ti\n";
		GRBVar t[7];
		for (auto& i : V1) {
			name = "t" + to_string(i);
			t[i] = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0, GRB_CONTINUOUS, name);
		}
		t[0] = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0, GRB_CONTINUOUS, name);
		t[6] = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0, GRB_CONTINUOUS, name);

		//cout << "pi\n";
		GRBVar p[7];
		for (int i = 0; i <= v + 1; i++) {
			if (V2.find(i) != V2.end() || i == 0 || i == v + 1) {
				name = "p" + to_string(i);
				p[i] = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0, GRB_CONTINUOUS, name);
			}
		}

		//cout << "zi_j\n";
		GRBVar z[7][7];
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				if (A1.find(make_pair(i, j)) != A1.end() && A2.find(make_pair(i, j)) != A2.end()) {
					name = "z" + to_string(i) + "_" + to_string(j);
					z[i][j] = model.addVar(0, 1, 0, GRB_BINARY, name);
				}
			}
		}

		/*Objective*/
		//cout << "obj(1)\n";
		GRBLinExpr sum = 0;
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				if (A1.find(make_pair(i, j)) != A1.end())
					sum += c[i][j] * x[i][j];
				if (A2.find(make_pair(i, j)) != A2.end())
					sum += e[i][j] * y[i][j];
				if (A1.find(make_pair(i, j)) != A1.end() && A2.find(make_pair(i, j)) != A2.end())
					sum -= e[i][j] * z[i][j];
			}
		}

		model.setObjective(sum, GRB_MINIMIZE);

		/*Constraints*/
		//cout << "c1(2)\n";
		for (auto& i : C) {
			sum = 0;
			for (auto& j : deltaPlus1[i]) {
				sum += x[i][j];
			}
			for (auto& j : deltaPlus2[i]) {
				sum += y[i][j];
			}
			name = "c1_" + to_string(i);
			model.addConstr(sum >= 1, name);
		}

		//cout << "c2(3)\n";
		sum = 0;
		for (auto& j : deltaPlus1[0])
			sum += x[0][j];
		name = "c2";
		model.addConstr(sum == 1, name);

		//cout << "c3(4)\n";
		sum = 0;
		for (auto& j : deltaPlus2[0])
			sum += y[0][j];
		name = "c3";
		model.addConstr(sum == 1, name);

		//cout << "c4(5)\n";
		set<int> ob5 = V1;
		ob5.erase(0);
		ob5.erase(v + 1);
		for (auto& j : ob5) {
			sum = 0;
			for (auto& i : deltaMinus1[j])
				sum += x[i][j];
			for (auto& i : deltaPlus1[j]) {
				sum -= x[j][i];
			}
			name = "c4_" + to_string(j);
			model.addConstr(sum == 0, name);
		}

		//cout << "c5(6)\n";
		set<int> ob6 = V2;
		ob6.erase(0);
		ob6.erase(v + 1);
		for (auto& j : ob6) {
			sum = 0;
			for (auto& i : deltaMinus2[j])
				sum += y[i][j];
			for (auto& i : deltaPlus2[j])
				sum -= y[j][i];
			name = "c5_" + to_string(j);
			model.addConstr(sum == 0, name);
		}

		//cout << "c6(7)\n";
		sum = 0;
		for (auto& i : deltaMinus1[v + 1])
			sum += x[i][v + 1];
		name = "c6";
		model.addConstr(sum == 1, name);

		//cout << "c7(8)\n";
		sum = 0;
		for (auto& i : deltaMinus2[v + 1])
			sum += y[i][v + 1];
		name = "c7";
		model.addConstr(sum == 1, name);

		//cout << "c8(9)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				if (A1.find(make_pair(i, j)) != A1.end() && A2.find(make_pair(i, j)) != A2.end()) {
					name = "c8_" + to_string(i) + to_string(j) + "_1";
					model.addConstr(x[i][j] + y[i][j] - 1 <= z[i][j], name);
					name = "c8_" + to_string(i) + to_string(j) + "_2";
					model.addConstr(z[i][j] <= x[i][j], name);
				}
			}
		}

		//cout << "c9(10)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				if (A1.find(make_pair(i, j)) != A1.end() && A2.find(make_pair(i, j)) != A2.end()) {
					name = "c9_" + to_string(i) + to_string(j) + "_1";
					model.addConstr(x[i][j] + y[i][j] - 1 <= z[i][j], name);
					name = "c9_" + to_string(i) + to_string(j) + "_2";
					model.addConstr(z[i][j] <= y[i][j], name);
				}
			}
		}

		//cout << "c10(11)\n";
		for (auto& k : A1) {
			name = "c10_" + to_string(k.first) + to_string(k.second);
			model.addConstr(t[k.first] + s1[k.first] + d[k.first][k.second] - t[k.second] <= (1 - x[k.first][k.second]) * M, name);
		}

		//cout << "c11(12)\n";
		for (auto& k : A2) {
			name = name = "c11_" + to_string(k.first) + to_string(k.second);
			model.addConstr(p[k.first] + s2[k.first] + r[k.first][k.second] - p[k.second] <= (1 - y[k.first][k.second]) * M, name);
		}

		//cout << "c12(13)\n";
		set<int> ob13 = V1;
		V1.insert(0);
		V1.insert(v + 1);
		for (auto& i : ob13) {
			name = "c12_" + to_string(i) + "_1";
			model.addConstr(t[i] >= a[i], name);
			name = "c12_" + to_string(i) + "_2";
			model.addConstr(b[i] >= t[i], name);
		}

		//cout << "c13(14)\n";
		set<int> ob14 = V2;
		ob14.insert(0);
		ob14.insert(v + 1);
		for (auto& i : ob14) {
			name = "c13_" + to_string(i) + "_1";
			model.addConstr(a[i] <= p[i], name);
			name = "c13_" + to_string(i) + "_2";
			model.addConstr(p[i] <= b[i], name);
		}

		//cout << "c14(15)\n";
		set<int> ob15;
		set_intersection(V1.begin(), V1.end(), V2.begin(), V2.end(), inserter(ob15, ob15.end()));
		ob15.erase(0);
		ob15.erase(v + 1);
		for (auto& i : ob15) {
			sum = 0;
			for (int j = 0; j <= v + 1; j++) {
				if (deltaMinus1[i].find(j) != deltaMinus1[i].end())
					sum += x[j][i];
				if (deltaMinus2[i].find(j) != deltaMinus2[i].end())
					sum += y[j][i];
			}
			name = "c14_" + to_string(i) + "_1";
			model.addConstr(p[i] + (sum - 2) * M <= t[i], name);
			name = "c14_" + to_string(i) + "_2";
			model.addConstr(t[i] <= p[i] - (sum - 2) * M, name);
		}

		//cout << "c15(16)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				for (int l = 0; l <= v + 1; l++) {
					sum = 0;
					if (A1.find(make_pair(i, j)) != A1.end() && A1.find(make_pair(j, l)) != A1.end()) {
						for (int m = 0; m <= v + 1; m++) {
							if (deltaMinus1[i].find(m) != deltaMinus1[i].end())
								sum += x[m][i];
							if (deltaMinus1[l].find(m) != deltaMinus1[l].end())
								sum += x[m][l];
						}
						name = "c15_" + to_string(i) + to_string(j) + to_string(l);
						model.addConstr(sum >= 2 - ((1 - y[i][j]) * M + x[i][j] * M + (1 - y[j][l]) * M + x[j][l] * M), name);
					}
					
				}
			}
		}
		set<pair<int, int> > ob17;
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				if (A1.find(make_pair(i, j)) == A1.end() && A2.find(make_pair(i, j)) != A2.end())
					ob17.insert(make_pair(i, j));
			}
		}

		//cout << "c16(17)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				for (int l = 0; l <= v + 1; l++) {
					sum = 0;
					if (ob17.find(make_pair(i, j)) != ob17.end() && ob17.find(make_pair(j, l)) != ob17.end()) {
						for (int m = 0; m <= v + 1; m++) {
							if (deltaMinus1[i].find(m) != deltaMinus1[i].end())
								sum += x[m][i];
							if (deltaMinus1[l].find(m) != deltaMinus1[l].end())
								sum += x[m][l];
						}
						name = "c16_" + to_string(i) + to_string(j) + to_string(l);
						model.addConstr(sum >= 2 - ((1 - y[i][j]) * M + (1 - y[j][l]) * M), name);
					}
					
				}
			}
		}

		//cout << "c17(18)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				for (int l = 0; l <= v + 1; l++) {
					sum = 0;
					if (ob17.find(make_pair(i, j)) != ob17.end() && A1.find(make_pair(j, l)) != A1.end()) {
						for (int m = 0; m <= v + 1; m++) {
							if (deltaMinus1[i].find(m) != deltaMinus1[i].end())
								sum += x[m][i];
							if (deltaMinus1[l].find(m) != deltaMinus1[l].end())
								sum += x[m][l];
						}
						name = "c17_" + to_string(i) + to_string(j) + to_string(l);
						model.addConstr(sum >= 2 - ((1 - y[i][j]) * M + (1 - y[j][l]) * M + x[j][l] * M), name);
					}
				}
			}
		}

		//cout << "c18(19)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				for (int l = 0; l <= v + 1; l++) {
					sum = 0;
					if (ob17.find(make_pair(j, l)) != ob17.end() && A1.find(make_pair(i, j)) != A1.end()) {
						for (int m = 0; m <= v + 1; m++) {
							if (deltaMinus1[i].find(m) != deltaMinus1[i].end())
								sum += x[m][i];
							if (deltaMinus1[l].find(m) != deltaMinus1[l].end())
								sum += x[m][l];
						}
						name = "c18_" + to_string(i) + to_string(j) + to_string(l);
						model.addConstr(sum >= 2 - ((1 - y[j][l]) * M + (1 - y[i][j]) * M + x[i][j] * M), name);
					}
				}
			}
		}

		//cout << "c19(20)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				for (int l = 0; l <= v + 1; l++) {
					if (A1.find(make_pair(j, l)) != A1.end() && A1.find(make_pair(i, j)) != A1.end()) {
						name = "c19_" + to_string(i) + to_string(j) + to_string(l);
						model.addConstr(r[i][j] + s2[j] + r[j][l] <= T + ((1 - y[i][j]) * M + x[i][j] * M + (1 - y[j][l]) * M + x[j][l] * M), name);
					}
				}
			}
		}

		//cout << "c20(21)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				for (int l = 0; l <= v + 1; l++) {
					if (ob17.find(make_pair(j, l)) != ob17.end() && ob17.find(make_pair(i, j)) != ob17.end()) {
						name = "c20_" + to_string(i) + to_string(j) + to_string(l);
						model.addConstr(r[i][j] + s2[j] + r[j][l] <= T + ((1 - y[i][j]) * M + (1 - y[j][l]) * M), name);
					}
				}
			}
		}

		//cout << "c21(22)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				for (int l = 0; l <= v + 1; l++) {
					if (A1.find(make_pair(j, l)) != A1.end() && ob17.find(make_pair(i, j)) != ob17.end()) {
						name = "c21_" + to_string(i) + to_string(j) + to_string(l);
						model.addConstr(r[i][j] + s2[j] + r[j][l] <= T + ((1 - y[i][j]) * M + (1 - y[j][l]) * M + x[j][l] * M), name);
					}
				}
			}
		}

		//cout << "c22(23)\n";
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				for (int l = 0; l <= v + 1; l++) {
					if (A1.find(make_pair(i, j)) != A1.end() && ob17.find(make_pair(j, l)) != ob17.end()) {
						name = "c22_" + to_string(i) + to_string(j) + to_string(l);
						model.addConstr(r[i][j] + s2[j] + r[j][l] <= T + ((1 - y[i][j]) * M + x[i][j] * M + (1 - y[j][l]) * M), name);
					}
				}
			}
		}

		//cout << "c23(24)\n";
		for (auto& i : C1) {
			sum = 0;
			for (auto& j : deltaMinus1[i]) {
				sum += x[j][i];
			}
			name = "c23_" + to_string(i);
			model.addConstr(sum == 1, name);
		}


		//cout << "c24(25)\n";
		GRBLinExpr sum2 = 0;
		for (auto& i : C1) {
			sum = 0;
			sum2 = 0;
			for (auto& j : deltaMinus1[i])
				sum += z[j][i];
			for (auto& j : deltaPlus1[i])
				sum2 += z[i][j];
			name = "c24_" + to_string(i);
			model.addConstr(sum == sum2, name);
		}

		model.optimize();
		cout << "*--- Result ---*\n" 
			 << "Objective value = " << model.get(GRB_DoubleAttr_ObjVal) << endl;
				
		cout << "Truck : ";
		int next = 0;
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				if (x[next][j].get(GRB_DoubleAttr_X) == 1) {
					cout << next <<  " -> ";
					next = j;
				}
			}
		}
		cout << next;

		cout << "\nDrone : ";
		next = 0;
		for (int i = 0; i <= v + 1; i++) {
			for (int j = 0; j <= v + 1; j++) {
				if (y[next][j].get(GRB_DoubleAttr_X) == 1) {
					cout << next << " -> ";
					next = j;
				}
			}
		}
		cout << next << "\n";
		//model.computeIIS();
		//model.write("model.ilp");

	}
	catch (GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...) {
		cout << "Exception during optimization" << endl;
	}

	system("pause");
	return 0;
}
