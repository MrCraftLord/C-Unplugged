#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/song.h"
#include "include/linkedlist.h"
#include "include/io.h"
#include "include/album.h"
#include "include/playlist.h"

static void read_line(const char* prompt, char* buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        if (size > 0) {
            buffer[0] = '\0';
        }
    }
}

static int read_int(const char* prompt) {
    int value;
    char line[64];

    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            return 0;
        }
        if (sscanf(line, "%d", &value) == 1) {
            return value;
        }
        printf("Please enter a valid number.\n");
    }
}

static void print_menu(void) {
    printf("\n========== C-Unplugged Menu ==========\n");
    printf("1.  Add Song\n");
    printf("2.  List Songs\n");
    printf("3.  Delete Song\n");
    printf("4.  Create Album\n");
    printf("5.  Add Song to Album\n");
    printf("6.  View Album\n");
    printf("7.  List Albums\n");
    printf("8.  Delete Album\n");
    printf("9.  Create Playlist\n");
    printf("10. Add Song to Playlist\n");
    printf("11. View Playlist\n");
    printf("12. List Playlists\n");
    printf("13. Play Next\n");
    printf("14. Play Previous\n");
    printf("15. Remove from Playlist\n");
    printf("16. Delete Playlist\n");
    printf("17. Save Library\n");
    printf("18. Load Library\n");
    printf("19. Help\n");
    printf("20. Exit\n");
    printf("======================================\n");
}

static void print_help(void) {
    printf("\nCommands:\n");
    printf("1  - Add a new song to the library\n");
    printf("2  - List all songs in the library\n");
    printf("3  - Delete a song by ID\n");
    printf("4  - Create a new album\n");
    printf("5  - Add a song to an album\n");
    printf("6  - View songs in an album\n");
    printf("7  - List all albums\n");
    printf("8  - Delete an album\n");
    printf("9  - Create a new playlist\n");
    printf("10 - Add a song to a playlist\n");
    printf("11 - View a playlist\n");
    printf("12 - List all playlists\n");
    printf("13 - Play next song in current playlist\n");
    printf("14 - Play previous song in current playlist\n");
    printf("15 - Remove a song from the current playlist\n");
    printf("16 - Delete a playlist\n");
    printf("17 - Save the song library to a file\n");
    printf("18 - Load the song library from a file\n");
    printf("19 - Show this help menu\n");
    printf("20 - Exit the program\n");
}

static int get_max_id(Node* library) {
    int max_id = 0;
    Node* current = library;
    while (current) {
        if (current->song->id > max_id) {
            max_id = current->song->id;
        }
        current = current->next;
    }
    return max_id;
}

