#include "MorseTranslator.h"
#include "MorseBST.h"

MorseTranslator::MorseTranslator()
{
    morseBst = new morsebst::MorseBST();
}

MorseTranslator::~MorseTranslator() {
    delete morseBst; // recursivelly will delete all nodes in a binary search tree
}

const char* MorseTranslator::translate2Morse(const char character){
  switch (character) {
  case 'a':
  case 'A':
    return ".-";
  case 'b':
  case 'B':
    return "-...";
  case 'c':
  case 'C':
    return "-.-.";
  case 'd':
  case 'D':
    return "-..";
  case 'e':
  case 'E':
    return ".";
  case 'f':
  case 'F':
    return "..-.";
  case 'g':
  case 'G':
    return "--.";
  case 'h':
  case 'H':
    return "....";
  case 'i':
  case 'I':
    return "..";
  case 'j':
  case 'J':
    return ".---";
  case 'k':
  case 'K':
    return "-.-";
  case 'l':
  case 'L':
    return ".-..";
  case 'm':
  case 'M':
    return "--";
  case 'n':
  case 'N':
    return "-.";
  case 'o':
  case 'O':
    return "---";
  case 'p':
  case 'P':
    return ".--.";
  case 'q':
  case 'Q':
    return "--.-";
  case 'r':
  case 'R':
    return ".-.";
  case 's':
  case 'S':
    return "...";
  case 't':
  case 'T':
    return "-";
  case 'u':
  case 'U':
    return "..-";
  case 'v':
  case 'V':
    return "...-";
  case 'w':
  case 'W':
    return ".--";
  case 'x':
  case 'X':
    return "-..-";
  case 'y':
  case 'Y':
    return "-.--";
  case 'z':
  case 'Z':
    return "--..";
  case '0':
    return "-----";
  case '1':
    return ".----";
  case '2':
    return "..---";
  case '3':
    return "...--";
  case '4':
    return "....-";
  case '5':
    return ".....";
  case '6':
    return "-....";
  case '7':
    return "--...";
  case '8':
    return "---..";
  case '9':
    return "----.";
  case ' ':
    return "/";
  default:
      return " ";
  }
}


void MorseTranslator::translate2MorseWholeString(const std::string* str, std::string* output)
{
 for(std::string::const_iterator it = str->begin(); it != str->end(); ++it)
 {
     *output += MorseTranslator::translate2Morse(*it);
     *output += ' ';
 }
}

morsebst::MorseBST *MorseTranslator::getMorseBst() const
{
    return morseBst;
}
