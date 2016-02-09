//
//  main.cpp
//  DoubleArrayTrie
//
//  Created by User on 2/6/16.
//  Copyright © 2016 User. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


class Node
{
    const static int MAXCHILDNODES = 26;
    
public: Node** childNodes = NULL;
public: bool IsEOW;
    
public: Node()
    {
        IsEOW = false;
    }
    
public: int GetNodeCount()
    {
        return 1;
    }
    
public: bool InitializeChildNodes()
    {
        childNodes = new Node*[26];
        for(int i=0;i<MAXCHILDNODES;i++) {
            childNodes[i] = NULL;
        }
        return true;
    }
};


class Trie
{
    Node* RootNode;
    int NodeCount = 1;
public: Trie()
    {
        RootNode = new Node();
        NodeCount += RootNode->GetNodeCount();
    }
    
public: int GetNodeCount()
    {
        return NodeCount;
    }
public: bool Exists(char* newStr)
    {
        if (newStr == NULL)
            return false;
        
        return Exists(RootNode, newStr);
    }
    
    bool Exists(Node* node, char* newStr)
    {
        if (node != NULL)
        {
            if (*newStr == '\0')
            {
                if (node->IsEOW == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            int index = *newStr - 'a';
            if (node->childNodes == NULL || index < 0 || index >= 26)
                return false;
            
            return Exists(node->childNodes[*newStr - 'a'], newStr + 1);
        }
        
        return false;
    }
    
public: bool Insert(char* newStr)
    {
        if (newStr == NULL)
            return false;
        
        return Insert(RootNode, newStr);
    }
    
    bool Insert(Node* node, char* newStr)
    {
        if (*newStr == '\0')
        {
            node->IsEOW = true;
            return true;
        }
        
        int index = *newStr - 'a';
        
        if (index < 0 || index >= 26)
        {
            return false;
        }
        
        if (node->childNodes == NULL)
            node->InitializeChildNodes();
        
        if (node->childNodes[index] == NULL)
        {
            node->childNodes[index] = new Node();
            NodeCount += node->childNodes[index]->GetNodeCount();
        }
        
        return Insert(node->childNodes[index], newStr + 1);
    }
};

class DoubleArrayTrie
{
    int* baseArray;
    int* checkArray;
    const int MAX_LENGTH = 10000;
    int CURRENT_LENGTH = 1000;
    const int INCREMENT = 500;

    public: DoubleArrayTrie()
    {
        baseArray = new int[CURRENT_LENGTH];
        checkArray = new int[CURRENT_LENGTH];
        baseArray[0] = 1;
        checkArray[0] = 0;
    }
    
    public: bool Insert(char* newStr)
    {
        
        return false;
    }
    
    int GetIndex(char ch)
    {
        if (ch == '\0')
            return 1;
        return ch - 'a' + 2;
    }

    void Relocate (int s, int b)
    {
        int maxIndex = GetIndex('z');
        
        for (int i=1; i<=maxIndex; i++)
        {
            if (checkArray[baseArray[s] + i] == s)
            {
                checkArray[b + i] = s;
                baseArray[b + i] = baseArray[baseArray[s] + i];
                
            }
        }
    }
    public: bool Exists(char* newStr)
    {
        int s = 0;
        int index = 0;
        int chIndex = 0;
        
        while(chIndex != 1)
        {
            int chIndex = GetIndex(newStr[index]);
            int t = baseArray[s] + chIndex;
            if (checkArray[t] != s)
                break;
            s = t;
        }
        
        return (chIndex == 1);
    }
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    long int count = 0;
    long int notinserted = 0;
    Trie* myTrie = new Trie();
    ifstream file;
    file.open("words.txt");
    for( std::string line; getline( file, line ); )
    {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        
        istringstream ifstream(line);
        
        string word;
        while (getline(ifstream, word, ' '))
        {
            cout << word << endl;
            char* wordToInsert = const_cast<char*>(word.c_str());
            
            bool didInsert = myTrie->Insert(wordToInsert);
            if (didInsert)
            {
                count++;
            }
            else
            {
                notinserted++;
            }
        }
    }
    
    cout << "Total number of words inserted : "  << count << endl;
    cout << "Total number of words not inserted : "  <<   notinserted << endl;
    cout << "Total number of nodes : " << myTrie->GetNodeCount() << endl;
    cout << endl;

    cout << "Please enter a string to check :" << endl;
    
    string inputstr;
    while (true)
    {
        getline(cin, inputstr);
        if (inputstr.length() == 0)
            break;
        cout << myTrie->Exists(const_cast<char*>(inputstr.c_str())) << endl;
    }
    
    return 0;
}

