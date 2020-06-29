#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <cryptopp/gost.h>

using namespace std;
using namespace CryptoPP;

class GOST_Cryptor
{
private:
  string FileIn;
  string FileOut;
  string psw;

  string salt = "uparygjfv3iwu4oiejfni3co4wiefnjbvieoiwejfnveiorsiefjnveirosiefjnveripbn";
public:
  GOST_Cryptor() = delete;
  GOST_Cryptor(const string& Input, const string& Output, const string& Pass);
  bool GOST_Encrypt ();
  bool GOST_Decrypt ();
};