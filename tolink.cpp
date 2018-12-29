#include <bits/stdc++.h>

using namespace std;
typedef string PATH;
#define rep(i, a, b) for (int i = (int)a; i <= (int)b; i++)

/* "Error code: " << endl << */
/* "  0001      Too much or too less parameter" << endl << */ 
/* "  0002      Can't create or write the config file" << endl << */
/* "  0003      No such '-' options" << endl << */
/* "  0004      Illegal website address" << endl << */ 
/* "  0005      No such name or ID" << endl << */ 
/* "  0006      Already have the name" << endl << */ 
/* "  0007      Illegal name" << endl << endl << */ 

const string Error[10] = {
	/* Error infor {{{ */
	"",
	"Too much or too less parameter.",
	"Can't create or write the config file.",
	"No such '-' options.",
	"Illegal website address.",
	"No such name or ID.",
	"Already have the name.",
	"Illegal name."
	/* }}} */
};

class Link {
	public:
		bool deleted;
		string name; PATH path;
};

namespace SURVICE {
	PATH HOME; // The path of home dir.
/* Functions {{{*/
	void init(void); // Get the HOME path.
	void bash_run(string); // Give a command and run in bash.
	void show_wrong(int); // Show 'Error', give the error infor and quit.
	void install(); // Install the application into the computer
	void uninstall(); // Uninstall the application from the computer
	bool check_path(string); // Check if there is the designated path.
	bool check_address(string); // Check if it is a legal website address.
	int common_substring(string, string); // Find the len of longest common substring
	string to_string(char *); // Trun char array to string
	string expand_user(string); // Expand '~' to the home path.
/* }}} */
}

namespace PROGRAM {
	PATH configFile; // The path of config file.
	vector<Link>link; // All the link
	string defaltBrowser; // The defalt browser for opening the link.
	/* Functions {{{ */
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
	bool start_test(void); // Start https://www.samcompu.com to check the browser
	int get_id(string); // Find the link by the string
	int find_link(string); // Check if the link is exist and return its ID.
	/* }}} */
}

void quit(void); // Quit the application with some necessary operating.

int main(int argc, char* argv[]) {
	SURVICE::init();
	PROGRAM::init();
	if (argc == 1) {
		PROGRAM::list_link();
		quit();
	}
	string parameter = SURVICE::to_string(argv[1]);
	if (parameter == "-a" || parameter == "--add") {
		if (argc == 2) PROGRAM::add_link((Link) {false, "", ""});
		else if (argc == 4) PROGRAM::add_link((Link) {false, SURVICE::to_string(argv[2]), SURVICE::to_string(argv[3])});
		else SURVICE::show_wrong(1);
	} else if (parameter == "-c" || parameter == "--change") {
		if (argc == 2) PROGRAM::change_name(-1, "");
		else if (argc == 3) PROGRAM::change_name(PROGRAM::get_id(SURVICE::to_string(argv[2])), "");
		else if (argc == 4) PROGRAM::change_name(PROGRAM::get_id(SURVICE::to_string(argv[2])), SURVICE::to_string(argv[3]));
		else SURVICE::show_wrong(1);
	} else if (parameter == "-cb" || parameter == "--changebrowser") {
		if (argc == 2) PROGRAM::change_browser("");
		else if (argc == 3) PROGRAM::change_browser(SURVICE::to_string(argv[2]));
		else SURVICE::show_wrong(1);
	} else if (parameter == "-d" || parameter == "--delete") {
		if (argc == 2) PROGRAM::del_link("");
		else if (argc == 3) PROGRAM::del_link(SURVICE::to_string(argv[2]));
		else SURVICE::show_wrong(1);
	} else if (parameter == "-h" || parameter == "--help") {
		if (argc == 2) PROGRAM::show_help();
		else SURVICE::show_wrong(1);
	} else if (parameter == "-i" || parameter == "--install") {
		if (argc == 2) SURVICE::install();
		else SURVICE::show_wrong(1);
	} else if (parameter == "-l" || parameter == "--list") {
		if (argc == 2) PROGRAM::list_link();
		else SURVICE::show_wrong(1);
	} else if (parameter == "-u" || parameter == "--uninstall") {
		if (argc == 2) SURVICE::uninstall();
		else SURVICE::show_wrong(1);
	} else {
		if (argv[1][0] == '-') SURVICE::show_wrong(3);
		if (argc != 2) SURVICE::show_wrong(1);
		PROGRAM::open_link(SURVICE::to_string(argv[1]));
	}
	quit();
	return 0;
}

