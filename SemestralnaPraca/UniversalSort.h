#pragma once
#include "../DataStructures/libds/heap_monitor.h"

#include "libds/adt/sorts.h"
#include <functional>
#include "libds/adt/list.h"

// Namespace pre sortovacie algoritmy.
namespace sort {

    // �trukt�ra qsort, ktor� implementuje r�chle triedenie (quicksort).
    template<typename T>
    struct qsort {
        // Oper�tor (), ktor� vykon� r�chle triedenie na zadanom ImplicitList.
        void operator()(ds::adt::ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
        {
            ds::adt::QuickSort<T> sort;
            sort.sort(is, compare);
        }
    };
}
