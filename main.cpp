#include <bits/stdc++.h>
#include "init.h"
#include "service.h"
#include "program.h"

using namespace std;

int main(int argc, char* argv[]) {
	SERVICE::init();
	PROGRAM::init(); 
	if (argc == 1) {
		PROGRAM::list_link();
		PROGRAM::quit();
	}
	string parameter = SERVICE::to_string(argv[1]);
	if (parameter == "-a" || parameter == "--add") {
		if (argc == 2) PROGRAM::add_link((Link) {false, "", ""});
		else if (argc == 4) PROGRAM::add_link((Link) {false, SERVICE::to_string(argv[2]), SERVICE::to_string(argv[3])});
		else PROGRAM::show_wrong(1);
	} 
	else if (parameter == "-c" || parameter == "--change") {
		if (argc == 2) PROGRAM::change_name(-1, "");
		else if (argc == 3) PROGRAM::change_name(PROGRAM::get_id(SERVICE::to_string(argv[2])), "");
		else if (argc == 4) PROGRAM::change_name(PROGRAM::get_id(SERVICE::to_string(argv[2])), SERVICE::to_string(argv[3]));
		else PROGRAM::show_wrong(1);
	} 
	else if (parameter == "-d" || parameter == "--delete") {
		if (argc == 2) PROGRAM::del_link("");
		else if (argc == 3) PROGRAM::del_link(SERVICE::to_string(argv[2]));
		else PROGRAM::show_wrong(1);
	} 
	else if (parameter == "-h" || parameter == "--help") {
		if (argc == 2) PROGRAM::show_help();
		else PROGRAM::show_wrong(1);
	} 
	else if (parameter == "-l" || parameter == "--list") {
		if (argc == 2) PROGRAM::list_link();
		else PROGRAM::show_wrong(1);
	} 
	else if (parameter == "-s" || parameter == "--search") {
		if (argc == 2) PROGRAM::search_link("");
		else if (argc == 3) PROGRAM::search_link(SERVICE::to_string(argv[2]));
		else PROGRAM::show_wrong(1);
	} 
	else if (parameter == "--changebrowser") {
		if (argc == 2) PROGRAM::change_browser("");
		else if (argc == 3) PROGRAM::change_browser(SERVICE::to_string(argv[2]));
		else PROGRAM::show_wrong(1);
	} 
	else if (parameter == "--install") {
		if (argc == 2) PROGRAM::install();
		else PROGRAM::show_wrong(1);
	} 
	else if (parameter == "--uninstall") {
		if (argc == 2) PROGRAM::uninstall();
		else PROGRAM::show_wrong(1);
	} 
	else if (parameter == "--update") {
		if (argc == 2) PROGRAM::update();
		else PROGRAM::show_wrong(1);
	}
	else {
		if (argv[1][0] == '-') PROGRAM::show_wrong(3);
		if (argc != 2) PROGRAM::show_wrong(1);
		PROGRAM::open_link(SERVICE::to_string(argv[1]));
	}
	PROGRAM::write_config();
	return 0;
}

