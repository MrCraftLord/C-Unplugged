# C-Unplugged

A simple music library manager written in C. You can add songs, make albums, create playlists, and save everything to a file.

## What it does

- Add songs to your library with title, artist, album, and duration
- Create albums and add songs to them
- Make playlists and control playback (next/previous)
- Save your library to a file so you don't lose it
- Load your library when you start the program again

## How to build it

Just run:
```bash
make
```

Then run the program:
```bash
./music
```

If you want to clean up:
```bash
make clean
```

## How to use it

When you start the program, type a number for what you want to do:

- Type `1` to add a song
- Type `2` to see all your songs
- Type `9` to create a playlist
- Type `19` to see all commands
- Type `20` to exit

Each song gets an ID number. You'll need that ID to add songs to albums or playlists.

## Example
```
C-Unplugged> 1
Enter Title: Bohemian Rhapsody
Enter Artist: Queen
Enter Album: A Night at the Opera
Enter Duration (seconds): 354
Song Added! ID: 1

C-Unplugged> 2
ID: 1 | Title: Bohemian Rhapsody | Artist: Queen | Album: A Night at the Opera | Duration: 354 sec

C-Unplugged> 17
Library saved to library.txt
```

## Files

- `main.c` - main program
- `include/` - header files
- `src/` - implementation files
- `Makefile` - build instructions

## Saving your data

Use command `17` to save your library. It saves to `library.txt`.
Use command `18` to load it back when you start the program again.

That's it!