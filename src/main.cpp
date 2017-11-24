#include <iostream>
#include <algorithm>
#include <string>
#include "View.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2)
	{
		cout << "Usage: ./program_name [sorting_algorithm]";
		return 0;
	}

	string algorithm = argv[1];
	transform(algorithm.begin(), algorithm.end(), algorithm.begin(), ::tolower);
	View view;
	view.init(algorithm);

	return 0;
}