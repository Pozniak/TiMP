#include "Cipher.h"
Cipher::Cipher(int key, const string& s)
{
    n = key;
    v = ((s.size() - 1)/n + 1);
    value = new char * [v];
    for (int i = 0; i < v; i++) {
        value[i] = new char [n];
    }
}
string Cipher::encrypt(const string& open_text)
{
    for (int i=0; i < v; i++)
        for (int j=0; j < n; j++)
            value[i][j] = '*';
    for (unsigned i = 0; i < open_text.size(); i ++)
        value[i/n][i%n] = open_text[i];
    string cipher_text;
    for (int i = n - 1; i >= 0; i --)
        for (int j = 0; j < v; j++)
            cipher_text += value[j][i];
    return cipher_text;
}
string Cipher::decrypt(const string& cipher_text)
{
    for (int i=0; i < v; i++)
        for (int j=0; j < n; j++)
            value[i][j] = '*';
    for (unsigned i = 0; i < cipher_text.size(); i ++)
        value[i%v][i/v] = cipher_text[i];
    string open_text;
    for (int i = 0; i < v; i ++)
        for (int j = n - 1; j >= 0; j--)
            open_text += value[i][j];
    return open_text;
}
Cipher::~Cipher()
{
    for (int i = 0; i < v; i++) {
        delete [] value[i];
    }
    delete [] value;
}
