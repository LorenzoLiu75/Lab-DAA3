#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

int main()
{
    ifstream file("dict.txt");

    if(!file.is_open()) 
      return 1;

    map<string, int> wordName;

    while(file.good())
    {
        string x;
        getline(file, x);
        int position = x.find_first_of(' ');
        if(position < 0) 
          continue;

        while(x.size() > 0)
        {
            position = x.find_first_of(' ');
            if(position < 0)
                position = x.size();

            string word = x.substr(0, position);

            if(word != "")
                wordName[word]++;

            x = x.erase(0, position+1);
        }
    }

    for (map<string, int>::iterator i = wordName.begin(); i != wordName.end(); i++){

        cout << "word: " << i->first << ", frequencies: " << i->second << endl;
    }

    return 0;
}