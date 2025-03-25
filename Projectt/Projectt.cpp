#include <iostream>
#include <string>
#include <conio.h> // For _kbhit() and _getch()
#include <iomanip>
#include <fstream>

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

static int nextSurahID = 1;
static int nextPlaylistID = 1;

template <typename DT>
class Node
{
public:
    DT data;
    Node* NEXT;
    Node* PREV;

    Node()
    {
        NEXT = nullptr;
        PREV = nullptr;
    }
    Node(DT newData)
    {
        data = newData;
        NEXT = nullptr;
        PREV = nullptr;
    }

};


template <typename DT>
class DoublyLinkedList
{
public:
    Node<DT>* HEAD;
    Node<DT>* TAIL;
    int size = 0;
    DoublyLinkedList()
    {
        HEAD = nullptr;
        TAIL = nullptr;
    }
    bool isEmpty()
    {
        return HEAD == nullptr;
    }
    void insert(DT data)
    {
        Node<DT>* newNode = new Node<DT>(data);
        if (isEmpty())
        {
            HEAD = newNode;
            TAIL = newNode;
            newNode->NEXT = nullptr;
            newNode->PREV = nullptr;
        }
        else
        {
            newNode->NEXT = nullptr;
            newNode->PREV = TAIL;
            TAIL->NEXT = newNode;
            TAIL = newNode;
        }
        ++size;
    }
    void remove(size_t Position)
    {
        if (isEmpty())
        {
            throw out_of_range("List is empty");
        }

        Node<DT>* temp = HEAD;
        int counter = 0;

        while (temp != nullptr && counter < Position)
        {
            temp = temp->NEXT;
            counter++;
        }

        if (temp == nullptr)
        {
            throw out_of_range("Position out of bounds");
        }

        if (temp == HEAD)
        {
            HEAD = temp->NEXT;
            if (HEAD != nullptr)
            {
                HEAD->PREV = nullptr;
            }
            else
            {
                TAIL = nullptr;
            }
        }
        else if (temp == TAIL)
        {
            TAIL = temp->PREV;
            if (TAIL != nullptr)
            {
                TAIL->NEXT = nullptr;
            }
            else
            {
                HEAD = nullptr;
            }
        }
        else
        {
            temp->PREV->NEXT = temp->NEXT;
            temp->NEXT->PREV = temp->PREV;
        }
        --size;
        delete temp;
    }
    DT& getElement(size_t position)
    {
        int counter = 0;
        Node<DT>* temp = HEAD;
        while (temp != nullptr)
        {
            if (counter == position)
                return temp->data;

            temp = temp->NEXT;
            counter++;
        }

        throw std::out_of_range("Index out of range");
    }

    int getSize() const
    {
        return size;
    }

    void update(size_t Position, DT newData)
    {
        Node<DT>* nodeToUpdate = getElement(Position);
        if (nodeToUpdate == nullptr)
            throw out_of_range("Position out of bounds");

        nodeToUpdate->data = newData;
    }
    void reverse()
    {
        Node<DT>* current = HEAD;
        Node<DT>* temp = nullptr;

        while (current != nullptr)
        {
            temp = current->PREV;
            current->PREV = current->NEXT;
            current->NEXT = temp;

            current = current->PREV;
        }

        if (temp != nullptr)
        {
            HEAD = temp->PREV;
        }
        temp = HEAD;
        HEAD = TAIL;
        TAIL = temp;
    }

    int search(DT data)
    {
        Node<DT>* temp = HEAD;
        int counter = 0;
        while (temp != nullptr)
        {
            if (temp->data == data)
                return counter;
            temp = temp->NEXT;
            counter++;
        }
        return -1;
    }
};


class Surah
{
private:
    int surahID;
    string surahName;
    string surahType;
    string surahPath;

public:
    Surah()
    {
        surahID = 0;
        surahName = "";
        surahType = "";
        surahPath = "";
    }
    Surah(string& newSurahName, string& newSurahType, string& newSurahPath)
    {
        surahID = nextSurahID++;
        surahName = newSurahName;
        surahType = newSurahType;
        surahPath = newSurahPath;
    }    
    string getSurahName() const
    {
        return surahName;
    }
    string getSurahType() const
    {
        return surahType;
    }
    string getSurahPath() const
    {
        return surahPath;
    }
    int getSurahID() const
    {
        return surahID;
    }

