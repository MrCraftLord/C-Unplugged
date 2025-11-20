#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/playlist.h"

Playlist* create_playlist(const char* name) {
    Playlist* playlist = malloc(sizeof(Playlist));
    if (!playlist) {
        return NULL;
    }

    strncpy(playlist->name, name, sizeof(playlist->name) - 1);
    playlist->name[sizeof(playlist->name) - 1] = '\0';

    playlist->songs = NULL;
    playlist->current = NULL;
    playlist->next = NULL;

    return playlist;
}

Playlist* add_playlist(Playlist* head, const char* name) {
    Playlist* playlist = create_playlist(name);
    if (!playlist) {
        return head;
    }

    if (!head) {
        return playlist;
    }

    Playlist* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = playlist;

    return head;
}

Playlist* find_playlist(Playlist* head, const char* name) {
    Playlist* current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void add_song_to_playlist(Playlist* playlist, Song* song) {
    if (!playlist || !song) {
        return;
    }

    Song* copy = create_song(song->title, song->artist, song->duration, song->album, song->id);
    if (!copy) {
        return;
    }

    playlist->songs = add_to_back(playlist->songs, copy);

    if (!playlist->current) {
        playlist->current = playlist->songs;
    }
}

void play_next(Playlist* playlist) {
    if (!playlist || !playlist->current) {
        printf("No song playing.\n");
        return;
    }

    if (!playlist->current->next) {
        playlist->current = playlist->songs;
    } else {
        playlist->current = playlist->current->next;
    }

    printf("Now playing: %s by %s\n",
           playlist->current->song->title,
           playlist->current->song->artist);
}

void play_previous(Playlist* playlist) {
    if (!playlist || !playlist->current) {
        printf("No song playing.\n");
        return;
    }

    if (playlist->current == playlist->songs) {
        Node* current = playlist->songs;
        while (current->next) {
            current = current->next;
        }
        playlist->current = current;
    } else {
        Node* current = playlist->songs;
        while (current->next && current->next != playlist->current) {
            current = current->next;
        }
        playlist->current = current;
    }

    printf("Now playing: %s by %s\n",
           playlist->current->song->title,
           playlist->current->song->artist);
}

void remove_from_playlist(Playlist* playlist, int id) {
    if (!playlist) {
        return;
    }

    if (playlist->current && playlist->current->song->id == id) {
        if (playlist->current->next) {
            playlist->current = playlist->current->next;
        } else {
            playlist->current = playlist->songs;
        }
    }

    playlist->songs = remove_song(playlist->songs, id);
    printf("Song removed from playlist.\n");
}

void add_song_at_position(Playlist* playlist, Song* song, int position) {
    if (!playlist || !song) {
        return;
    }

    Song* copy = create_song(song->title, song->artist, song->duration, song->album, song->id);
    if (!copy) {
        return;
    }

    if (position <= 1 || !playlist->songs) {
        playlist->songs = add_to_front(playlist->songs, copy);
        if (!playlist->current) {
            playlist->current = playlist->songs;
        }
        return;
    }

    Node* current = playlist->songs;
    int index = 1;

    while (current->next && index < position - 1) {
        current = current->next;
        index++;
    }

    Node* node = malloc(sizeof(Node));
    if (!node) {
        free(copy);
        return;
    }

    node->song = copy;
    node->next = current->next;
    current->next = node;
}

void view_playlist(Playlist* playlist) {
    if (!playlist) {
        printf("Playlist not found.\n");
        return;
    }

    printf("\n=== Playlist: %s ===\n", playlist->name);

    if (playlist->current) {
        printf("Currently playing: %s by %s\n\n",
               playlist->current->song->title,
               playlist->current->song->artist);
    }

    print_list(playlist->songs);
}

void list_playlists(Playlist* head) {
    if (!head) {
        printf("No playlists created.\n");
        return;
    }

    printf("\n=== Playlists ===\n");
    Playlist* current = head;
    while (current) {
        printf("- %s\n", current->name);
        current = current->next;
    }
}

void free_playlists(Playlist* head) {
    Playlist* current = head;
    while (current) {
        Playlist* next = current->next;
        free_list(current->songs);
        free(current);
        current = next;
    }
}

Playlist* delete_playlist(Playlist* head, const char* name) {
    if (!head) {
        return NULL;
    }

    if (strcmp(head->name, name) == 0) {
        Playlist* next = head->next;
        free_list(head->songs);
        free(head);
        return next;
    }

    Playlist* current = head;
    while (current->next) {
        if (strcmp(current->next->name, name) == 0) {
            Playlist* to_remove = current->next;
            current->next = to_remove->next;
            free_list(to_remove->songs);
            free(to_remove);
            return head;
        }
        current = current->next;
    }

    return head;
}
