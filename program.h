#pragma once
#include <bits/stdc++.h>
#include "init.h"
#include "service.h"

using namespace std;

#define rep(i, a, b) for (int i = (int)a; i <= (int)b; i++)

namespace PROGRAM {
	string configFile; // The path of config file.
	vector<Link>link; // All the link
	string defaltBrowser; // The defalt browser for opening the link.
	void init(void); // Get the config file path.
	void read_config(void); // Read the config from the config file.
	void write_config(void); // Write the infor into the config file.
	void show_help(void); // Show program's help.
	void welcome(void); // A welcome guide for the first time.
	void add_link(Link); // Add the designated link.
	void list_link(); // List all the added link.
	void del_link(string); // Delete the designated path.
	void open_web(string); // Open the designated web address in browser
	void change_browser(string); // Change the defalt browser
	void change_name(int, string); // Change the link's name
	void open_link(string); // Open the saved link or designated link
	void check_name(string); // Check if the name is usable.
	void show_wrong(int); // Show 'Error', give the error infor and quit.
	bool start_test(void); // Start https://www.samcompu.com to check the browser
	int get_id(string); // Find the link by the string
	int find_link(string); // Check if the link is exist and return its ID.
	void quit(void); // Quit the application with some necessary operating.
}

/* Functions {{{ */
void PROGRAM::init(void) {
	string configPath = SERVICE::HOME + "/.config/tolink";
	if (!SERVICE::check_path(configPath)) {
		SERVICE::bash_run("mkdir " + configPath);
		if (!SERVICE::check_path(configPath)) PROGRAM::show_wrong(2);
	}
	PROGRAM::configFile = SERVICE::HOME + "/.config/tolink/init.cfg";
	if (!SERVICE::check_path(PROGRAM::configFile)) PROGRAM::welcome();
	else PROGRAM::read_config();
}

void PROGRAM::show_help(void) {
	cout << 
		"'tolink' can open the designated or saved link in the browser." << endl << endl <<
		"Usage: " << endl << 
		"  to/tolink [parameter]      Open the link" << endl <<
		"  to/tolink [options]        Change or show the saved information" << endl <<  endl <<
		"Parameter: " << endl << 
		"  <path>                  The full website link." << endl <<
		"  <name>                  A string with only alaphabet." << endl << 
		"  <browser>               The command to start the browser." << endl << 
		"  <ID>                    The id for the saved link." << endl << endl <<
		"Options: " << endl << 
		"  -a, -a <name> <path>    Add new address with the unique name" << endl <<
		"      --add" << endl <<
		"  -c, -c <name> <name>    Change the name of link" << endl << 
		"      --change" << endl << 
		"  -cb,-cb <browser>       Change the defalt browser" << endl << 
		"      --changebrowser" << endl << 
		"  -d, -d <ID>/<name>      Delete the address by its ID and name" << endl << 
		"      --delete" << endl <<
		"  -h                      Show help" << endl <<
		"      --help" << endl << 
		"  -i                      Install 'tolink' into the computer" << endl <<
		"      --install" << endl <<
		"  -l                      List the all the address with its ID and name" << endl <<
		"      --list" << endl << 
		"  -u                      Uninstall 'tolink' from the computer" << endl <<
		"      --uninstall" << endl << endl <<
		"Report bugs to email: admin@samcompu.com" << endl;
}

bool PROGRAM::start_test(void) {
	string c;
	PROGRAM::open_web("https://www.samcompu.com");
	cout << "Have you open 'https://www.samcompu.com'? (y/n) ";
	cin >> c;
	return c != "n";
}

void PROGRAM::welcome(void) {
	string c = "n";
	cout << "Welcome to use 'tolink'!" << endl << "This is the first time you run this application!" << endl;
	while (c == "n") {
		cout << "Please set your defult browser first: ";
		cin >> PROGRAM::defaltBrowser;
		cout << "Now start your defult browser for checking if is useable." << endl;
		cout << "Type 'y' for starting checking or 'n' for changing defult browser:";
		cin >> c;
	}
	while (!PROGRAM::start_test()) {
		cout << "Sorry about that! It means 'tolink' doesn't support this browser." << endl;
		cout << "Please set another browser: ";
		cin >> PROGRAM::defaltBrowser;
	}
	cout << "Congratulations! You can't use 'tolink' now!" << endl << endl;
}

void PROGRAM::write_config(void) {
	ofstream fout(PROGRAM::configFile);
	if (!fout) PROGRAM::show_wrong(2);
	fout << "[Links]" << endl;
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link t = PROGRAM::link.at(i);
		if (t.deleted) continue;
		fout << t.name << " " << t.path << endl;
	}
	fout << endl;
	fout << "[Defalt Browser]" << endl << PROGRAM::defaltBrowser << endl;
	fout.close();
}

void PROGRAM::add_link(Link t) { 
	if (t.name == "") {
		cout << "Link name: ";
		cin >> t.name;
	}
	PROGRAM::check_name(t.name);
	if (t.path == "") {
		cout << "Link path: ";
		cin >> t.path;
	}
	if (!SERVICE::check_address(t.path)) PROGRAM::show_wrong(4);
	PROGRAM::link.push_back(t); 
}

