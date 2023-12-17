#include <iostream>
#include <fstream>
#include<set>
#include<utility>
#include<algorithm>
#include<string>
#include<vector>
#include "gurobi_c++.h"
using namespace std;
int main() { 

	int inputint;
	double inputdouble;

	fstream fin;
	fin.open("C:/Users/User/Desktop/data/case3.txt", ios::in);
	if (!fin) {
		cerr << "Can't open file!\n";
		system("pause");
		exit(1);
	}
	else
		cout << "File open successfully!\n";

	int c, M, e, v, K;
	fin >> c >> M >> e >> v >> K;
	cout << c << " " << M << " " << e << " " << v << " " << K << "\n";

	/*Set*/

	set<int> I;
	for (int i = 0; i <= c + 1; i++) {
		I.insert(i);
	}
	cout << "Set I: ";
	for (auto& i : I) {
		cout << i << " ";
	}
	cout << "\n";

	set<pair<int, int> > A;
	for (int i = 0; i <= c; i++) {
		for (int j = 1; j <= c + 1; j++) {
			if (i != j) A.insert(make_pair(i, j));
		}
	}
	cout << "Set A: \n";
	for (auto& i : A) {
		cout << i.first << i.second << "\n";
	}

	set<int> C;
	for (int i = 1; i <= c; i++) {
		C.insert(i);
	}
	cout << "Set C: ";
	for (auto& i : C) {
		cout << i << " ";
	}
	cout << "\n";

	set<int> C1, C2, C3, C4, C5, C6, C7;
	for (int i = 1; i <= c; i++) {
		fin >> inputint;
		if (inputint == 1) C1.insert(i);
		else if (inputint == 2) C2.insert(i);
		else if (inputint == 3) C3.insert(i);
		else if (inputint == 4) C4.insert(i);
		else if (inputint == 5) C5.insert(i);
		else if (inputint == 6) C6.insert(i);
		else if (inputint == 7) C7.insert(i);
	}
	cout << "Set C1: ";
	for (auto& i : C1) {
		cout << i << " ";
	}
	cout << "\nSet C2: ";
	for (auto& i : C2) {
		cout << i << " ";
	}
	cout << "\nSet C3: ";
	for (auto& i : C3) {
		cout << i << " ";
	}
	cout << "\nSet C4: ";
	for (auto& i : C4) {
		cout << i << " ";
	}
	cout << "\nSet C5: ";
	for (auto& i : C5) {
		cout << i << " ";
	}
	cout << "\nSet C6: ";
	for (auto& i : C6) {
		cout << i << " ";
	}
	cout << "\nSet C7: ";
	for (auto& i : C7) {
		cout << i << " ";
	}

	set<int> T;
	for (int i = 0; i < v; i++) {
		T.insert(i);
	}
	cout << "\nSet T: ";
	for (auto& i : T) {
		cout << i;
	}
	cout << "\n";

	set<int> T1, T2, T3;
	for (int i = 0; i < v; i++) {
		fin >> inputint;
		if (inputint == 1) T1.insert(i);
		else if (inputint == 2) T2.insert(i);
		else if (inputint == 3) T3.insert(i);
	}
	cout << "Set T1: ";
	for (auto& i : T1) {
		cout << i << " ";
	}
	cout << "\nSet T2: ";
	for (auto& i : T2) {
		cout << i << " ";
	}
	cout << "\nSet T3: ";
	for (auto& i : T3) {
		cout << i << " ";
	}

	set<int> E;
	for (int i = 0; i < e; i++) {
		E.insert(i);
	}
	cout << "\nSet E: ";
	for (auto& i : E) {
		cout << i << " ";
	}

	set<int> E1, E2;
	for (int i = 0; i < e; i++) {
		fin >> inputint;
		if (inputint == 1) E1.insert(i);
		else if (inputint == 2) E2.insert(i);
	}

	cout << "\nSet E1: ";
	for (auto& i : E1) {
		cout << i << " ";
	}
	cout << "\nSet E2: ";
	for (auto& i : E2) {
		cout << i << " ";
	}

	/*Paramerers*/
	
	vector<int> s;
	for (int i = 0; i < c; i++) {
		fin >> inputint;
		s.push_back(inputint);
	}
	cout << "\nsi: ";
	for (auto& i : s) {
		cout << i << " ";
	}
	
	vector<vector<double> > d;
	for (int i = 0; i <= c + 1; i++) {
		vector<double> row;
		for (int j = 0; j <= c + 1; j++) {
			fin >> inputdouble;
			row.push_back(inputdouble);
		}
		d.push_back(row);
	}

	cout << "\ndij: \n";
	for (auto& i : d) {
		for (auto& j : i) {
			cout << j << " ";
		}
		cout << "\n";
	}

	vector<vector<double> > w;
	for (int i = 0; i <= c + 1; i++) {
		vector<double> row;
		for (int j = 0; j <= c + 1; j++) {
			fin >> inputdouble;
			row.push_back(inputdouble);
		}
		w.push_back(row);
	}

	cout << "wij: \n";
	for (auto& i : w) {
		for (auto& j : i) {
			cout << j << " ";
		}
		cout << "\n";
	}

	int h, F, H;
	fin >> h >> F >> H;
	cout << h << " " << F << " " << H << "\n";

	vector<double> g;
	for (int i = 0; i < c; i++) {
		fin >> inputdouble;
		g.push_back(inputdouble);
	}
	cout << "gi: ";
	for (auto& i : g) {
		cout << i << " ";
	}

	vector<int> o;
	for (int i = 0; i < c; i++) {
		fin >> inputint;
		o.push_back(inputint);
	}
	cout << "\noi: ";
	for (auto& i : o) {
		cout << i << " ";
	}

	vector<int> a;
	for (int i = 0; i < c; i++) {
		fin >> inputint;
		a.push_back(inputint);
	}
	cout << "\nai: ";
	for (auto& i : a) {
		cout << i << " ";
	}

	vector<int> b;
	for (int i = 0; i < c; i++) {
		fin >> inputint;
		b.push_back(inputint);
	}
	cout << "\nbi: ";
	for (auto& i : b) {
		cout << i << " ";
	}

	vector<int> t;
	for (int i = 0; i < K; i++) {
		fin >> inputint;
		t.push_back(inputint);
	}
	cout << "\nti: ";
	for (auto& i : t) {
		cout << i << " ";
	}

	vector<int> V;
	for (int i = 0; i < K; i++) {
		fin >> inputint;
		V.push_back(inputint);
	}
	cout << "\nVi: ";
	for (auto& i : V) {
		cout << i << " ";
	}

	vector<int> W;
	for (int i = 0; i < K; i++) {
		fin >> inputint;
		W.push_back(inputint);
	}
	cout << "\nWi: ";
	for (auto& i : W) {
		cout << i << " ";
	}

	vector<int> k;
	for (int i = 0; i < K; i++) {
		fin >> inputint;
		k.push_back(inputint);
	}
	cout << "\nki: ";
	for (auto& i : k) {
		cout << i << " ";
	}

	int m;
	fin >> m;
	cout << "\nm: " << m;

	vector<double> f;
	for (int i = 0; i < K; i++) {
		fin >> inputdouble;
		f.push_back(inputdouble);
	}
	cout << "\nfi: ";
	for (auto& i : f) {
		cout << i << " ";
	}

	fin.close();


	try {

		GRBEnv env = GRBEnv();
		GRBModel model = GRBModel(env);

		/*Variables*/
		string name;

		vector<vector<GRBVar> > u; //u_i^p
		for (int i = 0; i <= c + 1; i++) {
			vector<GRBVar> row;
			for (int p = 0; p < v; p++) {
				name = "u" + to_string(i) + to_string(p);
				row.push_back(model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, name));
			}
			u.push_back(row);
		}

		vector<vector<vector<GRBVar> > > x; //x_ij^p
		for (int i = 0; i < c + 1; i++) { //0-2
			vector<vector<GRBVar> > len;
			for (int j = 1; j <= c + 1; j++) { //1-3
				vector<GRBVar> wid;
				if (i != j) {
					for (int p = 0; p < v; p++) {
						name = "x" + to_string(i) + to_string(j) + to_string(p);
						wid.push_back(model.addVar(0, 1, 0, GRB_BINARY, name));
					}
				}
				len.push_back(wid);
			}
			x.push_back(len);
		}
		cout << "x0: " << x[0].size();

		vector<GRBVar> U; //Ui
		for (int i = 0; i <= c; i++) {
			name = "U" + to_string(i);
			U.push_back(model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, name));
		}

		vector<vector<GRBVar> > y; //y_i^p
		for (int i = 0; i <= e; i++) {
			vector<GRBVar> row;
			for (int p = 0; p < v; p++) {
				name = "y" + to_string(i) + to_string(p);
				row.push_back(model.addVar(0, 1, 0, GRB_BINARY, name));
			}
			y.push_back(row);
		}

		/*Objective Function*/

		GRBLinExpr sum = 0;
		for (auto& i : A) {
			for (auto& p : T) {
				if(T1.find(p) != T1.end()) sum += f[0] * d[i.first][i.second]* x[i.first][i.second-1][p];
				else if (T2.find(p) != T2.end()) sum += f[1] * d[i.first][i.second] * x[i.first][i.second-1][p];
				else if(T3.find(p) != T3.end()) sum += f[2] * d[i.first][i.second] * x[i.first][i.second-1][p];
			}
		}
		for (auto& j : C) {
			for (auto& p : T1) sum += t[0] * x[0][j-1][p];
			for (auto& p : T2) sum += t[1] * x[0][j-1][p];
			for (auto& p : T3) sum += t[2] * x[0][j-1][p];
		}
		for (auto& p : T) {
			for(auto& i : E) {
				sum += m * y[i][p];
			}
		}
		model.setObjective(sum, GRB_MINIMIZE);

		/*Constraints*/

		//c1
		sum = 0;
		for (auto& j : C) {
			if (C7.find(j) == C7.end()) { // j in C\C7
				for (auto& p : T) {
					for (auto& i : A) {
						if (j == i.second) {
							sum += x[i.first][i.second - 1][p];
						}
					}
				}
				name = "c1_j" + to_string(j);
				model.addConstr(sum == 1, name);
				sum = 0;
			}
		}

		sum = 0;
		for (auto& i : C) {
			if (C7.find(i) == C7.end()) { // i in C\C7
				for (auto& p : T) {
					for (auto& j : A) {
						if (i == j.first) {
							sum += x[j.first][j.second - 1][p];
						}
					}
				}
				name = "c1-2_i" + to_string(i);
				model.addConstr(sum == 1, name);
				sum = 0;
			}
		}/**/

		//c2
		set<int> c2obj;
		set_union(T2.begin(), T2.end(), T3.begin(), T3.end(),
			std::inserter(c2obj, c2obj.begin()));
		sum = 0;
		for (auto& i : C7) {
			for (auto& p : c2obj) {
				for (auto& j : A) {
					if (i == j.first) {
						sum += x[j.first][j.second - 1][p];
					}
				}
			}
			name = "c2_i" + to_string(i);
			model.addConstr(sum == 2, name);
			sum = 0;
		}

		//c3
		sum = 0;
		for (auto& j : C7) {
			for (auto& p : c2obj) {
				for (auto& i : A) {
					if (j == i.second) {
						sum += x[i.first][j - 1][p];
					}
				}
			}
			name = "c3_j" + to_string(j);
			model.addConstr(sum == 2, name);
			sum = 0;
		}

		//c4
		sum = 0;
		for (auto& p : T) {
			for (auto& j : C7) {
				for (auto& i : I) {
					if (i != c + 1) {
						sum += x[i][j - 1][p];
					}
				}
				name = "c4_p" + to_string(p) + "_j" + to_string(j);
				model.addConstr(sum <= 1, name);
				sum = 0;
			}
		}

		//c5
		sum = 0;
		for (auto& j : C7) {
			for (auto& p : T1) {
				for (auto& k : A) {
					if (k.second == j) {
						sum += x[k.first][j - 1][p];
					}
				}
			}
			name = "c5_j" + to_string(j);
			model.addConstr(sum == 0, name);
			sum = 0;
		}

		//c6
		sum = 0;
		for (auto& p : T) {
			for (auto& k : A) {
				if (k.first == 0) {
					sum = x[0][k.second - 1][p];
				}
			}
			name = "c6_p" + to_string(p);
			model.addConstr(sum == 1, name);
			sum = 0;
		}

		//c7
		sum = 0;
		for (auto& j : C) {
			for (auto& p : T) {
				for (auto& k : A) {
					if (k.second == j) sum += x[k.first][j - 1][p];
					if (k.first == j) sum -= x[j][k.second - 1][p];
				}
				name = "c7_j" + to_string(j) + "_p" + to_string(p);
				model.addConstr(sum == 0, name);
				sum = 0;
			}
		}/**/

		//c8
		sum = 0;
		for (auto& p : T) {
			for (auto& k : A) {
				if (k.second == c + 1) sum += x[k.first][c][p];
			}
			name = "c8_p" + to_string(p);
			model.addConstr(sum == 1, name);
			sum = 0;
		}
		
		//c9
		set<int> c9obj1; // I\C7, c+1
		set_difference(I.begin(), I.end(),C7.begin(), C7.end(), std::inserter(c9obj1, c9obj1.begin()));
		c9obj1.erase(c + 1);
		set<int> c9obj2; // I\C7, 0
		set_difference(I.begin(), I.end(), C7.begin(), C7.end(), std::inserter(c9obj2, c9obj2.begin()));
		c9obj1.erase(0);
		for (auto& p : T) {
			for (auto& k : A) {
				if (c9obj1.find(k.first) != c9obj1.end() && c9obj2.find(k.second) != c9obj2.end()) {
					name = "c9_i" + to_string(k.first) + "_j" + to_string(k.second) + "_p" + to_string(p);
					model.addConstr(u[k.first][p] + w[k.first][k.second] + s[k.first-1] - u[k.second][p] <= (1 - x[k.first][k.second-1][p]) * M, name);
				} 
			}
		}
		
		//10
		for (auto& p : T) {
			for (auto& k : A) {
				if (c9obj1.find(k.first) != c9obj1.end() && C7.find(k.second) != C7.end()) {
					name = "c10_i" + to_string(k.first) + "_j" + to_string(k.second) + "_p" + to_string(p);
					cout << k.first << " " << k.second << "\n";
					model.addConstr(u[k.first][p] + w[k.first][k.second] + s[k.first - 1] - U[k.second] <= (1 - x[k.first][k.second - 1][p]) * M, name);
				}
			}
		}

		//11
		for (auto& p : T) {
			for (auto& k : A) {
				if (C7.find(k.first) != C7.end() && C7.find(k.second) != C7.end()) {
					name = "c11_i" + to_string(k.first) + "_j" + to_string(k.second) + "_p" + to_string(p);
					cout << k.first << " " << k.second << "\n";
					model.addConstr(U[k.first] + w[k.first][k.second] + s[k.first - 1] - U[k.second] <= (1 - x[k.first][k.second - 1][p]) * M, name);
				}
			}
		}

		//12
		for (auto& p : T) {
			for (auto& k : A) {
				if (C7.find(k.first) != C7.end() && c9obj2.find(k.second) != c9obj2.end()) {
					name = "c12_i" + to_string(k.first) + "_j" + to_string(k.second) + "_p" + to_string(p);
					cout << k.first << " " << k.second << "\n";
					model.addConstr(U[k.first] + w[k.first][k.second] + s[k.first - 1] - u[k.second][p] <= (1 - x[k.first][k.second - 1][p]) * M, name);
				}
			}
		} 

		//13
		sum = 0;
		for (auto& p : T) {
			for (auto& i : C) {
				for (auto& k : A) {
					if (i == k.first) sum += x[i][k.second - 1][p];
				}
				name = "c13a_i" + to_string(i) + "_p" + to_string(p);
				model.addConstr(a[i - 1] * sum <= u[i][p], name);
				sum = 0;
				for (auto& k : A) {
					if (i == k.first) sum += x[i][k.second - 1][p];
				}
				name = "c13b_i" + to_string(i) + "_p" + to_string(p);
				model.addConstr(u[i][p] <= b[i - 1] * sum, name);
				sum = 0;
			}
		}

		//14
		set<int> c14obj; // T\T1
		set_difference(T.begin(), T.end(), T1.begin(), T1.end(), std::inserter(c14obj, c14obj.begin()));
		for (auto& i : C7) {
			for (auto& p : c14obj) {
				name = "c14_i" + to_string(i) + "_p" + to_string(p);
				model.addConstr(U[i] >= u[i][p], name);
			}
		}

		//15
		for (auto& i : I) {
			for (auto& p : T) {
				name = "c15-1_i" + to_string(i) + "_p" + to_string(p);
				model.addConstr(F <= u[i][p], name);
				name = "c15-2_i" + to_string(i) + "_p" + to_string(p);
				model.addConstr(u[i][p] <= H, name);
			}
		}

		//16
		set<int> c16obj = I;
		c16obj.erase(0);
		GRBLinExpr sum2 = 0;
		sum = 0;
		/*for (auto& p : T) {
			for (auto& i : C) {//12
				for (auto& j : c16obj) {//123
					sum += g[i - 1] * x[3][j-1][p];
				}
				sum2 += sum;
				sum = 0;
			}
			name = "c16_p" + to_string(p);
			if(T1.find(p) != T1.end()) model.addConstr(sum2 <= W[0], name);
			else if(T2.find(p) != T2.end()) model.addConstr(sum2 <= W[1], name);
			else if(T3.find(p) != T3.end()) model.addConstr(sum2 <= W[2], name);
			sum2 = 0;
		}*/
		sum = 0;
		for (auto& p : T) {
			for (auto& k : A) {
				if (k.first != 0) {
					sum += g[k.first - 1] * x[k.first][k.second - 1][p];
				}
			}
			name = "c16_p" + to_string(p);
			if (T1.find(p) != T1.end()) model.addConstr(sum <= W[0], name);
			else if (T2.find(p) != T2.end()) model.addConstr(sum <= W[1], name);
			else if (T3.find(p) != T3.end()) model.addConstr(sum <= W[2], name);
			sum = 0;
		}

		//17
		/*sum = 0;
		for (auto& p : T) {
			for (auto& k : A) {
				if (k.first != 0) {
					sum += o[k.first - 1] * x[k.first][k.second - 1][p];
				}
			}
			name = "c17_p" + to_string(p);
			if (T1.find(p) != T1.end()) model.addConstr(sum <= V[0], name);
			else if (T2.find(p) != T2.end()) model.addConstr(sum <= V[1], name);
			else if (T3.find(p) != T3.end()) model.addConstr(sum <= V[2], name);
			sum = 0;
		}

		//18
		for (auto& p : T) {
			name = "c18_p" + to_string(p);
			model.addConstr(u[c + 1][p] - u[0][p] <= h, name);
		}

		//19
		set<int> c19obj;
		set_difference(E.begin(), E.end(), E2.begin(), E2.end(), inserter(c19obj, c19obj.begin()));
		sum = 0;
		sum2 = 0;
		for (auto& p : T1) {
			for (auto& i : c19obj) sum += y[i][p];
			for (auto& j : C) sum2 += x[0][j - 1][p];
			name = "c19_p" + to_string(p);
			model.addConstr(sum == sum2, name);
			sum = 0;
			sum2 = 0;
		}

		//20
		sum = 0;
		sum2 = 0;
		for (auto& p : c14obj) { // T\T1
			for (auto& i : E) sum += y[i][p];
			for (auto& j : C) sum2 += x[0][j - 1][p];
			name = "c20_p" + to_string(p);
			model.addConstr(sum == 2 * sum2, name);
			sum = 0;
			sum2 = 0;
		}

		//21
		sum = 0;
		sum2 = 0;
		set<int> c21obj = C;
		C.insert(0);
		for (auto& p : T) {
			for (auto& j : C3) {
				for (auto& k : E1) sum += y[k][p];
				for (auto& i : c21obj) sum2 += x[i][j - 1][p];
				name = "c21_p" + to_string(p) + "_j" + to_string(j);
				model.addConstr(sum2 <= sum, name);
				sum = 0;
				sum2 = 0;
			}
		}

		//22
		set<int> c22obj;
		set_union(C4.begin(), C4.end(), C5.begin(), C5.end(),
			std::inserter(c22obj, c22obj.begin()));
		sum = 0;
		sum2 = 0;
		for (auto& p : c2obj) {
			for (auto& j : c22obj) {
				for (auto& k : E) sum += y[k][p];
				for (auto& i : c21obj) sum2 += x[i][j - 1][p];
				name = "c22_p" + to_string(p) + "_j" + to_string(j);
				model.addConstr(2*sum2 <= sum, name);
				sum = 0;
				sum2 = 0;
			}
		}

		//23
		sum = 0;
		sum2 = 0;
		for (auto& p : c2obj) {
			for (auto& j : C6) {
				for (auto& k : E2) sum += y[k][p];
				for (auto& i : c21obj) {
					if(i != j) sum2 += x[i][j - 1][p];
				}
				name = "c23_p" + to_string(p) + "_j" + to_string(j);
				model.addConstr(2 * sum2 <= sum, name);
				cout << "sum2: ";
				cout << sum2 << " ";
				sum = 0;
				sum2 = 0;
			}
		}

		//24
		sum = 0;
		sum2 = 0;
		for (auto& p : c14obj) {
			for (auto& j : C7) {
				for (auto& k : E) sum += y[k][p];
				for (auto& i : c21obj) {
					if (i != j) sum2 += x[i][j - 1][p];
				}
				name = "c24_p" + to_string(p) + "_j" + to_string(j);
				model.addConstr(4 * sum2 <= sum, name);
				sum = 0;
				sum2 = 0;
			}
		}*/

		model.optimize();
		model.computeIIS();
		model.write("model.ilp");
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
