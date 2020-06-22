#include <UnitTest++/UnitTest++.h>
#include "/home/daniil/C++/timp/test2/modAlphaCipher.h"
#include "/home/daniil/C++/timp/test2/modAlphaCipher.cpp"
struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};
SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("БВГБВ",modAlphaCipher("БВГ").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("БВГДЕ",modAlphaCipher("БВГДЕЁЖЗИЙ").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("БВГБВ",modAlphaCipher("бвг").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Б1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("Б,В"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("Б В"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("РПЕЫЖНТИБУПОФГЩЁДПЮТНЙОЧБМЁДЛПВЭЯЪЁКТАЕСЁГОЁДСЁШЁТЛПКБНХПСЬТПРСАЗЖОТУЁЦОЙШЁТЛЙНЙУСФЕОПТУАНЙ",p->encrypt("ПОДЪЁМСЗАТОНУВШЕГОЭСМИНЦАЛЕГКОБЬЮЩЕЙСЯДРЕВНЕГРЕЧЕСКОЙАМФОРЫСОПРЯЖЁНСТЕХНИЧЕСКИМИТРУДНОСТЯМИ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("РПЕЫЖНТИБУПОФГЩЁДПЮТНЙОЧБМЁДЛПВЭЯЪЁКТАЕСЁГОЁДСЁШЁТЛПКБНХПСЬТПРСАЗЖОТУЁЦОЙШЁТЛЙНЙУСФЕОПТУАНЙ",p->encrypt("подъёмсзатонувшегоэсминцалегкобьющейсядревнегреческойамфорысопряжёнстехническимитрудностями"));
    }
    TEST_FIXTURE(KeyB_fixture,
                 StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("РПЕЫЖНТИБУПОФГЩЁДПЮТНЙОЧБМЁДЛПВЭЯЪЁКТАЕСЁГОЁДСЁШЁТЛПКБНХПСЬТПРСАЗЖОТУЁЦОЙШЁТЛЙНЙУСФЕОПТУАНЙ",p->encrypt("ПОДЪЁМ С ЗАТОНУВШЕГО ЭСМИНЦА ЛЕГКО БЬЮЩЕЙСЯ ДРЕВНЕГРЕЧЕСКОЙ АМФОРЫ СОПРЯЖЁН С ТЕХНИЧЕСКИМИ ТРУДНОСТЯМИ!!!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ТШБТУМЙГПДПОПГПДПДПЕБ", p->encrypt("Счастливого Нового 2020 Года"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1234+8765=9999"),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ОНГЩЕЛРЖЯСНМТБЧДВНЬРЛЗМХЯКДВЙНАЫЭШДИРЮГПДБМДВПДЦДРЙНИЯЛУНПЪРНОПЮЁЕМРСДФМЗЦДРЙЗЛЗСПТГМНРСЮЛЗ",modAlphaCipher("Я").encrypt("ПОДЪЁМСЗАТОНУВШЕГОЭСМИНЦАЛЕГКОБЬЮЩЕЙСЯДРЕВНЕГРЕЧЕСКОЙАМФОРЫСОПРЯЖЁНСТЕХНИЧЕСКИМИТРУДНОСТЯМИ"));
    }
}
SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ПОДЪЁМСЗАТОНУВШЕГОЭСМИНЦАЛЕГКОБЬЮЩЕЙСЯДРЕВНЕГРЕЧЕСКОЙАМФОРЫСОПРЯЖЁНСТЕХНИЧЕСКИМИТРУДНОСТЯМИ",p->decrypt("РПЕЫЖНТИБУПОФГЩЁДПЮТНЙОЧБМЁДЛПВЭЯЪЁКТАЕСЁГОЁДСЁШЁТЛПКБНХПСЬТПРСАЗЖОТУЁЦОЙШЁТЛЙНЙУСФЕОПТУАНЙ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("рпеЫЖНТИБУПОФГЩЁДПЮТНЙОЧБМЁДЛПВЭЯЪЁКТАЕСЁГОЁДСЁШЁТЛПКБНХПСЬТПРСАЗЖОТУЁЦОЙШЁТЛЙНЙУСФЕОПТУАНЙ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("РПЕЫЖН Т ИБУПОФГЩЁДП ЮТНЙОЧ БМЁДЛ ПВ ЭЯЪЁКТА ЕСЁГОЁДСЁ ШЁ ТЛПКБНХ ПСЬТПРС АЗЖОТУЁЦ ОЙШЁТЛЙНЙУСФЕОПТУАНЙ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("ШБТУМЙГПДПОПГПДП2020ДПЕБ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("АЕЕПМЙГП,ДПОПГПДП"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ПОДЪЁМСЗАТОНУВШЕГОЭСМИНЦАЛЕГКОБЬЮЩЕЙСЯДРЕВНЕГРЕЧЕСКОЙАМФОРЫСОПРЯЖЁНСТЕХНИЧЕСКИМИТРУДНОСТЯМИ",modAlphaCipher("Я").decrypt("ОНГЩЕЛРЖЯСНМТБЧДВНЬРЛЗМХЯКДВЙНАЫЭШДИРЮГПДБМДВПДЦДРЙНИЯЛУНПЪРНОПЮЁЕМРСДФМЗЦДРЙЗЛЗСПТГМНРСЮЛЗ"));
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}