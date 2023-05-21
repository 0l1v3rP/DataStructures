#pragma once
#include <libds/heap_monitor.h>

#include <functional>
#include "DataItem.h"
#include <algorithm> 
#include <cctype>    
#include <cwctype>    
#include <locale>
#include <cstring>
#include <string>
#include <cstdlib>

namespace predicates
{
    // Funkcia pre transform�ciu re�azca na mal� p�smen�
    inline std::string transform_to_lower(std::string string_to_transform)
    {
        std::string data_lowered;
        for (auto& i : string_to_transform)
        {
            auto d = std::tolower(i);
            data_lowered += d;
        }
        return data_lowered;
    }

    // Predik�t, ktor� kontroluje, �i zadan� re�azec obsahuje �pecifick� podre�azec
    struct contains {
        auto operator()(std::string contains)
        {
            std::string contains_lowered = transform_to_lower(contains);
            return[contains_lowered](std::string data)
            {
                if (contains_lowered.find("SKZ") != std::string::npos)
                {
                    return true;
                }
                std::string data_lowered = transform_to_lower(data);
                return data_lowered.find(contains_lowered) != std::string::npos;
            };
        }
    };

    // Predik�t, ktor� kontroluje, �i zadan� re�azec za��na �pecifick�m podre�azcom
    struct beginsWith
    {
        auto operator()(std::string contains)
        {
            std::string contains_lowered = transform_to_lower(contains);
            return [contains_lowered](std::string data)
            {
                if (contains_lowered == "9")
                {
                    return true;
                }
                std::string data_lowered = transform_to_lower(data);
                return data_lowered.rfind(contains_lowered, 0) == 0;
            };
        }
    };

    // Predik�t, ktor� kontroluje, �i zadan� typ �dajov zodpoved� �pecifick�mu typu
    struct hasType
    {
        auto operator()(DataType type)
        {
            return[type](std::string str)
            {
                if (str == "1" && type == REGION) {
                    return true;
                }
                else if (str == "2" && type == DISTRICT) {
                    return true;
                }
                else if (str == "3" && type == VILLAGE) {
                    return true;
                }
                else {
                    return false;
                }
            };
        }
    };

    // Predik�t, ktor� kontroluje, �i zadan� re�azec m� aspo� �pecifick� d�ku
    struct hasAtLeast
    {
        auto operator()(int atLeast)
        {
            return [atLeast](std::string data)
            {
                return stoi(data) >= atLeast;
            };
        }
    };
}

