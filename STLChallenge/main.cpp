// Section 20
// Challenge 2
//  Lists

#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
#include <fstream>

class Song {
    friend std::ostream& operator<<(std::ostream& os, const Song& s);
    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    Song(std::string name, std::string artist, int rating)
        : name{ name }, artist{ artist }, rating{ rating } {}
    std::string get_name() const {
        return name;
    }
    std::string get_artist() const {
        return artist;
    }
    int get_rating() const {
        return rating;
    }

    bool operator<(const Song& rhs) const {
        return this->name < rhs.name;
    }

    bool operator==(const Song& rhs) const {
        return this->name == rhs.name;
    }
};

std::ostream& operator<<(std::ostream& os, const Song& s) {
    os << std::setw(20) << std::left << s.name
        << std::setw(30) << std::left << s.artist
        << std::setw(2) << std::left << s.rating;
    return os;
}

void display_menu() {
    std::cout << std::endl;
    std::cout << "F - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "L - List the current playlist" << std::endl;
    std::cout << "S - Save Playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song& song) {
    // This function should display 
    // Playing: followed by the song that is playing
    std::cout << std::endl;
    std::cout << "Now Playing: " << std::endl;
    std::cout << "*" << song << std::endl;
}

void display_playlist(const std::list<Song>& playlist, const Song& current_song) {
    // This function should display the current playlist 
    // and then the current song playing.
    std::cout << std::endl;
    for (auto &c : playlist)
        std::cout << c << std::endl;
    std::cout << "Current song:" << std::endl;
    std::cout << "*" <<  current_song << std::endl;
}

int main() {

    std::list<Song> playlist{
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weekend and K. Lamar",  4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroone 5",                 4},
            {"Whatever It Takes", "Imagine Dragons",           3}
    };

    std::list<Song>::iterator current_song = playlist.begin();
   
    char choice{};
    
    do {
        display_menu();
        std::cin >> choice; 

        switch (choice)
        {
        case 'f':
        case 'F': {
            current_song = playlist.begin();
            play_current_song(*current_song);
            break; 
        }
        case 'n':
        case 'N': {
            current_song++; 
            if (current_song == playlist.end())
                current_song = playlist.begin();
            play_current_song(*current_song);
            break; 
        }
        case 'p':
        case 'P': {
            if (current_song == playlist.begin())
            {
                current_song = playlist.end(); 
                current_song--; 
            }
            else
                current_song--; 
            play_current_song(*current_song);
            break;
        }
        case 'a':
        case 'A': {
            std::cin.ignore();
            std::cout << std::endl;
            std::cout << "Please enter a song name to add: ";  
            std::string name{};
            std::getline(std::cin, name); 
            std::cout << "\nPlease enter the artist's name: "; 
            std::string artist{};
            std::getline(std::cin, artist); 
            std::cout << "\nPlease enter a rating: "; 
            int rating{}; 
            std::cin >> rating; 
            std::cout << std::endl;
            playlist.emplace(current_song, name, artist, rating);
            current_song--; 
            play_current_song(*current_song);
            break;
        }
        case 'l':
        case 'L': {
            std::cout << std::endl;
            std::cout << "The current playlist is: " << std::endl;
            display_playlist(playlist, *current_song);
            break;
        }
        case 's':
        case 'S': {
            std::ofstream out_file{ "songs.txt" };
            if (!out_file)
                std::cerr << "Couldn't open write file" << std::endl;

            for (auto c : playlist) {
                out_file << c.get_name() << std::endl;
                out_file << c.get_artist() << std::endl;
                out_file << c.get_rating() << std::endl;
            }

            std::cout << "Playlist Saved!" << std::endl;
            out_file.close();
        }

        }
    } while (choice != 'q' && choice != 'Q');
    
    std::cout << "Thanks for listening!" << std::endl;
    return 0;
}