    void setSurahID(int newSurahID)
    {
        surahID = newSurahID;
    }

    void setSurahName(const string& newSurahName)
    {
        surahName = newSurahName;
    }
    void setSurahType(const string& newSurahType)
    {
        surahType = newSurahType;
    }
    void setSurahPath(const string& newSurahPath)
    {
        surahPath = newSurahPath;
    }
};


class Playlist
{
    int playlistID;
    string playlistName;

public:
    DoublyLinkedList<Surah> surahList;
    Playlist()
    {
        playlistID = 0;
        playlistName = "";
    }
    Playlist(string& newPlaylistName)
    {
        playlistID = nextPlaylistID++;
        playlistName = newPlaylistName;
    }
    int getPlaylistID() const
    {
        return playlistID;
    }
    string getPlaylistName() const
    {
        return playlistName;
    }
    void setPlaylistName(const string& newPlaylistName)
    {
        playlistName = newPlaylistName;
    }
    void setPlaylistID(int newPlaylistID)
    {
        playlistID = newPlaylistID;
    }

    void addSurah(Surah& surah)
    {
        surahList.insert(surah);
        for (int i = 0; i < surahList.getSize(); i++)
        {
            surahList.getElement(i).setSurahID(i + 1);
        }
    }

    void removeSurah(int index)
    {
        surahList.remove(index - 1);
        for (int i = 0; i < surahList.getSize(); i++)
        {
            surahList.getElement(i).setSurahID(i + 1);
        }
    }
    void displaySurahs()
    {
        for (int i = 0; i < surahList.getSize(); i++)
        {
            const Surah& surah = surahList.getElement(i);
            cout << "ID: " << surah.getSurahID() << " || "
                << "Name: " << surah.getSurahName() << " || "
                << "Type: " << surah.getSurahType() << " || "
                << "Path: " << surah.getSurahPath() << endl;
        }
    }

    void playSurah(int surahID)
    {
        int currentSurahIndex = -1;

        for (int i = 0; i < surahList.getSize(); i++)
        {
            if (surahList.getElement(i).getSurahID() == surahID)
            {
                currentSurahIndex = i;
                break;
            }
        }

        if (currentSurahIndex == -1)
        {
            cout << "Surah with ID " << surahID << " not found." << endl;
            return;
        }

        int lastPlayedIndex = -1;
        bool isPaused = false;

        while (true)
        {
            if (currentSurahIndex != lastPlayedIndex)
            {
                Surah currentSurah = surahList.getElement(currentSurahIndex);
                string path = currentSurah.getSurahPath();
                string name = currentSurah.getSurahName();
                string type = currentSurah.getSurahType();

                wstring wPath(path.begin(), path.end());
                wstring openCommand = L"open \"" + wPath + L"\" type mpegvideo alias myAudio";
                mciSendString(openCommand.c_str(), NULL, 0, NULL);
                mciSendString(L"play myAudio", NULL, 0, NULL);

                


                // wstring wPath(path.begin(), path.end());
                // PlaySound(wPath.c_str(), NULL, SND_LOOP | SND_ASYNC);

                //string command = "start " + path + " &";
                //system(command.c_str());

                // Display Surah information
                system("cls");
                cout << "Now playing: " << name << " (" << type << ")" << endl;
                cout << "[<--] Previous Surah\n[-->] Next Surah\n[SPACE] Pause/Resume\n[ESC] Quit..." << endl;

                lastPlayedIndex = currentSurahIndex;
                isPaused = false;
            }

            char userInput = _getch();

            if (userInput == 27) // ESC key to exit
            {
                mciSendString(L"stop myAudio", NULL, 0, NULL); // Stop playback
                mciSendString(L"close myAudio", NULL, 0, NULL); // Close the audio file
                cout << "Exiting Surah playback." << endl;
                break;
            }
            else if (userInput == 75) // Left arrow key for Previous Surah
            {
                if (currentSurahIndex > 0)
                {
                    mciSendString(L"stop myAudio", NULL, 0, NULL); // Stop current playback
                    mciSendString(L"close myAudio", NULL, 0, NULL); // Close current audio
                    currentSurahIndex--; // Move to the previous Surah
                }
            }
            else if (userInput == 77) // Right arrow key for Next Surah
            {
                if (currentSurahIndex < surahList.getSize() - 1)
                {
                    mciSendString(L"stop myAudio", NULL, 0, NULL); // Stop current playback
                    mciSendString(L"close myAudio", NULL, 0, NULL); // Close current audio
                    currentSurahIndex++; // Move to the next Surah
                }
            }

            else if (userInput == ' ')
            {
                if (isPaused)
                {
                    mciSendString(L"resume myAudio", NULL, 0, NULL);
                    cout << "Resumed audio." << endl;
                    isPaused = false;
                }
                else
                {
                    mciSendString(L"pause myAudio", NULL, 0, NULL);
                    cout << "Paused audio." << endl;
                    isPaused = true;
                }
                
            }

        }
    }
    void saveToFile(string filename)
    {
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            for (int i = 0; i < surahList.getSize(); i++)
            {
                file << "Surah " << surahList.getElement(i).getSurahID() << ": " << surahList.getElement(i).getSurahName() << ", " << surahList.getElement(i).getSurahType() << ", " << surahList.getElement(i).getSurahPath() << endl;
            }
            file.close();
        }
    }
    void loadFromFile(ifstream& file)
    {
        string line;
        while (getline(file, line))
        {
            if (line.find("--------------------------------------------") != string::npos)
            {
                break;
            }

            if (line.rfind("Surah ", 0) == 0)
            {
                size_t idPos = line.find("Surah ") + 6;
                size_t namePos = line.find(": ", idPos);
                size_t typePos = line.find(", ", namePos);
                size_t pathPos = line.find(", ", typePos + 2);

                int surahID = stoi(line.substr(idPos, namePos - idPos));
                string surahName = line.substr(namePos + 2, typePos - namePos - 2);
                string surahType = line.substr(typePos + 2, pathPos - typePos - 2);
                string surahPath = line.substr(pathPos + 2);

                Surah surah(surahName, surahType, surahPath);
                surah.setSurahID(surahID);

                surahList.insert(surah);
            }
        }
    }
};





