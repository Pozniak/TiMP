#include <iostream>
#include <cctype>
#include <codecvt>
#include "modAlphaCipher.h"
#include <locale>
using namespace std;
void check(const string& Text, const string& key, const bool destructCipherText=false)
{
    try {
        locale loc("ru_RU.UTF-8");
        wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
        string cipherText;
        string decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText) {
            wstring ws = cipher.wnext(cipherText);
            ws.front() = tolower(ws.front(),loc);
            cipherText = cipher.fwnext(ws);
        }
        decryptedText = cipher.decrypt(cipherText);
        cout<<"Ключ = "<<key<<endl;
        cout<<Text<<endl;
        cout<<cipherText<<endl;
        cout<<decryptedText<<endl;
    } catch (const cipher_error & e) {
        cerr<<"Ошибка: "<<e.what()<<endl;
    }
}
int main(int argc, char **argv)
{
    cout<<"Мишин Даниил Викторович | 111\n";
    check("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ","Простой");
    check("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ","");
    check("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ","АБВГ123") ;
    check("В Темнице Сырой Вскормленный В Неволе Орел Молодой","Превосходно");
    check("123","АБВГ");
    check("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ","СОВЕРШЕННОСЕКРЕТНО", true);
    return 0;
}