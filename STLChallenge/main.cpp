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
#include <sstream>

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

void load_file(std::ifstream &read_file, std::list<Song>& ls); 
void case_f(std::list<Song>::iterator& curr_song, std::list<Song>& ls); 
void case_n(std::list<Song>::iterator& curr_song, std::list<Song>& ls); 
void case_p(std::list<Song>::iterator& curr_song, std::list<Song>& ls); 
void case_a(std::list<Song>::iterator& curr_song, std::list<Song>& ls); 
void case_l(std::list<Song>::iterator& curr_song, std::list<Song>& ls); 
void case_s(std::ofstream &write_file, std::list<Song>& ls); 

int main() {

    std::list<Song> playlist{};
    std::ifstream in_file{ "songs.txt" };

    load_file(in_file, playlist); 
    
    std::list<Song>::iterator current_song = playlist.begin();

    char choice{};
    
    do {
        display_menu();
        std::cin >> choice; 

        switch (choice)
        {
        case 'f':
        case 'F': {
            case_f(current_song, playlist); 
            break; 
        }
        case 'n':
        case 'N': {
            case_n(current_song, playlist); 
            break; 
        }
        case 'p':
        case 'P': {
            case_p(current_song, playlist); 
            break;
        }
        case 'a':
        case 'A': {
            case_a(current_song, playlist); 
            break;
        }
        case 'l':
        case 'L': {
            case_l(current_song, playlist); 
            break;
        }
        case 's':
        case 'S': {
            std::ofstream out_file{ "songs.txt" }; 
            case_s(out_file, playlist); 
            break; 
        }

        }
    } while (choice != 'q' && choice != 'Q');
    
    std::cout << "Thanks for listening!" << std::endl;
    return 0;
}


void load_file(std::ifstream& read_file, std::list<Song>& ls) {
   
    if (!read_file)
        std::cerr << "Could not open read file" << std::endl;

    std::string name{}, artist{}, temp_rating{};
    int rating{}; 

    while (std::getline(read_file, name) && std::getline(read_file, artist) && std::getline(read_file, temp_rating))
    {
        std::istringstream convertor{ temp_rating };
        convertor >> rating;

        Song new_song(name, artist, rating);
        ls.push_back(new_song);
    }
}

void case_f(std::list<Song>::iterator& curr_song, std::list<Song>& ls) {
    curr_song = ls.begin();
    play_current_song(*curr_song);
}

void case_n(std::list<Song>::iterator& curr_song, std::list <Song>& ls) {
    curr_song++;
    if (curr_song == ls.end())
        curr_song = ls.begin();
    play_current_song(*curr_song);
}

void case_p(std::list<Song>::iterator& curr_song, std::list<Song>& ls) {
    if (curr_song == ls.begin())
    {
        curr_song = ls.end();
        curr_song--;
    }
    else
        curr_song--;
    play_current_song(*curr_song);
}

void case_a(std::list<Song>::iterator& curr_song, std::list<Song>& ls) {
    //get rid of the leftover newline character from previous input
    std::string leftover; 
    std::getline(std::cin, leftover);
    std::cout << std::endl;
    std::cout << "Please enter a song name to add: ";
    std::string a_name{};
    std::getline(std::cin, a_name);
    std::cout << "\nPlease enter the artist's name: ";
    std::string a_artist{};
    std::getline(std::cin, a_artist);
    std::cout << "\nPlease enter a rating: ";
    std::string a_temp_rating{};
    std::getline(std::cin, a_temp_rating);
    std::istringstream a_convertor{ a_temp_rating };
    int a_rating{};
    a_convertor >> a_rating;
    std::cout << std::endl;
    ls.emplace(curr_song, a_name, a_artist, a_rating);
    curr_song--;
    play_current_song(*curr_song);
}

void case_l(std::list<Song>::iterator& curr_song, std::list<Song>& ls) {
    std::cout << std::endl;
    std::cout << "The current playlist is: " << std::endl;
    display_playlist(ls, *curr_song);
}

void case_s(std::ofstream& write_file, std::list<Song>& ls) {
    if (!write_file)
        std::cerr << "Couldn't open write file" << std::endl;

    for (auto c : ls) {
        write_file << c.get_name() << std::endl;
        write_file << c.get_artist() << std::endl;
        write_file << c.get_rating() << std::endl;
    }

    std::cout << "Playlist Saved!" << std::endl;
    write_file.close();
}