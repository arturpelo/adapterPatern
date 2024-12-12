#include <iostream>
#include <string>

//____________________________________________________
class OldPlayer {
private:
    std::string name;
public:
    void goDisc() {
        std::cout << "Gramofon: " << name << " gra muzyka\n";
    }

    OldPlayer(std::string name) {
        this->name = name;
    }
};

//____________________________________________________
class ModernPlayer {
public:
    virtual void playMusic() = 0;
    //virtual ~ModernPlayer() = default; 
};
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
class MP3Player : public ModernPlayer {
private:
    std::string name;
public:
    MP3Player(std::string name) {
        this->name = name;
    }

    void playMusic() override {
        std::cout << "Odtwarzacz: " << name << " gra muzyka z pliku mp3\n";
    }
};

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
class NetPlayer : public ModernPlayer {
private:
    std::string name;
public:
    NetPlayer(std::string name) {
        this->name = name;
    }
    void playMusic() override {
        std::cout << "Odtwarzacz: " << name << " gra muzyka z Internetu\n";
    }
};
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
class AdapterOldPlayer : public ModernPlayer {
private:
    OldPlayer* gramofon;
public:
    AdapterOldPlayer(OldPlayer* gramofon) {
        this->gramofon = gramofon;
    }
    void playMusic() override {
        gramofon->goDisc(); 
    }
};
//________________________MAIN_________________________
int main() {
    OldPlayer* oldPlayer = new OldPlayer("Gramofon");
    ModernPlayer* adapterOldPlayer = new AdapterOldPlayer(oldPlayer);
    ModernPlayer* modernPlayerMP3 = new MP3Player("MP3_Tomasz");
    ModernPlayer* modernPlayerNet = new NetPlayer("NetPlay_Kasia");
    ModernPlayer* device = nullptr;

    int select;
    do {
        std::cout << "\n1 - graj gramofon\n2 - graj na mp3\n3 - graj z internetu\n0 - exit\n\n?>";
        std::cin >> select;

        if (select == 1) device = adapterOldPlayer;
        if (select == 2) device = modernPlayerMP3;
        if (select == 3) device = modernPlayerNet;

        if (device != nullptr) {
            device->playMusic();
        }
    } while (select != 0);

    delete oldPlayer;
    delete adapterOldPlayer;
    delete modernPlayerMP3;
    delete modernPlayerNet;

    return 0;
}