#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "song.h"

typedef struct _Node {
    Song* song;
    struct _Node* next;
} Node;

Node* add_to_front(Node* head, Song* song);
Node* add_to_back(Node* head, Song* song);
void print_list(Node* head);
void free_list(Node* head);
Node* remove_song(Node* head, int id);
Song* find_song(Node* head, int id);

#endif