void quit(void) {
	PROGRAM::write_config();
	exit(0);
}

/* SURVICE {{{ */
bool SURVICE::check_path(string s) {
	s = SURVICE::expand_user(s);
	ifstream fin(s.data());
	bool ok = !fin;
	fin.close();
	return !ok;
}

bool SURVICE::check_address(string s) { return !min(min(s.find("http://", 0), s.find("https://", 0)), s.find("ftp://", 0)); }

void SURVICE::init(void) { SURVICE::HOME = getenv("HOME"); }

void SURVICE::show_wrong(int code) { 
	cout << Error[code] << endl;
	/* cout << "Something went wrong!" << endl << "Error code: " << code << endl << "You can use '-h' to know why." << endl; */ 
	quit();
}

string SURVICE::expand_user(string s) {
	if (s.at(0) == '~') s.replace(0, 1, SURVICE::HOME);
	return s;
}

void SURVICE::bash_run(string s) { system(s.data()); }

string SURVICE::to_string(char *c) {
	string s = c;
	return s;
}

void SURVICE::install() {
	SURVICE::bash_run("sudo cp tolink /usr/bin");
	string c;
	cout << "Do you want to alias 'tolink' to 'to'? (y/n) ";
	cin >> c;
	if (c != "y" || c != "Y") return ;
	if (SURVICE::check_path("~/.zshrc"))
		SURVICE::bash_run("echo 'alias to=\"tolink\"' >> ~/.zshrc");
	if (SURVICE::check_path("~/.bashrc"))
		SURVICE::bash_run("echo 'alias to=\"tolink\"' >> ~/.bashrc");
}

void SURVICE::uninstall() {
	SURVICE::bash_run("sudo rm /usr/bin/tolink");
}

int SURVICE::common_substring(string a, string b) {
	a.push_back('#'), b.push_back('#');
	int res = 0, t = 0, last = 0;
	rep(i, 0, b.size() - 1) {
		if (a.at(t) == b.at(i)) {
			res -= i - last;
			last = i;
			t++;
		}
	}
	return res + t * b.size();
}
/* }}} */

/* PROGRAM {{{ */
void PROGRAM::init(void) {
	string configPath = SURVICE::HOME + "/.config/tolink";
	if (!SURVICE::check_path(configPath)) {
		SURVICE::bash_run("mkdir " + configPath);
		if (!SURVICE::check_path(configPath)) SURVICE::show_wrong(2);
	}
	PROGRAM::configFile = SURVICE::HOME + "/.config/tolink/init.cfg";
	if (!SURVICE::check_path(PROGRAM::configFile)) PROGRAM::welcome();
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
	if (!fout) SURVICE::show_wrong(2);
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
	if (!SURVICE::check_address(t.path)) SURVICE::show_wrong(4);
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
		if (!SURVICE::check_address(t.path)) {
			cout << "----" << "Wronging: Some config files has been changed artificial." << endl << "You'd better have a check." << "----" << endl;
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
		if (res >= (int) PROGRAM::link.size()) SURVICE::show_wrong(5);
	} else {
		int maxSame = 0;
		rep(i, 0, PROGRAM::link.size() - 1) {
			Link t = PROGRAM::link.at(i);
			int tSame = SURVICE::common_substring(t.name, s);
			if (tSame > maxSame) maxSame = tSame, res = i;
		}
	}
	return res;
}

void PROGRAM::open_web(string s) {
	SURVICE::bash_run(PROGRAM::defaltBrowser + " " + s);
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
	if (SURVICE::check_address(s)) {
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
		if (!isalpha(s.at(i))) SURVICE::show_wrong(7);
	}
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link t = PROGRAM::link.at(i);
		if (t.name == s) SURVICE::show_wrong(6);
	}
}
/* }}} */
