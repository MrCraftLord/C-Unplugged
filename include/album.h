#ifndef ALBUM_H
#define ALBUM_H

#include "song.h"
#include "linkedlist.h"

typedef struct _Album {
    char name[50];
    Node* songs;
    struct _Album* next;
} Album;

Album* create_album(const char* name);
Album* add_album(Album* head, const char* name);
Album* find_album(Album* head, const char* name);
void add_song_to_album(Album* album, Song* song);
void view_album(Album* album);
void list_albums(Album* head);
void free_albums(Album* head);
Album* delete_album(Album* head, const char* name);

#endif
