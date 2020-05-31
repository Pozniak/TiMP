#pragma once
#include <string>
using namespace std;
class Cipher
{
    char** value;
    int v, n;
public:
    Cipher() = delete;
    Cipher(int key, const string& s);
    string encrypt(const string& open_text);
    string decrypt(const string& cipher_text);
    ~Cipher();
};
