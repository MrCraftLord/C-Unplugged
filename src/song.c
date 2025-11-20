#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/song.h"

Song* create_song(const char* title, const char* artist, int duration, const char* album, int id) {
    Song* song = malloc(sizeof(Song));
    if (!song) {
        return NULL;
    }

    strncpy(song->title, title, sizeof(song->title) - 1);
    song->title[sizeof(song->title) - 1] = '\0';

    strncpy(song->artist, artist, sizeof(song->artist) - 1);
    song->artist[sizeof(song->artist) - 1] = '\0';

    strncpy(song->album, album, sizeof(song->album) - 1);
    song->album[sizeof(song->album) - 1] = '\0';

    song->duration = duration;
    song->id = id;

    return song;
}
