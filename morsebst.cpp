#include "MorseBST.h"
#include <QtDebug>
#include <sstream>

namespace morsebst {
static const char* const numbers[] =
{
    "-----", // 0
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----."  // 9
};

static const char* const letters[] =
{
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--.." // Z
};


MorseBST::MorseBST() : root(nullptr)
{
    initMorseBST();
}

MorseBST::~MorseBST()
{
    delete root; // this will trigger automatic deletion all children recursivelly
}

void MorseBST::initMorseBST()
{
    if(root == nullptr) root = new MorseBST::Node( nullptr, '\0');
    //    std::vector<MorseBST::Node*> deb_nodes;
    for( int i =0; i< LETTERS; i++)
        put(&root, letters[i], 'A' + i);
    for( int i =0; i< NUMBERS; i++)
        put(&root, numbers[i], '0' + i);

    //    for(std::vector<MorseBST::Node*>::iterator it = deb_nodes.begin() ; it != deb_nodes.end(); ++it)
    //    {
    //        qDebug() << "getLeft_dit: " << *(*it)->getLeft_dit() << "getRight_dat: " << *(*it)->getRight_dah() << "getValue: " << (*it)->getValue() ;
    //    }
}

MorseBST::Node *MorseBST::put(MorseBST::Node **x, const char* key, char value)
{
    if(*x == nullptr) *x = new MorseBST::Node( key, '\0');
    if(*key == '\0')
    {
        (*x)->setValue(value);
    }
    if(*key == '.') put((*x)->getLeft_dit(), ++key, value);
    else if(*key == '-') put((*x)->getRight_dah(), ++key, value);
    return *x;
}

char *MorseBST::get(MorseBST::Node *x, const char* key)
{
    if (x == nullptr) return nullptr;
    if(*key == '\0') return x->getValue();
    if(*key == '.') return get(*x->getLeft_dit(), ++key);
    else if(*key == '-') return get(*x->getRight_dah(), ++key);
    else
        return nullptr;
}

char *MorseBST::get(const char* key)
{
    return get(root, key);
}

MorseBST::Node::Node(const char *key, char value) :  key(key),
    value(value)
{
    left_dit = nullptr;
    right_dah = nullptr;
    N++;
}

MorseBST::Node::~Node()
{
    if(left_dit != nullptr)
        delete left_dit;
    if(right_dah != nullptr)
        delete right_dah;
    N--;
    if(N < 0)
        qDebug() << "Invalid parameter. accepted a-z and 0-9 only";
}

void MorseBST::Node::setValue(char value)
{
    this->value = value;
}

MorseBST::Node **MorseBST::Node::getRight_dah()
{
    return &right_dah;
}


char* MorseBST::Node::getValue()
{
    return &value;
}

MorseBST::Node** MorseBST::Node::getLeft_dit()
{
    return &left_dit;
}

void MorseBST::tokenize(std::string const &str, const char delim,
                        std::vector<std::string> &out)
{
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

void MorseBST::decodeWholeText(std::string* input_str, std::string* output_str)
{
    const char delim = '/';
    std::string & out_str= *output_str;

    std::vector<std::string> out;
    tokenize(*input_str, delim, out);

    for (auto &s: out) {
        qDebug() << s.c_str() << '\n';
    }

    for(auto &s: out)
    {
        std::vector<std::string> single_letters;
        tokenize(s, ' ', single_letters);
        for(auto &sl : single_letters)
        {
            if(*sl.c_str() == '\0')
                continue;

            const char* decoded_ascii_ptr = get(sl.c_str());

            if(decoded_ascii_ptr != nullptr)
            {
                char dec_ascii = *decoded_ascii_ptr;
                out_str += dec_ascii;
            }
        }
        out_str += ' ';
    }

}

}