class QuranManager
{
    DoublyLinkedList<Playlist> playLists;

public:
    void addPlaylist(Playlist& playlist)
    {
        playLists.insert(playlist);
        for (int i = 0; i < playLists.getSize(); i++)
        {
            playLists.getElement(i).setPlaylistID(i + 1);
        }
        cout << "Playlist added successfully" << endl;
    }
    void removePlaylist(int playlistID)
    {
        playLists.remove(playlistID - 1);
        for (int i = 0; i < playLists.getSize(); i++)
        {
            playLists.getElement(i).setPlaylistID(i + 1);
        }

        cout << "Playlist Removed successfully" << endl;
    }
    void displayPlaylists()
    {
        if (playLists.getSize() == 0)
        {
            cout << "No playlists available." << endl;
            return;
        }

        system("cls");
        cout << "Playlist List:" << endl;

        cout << string(28, '-') << endl;
        cout << "| " << setw(3) << left << "ID" << " | "
            << setw(18) << left << "Playlist Name" << " |" << endl;
        cout << string(28, '-') << endl;

        for (int i = 0; i < playLists.getSize(); i++)
        {
            cout << "| " << setw(3) << left << playLists.getElement(i).getPlaylistID() << " | "
                << setw(18) << left << playLists.getElement(i).getPlaylistName() << " |" << endl;
        }

        cout << string(28, '-') << endl;
    }
    void addSurahToPlaylist(int playlistID, Surah& surah)
    {
        for (int i = 0; i < playLists.getSize(); i++)
        {
            if (playLists.getElement(i).getPlaylistID() == playlistID)
            {
                playLists.getElement(i).addSurah(surah);
                cout << "Surah added to Playlist ID " << playlistID << endl;
                return;
            }
        }
    }
    void removeSurahFromPlaylist(int playlistID, int sorahID)
    {

        for (int i = 0; i < playLists.getSize(); i++)
        {
            if (playLists.getElement(i).getPlaylistID() == playlistID)
            {
                playLists.getElement(i).removeSurah(sorahID);
                cout << "Surah removed from Playlist ID " << playlistID << endl;
                return;
            }
        }
    }

