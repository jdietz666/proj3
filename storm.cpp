//Programmer: Jorge Dietz
//Date: 10/21/2021
//Description: Program reads csv files,stores data, and manipulates it

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstring>
using namespace std;

#define STATE_LEN 20
#define MONTH_LEN 15
#define EVENT_LEN 30
#define COUNTY_LEN 35
#define DATE_LEN 25
#define FAT_LOC 30

struct annual_storms{
    int year; // Year of storm events
    struct storm_event *events;  // Pointer to array of storm events for the given year
};
struct storm_event{
    int event_id; // Event id
    char state[ STATE_LEN ]; // State name
    int year; // Four digit year of event
    char month_name[ MONTH_LEN ]; // Month of event
    char event_type[ EVENT_LEN ]; // Event type
    char cz_type; // Where event happened, C, Z, or M
    char cz_name[ COUNTY_LEN ]; // Name of county/zone
    int injuries_direct; // Number of direct injuries
    int injuries_indirect; // Number of indirect injuries
    int deaths_direct; // Number of direct deaths
    int deaths_indirect; // Number of indirect deaths
    int damage_property; // Amount of property damage; convert to integer
    int damage_crops; // Amount of crop damage; convert to integer
    struct fatality_event *f; // Linked list of fatalities associated with this storm event
};
struct fatality_event{
    int fatality_id; // Identifier of the fatality
    int event_id; // Identifier of the storm event
    char fatality_type; // D or I
    char fatality_date[ DATE_LEN ]; // Date and time of fatality
    int fatality_age; // Age of fatality
    char fatality_sex; // Gender of fatality
    char fatality_location[ FAT_LOC ]; // Location of fatality
    struct fatality_event *next; // Pointer to next fatality event
};
struct hash_table_entry{
    int event_id; // Event id -- key used to hash on
    int year; // Year of storm event
    int event_index; // For the given year, the index into array of storm events
    struct hash_table_entry *next; // Pointer to next entry in case of collisions
};
struct bst{ // A binary search tree
    char *s; // String corresponding to either a state or a month_name
    int event_id; // Identifier of storm event
    int year; // Year of storm event
    int event_index; // For the given year, the index into array of storm events
    struct bst *left;  // Pointer to the left subtree
    struct bst *right;  // Pointer to the right subtree
};
struct heap_entry{ // An entry in a max-heap
    int damage_amount; // Amount of damage to property or crops
    int year; // Year of storm event
    int event_index; // For the given year, the index into array of storm events
};


template<typename T> void cinGet(T &var) {
    string line;
    getline(cin, line);
    stringstream ss(line);
    ss >> var;
}

void cinGetLine(string &line) {
    getline(cin, line);
    size_t nl = line.find_first_of("\r\n");
    if (nl != string::npos) {
        line = line.substr(0, nl);
    }
}


void getInput(){
    int number_of_commands;
    cinGet(number_of_commands);
    cout << number_of_commands << endl;
    cout << endl;
    for(int i = 0; i < number_of_commands; i++) {
       string line;
       cinGetLine(line);
       cout << "Query:" << line << endl;
       cout << '\n' << endl;
       cout << "    Month Name:" << endl;
       cout << "    Event ID:" << endl;
       cout << "    Year:" << endl;
       cout << "    Event Type:" << endl;
       cout << "    County/Zone Type:" << endl;
       cout << "    County/Zone Name:" << endl;
       cout << '\n' << endl;

       stringstream cmd(line);
       string command;
       cmd >> command;
   }
}

    int main(int argc, char* argv[]) {

        string year = argv[1]; //stores year of command argument: "1950" <
        string count = argv[2]; //stores second command argument: amount of years
        string filenameA = "details-";
        string filenameB = ".csv";

        stringstream geek(year);    //turn to int func
        stringstream glock(count); //turn to int func

        int number_of_files = 0;  //initialize
        int number_of_years = 0;  //initialize
        geek >> number_of_files; // turns string "1950" to int = 1950
        glock >> number_of_years;  // turns string "1","2","3","4"...."i" to int = 1,2,3

        annual_storms aStorms[number_of_years]; //initialize array of struct size of amount of years
        string filenames[number_of_years]; //array of filenames

        int c = number_of_files; //To increment years 1950->1951->1952
        for (int i = 0; i < number_of_years; i++) {
            filenames[i] = filenameA+year+filenameB; //appending string together to form "details-YYYY.cvs"
            stringstream num(year); //to turn string YYYY into int
            num >> c; //stores year as an int in the c variable
            aStorms[i].year = c; //stores the year in array of struct annual_storms
            c += 1; // increment year by one
            stringstream ss; //to turn int YYYY into string
            ss << c;
            year = ss.str(); //year converted back to string for next iteration
        }

        string line;
        int size_of_arr[number_of_years];
        for (int i = 0; i < number_of_years; i++) {
            int rows = 0;
            ifstream details(filenames[i]);
            if (!details.is_open()) { cout << "FAILURE TO OPEN" << endl; }
            if (details.is_open()) {
                while (!details.eof()) {
                    getline(details, line);
                    rows++;
                }
            }
            details.close(); //close to prevent leaks
            size_of_arr[i] = rows; //stores the number of rows for each csv file read
        }

      //  string line2;
      //  storm_event sEvents[0];
    /*    for(int i =0;i < number_of_years;i++){
            ifstream details(filenames[i]);
            if(!details.is_open()){cout << "FAILURE TO OPEN" << endl;}
            if(details.is_open()){
                while(!details.eof()){
                    sEvents[size_of_arr[i]];
                }
            }
            details.close();
        }*/
        getInput();
    }






