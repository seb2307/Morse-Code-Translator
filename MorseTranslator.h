#pragma once
#ifndef MORSETRANSLATOR_H
#define MORSETRANSLATOR_H
#include <string>
#include "MorseBST.h"

/*
 * Morse Translator class
 *
 * Contains very simple methods for translation from alphabet to Morse Code
 * a class has morse binary search tree instance for decoding from Morse Code to alphabet
 *
 * */
class MorseTranslator
{
public:
  MorseTranslator();
  ~MorseTranslator();

  static const char* translate2Morse(const char character);
  static void translate2MorseWholeString(const std::string* character, std::string* output);

  morsebst::MorseBST *getMorseBst() const;

private:
  morsebst::MorseBST *morseBst;


};

#endif

