#pragma once
#include <bits/stdc++.h>

using namespace std;

const string Error[10] = {
	/* Error infor {{{ */
	/*0000*/"",
	/*0001*/"Too much or too less parameter.",
	/*0002*/"Can't create or write the config file.",
	/*0003*/"No such '-' options.",
	/*0004*/"Illegal website address.",
	/*0005*/"No such name or ID.",
	/*0006*/"Already have the name.",
	/*0007*/"Illegal name."
	/* }}} */
};

class Link {
	public:
		bool deleted;
		string name, path;
};
