#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h> // Para getopt

#define STR_TIME_PATTERN "-->"
#define ERROR_FILE_OPEN "Was not possible open the srt file"
#define ERROR_RIGHT_USE "Usage: -f <caminho_do_srt> -t <milissegundos> -o <delay|advance>"

using namespace std;

// Função para converter string de tempo para milissegundos
long long timeToMs(const string& timeStr) {
    istringstream iss(timeStr);
    int hours, minutes, seconds, milliseconds;
    char discard;
    iss >> hours >> discard >> minutes >> discard >> seconds >> discard >> milliseconds;
    return hours * 3600000LL + minutes * 60000LL + seconds * 1000LL + milliseconds;
}

// Função para converter milissegundos para string de tempo
string msToTime(long long ms) {
    int hours = ms / 3600000;
    ms %= 3600000;
    int minutes = ms / 60000;
    ms %= 60000;
    int seconds = ms / 1000;
    int milliseconds = ms % 1000;
    
    ostringstream oss;
    oss << setfill('0') << setw(2) << hours << ":" 
        << setfill('0') << setw(2) << minutes << ":" 
        << setfill('0') << setw(2) << seconds << "," 
        << setfill('0') << setw(3) << milliseconds;
    return oss.str();
}

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

	string outputPath = filePath + ".new.srt"; // Nome do arquivo de saída
    ofstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        cerr << "Não foi possível criar o arquivo de saída." << endl;
        return 1;
    }

	string line;
	while (getline(srtFile, line)) {
		if (line.find("-->") != string::npos) {
			size_t start = line.find_first_not_of(" \t");
			size_t end = line.find_last_not_of(" \t");
			if (start != string::npos && end != string::npos) {
				string timePart = line.substr(start, end - start + 1);
				size_t arrowPos = timePart.find("-->");
				string startTime = timePart.substr(0, arrowPos - 1);
				string endTime = timePart.substr(arrowPos + 4);

				long long startMs = timeToMs(startTime);
				long long endMs = timeToMs(endTime);
				
				if (operation == "delay") {
					startMs += timeShift;
					endMs += timeShift;
				} else if (operation == "advance") {
					startMs -= timeShift;
					endMs -= timeShift;
				}

				// Garantir que o tempo não seja negativo
				startMs = max(startMs, 0LL);
				endMs = max(endMs, 0LL);

				string newStartTime = msToTime(startMs);
				string newEndTime = msToTime(endMs);

				// Reconstruir a linha com o novo tempo
				line.replace(start + arrowPos - 1, arrowPos + 4, newStartTime + " --> " + newEndTime);
			}
		}
		outputFile << line << endl;
	}

	srtFile.close();
	return 0;
}