#ifndef MORSEBST_H
#define MORSEBST_H

#define LETTERS 26
#define NUMBERS 10
#define MAX_ALLOWED_CHARS (LETTERS + NUMBERS + 1) //1 additionally for space character

#include <string>
#include <vector>

namespace morsebst {
class MorseBST
{



public:

    class Node
    {
    public:
        Node(const char* key, char value);
        ~Node();

        void setValue(char value);

        Node **getLeft_dit();

        Node **getRight_dah();

        char* getValue();

    private:

        const char *key;
        char value;
        Node *left_dit;
        Node *right_dah;
        static int N;
    };
    MorseBST();
    ~MorseBST();
    void initMorseBST();
    int size();
    Node* put(char key, char value);
    char* get(const char* key);
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
