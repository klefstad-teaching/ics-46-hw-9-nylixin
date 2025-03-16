#include <gtest/gtest.h>
#include <iostream>

#include "dijkstras.h"
#include "ladder.h"
using namespace std;

TEST(ladder, errorMsg) {
  ostringstream out;
  streambuf* old_cout = cout.rdbuf(out.rdbuf());

  error("hi", "there", "this is my error");

  cout.rdbuf(old_cout);
  string output = out.str();

  EXPECT_NE(output.find("There has been an issue with your words: hi and there"), string::npos);
  EXPECT_NE(output.find("this is my error"), string::npos);
}

TEST(ladder, editDistance)
{
  EXPECT_TRUE(edit_distance_within("a", "b", 1));
  EXPECT_TRUE(edit_distance_within("aa", "ab", 1));
  EXPECT_TRUE(edit_distance_within("ba", "aa", 1));
  EXPECT_FALSE(edit_distance_within("too many changes", "for us", 1));
}

// lol the exact same test
TEST(ladder, isADJ)
{
  EXPECT_TRUE(is_adjacent("a", "b"));
  EXPECT_TRUE(is_adjacent("aa", "ab"));
  EXPECT_TRUE(is_adjacent("ba", "aa"));
  EXPECT_FALSE(is_adjacent("too many changes", "for us"));
}

TEST(ladder, generateWordLadderReturnsEmpty)
{
  set<string> my_words = {"bye notin in here"};
  vector<string> ladder = generate_word_ladder("firt word", "NOT IN THE LIST MUWAUAU", my_words);

  ASSERT_TRUE(ladder.empty());
}

// i feel like i don't need to do this test bc we already have one
TEST(ladder, generateWordLadderReturnsExpected)
{
  // creative ik
  set<string> my_words = {"yelbow", "elbow", "elow", "blow", "bloe", "blue"};
  vector<string> ladder = generate_word_ladder("yellow", "blue", my_words);
  vector<string> true_ladder = {"yellow", "yelbow", "elbow", "elow", "blow", "bloe", "blue"};

  EXPECT_EQ(ladder, true_ladder);
}

TEST(ladder, generateWordLadderReturnsExpectedShorter)
{
  set<string> my_words = {"orcange", "orchnge", "orchage", "orchare", "orchard"};
  vector<string> ladder = generate_word_ladder("orange", "orchard", my_words);
  vector<string> true_ladder = {"orange", "orcange", "orchnge", "orchage", "orchare", "orchard"};

  EXPECT_EQ(ladder, true_ladder);
}

TEST(ladder, lw)
{
  set<string> word_list;
  set<string> expected = {"hi", "my", "words"};
  load_words(word_list, "/home/anwinn/ICS46/HW9/src/test.txt");
  EXPECT_EQ(word_list, expected);
}

TEST(ladder, printLadder)
{
  ostringstream out;
  streambuf* old_cout = cout.rdbuf(out.rdbuf());

  vector<string> ladder = {"hi", "my", "words"};
  print_word_ladder(ladder);

  cout.rdbuf(old_cout);
  string output = out.str();

  EXPECT_NE(output.find("hi->my->words"), string::npos);
}

/*
DONE void error(string word1, string word2, string msg);
DONE bool edit_distance_within(const std::string& str1, const std::string& str2, int d);
DONE bool is_adjacent(const string& word1, const string& word2);
DONE vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);
DONE void load_words(set<string> & word_list, const string& file_name);
DONE void print_word_ladder(const vector<string>& ladder);
*/