#pragma once
#include "../DataStructures/libds/heap_monitor.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Predicates.h"
#include "DataItem.h"
namespace comparators
{
    // Comparátor pre porovnanie stringov pod¾a slovenskej abecedy
    struct CompareAlphabetical {

        // Slovenská abeceda v poradí
        const std::string slovakAlphabet = "aáäbcèdïeéfghiíjklå¾mnòoóôpqrsštuúvwxyz";

        // Porovnanie jednotlivıch znakov pod¾a ich poradia v slovenskej abecede
        bool compareCharacters(char a, char b) {
            int a_order = slovakAlphabet.find(a);
            int b_order = slovakAlphabet.find(b);
            return a_order < b_order;
        }

        // Porovnanie stringov pod¾a slovenskej abecedy
        bool compareStrings(const std::string& a, const std::string& b) {
            size_t length = std::min(a.length(), b.length());
            for (size_t i = 0; i < length; i++) {
                if (a[i] != b[i]) {
                    return compareCharacters(a[i], b[i]);
                }
            }
            return a.length() < b.length();
        }

        // Operátor pre porovnanie dátovıch poloiek pod¾a ich skratiek v slovenskej abecede
        bool operator()(DataItem* a, DataItem* b) {
            return compareStrings(predicates::transform_to_lower(a->getShortTitle()),
                predicates::transform_to_lower(b->getShortTitle()));
        }
    };

    // Comparátor pre porovnanie stringov pod¾a poètu samohlások
    struct CompareVowelsCount
    {
        // Zoznam samohlások
        const std::string VOWELS = "aáäeéiíyıoóuú";

        // Poèítanie samohlások v reazci
        int count_vowels(std::string str) {
            int count = 0;
            std::string str_lowered = predicates::transform_to_lower(str);

            for (char c : str_lowered) {
                if (VOWELS.find(c) != std::string::npos) {
                    count++;
                }
            }
            return count;
        }

        // Operátor pre porovnanie dátovıch poloiek pod¾a poètu samohlások v ich skratkách
        bool operator()(DataItem* a, DataItem* b) {
            int a_vowels = count_vowels(a->getShortTitle());
            int b_vowels = count_vowels(b->getShortTitle());

            return a_vowels > b_vowels;

        }
    };
}

