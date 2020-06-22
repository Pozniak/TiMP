#include <UnitTest++/UnitTest++.h>
#include "/home/daniil/C++/timp/cipher/Cipher.h"
#include "/home/daniil/C++/timp/cipher/Cipher.cpp"
struct KeyThree_fixture {
    Cipher * p;
    KeyThree_fixture()
    {
        p = new Cipher(5,"THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG");
    }
    ~KeyThree_fixture()
    {
        delete p;
    }
};
SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("UROPRAGQBFMELOEKNUVEDHCWJOHYTIOXSTZ",Cipher(5,"THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG").encrypt("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG"));
    }
    TEST(InValidKey) {
        CHECK_THROW(Cipher(1,"THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG").encrypt("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG"),Error);
    }
}
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyThree_fixture,UpCaseString) {
        CHECK_EQUAL("UROPRAGQBFMELOEKNUVEDHCWJOHYTIOXSTZ",p->encrypt("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG"));
    }
    TEST_FIXTURE(KeyThree_fixture,LowCaseString) {
        CHECK_EQUAL("uropragQBFmeLoeknuveDhcwJOhyTioxsTz",p->encrypt("TheQuickBrownFoxJumpsOverTheLazyDog"));
    }
    TEST_FIXTURE(KeyThree_fixture,StringWithWhitspaceAndPunct) {
        CHECK_THROW(p->encrypt("The Quick Brown Fox Jumps Over The Lazy Dog!!!"),Error);
    }
    TEST_FIXTURE(KeyThree_fixture,StringWithNumbers) {
        CHECK_THROW(p->encrypt("THE3QUI4CKBRO5WN2FOXJUMPSO1VERTHELAZYDOG"),Error);
    }
    TEST_FIXTURE(KeyThree_fixture,EmptyString) {
        CHECK_THROW(p->encrypt(""),Error);
    }
    TEST_FIXTURE(KeyThree_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1234+8765=9999"),Error);
    }
}
SUITE(DecryptTest)
{
    TEST_FIXTURE(KeyThree_fixture,UpCaseString) {
        CHECK_EQUAL("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG",p->decrypt("UROPRAGQBFMELOEKNUVEDHCWJOHYTIOXSTZ"));
    }
    TEST_FIXTURE(KeyThree_fixture,LowCaseString) {
        CHECK_EQUAL("TheQuickBrownFoxJumpsOverTheLazyDog",p->decrypt("uropragQBFmeLoeknuveDhcwJOhyTioxsTz"));
    }
    TEST_FIXTURE(KeyThree_fixture,WhitespaceString) {
        CHECK_THROW(p->decrypt("URO PRAGQ BFMEL OEK NUVED HCWJ OHY TIOX STZ"),Error);
    }
    TEST_FIXTURE(KeyThree_fixture,DigitsString) {
        CHECK_THROW(p->decrypt("UR46OPRA52GQBFME66LOEKNUVE67DHCWJ7OHYTIOX3STZ"),Error);
    }
    TEST_FIXTURE(KeyThree_fixture,EmptyString) {
        CHECK_THROW(p->decrypt(""),Error);
    }
    TEST_FIXTURE(KeyThree_fixture,NoAlphaString) {
        CHECK_THROW(p->decrypt("1234+8765=9999"),Error);
    }
    TEST_FIXTURE(KeyThree_fixture,PunctString) {
        CHECK_THROW(p->decrypt("UROPRAGQBFMELOEKNUVEDHCWJOHYTIOXSTZ!!!"),Error);
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}