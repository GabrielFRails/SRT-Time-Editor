# SRT-Time-Editor

## Introduction
I use to watch a lot of media with .srt files together because my mother language is
Brasil Portuguese (the better one). Sometimes the .srt files i find are out of sync
and i just use the vlc function to delay or advance the subtitles.

Since i'm on college break, i decided to build my own srt time editor, just for fun :)

## Usage

compilation:
```
$ g++ -std=c++11 main.cpp -o main
```

exec:
```
$ ./main -f <srt file path> -t <time in ms> -o <delay|advance>
```

example:
```
./main -f ./Industry.S01E01.srt -t 1000 -o advance
```

I recommend you watch the Industry (HBO) btw