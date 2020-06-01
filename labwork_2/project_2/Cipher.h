#pragma once
#include <string>
#include <stdexcept>
using namespace std;
class Cipher
{
    char** value;
    int v, n;
    string getValidText(const string& s);
public:
    Cipher() = delete;
    Cipher(int key, const string& s);
    string encrypt(const string& open_text);
    string decrypt(const string& cipher_text);
    ~Cipher();
};
class Error: public invalid_argument
{
public:
    explicit Error (const string& what_arg):        
    invalid_argument(what_arg) {}    
    explicit Error (const char* what_arg):        
    invalid_argument(what_arg) {}
};
