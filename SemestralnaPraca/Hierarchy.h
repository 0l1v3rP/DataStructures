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


// Namespace pre prácu s hierarchiou územných jednotiek.
namespace hierarchy
{
    // Trieda Hierarchy reprezentuje štruktúru hierarchie územných jednotiek.
    class Hierarchy
    {
    private:
        // Hierarchia územných jednotiek.
        ds::amt::MultiWayExplicitHierarchy<DataItem*> hierarchy{};
        // DataItem reprezentujúci Slovensko.
        DataItem slovakia;
        // Zoznam krajov.
        ds::adt::ImplicitList<DataItem*>* regions;
        // Zoznam okresov.
        ds::adt::ImplicitList<DataItem*>* districts;
        // Zoznam obcí.
        ds::adt::ImplicitList<DataItem*>* villages;

    public:
        // Konštruktor pre Hierarchy. Inicializuje údaje a vytvára hierarchiu.
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

        // Funkcia, ktorá zobrazuje menu pre manipuláciu s hierarchiou.
        void hierarchyMenu();

    private:
        // Funkcia, ktorá vytvára hierarchiu územných jednotiek.
        void createHierarchy();
    };
}

