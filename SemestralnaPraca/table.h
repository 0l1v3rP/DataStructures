#pragma once
#include <libds/heap_monitor.h>
#include "DataItem.h"
#include "../DataStructures/libds/adt/table.h"
#include "Input.h"

#include <sstream>

// Tento k�d je s��as�ou namespace "table", ktor� obsahuje r�zne funkcie a triedy pre pr�cu s tabu�kami �dajov.

namespace table 
{
    // Trieda "TypedTable" je podtriedou HashTable a sl��i k ukladaniu �dajov ur�it�ho typu.
    template<typename K, typename T>
    class TypedTable : public ds::adt::HashTable<K, T> {
    private:
        // Typ �dajov, ktor� s� v tabu�ke ulo�en�.
        DataType type_;
    public:
        // Kon�truktor pre triedu "TypedTable". Inicializuje HashTable a nastav� typ �dajov.
        TypedTable(DataType type) :
            ds::adt::HashTable<K, T>(), type_(type) {}

        // Funkcia, ktor� vr�ti typ �dajov v tabu�ke.
        DataType getType() const { return type_; }

        // Funkcia na vkladanie �dajov do tabu�ky. Vklad� �daje s duplicitami.
        void insertWithDuplicates(K key, DataItem* data);
    };

    // Implement�cia funkcie "insertWithDuplicates". Ak u� v tabu�ke existuje k���, prid�va k nemu nov� �daje.
    // Ak k��� neexistuje, vytvor� nov� zoznam a vlo�� ho do tabu�ky.
    template<typename K, typename T>
    inline void TypedTable<K, T>::insertWithDuplicates(K key, DataItem* data)
    {
        ds::adt::ImplicitList<DataItem*>** existingData{ nullptr };
        if (this->tryFind(key, existingData)) {
            (*existingData)->insertLast(data);
        }
        else {
            ds::adt::ImplicitList<DataItem*>* newList = new ds::adt::ImplicitList<DataItem*>;
            newList->insertLast(data);
            this->insert(key, newList);
        }
    }

    // Funkcia "tableMenu" umo��uje interakciu s tabu�kami krajov, okresov a obc�.
    // Umo��uje vyh�ad�va� �zemn� jednotky pod�a k���a.
    void tableMenu(table::TypedTable<std::string, ds::adt::ImplicitList<DataItem*>*>& regions,
        table::TypedTable<std::string, ds::adt::ImplicitList<DataItem*>*>& districts,
        table::TypedTable<std::string, ds::adt::ImplicitList<DataItem*>*>& villages)
    {
        std::string choice{};
        std::string str{};
        std::function<bool(std::string)> predicate{};
        ds::adt::ImplicitList<DataItem*> filteredData{};

            auto lambda_strComp = [](ds::amt::ImplicitSequence<ds::adt::TableItem<std::string, ds::adt::ImplicitList<DataItem*>*>>::ImplicitSequenceIterator data)
        {
            return (*data).data_->accessFirst()->getShortTitle();
        };
 

        table::TypedTable<std::string, ds::adt::ImplicitList<DataItem*>*>* tableItems;

        while (true)
        {
            std::cout << "Vyhladavanie uzemnej jednotky: " << std::endl;
            std::cout << "1. Vyhladavaj kraj" << std::endl;
            std::cout << "2. Vyhladavaj okres" << std::endl;
            std::cout << "3. Vyhladavaj obec" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "zadaj volbu (0-3): ";

            std::cin >> choice;
            if (choice == "0")
            {
                break;
            }
            if (choice == "1")
            {
                tableItems = &regions;
            }
            else if (choice == "2")
            {
                tableItems = &districts;
            }
            else if (choice == "3")
            {
                tableItems = &villages;
            }
            else
            {
                std::cout << "neplatn� vstup, skus znova" << std::endl;
                continue;
            }

            std::cout << "zadaj uzemnu jednotku: " << std::endl;
            std::cin.ignore(); 
            std::getline(std::cin, str);
            ds::adt::ImplicitList<DataItem*>** result = nullptr;

            if (tableItems->tryFind(str, result))
            {
                for (auto i = (*result)->begin(); i != (*result)->end(); ++i)
                {
                    std::cout << *(*i) << std::endl;
                }
            }
            else
            {
                std::cout << "no key found" << std::endl;
            }
        }
    }


}