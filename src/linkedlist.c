#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linkedlist.h"

Node* add_to_front(Node* head, Song* song) {
    Node* node = malloc(sizeof(Node));
    if (!node) {
        return head;
    }
    node->song = song;
    node->next = head;
    return node;
}

Node* add_to_back(Node* head, Song* song) {
    Node* node = malloc(sizeof(Node));
    if (!node) {
        return head;
    }
    node->song = song;
    node->next = NULL;

    if (!head) {
        return node;
    }

    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
    return head;
}

void print_list(Node* head) {
    if (!head) {
        printf("No songs in library.\n");
        return;
    }

    Node* current = head;
    while (current) {
        printf("ID: %d | Title: %s | Artist: %s | Album: %s | Duration: %d sec\n",
               current->song->id,
               current->song->title,
               current->song->artist,
               current->song->album,
               current->song->duration);
        current = current->next;
    }
}

void free_list(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current->song);
        free(current);
        current = next;
    }
}

Node* remove_song(Node* head, int id) {
    if (!head) {
        return NULL;
    }

    if (head->song->id == id) {
        Node* next = head->next;
        free(head->song);
        free(head);
        return next;
    }

    Node* current = head;
    while (current->next) {
        if (current->next->song->id == id) {
            Node* to_remove = current->next;
            current->next = to_remove->next;
            free(to_remove->song);
            free(to_remove);
            return head;
        }
        current = current->next;
    }

    return head;
}

Song* find_song(Node* head, int id) {
    Node* current = head;
    while (current) {
        if (current->song->id == id) {
            return current->song;
        }
        current = current->next;
    }
    return NULL;
}
