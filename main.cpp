#include <iostream>
#include <fstream>
#include <string>

#define STR_TIME_PATTERN "-->"
#define ERROR_FILE_OPEN "Was not possible open the srt file"

using namespace std;

int main() {
	ifstream srtFile("./Industry.S01E01.srt");
	if (!srtFile.is_open()) {
		cerr << ERROR_FILE_OPEN << endl;
		return 1;
	}

	string line;
	while (getline(srtFile, line)) {
		if (line.find(STR_TIME_PATTERN) != string::npos) {
			cout << line << endl;
		}
	}

	srtFile.close();
	return 0;
}