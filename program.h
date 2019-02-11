#pragma once
#include <bits/stdc++.h>
#include "init.h"
#include "service.h"

using namespace std;

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
	void search_link(string); // Search the related link.
	void del_link(string); // Delete the designated link.
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
	void install(); // Install the application into the computer
	void uninstall(); // Uninstall the application from the computer
	void update(); // Update the application to the latest version
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
	if (SERVICE::check_path("./doc/help")) SERVICE::bash_run("cat ./doc/help");
	else SERVICE::bash_run("cat /usr/share/tolink/doc/help");
}

bool PROGRAM::start_test(void) {
	string c;
	PROGRAM::open_web("https://www.samcompu.com");
	cout << "Have you open 'https://www.samcompu.com'? (y/n) ";
	cin >> c;
	cin.ignore();
	return c != "n";
}

void PROGRAM::welcome(void) {
	string c = "n";
	cout << "Welcome to use 'tolink'!" << endl << "This is the first time you run this application!" << endl;
	/* while (c == "n") { */
	/* 	cout << "Where do you want to save your config file? [~/.config/tolink/init.cfg] " << endl; */
	/* } */
	while (c == "n") {
		cout << "Please set your defult browser first: ";
		cin >> PROGRAM::defaltBrowser;
		cin.ignore();
		cout << "Now start your defult browser for checking if is useable." << endl;
		cout << "Type 'y' for starting checking or 'n' for changing defult browser:";
		cin >> c;
		cin.ignore();
	}
	while (!PROGRAM::start_test()) {
		cout << "Sorry about that! It means 'tolink' doesn't support this browser." << endl;
		cout << "Please set another browser: ";
		cin >> PROGRAM::defaltBrowser;
		cin.ignore();
	}
	cout << "Congratulations! You can't use 'tolink' now!" << endl << endl;
}

void PROGRAM::write_config(void) {
	ofstream fout(PROGRAM::configFile.data());
	if (!fout) PROGRAM::show_wrong(2);
	fout << "[Links]" << endl;
	for (int i = 0; i < (int) PROGRAM::link.size(); i++) {
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
		cin.ignore();
	}
	PROGRAM::check_name(t.name);
	if (t.path == "") {
		cout << "Link path: ";
		cin >> t.path;
		cin.ignore();
	}
	if (!SERVICE::check_address(t.path)) PROGRAM::show_wrong(4);
	PROGRAM::link.push_back(t); }

void PROGRAM::read_config() {
	ifstream fin(PROGRAM::configFile.data());
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
	for (int i = 0; i < (int) PROGRAM::link.size(); i++) {
		Link t = PROGRAM::link.at(i);
		cout << "  " << i << "  " << t.name << "  " << t.path << endl;
	}
	cout << endl << "Defalt browser: " << PROGRAM::defaltBrowser << endl;
}

void PROGRAM::del_link(string s) {
	if (s == "") {
		cout << "Pleace enter the id or name of the link: ";
		cin >> s;
		cin.ignore();
	}
	Link &t = PROGRAM::link.at(PROGRAM::get_id(s));
	cout << "Do you want delete '" << t.name << "'? (y/[n]) ";
	char c = SERVICE::read_single_char();
	if (c != 'y' && c != 'Y') return ;
	t.deleted = true;
	cout << "Link has deleted." << endl;
}

int PROGRAM::get_id(string s) {
	bool isID = true;
	for (int i = 0; i < (int) s.size(); i++) {
		if (s.at(i) < '0' || s.at(i) > '9') isID = false;
	}
	int res = 0;
	if (isID) {
		for (int i = (int) s.size() - 1; i >= 0; i--) res = res * 10 + s.at(i) - '0';
		if (res >= (int) PROGRAM::link.size()) PROGRAM::show_wrong(5);
	} else {
		int bestMatch = INF;
		for (int i = 0; i < (int) PROGRAM::link.size(); i++) {
			Link t = PROGRAM::link.at(i);
			if (SERVICE::edit_distance(s, t.name) == (int) max(s.size(), t.name.size())) continue;
			int tMatch = SERVICE::common_distance(s, t.name);
			if (tMatch < bestMatch) bestMatch = tMatch, res = i;
		}
		if (bestMatch == INF) PROGRAM::show_wrong(5);
	}
	return res;
}

