#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

class meeting {
    int day, hour, min, duration, n;
    string* mem;

public:
    meeting(const int& day, const int& hour, const int& min, const int& duration,
        const int& n, string* mem) {
        this->day = day;
        this->hour = hour;
        this->min = min;
        this->duration = duration;
        this->n = n;
        this->mem = mem;
    }

    const int& GetDay() {
        return day;
    }

    const int& GetTime() {
        return hour * 60 + min;
    }

    const int& GetEndTime() {
        return hour * 60 + min + duration;
    }

    void PrintData() {
        printf("%02d:%02d %02d ", hour, min, duration);
        for (int i = 0; i < n; ++i)
            printf("%s ", mem[i].c_str());
        cout << '\n';
    }

    bool IsMember(const string& Member) {
        for(int i = 0; i < n; ++i)
            if (mem[i] == Member) 
                return true;
        return false;
    }

    ~meeting() {
        delete[] mem;
    }
};

template<>
struct less<meeting*> {
    bool operator()(meeting* First, meeting* Second) const {
            return First->GetDay()*24*60+ First->GetTime() < Second->GetDay() * 24 * 60 + Second->GetTime();
    }
};

void Appointing(set <meeting*, less<meeting*>>& Set, stringstream* sstr) {
  //  stringstream sstr;
    int day, hour, min, duration, n;
    string* mem;
  //  sstr << str;
    *sstr >> day >> hour >> min >> duration >> n;
    mem = new string[n];
    for (int i = 0; i < n; ++i) 
        *sstr >> mem[i];
    
    int time = hour * 60 + min;
    int EndTime = time + duration;

    for (meeting* meet : Set) {
        if (meet->GetDay() != day)
            continue;
        if (time > meet->GetTime() && time < meet->GetEndTime() ||
            EndTime > meet->GetTime() && EndTime < meet->GetEndTime()) {
            printf("FAIL\n");
            for (int i = 0; i < n; ++i)
                printf("%s ", mem[i].c_str());
            printf("\n");
            return;
        }    
    }
    Set.emplace(new meeting(day, hour, min, duration, n, mem));
    printf("OK\n");
}

void Printing(set <meeting*, less<meeting*>>& Set, stringstream* sstr) {
    //stringstream sstr;
    int day;
    string member;
    //sstr << str;
    *sstr >> day >> member;
    for (meeting* Member : Set) {
        if (Member->GetDay() != day)
            continue;
        if (Member->IsMember(member))
            Member->PrintData();
    }
}

int main()
{
    srand(time(0));
    {
        set <meeting*, less<meeting*>> Set;
        int n;
        cin >> n;
        cin.get();

        for (int i = 0; i < n; ++i) {
            stringstream* sstr = new stringstream;
            string str, command;
            getline(cin, str);
            int t = str.find(':');
            if (t != -1)
                str.replace(t, 1, " ");
            *sstr << str;
            *sstr >> command;

            if (command == "APPOINT") {
                Appointing(Set, sstr);
            }
            else if (command == "PRINT") {
                Printing(Set, sstr);
            }

            delete sstr;
        }

        for (meeting* meet : Set)
            delete meet;
    }

    _CrtDumpMemoryLeaks();
    return 0;
}
