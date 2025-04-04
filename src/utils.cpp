#include "utils.hpp"

using namespace std;


void decouper(const string& str, vector<string>& tokens, const string& delimiters) {
    if (str.length() == 0) return;
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        string::size_type pos_tmp = str.find_first_of(delimiters, pos+1);
        if(pos_tmp - pos == 1){
            lastPos = pos_tmp;
            pos = pos_tmp;
        }
        else {
            lastPos = str.find_first_not_of(delimiters, pos);
            pos = str.find_first_of(delimiters, lastPos);
        }
    }
}
