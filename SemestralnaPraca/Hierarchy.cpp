#pragma once
#include "Hierarchy.h"

void hierarchy::Hierarchy::createHierarchy()
{
    // Vloûenie Slovenska do koreÚa hierarchie.
    hierarchy.emplaceRoot().data_ = &slovakia;

    // PremennÈ, ktorÈ sleduj˙, kde pokraËovaù v prehæad·vanÌ okresov a obcÌ.
    int continueInSerachDistricts{ 0 };
    int continueInSerachVillages{ 0 };

    // Iter·cia cez vöetky kraje (regions).
    for (size_t i = 0; i < (*regions).size(); i++)
    {
        // Pridanie syna do koreÚa hierarchie (kraj).
        hierarchy.emplaceSon(*hierarchy.accessRoot(), i).data_ = &(*(*regions).access(i));

        // ZÌskanie okresov, ktorÈ patria do danÈho kraja.
        ds::adt::ImplicitList<DataItem*> regionSons = algorithm::alg<ds::adt::ImplicitList<DataItem*>::IteratorType,
            std::function<bool(std::string)>,
            std::function<void(DataItem*, ds::adt::ImplicitList<DataItem*>&)>,
            std::function<std::string(DataItem*)>>()
            ((*districts).begin() + continueInSerachDistricts, (*districts).end(), predicates::beginsWith()((*regions).access(i)->getCode()),
                [](DataItem* data, ds::adt::ImplicitList<DataItem*>& newDataStructure)
                {
                    newDataStructure.insertLast(data);
                },
                [](DataItem* data)
                {
                    return data->getNote().substr(0, 1);
                }, true);

        continueInSerachDistricts += regionSons.size();

        // Iter·cia cez vöetky okresy danÈho kraja.
        for (size_t j = 0; j < regionSons.size(); j++)
        {
            // Pridanie syna do kraja v hierarchii (okres).
            hierarchy.emplaceSon(*hierarchy.accessSon(*hierarchy.accessRoot(), i), j).data_ = &(*regionSons.access(j));

            // ZÌskanie obcÌ, ktorÈ patria do danÈho okresu.
            ds::adt::ImplicitList<DataItem*> districtSons = algorithm::alg<ds::adt::ImplicitList<DataItem*>::IteratorType,
                std::function<bool(std::string)>,
                std::function<void(DataItem*, ds::adt::ImplicitList<DataItem*>&)>,
                std::function<std::string(DataItem*)>>()
                ((*villages).begin() + continueInSerachVillages, (*villages).end(), predicates::contains()(regionSons.access(j)->getCode()),
                    [](DataItem* data, ds::adt::ImplicitList<DataItem*>& newDataStructure)
                    {
                        newDataStructure.insertLast(data);
                    },
                    [](DataItem* data) -> std::string
                    {
                        return data->getCode();
                    }, true);

            continueInSerachVillages += districtSons.size();

            // Iter·cia cez vöetky obce danÈho okresu.
            for (size_t k = 0; k < districtSons.size(); k++)
            {
                // Pridanie syna do okresu v hierarchii (obec).
                hierarchy.emplaceSon(*hierarchy.accessSon(*hierarchy.accessSon(*hierarchy.accessRoot(), i), j), k).data_ = &(*districtSons.access(k));
            }
        }
    }
}

