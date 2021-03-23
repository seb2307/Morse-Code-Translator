#pragma once
#ifndef MORSETRANSLATOR_H
#define MORSETRANSLATOR_H
#include <string>
class MorseTranslator
{
public:
  MorseTranslator() {};
  ~MorseTranslator() {};

  static const char* translate2Morse(const char character);
  static void translate2MorseWholeString(const std::string* character, std::string* output);

};

#endif

