#include "str_ops.h"

#include <gtest/gtest.h>

// ---------- str_len ----------

TEST(StrLen, NullPointerHasZeroLength) {
    EXPECT_EQ(str_len(nullptr), 0U);
}

TEST(StrLen, CountsCharactersBeforeTerminator) {
    EXPECT_EQ(str_len("hello"), 5U);
}

// ---------- str_alloc ----------

TEST(StrAlloc, CopiesStringToDynamicMemory) {
    char* copy = str_alloc("hello");

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy, "hello");

    str_delete(copy);
}

TEST(StrAlloc, CreatesIndependentCopy) {
    char source[] = "hello";
    char* copy = str_alloc(source);

    source[0] = 'H';

    EXPECT_STREQ(copy, "hello");
    str_delete(copy);
}

// ---------- str_copy ----------

TEST(StrCopy, CopiesToExistingBuffer) {
    char destination[16]{};

    str_copy(destination, "MAI");

    EXPECT_STREQ(destination, "MAI");
}

TEST(StrCopy, NullSourceProducesEmptyString) {
    char destination[16] = "old value";

    str_copy(destination, nullptr);

    EXPECT_STREQ(destination, "");
}

// ---------- str_delete ----------

TEST(StrDelete, FreesMemoryAndSetsPointerToNull) {
    char* text = str_alloc("delete me");

    str_delete(text);

    EXPECT_EQ(text, nullptr);
}

TEST(StrDelete, AcceptsNullPointer) {
    char* text = nullptr;

    str_delete(text);

    EXPECT_EQ(text, nullptr);
}

// ---------- str_substr ----------

TEST(StrSubstr, ExtractsMiddlePart) {
    char* result = str_substr("hello", 1, 3);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "ell");

    str_delete(result);
}

TEST(StrSubstr, TruncatesLengthAtStringEnd) {
    char* result = str_substr("hello", 3, 10);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "lo");

    str_delete(result);
}

TEST(StrSubstr, PositionBeyondEndProducesEmptyString) {
    char* result = str_substr("hello", 20, 3);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    str_delete(result);
}

// ---------- str_compare ----------

TEST(StrCompare, EqualStringsReturnZero) {
    EXPECT_EQ(str_compare("abc", "abc"), 0);
}

TEST(StrCompare, FirstDifferentCharacterDeterminesLess) {
    EXPECT_LT(str_compare("abc", "abd"), 0);
}

TEST(StrCompare, LongerStringAfterPrefixIsGreater) {
    EXPECT_GT(str_compare("abcd", "abc"), 0);
}

TEST(StrCompare, NullPointerIsTreatedAsEmptyString) {
    EXPECT_EQ(str_compare(nullptr, ""), 0);
    EXPECT_LT(str_compare(nullptr, "a"), 0);
    EXPECT_GT(str_compare("a", nullptr), 0);
}