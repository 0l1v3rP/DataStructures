#pragma once
#include "../DataStructures/libds/heap_monitor.h"
#include "Predicates.h"
#include "DataItem.h"
#include <fstream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../DataStructures/libds/adt/table.h"
#include "table.h"
namespace input
{
    class Input
    {
        //funkcia ktor8 vriacia poèet obyvate¾ov pre danú územnu jednotku
        std::string getPopulation(DataType& type, std::vector<std::string>& row, std::ifstream& file)
        {
            int population_size{ 0 };
            if (!file.eof())
            {
                std::vector<std::string> population;
                std::string line;
                std::string cell;
                std::getline(file, line);
                std::stringstream ss(line);

                while (std::getline(ss, cell, ';'))
                {
                    population.push_back(cell);
                }
                if (population[0].substr(0, 5) == "SKZZZ")
                {
                    return "0";
                }
                if (type == VILLAGE)
                {
                    population_size = stoi(population[1]);
                }
                else
                {
                    auto belongsToDistrict = predicates::beginsWith()(type == DISTRICT ?
                        row[1] : row[5].substr(5, std::string::npos));
                    while (belongsToDistrict(population[0]))
                    {
                        population_size += stoi(population[1]);
                        population.clear();
                        std::getline(file, line);
                        ss = std::stringstream(line);
                        while (std::getline(ss, cell, ';'))
                        {
                            population.push_back(cell);
                        }
                    }
                }
            }

            return std::to_string(population_size);
        }
    public:

        template<typename T, typename F>
        void readFromCsvFileToDataStructure(std::string filename, T& dataStructure, DataType type, F insertFunc)
        {
            std::ifstream file(filename);

            std::ifstream file_population("velkost_obyvatelstva.csv");

            if (!file)
            {
                throw std::runtime_error("file does not exist");
            }

            std::string line;

            std::getline(file, line);
            try
            {
                while (std::getline(file, line))
                {
                    if (line.back() == ';')
                    {
                        line += " ";
                    }

                    std::stringstream ss(line);
                    std::vector<std::string> row;
                    std::string cell;

                    while (std::getline(ss, cell, ';'))
                    {
                        row.push_back(cell);
                    }
                    row.push_back(getPopulation(type, row, file_population));
                    DataItem* item = new DataItem(row, type);
                    insertFunc(item, dataStructure);
                }
            }
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
            file.close();
            file_population.close();
        }
    };
}