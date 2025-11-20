#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"
#include "linkedlist.h"

typedef struct _Playlist {
    char name[50];
    Node* songs;
    Node* current;
    struct _Playlist* next;
} Playlist;

Playlist* create_playlist(const char* name);
Playlist* add_playlist(Playlist* head, const char* name);
Playlist* find_playlist(Playlist* head, const char* name);
void add_song_to_playlist(Playlist* playlist, Song* song);
void play_next(Playlist* playlist);
void play_previous(Playlist* playlist);
void remove_from_playlist(Playlist* playlist, int id);
void add_song_at_position(Playlist* playlist, Song* song, int position);
void view_playlist(Playlist* playlist);
void list_playlists(Playlist* head);
void free_playlists(Playlist* head);
Playlist* delete_playlist(Playlist* head, const char* name);

#endif
