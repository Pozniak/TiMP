#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "aes.h"
#include "gost_89.h"
#include "blow.h"
using namespace std;
using namespace CryptoPP;

int main ()
{
    unsigned op, cip;
    string FIn, FOut, Pass;

    do {
        cout << "Введите действие (0 - Выход, 1 - Шифрование, 2 - Расшифрование): ";
        cin >> op;

        if (op != 0) {
            cout << "Введите тип алгоритма: (1 - AES-256, 2 - GOST-89, 3 - BLOWFISH): ";
            cin >> cip;
        }

        if (op > 3) {
            cerr << "Ошибка. Неверная операция\n";
        }

        else if (op > 0) {
            cout << "Введите имя файла для совершения действия: ";
            cin >> FIn;

            cout << "Введите имя файла для записи действия: ";
            cin >> FOut;

            cout << "Введите пароль: ";
            cin >> Pass;

            if (cip == 1) {
                AES_Cryptor aes(FIn, FOut, Pass);

                if (op == 1) {
                    if (aes.AES_Encrypt())
                        cout << "Файл зашифрован!" << endl;
                    else
                        cout << "Ошибка зашифрования!" << endl;
                } else {
                    if (aes.AES_Decrypt())
                        cout << "Файл расшифрован!" << endl;
                    else
                        cout << "Ошибка расшифрования!" << endl;
                }
            }


            else if (cip == 2) {
                GOST_Cryptor go(FIn, FOut, Pass);

                if (op == 1) {
                    if (go.GOST_Encrypt())
                        cout << "Файл зашифрован!" << endl;
                    else
                        cout << "Ошибка зашифрования!" << endl;
                } else {
                    if (go.GOST_Decrypt())
                        cout << "Файл расшифрован!" << endl;
                    else
                        cout << "Ошибка расшифрования!" << endl;
                }
            } else if (cip == 3) {
                BLOW_Cryptor b(FIn, FOut, Pass);

                if (op == 1) {
                    if (b.BLOWFISH_Encrypt())
                        cout << "Файл зашифрован!" << endl;
                    else
                        cout << "Ошибка зашифрования!" << endl;
                } else {
                    if (b.BLOWFISH_Decrypt())
                        cout << "Файл расшифрован!" << endl;
                    else
                        cout << "Ошибка расшифрования!" << endl;
                }
            } else {
                cerr << "Ошибка! Неправильный алгоритм!!!\n";
            }
        }

    } while (op != 0);

    return 0;
}
