
#include "../src/XmlParser.hpp"
#include "../src/XmlParser.cpp"

#include <gtest/gtest.h>

TEST(Parser, unescapeString)
{
    struct _
    {
        static std::string unescapeString(const std::string& testStr, const std::string& testSuffix)
        {
            std::string testData = testStr + testSuffix;
            return ::unescapeString(testData.c_str(), testStr.size());
        }
    };

    EXPECT_EQ(_::unescapeString("test", "abc"), "test");
    EXPECT_EQ(_::unescapeString("test&amp;", "abc"), "test&");
    EXPECT_EQ(_::unescapeString("&amp;test", "abc"), "&test");
    EXPECT_EQ(_::unescapeString("&amp;&amp;", "abc"), "&&");
    EXPECT_EQ(_::unescapeString("a&amp;&amp;b", "abc"), "a&&b");
    EXPECT_EQ(_::unescapeString("&#38;", ""), "&");
    EXPECT_EQ(_::unescapeString("&amp", ";"), "&amp");
    EXPECT_EQ(_::unescapeString("a&amp", ";"), "a&amp");
    EXPECT_EQ(_::unescapeString("&#38;&#38;", ""), "&&");
    EXPECT_EQ(_::unescapeString("&#38abc38;", ""), "&#38abc38;");
    EXPECT_EQ(_::unescapeString("&a;", ""), "&a;");
    EXPECT_EQ(_::unescapeString("&;", ""), "&;");
    EXPECT_EQ(_::unescapeString("&ampx;", ""), "&ampx;");
}

TEST(Parser, decodeText)
{
    struct _
    {
        static std::string decodeText(const std::string& testStr, const std::string& testSuffix)
        {
            std::string testData = testStr + testSuffix;
            return ::decodeText(testData.c_str(), testStr.size());
        }
    };

    EXPECT_EQ(_::decodeText("<!-- abc -->", "abc"), "");
    EXPECT_EQ(_::decodeText("<!-- abc - -->", "abc"), "");
    EXPECT_EQ(_::decodeText("1<!-- abc -->2", "abc"), "12");
    EXPECT_EQ(_::decodeText("1<!-- abc -->2<!-- abc -->3", "abc"), "123");
    EXPECT_EQ(_::decodeText("a&amp;b", "abc"), "a&b");
    EXPECT_EQ(_::decodeText("&lt;&gt;&quot;&apos;&#38;", "abc"), "<>\"'&");
    EXPECT_EQ(_::decodeText("a&amp;<!-- &amp; -->b", "abc"), "a&b");
    EXPECT_EQ(_::decodeText("a&amp;<![CDATA[&amp;]]>b", "abc"), "a&&amp;b");
}
