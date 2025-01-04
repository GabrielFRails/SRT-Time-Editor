#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#define STR_TIME_PATTERN "-->"
#define ERROR_FILE_OPEN "Was not possible open the srt file"
#define ERROR_RIGHT_USE "Usage: -f <caminho_do_srt> -t <milissegundos> -o <delay|advance>"

using namespace std;

int main(int argc, char *argv[]) {
	string filePath;
	int timeShift = 0;
	string operation;

	int opt;
	while((opt = getopt(argc, argv, "f:t:o:")) != -1) {
		switch (opt) {
			case 'f':
				filePath = optarg;
				break;
			case 't':
				timeShift = atoi(optarg);
				break;
			case 'o':
				operation = optarg;
				break;
			default:
				cerr << ERROR_RIGHT_USE << endl;
				return 1;
		}
	}

	if (filePath.empty() || timeShift == 0 || operation.empty()) {
		cerr << ERROR_RIGHT_USE << endl;
		return 1;
	}

	ifstream srtFile(filePath);
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