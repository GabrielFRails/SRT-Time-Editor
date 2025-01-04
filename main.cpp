#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream srtFile("./Industry.S01E01.srt");
	if (!srtFile.is_open()) {
		cerr << "Was not possible open the srt file" << endl;
		return 1;
	}

	string line;
	while (getline(srtFile, line)) {
		if (line.find("-->") != string::npos) {
			cout << line << endl;
		}
	}

	srtFile.close();
	return 0;
}