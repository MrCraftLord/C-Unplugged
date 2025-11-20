#ifndef IO_H
#define IO_H

#include "song.h"
#include "linkedlist.h"

void save_library(Node* head, const char* filename);
Node* load_library(const char* filename);
void log_command(int command);

#endif
