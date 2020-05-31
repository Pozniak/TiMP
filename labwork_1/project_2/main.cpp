#include <iostream>
#include <cctype>
#include "Cipher.h"
using namespace std;
bool isValid(int key,const string& s )
{
    for (auto c:s)
        if (!isalpha(c))
            return false;
    if (key > s.size())
        return false;
    return true;
}
int main(int argc, char **argv)
{
    int key;
    string text;
    unsigned op;
    cout<<"Мишин Даниил Викторович | 111\n";
    do {
        cout<<"Выберете операцию (0-выход, 1-шифровать, 2-расшифровать): ";
        cin>>op;
        if (op > 2)
            cout<<"Незаконная операция\n";
        else if (op > 0) {
            cout<<"Шифр готов. Введите текст: ";
            cin>>text;
            cout<<"Введите ключ: ";
            cin>>key;
            if (!isValid(key, text)) {
                cerr<<"Ключ не действителен\n";
            } else {
                Cipher cipher(key, text);
                if (op==1) {
                    cout<<"Зашифрованнный текст: "<<cipher.encrypt(text)<<endl;
                } else {
                    cout<<"Расшифрованный текст: "<<cipher.decrypt(text)<<endl;
                }
            }
        }
    } while (op != 0);
    return 0;
}
