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
    // Compar�tor pre porovnanie stringov pod�a slovenskej abecedy
    struct CompareAlphabetical {

        // Slovensk� abeceda v porad�
        const std::string slovakAlphabet = "a��bc�d�e�fghi�jkl�mn�o��pqrs�t�u�vwxyz�";

        // Porovnanie jednotliv�ch znakov pod�a ich poradia v slovenskej abecede
        bool compareCharacters(char a, char b) {
            int a_order = slovakAlphabet.find(a);
            int b_order = slovakAlphabet.find(b);
            return a_order < b_order;
        }

        // Porovnanie stringov pod�a slovenskej abecedy
        bool compareStrings(const std::string& a, const std::string& b) {
            size_t length = std::min(a.length(), b.length());
            for (size_t i = 0; i < length; i++) {
                if (a[i] != b[i]) {
                    return compareCharacters(a[i], b[i]);
                }
            }
            return a.length() < b.length();
        }

        // Oper�tor pre porovnanie d�tov�ch polo�iek pod�a ich skratiek v slovenskej abecede
        bool operator()(DataItem* a, DataItem* b) {
            return compareStrings(predicates::transform_to_lower(a->getShortTitle()),
                predicates::transform_to_lower(b->getShortTitle()));
        }
    };

    // Compar�tor pre porovnanie stringov pod�a po�tu samohl�sok
    struct CompareVowelsCount
    {
        // Zoznam samohl�sok
        const std::string VOWELS = "a��e�i�y�o�u�";

        // Po��tanie samohl�sok v re�azci
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

        // Oper�tor pre porovnanie d�tov�ch polo�iek pod�a po�tu samohl�sok v ich skratk�ch
        bool operator()(DataItem* a, DataItem* b) {
            int a_vowels = count_vowels(a->getShortTitle());
            int b_vowels = count_vowels(b->getShortTitle());

            return a_vowels > b_vowels;

        }
    };
}

