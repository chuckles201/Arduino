#include <iostream>
using namespace std;
#include <cstdint> // int32_T
#include <string>

#define GROUND_TRUTH -1322

// defining data struct
struct MPUData {
    float data[6];


};

// parse the stream incoming:
// check for 000111 start
// seperate with each space!
MPUData parse_stream(string stream){
    string sToken = "000111";
    MPUData parts;
    // keep track of last one
    int current_last = 6;
    int ct = 0;
    if (stream.substr(0,6) == sToken) {
        // continuing, parse all data...
        for (int i = 6; i < stream.length(); i++) {
            // go over each character, until found space
            if (stream[i] == ' ') {
                // convert to float, skip a space.
                parts.data[ct] = stof(stream.substr(current_last,i-1));
                ct += 1;
                current_last = i+1; // last minus space!
                cout << parts.data[ct-1] << endl;
            }
        }
        
    }
    return parts;
}

int main() {
    // calculated value
    string incoming_data = "00011112.23 1.23 0.11 -12.22 1.2 12.222 ";
    MPUData incoming_data_parsed = parse_stream(incoming_data);
    cout << incoming_data_parsed.data[0] << "+++" << incoming_data_parsed.data[5];
    return 0;
}