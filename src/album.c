#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/album.h"

Album* create_album(const char* name) {
    Album* album = malloc(sizeof(Album));
    if (!album) {
        return NULL;
    }

    strncpy(album->name, name, sizeof(album->name) - 1);
    album->name[sizeof(album->name) - 1] = '\0';
    album->songs = NULL;
    album->next = NULL;

    return album;
}

Album* add_album(Album* head, const char* name) {
    Album* album = create_album(name);
    if (!album) {
        return head;
    }

    if (!head) {
        return album;
    }

    Album* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = album;
    return head;
}

Album* find_album(Album* head, const char* name) {
    Album* current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void add_song_to_album(Album* album, Song* song) {
    if (!album || !song) {
        return;
    }
    album->songs = add_to_back(album->songs, song);
}

void view_album(Album* album) {
    if (!album) {
        printf("Album not found.\n");
        return;
    }

    printf("\n=== Album: %s ===\n", album->name);
    print_list(album->songs);
}

void list_albums(Album* head) {
    if (!head) {
        printf("No albums created.\n");
        return;
    }

    printf("\n=== Albums ===\n");
    Album* current = head;
    while (current) {
        printf("- %s\n", current->name);
        current = current->next;
    }
}

void free_albums(Album* head) {
    Album* current = head;
    while (current) {
        Album* next = current->next;
        free_list(current->songs);
        free(current);
        current = next;
    }
}

Album* delete_album(Album* head, const char* name) {
    if (!head) {
        return NULL;
    }

    if (strcmp(head->name, name) == 0) {
        Album* next = head->next;
        free_list(head->songs);
        free(head);
        return next;
    }

    Album* current = head;
    while (current->next) {
        if (strcmp(current->next->name, name) == 0) {
            Album* to_remove = current->next;
            current->next = to_remove->next;
            free_list(to_remove->songs);
            free(to_remove);
            return head;
        }
        current = current->next;
    }

    return head;
}
