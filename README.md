# SRT-Time-Editor

## Introduction
I've watched a lot of media with .srt files because my native language is Brazilian Portuguese (the best one, obviously). Sometimes, the .srt files I come across are out of sync, so I usually adjust them using VLC's delay or advance functions.

Since I'm on a college break, I decided to build my own SRT time editor, just for fun! :)

## Usage

Compilation:
```
$ g++ -std=c++11 main.cpp -o main
```

Execution:
```
$ ./main -f <path_to_srt_file> -t <time_in_ms> -o <delay|advance>
```

Example:
```
./main -f ./Industry.S01E01.srt -t 1000 -o advance
```

I recommend you watch the Industry (HBO) btw
