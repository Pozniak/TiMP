#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include "blow.h"

BLOW_Cryptor::BLOW_Cryptor(const string& Input, const string& Output, const string& Pass)
{
    FileIn = Input;
    FileOut = Output;
    psw = Pass;
}

bool BLOW_Cryptor::BLOWFISH_Encrypt ()
{
    SecByteBlock key(Blowfish::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA512> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)psw.data(), psw.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);

    cout << "\nКлюч: ";
    StringSource(key.data(), key.size(), true, new HexEncoder( new FileSink(cout) ));

    AutoSeededRandomPool prng;
    byte iv[Blowfish::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));

    ofstream pull(string(FileOut + ".iv").c_str(), ios::out | ios::binary);
    pull.write((char*)iv, Blowfish::BLOCKSIZE);
    pull.close();

    cout << "\nIV Успешно создан: " << FileOut << ".iv" << endl;

    try {
        CBC_Mode<Blowfish>::Encryption encr;
        encr.SetKeyWithIV(key, key.size(), iv);

        FileSource fs(FileIn.c_str(), true, new StreamTransformationFilter(encr, new FileSink(FileOut.c_str())));
    }

    catch (const Exception& e) {
        cerr << e.what() << endl;

        return false;
    }

    return true;
}

bool BLOW_Cryptor::BLOWFISH_Decrypt ()
{
    SecByteBlock key(Blowfish::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA512> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)psw.data(), psw.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);

    cout << "Ключ: ";
    StringSource(key.data(), key.size(), true, new HexEncoder( new FileSink(cout) ));

    cout << endl;

    byte iv[Blowfish::BLOCKSIZE];
    ifstream pool(string(FileIn + ".iv").c_str(), ios::in | ios::binary);

    if (pool.good()) {
        pool.read((char*)&iv, Blowfish::BLOCKSIZE);
        pool.close();
    }

    else if (pool.bad()) {
        cerr << "IV файл не найден!" << endl;
        pool.close();
        return false;
    }

    else {
        cerr << "Неверный файл IV!" << endl;
        pool.close();
        return false;
    }

    try {
        CBC_Mode<Blowfish>::Decryption decr;
        decr.SetKeyWithIV(key, key.size(), iv);

        FileSource fs(FileIn.c_str(), true, new StreamTransformationFilter(decr, new FileSink(FileOut.c_str())));
    }

    catch (const Exception& e) {
        cerr << e.what() << endl;

        return false;
    }

    return true;
}