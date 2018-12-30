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
	int common_substring(string, string); // Find the len of longest common substring
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
	SERVICE::bash_run("sudo cp tolink /usr/bin");
	string c;
	cout << "Do you want to alias 'tolink' to 'to'? (y/n) ";
	cin >> c;
	if (c != "y" || c != "Y") return ;
	if (SERVICE::check_path("~/.zshrc"))
		SERVICE::bash_run("echo 'alias to=\"tolink\"' >> ~/.zshrc");
	if (SERVICE::check_path("~/.bashrc"))
		SERVICE::bash_run("echo 'alias to=\"tolink\"' >> ~/.bashrc");
}

void SERVICE::uninstall() {
	SERVICE::bash_run("sudo rm /usr/bin/tolink");
}

int SERVICE::common_substring(string a, string b) {
	a.push_back('#'), b.push_back('#');
	int res = 0, t = 0, last = 0;
	for (int i = 0; i < (int) b.size(); i++) {
		if (a.at(t) == b.at(i)) {
			res -= i - last;
			last = i;
			t++;
		}
	}
	return res + t * b.size();
}
/* }}} */
