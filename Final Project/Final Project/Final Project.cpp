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
	fin.open("C:/Users/User/Desktop/data/case1.txt", ios::in);
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

	vector<int> m;
	for (int i = 0; i < 2; i++) {
		fin >> inputint;
		m.push_back(inputint);
	}
	cout << "\nmi: ";
	for (auto& i : m) {
		cout << i << " ";
	}
	cout << "\n";

	fin.close();

	GRBEnv env = GRBEnv();
	GRBModel model = GRBModel(env);
	model.optimize();
}
