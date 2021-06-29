#include <iostream>
#include <fstream>
#include <vector>
#include "Trie.cpp"
using namespace std;
int main()
{
    std::cout << "Dictionary using Trie Datastructure \n";

    fstream data;
    string s;
    data.open("C:\\Users\\Adil\\Desktop\\Trie\\data.txt",ios::in);
    if (!data)
    {
        cout << "Error while loading file";
        return -1;
    }
    int totalWords{};
    Dictionary german;

    while (!data.eof())
    {
        data >> s;
        german.insert(s, s + "_meaning");

        totalWords++;
    }
    
    cout << totalWords<<"\n";
    
    while (1)
    {
        cout << "1. search word\n";
        cout << "2. remove word\n";
        cout << "3. exit app\n";

        int choice{1};
        cin >> choice;

        switch(choice)
        {
                case 1:
                { string s;
                cout << "Enter a word to search - ";
                cin >> s;
                german.search(s);
                break;
                }
                case 2:
                {  string s;
                cout << "Enter a word to remove - ";
                cin >> s;
                german.search(s);
                break;
                }
                case 3:
                {
                    exit(0);
                    break;
                }
                default:
                    cout << "Enter correct option\n";
                }
    }
}