    void displaySurahFromPlaylist(int playlistID)
    {
        for (int i = 0; i < playLists.getSize(); i++)
        {
            Playlist& playlist = playLists.getElement(i);

            if (playlist.getPlaylistID() == playlistID)
            {
                cout << "| " << setw(5) << left << "ID" << " | "
                    << setw(13) << left << "Surah Name" << " | "
                    << setw(10) << left << "Type" << " | "
                    << setw(17) << left << "Path" << " |" << endl;
                cout << string(58, '-') << endl;

                DoublyLinkedList<Surah>& surahList = playlist.surahList;

                if (surahList.getSize() == 0)
                {
                    cout << "No Surahs available in this playlist." << endl;
                    cout << string(58, '-') << endl;
                    return;
                }

                for (int j = 0; j < surahList.getSize(); j++)
                {
                    Surah& surah = surahList.getElement(j);
                    cout << "| " << setw(5) << left << surah.getSurahID() << " | "
                        << setw(13) << left << surah.getSurahName() << " | "
                        << setw(10) << left << surah.getSurahType() << " | "
                        << setw(17) << left << surah.getSurahPath() << " |" << endl;
                }

                cout << string(58, '-') << endl;
                return;
            }
        }

        cout << "Playlist with ID " << playlistID << " not found." << endl;
    }

    void displayAllPlaylistsSurah()
    {
        if (playLists.getSize() == 0)
        {
            cout << "No playlists available." << endl;
            return;
        }

        system("cls");

        for (int i = 0; i < playLists.getSize(); i++)
        {
            cout << string(33, '*') << endl;

            cout << "* " << setw(10) << left << "Playlist ID" << " | "
                << setw(15) << left << "Playlist Name" << " *" << endl;

            cout << string(33, '*') << endl;
            const Playlist& playlist = playLists.getElement(i);

            cout << "* " << setw(11) << left << playlist.getPlaylistID() << " | "
                << setw(15) << left << playlist.getPlaylistName() << " *" << endl;
            cout << string(58, '-') << endl;

            displaySurahFromPlaylist(playlist.getPlaylistID());
        }
    }

    void updatePlaylistOrder(int PlaylistID)
    {
        system("cls");
        displaySurahFromPlaylist(PlaylistID);
        int surahID;
        cout << "Enter Surah ID: ";
        cin >> surahID;
        system("cls");
        displayPlaylists();
        int newPlaylistID;
        cout << "Enter new playlist ID: ";
        cin >> newPlaylistID;
        system("cls");
        string surahName = playLists.getElement(PlaylistID - 1).surahList.getElement(surahID - 1).getSurahName();
        string surahType = playLists.getElement(PlaylistID - 1).surahList.getElement(surahID - 1).getSurahType();
        string surahPath = playLists.getElement(PlaylistID - 1).surahList.getElement(surahID - 1).getSurahPath();
        Surah newSurah(surahName, surahType, surahPath);
        addSurahToPlaylist(newPlaylistID, newSurah);
        removeSurahFromPlaylist(PlaylistID, surahID);
    }

    void playSurahFromPlaylist(int playlistID)
    {
        displaySurahFromPlaylist(playlistID);
        int surahID;
        cout << "Enter Surah ID: ";
        cin >> surahID;
        for (int i = 0; i < playLists.getSize(); i++)
        {
            if (playLists.getElement(i).getPlaylistID() == playlistID)
            {
                playLists.getElement(i).playSurah(surahID);
            }
        }
    }

    void savePlaylistToFile(int playlistID)
    {
        string fileName;
        cout << "Enter file name To Save: ";
        cin >> fileName;

        ofstream file(fileName, ios::app);
        // ofstream file(fileName, ios::trunc | ios::app);
        if (file.is_open())
        {
            Playlist& playList = playLists.getElement(playlistID - 1);
            file << "ID: " << playList.getPlaylistID() << " | Name: " << playList.getPlaylistName() << endl;
            playList.saveToFile(fileName);
            file << "--------------------------------------------" << endl;
            file.close();
            cout << "Playlist Saved Successfully" << endl;
        }
        else
        {
            cout << "Error opening file" << endl;
        }
    }
    void loadPlaylistFromFile()
    {
        string fileName;
        cout << "Enter file name to load: ";
        cin >> fileName;

        ifstream file(fileName);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line.rfind("ID: ", 0) == 0)
                {
                    size_t idPos = line.find("ID: ") + 4;
                    size_t namePos = line.find("| Name: ");
                    int playlistID = stoi(line.substr(idPos, namePos - idPos));
                    string playlistName = line.substr(namePos + 8);

                    Playlist playlist;
                    playlist.setPlaylistID(playlistID);
                    playlist.setPlaylistName(playlistName);

                    playlist.loadFromFile(file);

                    playLists.insert(playlist);
                }
            }

            file.close();
            cout << "Playlist Loaded Successfully" << endl;
        }
        else
        {
            cout << "Error opening file" << endl;
        }
    }

};


