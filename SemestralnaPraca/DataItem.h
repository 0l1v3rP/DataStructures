#pragma once
#include "../DataStructures/libds/heap_monitor.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
// Defin�cia enumer�cie DataType, ktor� reprezentuje r�zne typy �zemn�ch jednotiek.
enum DataType
{
    COUNTRY,
    REGION,
    DISTRICT,
    VILLAGE
};

// Trieda DataItem reprezentuje jednotliv� �zemn� jednotky v d�tach.
class DataItem
{
private:
    // Atrib�ty jednotliv�ch �zemn�ch jednotiek.
    int sortNumber_;
    std::string code_;
    std::string officialTitle_;
    std::string mediumTitle_;
    std::string shortTitle_;
    std::string note_;
    std::string population_;
    DataType type_;  // Typ �zemnej jednotky.

public:

    // Kon�truktor, ktor� inicializuje �zemn� jednotku na z�klade riadka d�t a jej typu.
    DataItem(std::vector<std::string> row, DataType type)
        : sortNumber_(std::stoi(row[0])),
        code_(row[1]),
        officialTitle_(row[2]),
        mediumTitle_(row[3]),
        shortTitle_(row[4]),
        note_(row[5]),
        population_(row[6]),
        type_(type) {}

    // Getter met�dy pre pr�stup k atrib�tom �zemnej jednotky.
    DataType getType() { return type_; }
    int getSortNumber() { return sortNumber_; }
    std::string getCode() { return code_; }
    std::string getOfficialTitle() { return officialTitle_; }
    std::string getMediumTitle() { return mediumTitle_; }
    std::string getShortTitle() { return shortTitle_; }
    std::string getNote() { return note_; }
    std::string getPopulation() { return population_; }

    // Pre�a�enie oper�tora << pre v�pis �zemnej jednotky do streamu.
    friend std::ostream& operator<<(std::ostream& outs, const DataItem& p)
    {
        return outs << "code: " << std::setw(20) << std::left << p.code_
            << "short title: " << std::setw(35) << std::left << p.shortTitle_
            << "population: " << std::setw(10) << std::left << p.population_;
    }
};

// Pomocn� funkcia pre konverziu hodn�t r�znych typov na re�azec.
template <typename T>
std::string to_string(const T& value)
{
    std::ostringstream ss;
    ss << value;
    return ss.str();
}
