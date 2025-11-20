#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/io.h"

void save_library(Node* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error saving library.\n");
        return;
    }

    Node* current = head;
    while (current) {
        fprintf(file, "%d|%s|%s|%s|%d\n",
                current->song->id,
                current->song->title,
                current->song->artist,
                current->song->album,
                current->song->duration);
        current = current->next;
    }

    fclose(file);
    printf("Library saved to %s\n", filename);
}

Node* load_library(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No saved library found.\n");
        return NULL;
    }

    Node* head = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        int id;
        int duration;
        char title[50];
        char artist[50];
        char album[50];

        if (sscanf(line, "%d|%49[^|]|%49[^|]|%49[^|]|%d",
                   &id, title, artist, album, &duration) == 5) {
            Song* song = create_song(title, artist, duration, album, id);
            if (song) {
                head = add_to_back(head, song);
            }
        }
    }

    fclose(file);
    printf("Library loaded from %s\n", filename);
    return head;
}

void log_command(int command) {
    FILE* file = fopen("command_log.txt", "a");
    if (!file) {
        printf("Error writing to command log.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    if (t) {
        fprintf(file,
                "[%04d-%02d-%02d %02d:%02d:%02d] Command %d executed\n",
                t->tm_year + 1900,
                t->tm_mon + 1,
                t->tm_mday,
                t->tm_hour,
                t->tm_min,
                t->tm_sec,
                command);
    } else {
        fprintf(file, "[unknown time] Command %d executed\n", command);
    }

    fclose(file);
}