void waitForEnter()
{
    cout << "Press Enter To Continue...!";
    cin.ignore();
    cin.get();
}
int main()
{
    // string line = "ID:";
    // size_t id = line.find("I");
    // cout << id;
    // waitForEnter();
    QuranManager Quran;
    while (true)
    {
        system("cls");
        int choice;
        cout << string(30, '=') << endl;
        cout << "Quran Playlist Manager Menu" << endl;
        cout << string(30, '=');

        cout << "\n 1. Add a new playlist"
            << "\n 2. Remove an existing playlist"
            << "\n 3. Display All current Playlists"
            << "\n 4. add Surah to an existing playlist"
            << "\n 5. Remove Surah from an existing playlist"
            << "\n 6. Display Surah in a specific playlist"
            << "\n 7. Display All Playlists Surah"
            << "\n 8. Play Surah from specific playlist"
            << "\n 9. Update the order of existing playlist"
            << "\n 10. Load an Existing playlist from a file"
            << "\n 11. Save an Existing playlist to a file"
            << "\n 12. Exit"
            << endl;
        cout << string(20, '=') << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string playlistName;
            cout << "Enter playlist name: ";
            cin >> playlistName;
            Playlist playlist(playlistName); // Initialize Playlist with a name
            Quran.addPlaylist(playlist);
            waitForEnter();
            break;
        }
        case 2:
        {
            Quran.displayPlaylists();
            int playlistID;
            cout << "Enter playlist ID to remove: ";
            cin >> playlistID;
            Quran.removePlaylist(playlistID);
            waitForEnter();
            break;
        }
        case 3:
            Quran.displayPlaylists();
            waitForEnter();
            break;
        case 4:
        {
            Quran.displayPlaylists();
            int playListID;
            cout << "Enter playlist ID: ";
            cin >> playListID;
            string surahName, surahType, surahPath;
            cout << "Enter Surah Name: ";
            cin >> surahName;
            cout << "Enter Surah Type: ";
            cin >> surahType;
            cout << "Enter Surah Path: ";
            cin >> surahPath;
            Surah newSurah(surahName, surahType, surahPath);
            Quran.addSurahToPlaylist(playListID, newSurah);
            waitForEnter();
            break;
        }
        case 5:
        {
            Quran.displayPlaylists();
            int playListID;
            cout << "Enter playlist ID: ";
            cin >> playListID;
            Quran.displaySurahFromPlaylist(playListID);
            int surahID;
            cout << "Enter Surah ID: ";
            cin >> surahID;
            Quran.removeSurahFromPlaylist(playListID, surahID);
            waitForEnter();
            break;
        }
        case 6:
        {
            Quran.displayPlaylists();
            int playlistID;
            cout << "Enter playlist ID: ";
            cin >> playlistID;
            Quran.displaySurahFromPlaylist(playlistID);
            waitForEnter();
            break;
        }
        case 7:
        {
            Quran.displayAllPlaylistsSurah();
            waitForEnter();
            break;
        }
        case 8:
        {
            Quran.displayPlaylists();
            int playlistID1;
            cout << "Enter playlist ID: ";
            cin >> playlistID1;
            Quran.playSurahFromPlaylist(playlistID1);
            waitForEnter();
            break;
        }
        case 9:
        {
            Quran.displayPlaylists();
            int PlaylistID;
            cout << "Enter Playlist ID: ";
            cin >> PlaylistID;
            Quran.updatePlaylistOrder(PlaylistID);
            system("cls");
            cout << "Playlist Updated Successfully" << endl;
            waitForEnter();
            break;
        }
        case 10:
        {
            Quran.loadPlaylistFromFile();
            waitForEnter();
            break;
        }
        case 11:
        {
            int playlistID;
            Quran.displayPlaylists();
            cout << "Enter playlist ID: ";
            cin >> playlistID;
            Quran.savePlaylistToFile(playlistID);
            waitForEnter();
            break;
        }
        case 12:
            cout << "Exiting..." << endl;
            return 0;
            waitForEnter();
            break;
        default:
            break;
        }
    }
}
