# 🎵 Music Playback Program

A dynamic and interactive C-based music playback program built using multithreading and system-level programming. This project showcases how multiple audio tracks can be handled with randomized playback for a fun and engaging user experience!

## 🚀 Features

- 🎶 Random music track playback
- 🔁 Continuous looping or shuffle modes
- ⏱️ Multi-threaded design for non-blocking UI
- 📁 Easy track management via directory scanning
- 🖥️ Terminal-based UI (lightweight and fast)

## 🛠️ Built With

- **C Programming Language**
- **POSIX Threads (pthreads)**
- **System calls** for file handling and process control
- **GCC / Clang** for compilation

## 📂 Project Structure
```bash
Music-Playback/
├── Makefile
├── README.md
├── player.c # Main source file
├── music/ # Directory containing .mp3 or .wav files
├── include/ # Header files (optional)
└── bin/ # Compiled output
```

## 📦 Setup & Usage

### 1. Clone the Repository
```bash
git clone https://github.com/JnanaranjanMajhi/Music-Playback.git
cd Music-Playback
```
### 2. Add Music Files
Place your .wav or .mp3 files inside the music/ directory.
### 3. Compile the Code
Make sure you have GCC installed:
```bash
make
```
### 4. Run the Program
```bash
./bin/player
```
✅ Dependencies
GCC or Clang
POSIX-compatible OS (Linux, macOS)
mpg123 or aplay for actual audio output (if using system call for playback)
You may install mpg123 using:
```bash
sudo apt install mpg123
```

🧠 Concepts Demonstrated
- Thread synchronization using mutexes
- File system navigation using opendir, readdir
- Process control and signal handling
- Command-line interface design

📜 License
This project is licensed under the MIT License[License]