void PROGRAM::read_config() {
	ifstream fin(PROGRAM::configFile);
	string s;
	fin >> s;
	while (1) {
		Link t;
		t.deleted = false;
		fin >> s, t.name = s;
		fin >> s, t.path = s;
		if (t.name == "[Defalt" && t.path == "Browser]") break;
		if (!SERVICE::check_address(t.path)) {
			cout << 
"---------------------------------------" << endl << 
"|                                     |" << endl << 
"|               WARNING               |" << endl << 
"|                                     |" << endl << 
"| Config file was changed artificial. |" << endl << 
"|     You'd better have a check.      |" << endl << 
"|                                     |" << endl << 
"---------------------------------------" << endl << endl;
			continue;
		}
		PROGRAM::link.push_back(t);
	}
	fin >> PROGRAM::defaltBrowser;
	fin.close();
}

void PROGRAM::list_link() {
	if (!PROGRAM::link.size()) {
		cout << "You don't have any link now!" << endl << "Use '-a' to add one." << endl;
		return ;
	}
	cout << "Link list:" << endl;
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link t = PROGRAM::link.at(i);
		cout << "  " << i << "  " << t.name << "  " << t.path << endl;
	}
	cout << endl << "Defalt browser: " << PROGRAM::defaltBrowser << endl;
}

void PROGRAM::del_link(string s) {
	if (s == "") {
		cout << "Pleace enter the id or name of the link: ";
		cin >> s;
	}
	Link &t = PROGRAM::link.at(PROGRAM::get_id(s));
	string c;
	cout << "Do you want delete '" << t.name << "'? (y/n) ";
	cin >> c;
	if (c == "y" || c == "Y") t.deleted = true;
}

int PROGRAM::get_id(string s) {
	bool isID = true;
	rep(i, 0, s.size() - 1) {
		if (s.at(i) < '0' || s.at(i) > '9') isID = false;
	}
	int res = 0;
	if (isID) {
		res = stoi(s);
		if (res >= (int) PROGRAM::link.size()) PROGRAM::show_wrong(5);
	} else {
		int bestMatch = INF;
		rep(i, 0, PROGRAM::link.size() - 1) {
			Link t = PROGRAM::link.at(i);
			int tMatch = SERVICE::edit_distance(s, t.name);
			if (tMatch == (int) t.name.size()) continue;
			if (tMatch < bestMatch) bestMatch = tMatch, res = i;
		}
		if (bestMatch == INF) PROGRAM::show_wrong(5);
	}
	return res;
}

void PROGRAM::open_web(string s) {
	SERVICE::bash_run(PROGRAM::defaltBrowser + " " + s);
}

void PROGRAM::change_browser(string s) {
	if (s == "") {
		cout << "Please enter the browser you want to change to: ";
		cin >> s;
	}
	PROGRAM::defaltBrowser = s;
}

int PROGRAM::find_link(string s) {
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link t = PROGRAM::link.at(i);
		if (t.path == s) return i;
	}
	return -1;
}

void PROGRAM::open_link(string s) {
	if (SERVICE::check_address(s)) {
		PROGRAM::open_web(s);
		int id = PROGRAM::find_link(s);
		if (id == -1) {
			string c;
			cout << "You haven't saved this link before. Save it? (y/n) ";
			cin >> c;
			if (c != "n") PROGRAM::add_link((Link) {false, "", s});
		} else {
			Link t = PROGRAM::link.at(id);
			cout << "You have saved this link before." << endl << "You can use 'tolink " << t.name << "' to open it next time.";
		}
	}
	else PROGRAM::open_web(PROGRAM::link.at(PROGRAM::get_id(s)).path);
}

void PROGRAM::change_name(int id, string s) {
	string c;
	if (id == -1) {
		cout << "The id or the name of the link: ";
		cin >> c;
		id = PROGRAM::get_id(c);
	}
	Link &t = PROGRAM::link.at(id);
	if (s == "") {
		cout << "New name of the link: ";
		cin >> s;
	}
	PROGRAM::check_name(s);
	cout << "What you change is this:" << endl << "  [" << t.name << "->" << s << "]  " << t.path << endl;
	cout << "Continue? (y/n) ";
	cin >> c;
	if (c == "n") return ;
	t.name = s;
}

void PROGRAM::check_name(string s) {
	rep(i, 0, s.size() - 1) {
		if (!isalpha(s.at(i))) PROGRAM::show_wrong(7);
	}
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link t = PROGRAM::link.at(i);
		if (t.name == s) PROGRAM::show_wrong(6);
	}
}

void PROGRAM::show_wrong(int code) { 
	cout << Error[code] << endl;
	/* cout << "Something went wrong!" << endl << "Error code: " << code << endl << "You can use '-h' to know why." << endl; */ 
	quit();
}

void PROGRAM::quit(void) {
	PROGRAM::write_config();
	exit(0);
}
/* }}} */
