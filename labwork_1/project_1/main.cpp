#include <iostream>
#include <cctype>
#include <codecvt>
#include "modAlphaCipher.h"
#include <locale>
using namespace std;
// проверка, чтобы строка состояла только из прописных букв
bool isValid(const string& s)
{
    locale loc("ru_RU.UTF-8");
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
    wstring ws = codec.from_bytes(s);
    for(auto wc:ws)        
        if (!isalpha(wc,loc) || !isupper(wc,loc))
            return false;
    return true;
}
int main(int argc, char **argv)
{
    string key;
    string text;
    unsigned op;
    cout<<"Мишин Даниил Викторович | 111\n";
    cout<<"Шифр готов. Введите ключ: ";
    cin>>key;
    if (!isValid(key)) {
        cerr<<"Ключ не действителен\n";
        return 1;
    }
    cout<<"Ключ загружен\n";
    modAlphaCipher cipher(key);
    do {
        cout<<"Шифр готов. Выберете операцию (0-выход, 1-шифровать, 2-расшифровать): ";
        cin>>op;
        if (op > 2) {
            cout<<"Незаконная операция\n";
        } else if (op >0) {
            cout<<"Шифр готов. Введите текст: ";
            cin>>text;
            if (isValid(text)) {
                if (op==1) {
                    cout<<"Зашифрованнный текст: "<<cipher.encrypt(text)<<endl;
                } else {
                    cout<<"Расшифрованный текст: "<<cipher.decrypt(text)<<endl;
                }
            } else {
                cout<<"Операция прервана: неверный текст\n";
            }
        }
    } while (op!=0);
    return 0;
}