void hierarchy::Hierarchy::hierarchyMenu()
{
    std::string predicate;
    std::string str;

    std::function<bool(DataItem*, DataItem*)> comparator;

    std::cout << "elements in hierarchy: " << hierarchy.size() << std::endl;

    ds::amt::MultiWayExplicitHierarchyBlock<DataItem*>* curPosition;

    curPosition = hierarchy.accessRoot();

    std::function<bool(std::string)> lambda_predicate;
    std::function<std::string(DataItem*)> lambda_strComp;


    std::string choice;

    DataType type{};



    bool sort{ false };

    while (true)
    {
        ds::amt::MultiWayExplicitHierarchy<DataItem*>::PreOrderHierarchyIterator endIt(&hierarchy, nullptr);

        ds::amt::MultiWayExplicitHierarchy <DataItem*>::PreOrderHierarchyIterator beginIt(&hierarchy, curPosition);

        std::cout << "moznosti: presun_sa_na_predka[1] | presun_sa_na_syna[2] | vyuzi_predikat[3] | exit[0] ";

        std::cin >> choice;

        if (choice == "1")
        {
            std::string level_up = &(*curPosition) == &(*hierarchy.accessRoot()) ? "si v root " : hierarchy.accessParent(*curPosition)->data_->getShortTitle();

            std::cout << "uroven vysie: " << level_up << std::endl;
            if (&(*curPosition) == &(*hierarchy.accessRoot()))
            {
                std::cout << "nachadzas sa v roote" << std::endl;
            }
            else
            {
                std::cout << "predok: " << hierarchy.accessParent(*curPosition)->data_->getShortTitle() << std::endl;

                curPosition = hierarchy.accessParent(*curPosition);
            }
        }
        else if (choice == "2")
        {
            std::cout << "uroven nizsie: ";
            for (size_t i = 0; i < curPosition->sons_->size(); i++)
            {
                std::cout << *curPosition->sons_->access(i)->data_->data_ << "[" << i << "]  " << "\n";
            }

            std::cout << "syn: ";
            std::cin >> str;
            std::cout << std::endl;

            curPosition = curPosition->sons_->access(stoi(str))->data_;
        }
        else if (choice == "3")
        {
            std::cout << "predikaty: zacina_s_retazcom[1], obsahuje_retazec[2], je_typu[3], ma_aspon_obyvatelov[4]" << std::endl;
            std::cin >> predicate;


            if (predicate == "1")
            {
                std::cout << "zacina sa s: ";
                std::cin >> str;
                std::cout << std::endl;
                lambda_predicate = predicates::beginsWith()(str);
                lambda_strComp = [](DataItem* data)
                {
                    return data->getShortTitle();
                };
            }
            else if (predicate == "2")
            {
                std::cout << "obsahuje reatazec: ";
                std::cin >> str;
                std::cout << std::endl;

                lambda_predicate = predicates::contains()(str);

                lambda_strComp = [](DataItem* data)
                {
                    return data->getShortTitle();
                };
            }
            else if (predicate == "3")
            {
                std::cout << "kraje[1] okresy[2] obce[3]: ";
                std::cin >> str;
                std::cout << std::endl;
                if (str == "1")
                {
                    type = REGION;
                }
                else if (str == "2")
                {
                    type = DISTRICT;
                }
                else
                {
                    type = VILLAGE;
                }

                lambda_predicate = predicates::hasType()(type);
                lambda_strComp = [](DataItem* data)
                {
                    switch (data->getType())
                    {
                    case REGION:
                        return "1";
                    case DISTRICT:
                        return "2";
                    default:
                        return "3";
                    }

                };
            }
            else if (predicate == "4")
            {
                std::cout << "min. populacia: ";
                std::cin >> str;
                std::cout << std::endl;
                lambda_predicate = predicates::hasAtLeast()(stoi(str));
                lambda_strComp = [](DataItem* data)
                {
                    return data->getPopulation();
                };
            }
            //vlozenie implicitneho listu do items na z·klade voæby predik·tu
            ds::adt::ImplicitList<DataItem*> items = algorithm::alg<ds::amt::MultiWayExplicitHierarchy<DataItem*>::PreOrderHierarchyIterator,
                std::function<bool(std::string)>,
                std::function<void(DataItem*, ds::adt::ImplicitList<DataItem*>&)>,
                std::function<std::string(DataItem*)>>()
                (beginIt,
                    endIt,
                    lambda_predicate,
                    [](DataItem* data, ds::adt::ImplicitList<DataItem*>& newDataStructure)
                    {
                        newDataStructure.insertLast(data);
                    },
                    lambda_strComp, false);

            std::cout << "elements in list: " << items.size() << std::endl;

            std::cout << "utrieÔ abecedne[1]     utrieÔ podæa poËtu samohlasok[2]     netrieÔ[3] ";
            std::cin >> str;
            std::cout << std::endl;

            if (str == "1")
            {
                comparator = comparators::CompareAlphabetical();

                sort = true;
            }
            else if (str == "2")
            {
                comparator = comparators::CompareVowelsCount();
                sort = true;
            }

            if (sort)
            {
                //sortovanie na z·klade kompar·tora
                sort::qsort<DataItem*>()(items, comparator);

                sort = false;
            }


            for (auto& i : items)
            {
                std::cout << *i << std::endl;
            }
        }
        else if (choice == "0") break;
    }
}