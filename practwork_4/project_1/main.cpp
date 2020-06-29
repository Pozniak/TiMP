#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
#include <string>
using namespace std;
int main (int argc, char* argv[])
{
    using namespace CryptoPP;
    SHA1 hash;
    std::cout << "Имя: " << hash.AlgorithmName() << std::endl;
    std::cout << "Размер хэша: " << hash.DigestSize() << std::endl;
    std::cout << "Размер блока: " << hash.BlockSize() << std::endl;
    std::string message;
    ifstream file;
    file.open("message.txt");
    while (getline(file,message)){
    std::vector<byte> digest(hash.DigestSize());
    hash.Update((const byte*)message.data(), message.size());
    hash.Final(digest.data());
    std::cout << "Сообщение: " << message << std::endl;
    std::cout << "Хэш: ";
    StringSource(digest.data(), digest.size(), true, new HexEncoder(new FileSink(std::cout)));
    std::cout << std::endl;
    }
    file.close();
    return 0;
}