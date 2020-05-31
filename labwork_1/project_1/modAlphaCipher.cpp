#include "modAlphaCipher.h"
modAlphaCipher::modAlphaCipher(const std::string& skey)
{
    for (unsigned i=0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    std::wstring wskey = wnext(skey);
    key = convert(wskey);
}
std::string modAlphaCipher::encrypt(const std::string& open_text)
{
    std::wstring open_wtext = wnext (open_text);
    std::vector<int> work = convert(open_wtext);
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
std::string modAlphaCipher::decrypt(const std::string& cipher_text)
{
    std::wstring cipher_wtext = wnext (cipher_text);
    std::vector<int> work = convert(cipher_wtext);
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
inline std::vector<int> modAlphaCipher::convert(const std::wstring& ws)
{
    std::vector<int> result;
    for(auto wc:ws) {
        result.push_back(alphaNum[wc]);
    }
    return result;
}
inline std::string modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring wresult;
    for(auto i:v) {
        wresult.push_back(numAlpha[i]);
    }
    std::string result = fwnext(wresult);
    return result;
}
std::wstring modAlphaCipher::wnext(const std::string& s)
{
    std::locale loc("ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
    std::wstring ws = codec.from_bytes(s);
    return ws;
}
std::string modAlphaCipher::fwnext(const std::wstring& ws)
{
    std::locale loc("ru_RU.UTF-8");
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
    std::string s = codec.to_bytes(ws);
    return s;
}