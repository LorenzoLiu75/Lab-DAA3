#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main() {
  string line;
  string words[50];
  ifstream dict("dict.txt");

  int index = 0;
  while (getline (dict, line)) {
    for (int i = 0; i < line.length(); i++) {
      if (line[i] == ' ') {
        index++;
      } else {
        words[index] += line[i];
      }
    }
    index++;
  }
  
  map<string, int> freq;
  map<string, int>::iterator itr;

  for (int i = 0; i < index; i++) {
    itr = freq.find(words[i]);
    if (itr == freq.end()) {
      freq.insert(pair<string, int>(words[i], 1));
    } else {
      int value = itr->second;
      itr->second = value + 1;
    }
  }

  for (itr = freq.begin(); itr != freq.end(); itr++) {
    cout << "Word: " << itr->first;
    cout << " | Frequency: " << itr->second << endl;
  }

  dict.close();
}