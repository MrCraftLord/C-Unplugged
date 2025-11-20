#ifndef SONG_H
#define SONG_H

typedef struct {
    char title[50];
    int duration;
    char artist[50];
    char album[50];
    int id;
} Song;

Song* create_song(const char* title, const char* artist, int duration, const char* album, int id);

#endif
