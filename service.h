#pragma once
#include <bits/stdc++.h>

using namespace std;

namespace SERVICE {
	string HOME; // The path of home dir.
	void init(void); // Get the HOME path.
	void bash_run(string); // Give a command and run in bash.
	void install(); // Install the application into the computer
	void uninstall(); // Uninstall the application from the computer
	bool check_path(string); // Check if there is the designated path.
	bool check_address(string); // Check if it is a legal website address.
	int edit_distance(string, string); // The edit distance between two string.
	int common_distance(string, string); // The common distance between two string.
	string to_string(char *); // Trun char array to string
	string expand_user(string); // Expand '~' to the home path.
}

/* Functions {{{ */
bool SERVICE::check_path(string s) {
	s = SERVICE::expand_user(s);
	ifstream fin(s.data());
	bool ok = !fin;
	fin.close();
	return !ok;
}

bool SERVICE::check_address(string s) { return !min(min(s.find("http://", 0), s.find("https://", 0)), s.find("ftp://", 0)); }

void SERVICE::init(void) { SERVICE::HOME = getenv("HOME"); }

string SERVICE::expand_user(string s) {
	if (s.at(0) == '~') s.replace(0, 1, SERVICE::HOME);
	return s;
}

void SERVICE::bash_run(string s) { system(s.data()); }

string SERVICE::to_string(char *c) {
	string s = c;
	return s;
}

void SERVICE::install() {
	SERVICE::bash_run("sudo cp ./tolink /usr/bin");
	string c;
	cout << "Do you want to alias 'tolink' to 'to'? (y/n) ";
	cin >> c;
	if (c != "y" && c != "Y") return ;
	SERVICE::bash_run("sudo cp ./tolink /usr/bin/to");
}

void SERVICE::uninstall() {
	SERVICE::bash_run("sudo rm /usr/bin/tolink");
	SERVICE::bash_run("sudo rm /usr/bin/to");
}

int SERVICE::edit_distance(string a, string b) {
	vector<vector<int>>d;
	vector<int>t;
	t.push_back(0);
	for (int i = 0; i < (int) b.size(); i++) t.push_back(i + 1);
	d.push_back(t);
	for (int i = 0; i < (int) a.size(); i++) {
		t.clear(); t.push_back(i + 1);
		for (int j = 0; j < (int) b.size(); j++) {
			if (a.at(i) == b.at(j)) t.push_back(d.at(i).at(j));
			else t.push_back(min(min(d.at(i).at(j + 1), t.back()), d.at(i).at(j)) + 1);
		}
		d.push_back(t);
	}
	return d.at(a.size()).at(b.size());
}

int SERVICE::common_distance(string a, string b) {
	int lastPos = 0, tPos = 0, res = 0;
	a.push_back('#'), b.push_back('#');
	for (int i = 0; i < (int) a.size(); i++) {
		while (tPos < (int) b.size() && b.at(tPos) != a.at(i)) tPos++;
		if (tPos == (int) b.size()) return res + (a.size() - i + 1) * b.size();
		res += (tPos - lastPos) * (tPos - lastPos);
		lastPos = tPos;
	}
	return res;
}
/* }}} */
