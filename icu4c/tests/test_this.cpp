#include <gtest/gtest.h>
#include <string>
#include <unicode/ustring.h>
#include <unicode/unistr.h>
#include <unicode/uloc.h>
#include <unicode/putil.h>
#include <unicode/uclean.h>
#include <unicode/casemap.h>
#include <codecvt>

using namespace icu;
using namespace std;
UErrorCode setupStatus = U_ZERO_ERROR;
string setupError = "";

void setup_icu()
{
    // ICU setup
    // we won't run asserts here, but check later.
    // Hack: Meson wrap setup is not right. workaround for <https://github.com/mesonbuild/wrapdb/issues/2020>
    u_setDataDirectory("../subprojects/icu/source/data/in");
    u_init(&setupStatus);
    uloc_setDefault("el", &setupStatus);
}

void ASSERT_EQ_UTF8(const u16string& s1, const u16string& s2) {
    wstring_convert<codecvt_utf8_utf16<char16_t>,char16_t> cvt8;
    std::string u1 = cvt8.to_bytes(s1);
    std::string u2 = cvt8.to_bytes(s2);
    ASSERT_EQ(u1, u2);
}

void ASSERT_EQ_UTF8(const u16string& s1, UnicodeString s2) {
    u16string s2s(s2.getTerminatedBuffer());
    ASSERT_EQ_UTF8(s1, s2s);
}

/* check that setup went through OK */
TEST(SetupOk, Basic)
{
    if (U_FAILURE(setupStatus)) {
        setupError = string(u_errorName(setupStatus));
    }
    ASSERT_EQ(setupError, string(""));
    ASSERT_FALSE(U_FAILURE(setupStatus));
    ASSERT_EQ(string("el"), string(uloc_getDefault()));
}

TEST(CaseTest, Basic)
{

    // I. Basic Case Conversion
    {
        // Test 1 simple lowercase to uppercase
        // ----
        const u16string input  = u"αβγδεζηθικλμνξοπρστυφχψω";
        const u16string expect = u"ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ";    UErrorCode status = U_ZERO_ERROR;

        UnicodeString s = input;
        // ----
        s.toUpper();
        // ----
        ASSERT_EQ_UTF8(expect, s);
    }
    {
        // Test 2: Simple Uppercase to Lowercase
        // ----
        const u16string input  = u"ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ";
        const u16string expect = u"αβγδεζηθικλμνξοπρστυφχψω";
        UnicodeString s = input;
        // ----
        s.toLower();
        // ----
        ASSERT_EQ_UTF8(expect, s);
    }
}

GTEST_API_ int
main(int argc, char **argv)
{
    setup_icu();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
