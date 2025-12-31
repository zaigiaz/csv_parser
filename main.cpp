#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define PATH_SEP ','
#define ENDL '\n'

struct fields {
  string name;
  string address;
  string comment;
};

int main() {
  string line;
  ifstream in("file.csv");
  if(!in.is_open()) { cout << "file not open\n"; return 1; }

  while(getline(in, line)) {
    vector<string> field_collec;
    size_t ctr = 0;
    for(size_t i = 0; i < line.length(); ++i) {
      if(line[i] == PATH_SEP) {
        field_collec.push_back(line.substr(ctr, i - ctr));
        ctr = i + 1; 
      }
    }
    if(ctr <= line.size())
      field_collec.push_back(line.substr(ctr));

    for(const auto &f : field_collec) cout << f << '\n';
    cout << "--------------\n";
  }

  in.close();
  return 0;
}