void PROGRAM::open_web(string s) {
	SERVICE::bash_run(PROGRAM::defaltBrowser + " \"" + s + "\"");
}

void PROGRAM::change_browser(string s) {
	if (s == "") {
		cout << "Please enter the browser you want to change to: ";
		cin >> s;
		cin.ignore();
	}
	PROGRAM::defaltBrowser = s;
}

int PROGRAM::find_link(string s) {
	for (int i = 0; i < (int) PROGRAM::link.size(); i++) {
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
			cout << "You haven't saved this link before. Save it? ([y]/n) ";
			char c = SERVICE::read_single_char();
			if (c != 'n' && c != 'N') PROGRAM::add_link((Link) {false, "", s});
		} else {
			Link t = PROGRAM::link.at(id);
			cout << "You have saved this link before." << endl << "You can use 'tolink " << t.name << "' to open it next time.";
		}
	}
	else PROGRAM::open_web(PROGRAM::link.at(PROGRAM::get_id(s)).path);
}

void PROGRAM::change_name(int id, string s) {
	if (id == -1) {
		cout << "The id or the name of the link: ";
		string tmp;
		cin >> tmp;
		cin.ignore();
		id = PROGRAM::get_id(tmp);
	}
	Link &t = PROGRAM::link.at(id);
	if (s == "") {
		cout << "New name of the link: ";
		cin >> s;
		cin.ignore();
	}
	PROGRAM::check_name(s);
	cout << "What you change is this:" << endl << "  [" << t.name << "->" << s << "]  " << t.path << endl;
	cout << "Continue? (y/[n]) ";
	char c = SERVICE::read_single_char();
	if (c != 'y' && c != 'Y') return ;
	t.name = s;
	cout << "Link name has changed." << endl;
}

void PROGRAM::check_name(string s) {
	for (int i = 0; i < (int) s.size(); i++) {
		if (!isalpha(s.at(i))) PROGRAM::show_wrong(7);
	}
	for (int i = 0; i < (int) PROGRAM::link.size(); i++) {
		Link t = PROGRAM::link.at(i);
		if (t.name == s) PROGRAM::show_wrong(6);
	}
}

void PROGRAM::show_wrong(int code) { 
	cout << Error[code] << endl;
	quit();
}

void PROGRAM::quit(void) {
	PROGRAM::write_config();
	exit(0);
}

void PROGRAM::search_link(string s) {
	if (s == "") {
		cout << "Search Key: ";
		cin >> s;
		cin.ignore();
	}
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >aboutLink;
	for (int i = 0; i < (int) PROGRAM::link.size(); i++) {
		Link t = PROGRAM::link.at(i);
		if (SERVICE::edit_distance(s, t.name) == (int)max(s.size(), t.name.size())) continue;
		aboutLink.push(make_pair(SERVICE::common_distance(s, t.name), i));
	}
	cout << "Search result:" << endl;
	int resultNum = 0;
	while (!aboutLink.empty()) {
		pair<int, int> f = aboutLink.top();
		aboutLink.pop();
		Link t = PROGRAM::link.at(f.second);
		cout << "  " << f.second << "  ", SERVICE::match_print(t.name, s), cout << " " << t.path << endl;
		resultNum++;
		if (resultNum == 10) {
			cout << "Continue? ([y]/n) ";
			char c = SERVICE::read_single_char();
			if (c != 'n' && c != 'N') break;
			cout << "\033[1A"; // Move the mouse to the begining of line.
			resultNum = 0;
		}
	}
}

void PROGRAM::uninstall() {
	if (SERVICE::check_path("./src/uninstall.sh")) SERVICE::bash_run("./src/uninstall.sh");
	else SERVICE::bash_run("/usr/share/tolink/src/uninstall.sh");
}

void PROGRAM::install() {
	SERVICE::bash_run("./src/install.sh");
}

void PROGRAM::update() {
	if (SERVICE::check_path("./src/update.sh")) SERVICE::bash_run("./src/update.sh");
	else SERVICE::bash_run("/usr/share/tolink/src/update.sh");
}
/* }}} */
