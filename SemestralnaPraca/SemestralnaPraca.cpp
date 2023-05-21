#pragma once
#include "../DataStructures/libds/heap_monitor.h"
#include <libds/amt/explicit_hierarchy.h>
#include "../DataStructures/libds/adt/list.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "Algorithm.h"
#include <fstream>
#include "Input.h"
#include "DataItem.h"
#include "Hierarchy.h"
#include <Windows.h>
#include <stdio.h>
#include "SemestralnaPraca.h"
#include "table.h"


class main
{

};


int main()
{
    initHeapMonitor();

    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    std::locale win1250("Slovak");
    std::locale loc(win1250);
    std::string choice;

    std::vector<std::string> slovakia_data;
    slovakia_data.push_back("1");
    slovakia_data.push_back("SK");
    slovakia_data.push_back("Slovak Republic");
    slovakia_data.push_back("Slovakia");
    slovakia_data.push_back("Slovakia");
    slovakia_data.push_back("");
    slovakia_data.push_back("5428792");

    DataItem slovakia(slovakia_data, COUNTRY);

    ds::adt::ImplicitList<DataItem*>* regions = new ds::adt::ImplicitList<DataItem*>;
    ds::adt::ImplicitList<DataItem*>* districts = new ds::adt::ImplicitList<DataItem*>;
    ds::adt::ImplicitList<DataItem*>* villages = new ds::adt::ImplicitList<DataItem*>;
    input::Input input;
    input.readFromCsvFileToDataStructure("kraje.csv", regions, REGION, [](DataItem*& item, ds::adt::ImplicitList<DataItem*>*& array)
        {
            array->insertLast(item);
        });
    input.readFromCsvFileToDataStructure("okresy.csv", districts, DISTRICT, [](DataItem*& item, ds::adt::ImplicitList<DataItem*>*& array)
        {
            array->insertLast(item);
        });
    input.readFromCsvFileToDataStructure("obce.csv", villages, VILLAGE, [](DataItem*& item, ds::adt::ImplicitList<DataItem*>*& array)
        {
            array->insertLast(item);
        });

    table::TypedTable<std::string, ds::adt::ImplicitList<DataItem*>*> regionTable(REGION);
    table::TypedTable<std::string, ds::adt::ImplicitList<DataItem*>*> districtTable(DISTRICT);
    table::TypedTable<std::string, ds::adt::ImplicitList<DataItem*>*> villageTable(VILLAGE );

    for (auto it = villages->begin(); it != villages->end(); ++it)
    {
        villageTable.insertWithDuplicates((*it)->getShortTitle(), *it);
    }
    for (auto it = regions->begin(); it != regions->end(); ++it)
    {
        regionTable.insertWithDuplicates((*it)->getShortTitle(), *it);
    }
    for (auto it = districts->begin(); it != districts->end(); ++it)
    {
        districtTable.insertWithDuplicates((*it)->getShortTitle(), *it);
    }        
    hierarchy::Hierarchy hierarchy(slovakia, regions, districts, villages);
    while (true)
    {
        std::cout << "****************************MAIN MENU****************************\n" << "hierarchia[1]        |        tabulky[2]         |        exit[0]" << std::endl;
        std::cin >> choice;
        if (choice == "1")
        {
            hierarchy.hierarchyMenu();
        }
        else if (choice == "2")
        {
            table::tableMenu(regionTable, districtTable, villageTable);

        }
        else if (choice == "0")
        {
            break;
        }
        else
        {
            std::cout << "try again :)" << std::endl;
        }
    }

    for (auto it = villages->begin(); it != villages->end(); ++it)
    {
        delete* it;
    }
    delete villages;
    for (auto it = regions->begin(); it != regions->end(); ++it)
    {
        delete* it;
    }
    delete regions;
    for (auto it = districts->begin(); it != districts->end(); ++it)
    {
        delete* it;
    }
    delete districts;

    for (auto it = regionTable.begin(); it != regionTable.end(); ++it)
    {

        delete (*it).data_;
    }
    
    for (auto it = districtTable.begin(); it != districtTable.end(); ++it)
    {

        delete (*it).data_;
    }
    for (auto it = villageTable.begin(); it != villageTable.end(); ++it)
    {

        delete (*it).data_;
    }
    return 0;
}
