#ifndef MORSEBST_H
#define MORSEBST_H

#define LETTERS 26
#define NUMBERS 10
#define MAX_ALLOWED_CHARS (LETTERS + NUMBERS + 1) //1 additionally for space character

#include <string>
#include <vector>

namespace morsebst {
/*
 * Morse Binary Search Tree
 *
 * Description:
 *  for Morse Code decoding purposes, the most convenient way
 *  is to describe all letters and numbers as binary tree, where
 *  for each encoded letter, algorithm traverses in either right nodes choice, standing for dahs '-'
 *  or left nodes direction standing for dits '.'
 *  Once each character of encoded letter is traversed, at the end of search, final node or leaf is found
 *  containing value of decoded alphabet character.
 *
 *  Binary search tree implementation is limited only to crutial functionality of Morse Code Translator.
 *  Creation of new nodes is only allowed for internal initialisation. A user has no permission to manipulate
 *  it's content.
 *
 */
class MorseBST
{

public:

    class Node
    {
    public:
        Node(const char* key, char value);

        //Destructor works in a recursive way, deleting node's children first
        ~Node();

        void setValue(char value);

        Node **getLeft_dit();

        Node **getRight_dah();

        char* getValue();

    private:

        const char *key;
        char value;
        Node *left_dit;  //pointer indicating a left child in a tree that has additional 'dit' sign
        Node *right_dah; //pointer indicating a right child in a tree that has additional 'dah' sign
        static int N;    // max number of all nodes created. not so much in use at least for actual functionality
    };


    MorseBST();
    ~MorseBST();
    void initMorseBST();
    int size();

    char* get(const char* key);

    // decodes a whole input string at once
    void decodeWholeText(std::string* input_str, std::string* output_str);


private:
    Node* put(Node **x, const char* key, char value);
    char* get(Node *x, const char* key);
    int size(Node *x);
    Node *root;
    void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

};
}


#endif // MORSEBST_H
