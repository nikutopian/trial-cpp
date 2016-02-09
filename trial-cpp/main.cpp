//
//  main.cpp
//  DoubleArrayTrie
//
//  Created by User on 2/6/16.
//  Copyright © 2016 User. All rights reserved.
//

#include <iostream>

class Node
{
public: Node* childNodes[26] = {NULL};
public: bool IsEOW;
    
public: Node()
    {
        IsEOW = false;
    }
};


class Trie
{
    Node* RootNode;
public: Trie()
    {
        RootNode = new Node();
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
            if (index < 0 || index >= 26)
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
        
        if (node->childNodes[index] == NULL)
        {
            node->childNodes[index] = new Node();
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
    std::cout << "Hello, World!\nWhats up" << std::endl;
    
    Trie* myTrie = new Trie();
    char mystring[] = "hello";
    myTrie->Insert(mystring);
    char mystring2[] = "hell";
    myTrie->Insert(mystring2);
    char mystring3[] = "what";
    
    std::cout << myTrie->Exists(mystring) << std::endl;
    std::cout << myTrie->Exists(mystring3) << std::endl;
    
    
    return 0;
}

