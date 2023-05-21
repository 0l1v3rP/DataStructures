#pragma once
#include "../DataStructures/libds/heap_monitor.h"

#include <vector>
#include <string>
#include "../DataStructures/libds/amt/explicit_hierarchy.h"
#include "DataItem.h"
#include "Algorithm.h"
#include "Predicates.h"
#include <chrono>
#include <stdio.h>
#include "Comparators.h"
#include "UniversalSort.h"


// Namespace pre pr�cu s hierarchiou �zemn�ch jednotiek.
namespace hierarchy
{
    // Trieda Hierarchy reprezentuje �trukt�ru hierarchie �zemn�ch jednotiek.
    class Hierarchy
    {
    private:
        // Hierarchia �zemn�ch jednotiek.
        ds::amt::MultiWayExplicitHierarchy<DataItem*> hierarchy{};
        // DataItem reprezentuj�ci Slovensko.
        DataItem slovakia;
        // Zoznam krajov.
        ds::adt::ImplicitList<DataItem*>* regions;
        // Zoznam okresov.
        ds::adt::ImplicitList<DataItem*>* districts;
        // Zoznam obc�.
        ds::adt::ImplicitList<DataItem*>* villages;

    public:
        // Kon�truktor pre Hierarchy. Inicializuje �daje a vytv�ra hierarchiu.
        Hierarchy(
            DataItem& slovakia,
            ds::adt::ImplicitList<DataItem*>* regions,
            ds::adt::ImplicitList<DataItem*>* districts,
            ds::adt::ImplicitList<DataItem*>* villages
        ) :
            slovakia(slovakia),
            regions(regions),
            districts(districts),
            villages(villages)
        {
            createHierarchy();
        }

        // Funkcia, ktor� zobrazuje menu pre manipul�ciu s hierarchiou.
        void hierarchyMenu();

    private:
        // Funkcia, ktor� vytv�ra hierarchiu �zemn�ch jednotiek.
        void createHierarchy();
    };
}

