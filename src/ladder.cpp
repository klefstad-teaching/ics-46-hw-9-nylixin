#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"
using namespace std;

// OK THINGS TO KEEP IN MIND!
// USE BREADTH FIRST SEARCH
// CHECK INPUT RIGHT AWAY TO MAKE SURE FIRST WORD AND LAST WORD NOT THE SAME
// IT'S OK TO ADD/REMOVE SINGLE LETTERS BETWEEN STRINGS @ EACH HOP
// DO NOT REUSE WORDS
// EVERY OTHER WORD BESIDES START HAS TO BE FROM DICTIONARY
void error(string word1, string word2, string msg)
{
    cout << "There has been an issue with your words: " << word1 << " and " << word2 << endl;
    cout << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    // from wikpedia
    // minimum # of operators between [str1 characters] [str2 characters] = ed[str1][str2]
    // for all chars, if str[i] == str2[j], return ; distance is the SAME
    // for all chars, if str[i] != str2[j], 
    // deletion = 1 + min(ed[i - 1][j])
    // insertion = ed[i][j - 1]
    // substitution = ed[i - 1][j - 1]

    int word1size = str1.size();
    int word2size = str2.size();

    // we have to make sure that we can delete, insert, or substitute within d operations
    if (abs(word1size - word2size) > d) {return false;}

    // characters that are different counter
    int diff_count = 0;

    if (word1size == word2size)
    {
        // words have the same length, no need to delete or insert
        for (int i = 0; i < word1size; i++)
        {
            if (str1[i] != str2[i])
            {
                ++diff_count;
                // if we can't do it within d operations
                if (diff_count > d) {return false;}
            }
        }  
    } 
    else
    {
        // words that are 1 letter apart: i.e. "cat" and "chat"
        int w1loopcount = 0;
        int w2loopcount = 0;

        // traversing through each word until one word is completely traversed through
        while (w1loopcount < word1size && w2loopcount < word2size)
        {   
            // encountering a letter that is different
            if (str1[w1loopcount] != str2[w2loopcount])
            {
                ++diff_count;
                // if we can't do it within d operations
                if (diff_count > d) {return false;}

                // we found a mismatch, so now we skip the longer word and keep going
                if (word1size > word2size) {w1loopcount++;}
                else {w2loopcount++;}
            }
            else
            {
                // continue to traverse if they're equal (no mismatch)
                w1loopcount++;
                w2loopcount++;
            }
        }
        // one word has an extra character if the while loop is skipped
        if (w1loopcount < word1size || w2loopcount < word2size)
        {
            ++diff_count;
        }
    }
    // return if we have difference count less than or equal to d
    return diff_count <= d;
}

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    // if the beginning and the end word are the same return an empty ladder
    if (begin_word == end_word)
    {
        error(begin_word, end_word, "These words are the same");
        return {};
    }

    if (word_list.find(end_word) == word_list.end())
    {
        error(begin_word, end_word, "End word is not in dictionary");
        return {};
    }

    // creating ladder vector queue and pushing first word
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    // creating visited string set and inserting first word
    set<string> visited;
    visited.insert(begin_word);
    
    while(!ladder_queue.empty())
    {
        // adding first ladder
        vector<string> ladder = ladder_queue.front();
        // removing ladder from queue
        ladder_queue.pop();
        // last word in the current ladder 
        string last_word = ladder.back();

        // if end word is reached we can return immediately
        if (last_word == end_word) {return ladder;}

        // finding words that are adjacent
        for (const string& word : word_list)
        {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end())
            {
                // insert the adjacent word into visited
                visited.insert(word);

                // make a copy of our current ladder and add our word
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                // if the end word is reached we can return immediately
                if (word == end_word) {return new_ladder;}

                // adding the new ladder to the queue
                ladder_queue.push(new_ladder);
            }
        }
    }
    // returning no ladder found
    return {};

    /* PSEUDOCODE
    function generate_word_ladder(begin_word, end_word, word_list):
        ladder_queue = queue of vector of strings
        ladder_queue.push([begin_word])
        visited = set of strings
        visited.insert(begin_word)
        while ladder_queue is not empty:
            ladder = ladder_queue.pop_front()
            last_word = last element of ladder
            for word in word_list:
                if is_adjacent(last_word, word):
                    if word not in visited:
                        visited.insert(word)
                        new_ladder = copy of ladder
                        new_ladder.push_back(word)
                        if word equals end_word:
                            return new_ladder
                        ladder_queue.push(new_ladder)
        return no ladder found
    end function
    */
}

void load_words(set<string> & word_list, const string& file_name)
{
    // open the file
    ifstream file(file_name);

    // make sure file can be opened
    if (!file)
    {
        cerr << "Error with opening file: " << file_name << endl;
        return;
    }

    // declare a string word as the var for all words
    // as we read the file, insert all the words into word list
    string word;
    while (file >> word)
    {
        word_list.insert(word);
    }

    file.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    // if the ladder is empty we won't have anything to print
    if (ladder.empty())
    {
        cout << "No word ladder found.\n" << endl;
        return;
    }

    cout << "Word ladder found: ";
    // prints a word, then the -> size for every word,
    // unles it's the last word
    size_t ladder_size = ladder.size();
    for (size_t i = 0; i < ladder_size; i++)
    {
        cout << ladder[i];
        //if (i < ladder_size - 1) { cout << " ";}
        cout << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

    /* CODE FROM WRITE UP
    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
    void verify_word_ladder() {
        set<string> word_list;
        load_words(word_list, "words.txt");
        my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
        my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
        my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
        my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
        my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
        my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
    }
    */
}

/*
DONE void error(string word1, string word2, string msg);
DONE bool edit_distance_within(const std::string& str1, const std::string& str2, int d);
DONE bool is_adjacent(const string& word1, const string& word2);
DONE vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);
DONE void load_words(set<string> & word_list, const string& file_name);
DONE void print_word_ladder(const vector<string>& ladder);
DONE void verify_word_ladder();
*/
