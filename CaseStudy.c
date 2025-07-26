#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// Define music file paths
const char *music_files[] = {
    "song1.mp3",
    "song2.mp3",
    "song3.mp3",
    "song4.mp3",
    "song5.mp3"
};

// Define song titles
const char *song_titles[] = {
    "Mocking Bard",
    "Kites",
    "Faded",
    "Whistle",
    "Violin"
};

const int num_files = sizeof(music_files) / sizeof(music_files[0]);
HANDLE music_process = NULL;
HANDLE music_thread = NULL;

// Function to play music in a separate thread
DWORD WINAPI play_music(LPVOID file) {
    const char *music_file = (const char *)file;
    printf("Playing: %s\n", music_file);
    char command[512];
    snprintf(command, sizeof(command), "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\" --intf dummy \"%s\" vlc://quit", music_file);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Failed to start VLC process.\n");
        return 1;
    }
    music_process = pi.hProcess;
    WaitForSingleObject(music_process, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(music_process);
    music_process = NULL;
    return 0;
}

// Function to stop the currently playing music
void stop_music() {
    if (music_process != NULL) {
        TerminateProcess(music_process, 0);
        CloseHandle(music_process);
        music_process = NULL;
        printf("Music stopped.\n");
    }
    if (music_thread != NULL) {
        WaitForSingleObject(music_thread, INFINITE);
        CloseHandle(music_thread);
        music_thread = NULL;
    }
}

// Function to play a specific song based on index
void play_selected_music(int index) {
    stop_music(); // Ensure the current song is stopped
    music_thread = CreateThread(NULL, 0, play_music, (LPVOID)music_files[index], 0, NULL);
    if (music_thread == NULL) {
        printf("Failed to create music thread.\n");
    }
}

// Function to play a random song
void play_random_music() {
    stop_music(); // Ensure the current song is stopped
    srand((unsigned int)time(NULL)); // Seed random number generator
    int random_index = rand() % num_files;
    play_selected_music(random_index);
}

// Main function
int main() {
    int choice;
    printf("Random Music Player\n");
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Play a specific song\n");
        printf("2. Play a random song\n");
        printf("3. Stop playing\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Clear input buffer
        if (choice == 1) {
            printf("Select a song:\n");
            for (int i = 0; i < num_files; i++) {
                printf("%d. %s\n", i + 1, song_titles[i]);
            }
            printf("Enter song number: ");
            int song_choice;
            scanf("%d", &song_choice);
            while (getchar() != '\n'); // Clear input buffer
            if (song_choice >= 1 && song_choice <= num_files) {
                play_selected_music(song_choice - 1);
            } else {
                printf("Invalid song number.\n");
            }
        } else if (choice == 2) {
            play_random_music();
        } else if (choice == 3) {
            stop_music();
        } else if (choice == 4) {
            stop_music();
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    printf("Exiting Music Player\n");
    return 0;
}