int main(void) {
    Node* library = NULL;
    Album* albums = NULL;
    Playlist* playlists = NULL;
    Playlist* current_playlist = NULL;

    int next_id = 1;
    int running = 1;

    printf("C-Unplugged Music Manager\n");
    printf("Type 19 for help.\n");

    while (running) {
        print_menu();

        int choice = read_int("\nC-Unplugged> ");
        log_command(choice);

        if (choice == 1) {
            char title[50];
            char artist[50];
            char album_name[50];
            int duration;

            read_line("Enter Title: ", title, sizeof(title));
            read_line("Enter Artist: ", artist, sizeof(artist));
            read_line("Enter Album: ", album_name, sizeof(album_name));
            duration = read_int("Enter Duration (seconds): ");

            Song* song = create_song(title, artist, duration, album_name, next_id);
            if (!song) {
                printf("Could not create song.\n");
                continue;
            }

            library = add_to_back(library, song);
            printf("Song added. ID: %d\n", next_id);
            next_id++;
        } else if (choice == 2) {
            print_list(library);
        } else if (choice == 3) {
            int id = read_int("Enter Song ID to delete: ");
            library = remove_song(library, id);
            printf("If the song existed, it has been removed.\n");
        } else if (choice == 4) {
            char name[50];
            read_line("Enter Album Name: ", name, sizeof(name));
            albums = add_album(albums, name);
            printf("Album created.\n");
        } else if (choice == 5) {
            char album_name[50];
            int id;

            read_line("Enter Album Name: ", album_name, sizeof(album_name));
            Album* album = find_album(albums, album_name);
            if (!album) {
                printf("Album not found.\n");
                continue;
            }

            id = read_int("Enter Song ID to add: ");
            Song* song = find_song(library, id);
            if (!song) {
                printf("Song not found.\n");
                continue;
            }

            add_song_to_album(album, song);
            printf("Song added to album.\n");
        } else if (choice == 6) {
            char name[50];
            read_line("Enter Album Name: ", name, sizeof(name));
            Album* album = find_album(albums, name);
            view_album(album);
        } else if (choice == 7) {
            list_albums(albums);
        } else if (choice == 8) {
            char name[50];
            read_line("Enter Album Name to delete: ", name, sizeof(name));
            albums = delete_album(albums, name);
            printf("If the album existed, it has been deleted.\n");
        } else if (choice == 9) {
            char name[50];
            read_line("Enter Playlist Name: ", name, sizeof(name));
            playlists = add_playlist(playlists, name);
            current_playlist = find_playlist(playlists, name);
            printf("Playlist created.\n");
        } else if (choice == 10) {
            char name[50];
            int id;

            read_line("Enter Playlist Name: ", name, sizeof(name));
            Playlist* playlist = find_playlist(playlists, name);
            if (!playlist) {
                printf("Playlist not found.\n");
                continue;
            }

            id = read_int("Enter Song ID to add: ");
            Song* song = find_song(library, id);
            if (!song) {
                printf("Song not found.\n");
                continue;
            }

            add_song_to_playlist(playlist, song);
            current_playlist = playlist;
            printf("Song added to playlist.\n");
        } else if (choice == 11) {
            char name[50];
            read_line("Enter Playlist Name: ", name, sizeof(name));
            Playlist* playlist = find_playlist(playlists, name);
            if (!playlist) {
                printf("Playlist not found.\n");
                continue;
            }
            current_playlist = playlist;
            view_playlist(playlist);
        } else if (choice == 12) {
            list_playlists(playlists);
        } else if (choice == 13) {
            if (!current_playlist) {
                char name[50];
                read_line("Enter Playlist Name to play: ", name, sizeof(name));
                current_playlist = find_playlist(playlists, name);
            }
            if (!current_playlist) {
                printf("No current playlist selected.\n");
            } else {
                play_next(current_playlist);
            }
        } else if (choice == 14) {
            if (!current_playlist) {
                char name[50];
                read_line("Enter Playlist Name to play: ", name, sizeof(name));
                current_playlist = find_playlist(playlists, name);
            }
            if (!current_playlist) {
                printf("No current playlist selected.\n");
            } else {
                play_previous(current_playlist);
            }
        } else if (choice == 15) {
            if (!current_playlist) {
                char name[50];
                read_line("Enter Playlist Name: ", name, sizeof(name));
                current_playlist = find_playlist(playlists, name);
            }
            if (!current_playlist) {
                printf("No current playlist selected.\n");
            } else {
                int id = read_int("Enter Song ID to remove from playlist: ");
                remove_from_playlist(current_playlist, id);
            }
        } else if (choice == 16) {
            char name[50];
            read_line("Enter Playlist Name to delete: ", name, sizeof(name));
            if (current_playlist && strcmp(current_playlist->name, name) == 0) {
                current_playlist = NULL;
            }
            playlists = delete_playlist(playlists, name);
            printf("If the playlist existed, it has been deleted.\n");
        } else if (choice == 17) {
            save_library(library, "library.txt");
        } else if (choice == 18) {
            free_list(library);
            library = load_library("library.txt");
            next_id = get_max_id(library) + 1;
        } else if (choice == 19) {
            print_help();
        } else if (choice == 20) {
            running = 0;
        } else {
            printf("Invalid choice. Type 19 for help.\n");
        }
    }

    free_list(library);
    free_albums(albums);
    free_playlists(playlists);

    return 0;
}
