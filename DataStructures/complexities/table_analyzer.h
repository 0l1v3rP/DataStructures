#pragma once

#include <complexities/complexity_analyzer.h>
#include <libds/adt/list.h>
#include <libds/adt/table.h>
#include <random>

namespace ds::utils {
    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table> {
    public:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
        void beforeOperation(Table& structure) override;
        void afterReplication(Table& structure) override;

    private:
        void insertNElements(Table& structure, size_t n);
        void findNElements(Table& structure, size_t n);


    private:
        std::default_random_engine rngIndex_;
        std::default_random_engine rngKey_;
        adt::ImplicitList<int> keyList_;
        size_t index_;
        int key_;
    };

    class TablesAnalyzer : public CompositeAnalyzer {
    public:
        TablesAnalyzer() :
            CompositeAnalyzer("Tables") {
            this->addAnalyzer(std::make_unique<TableAnalyzer<adt::SortedSequenceTable<int, int>>>("sst-contains"));
            this->addAnalyzer(std::make_unique<TableAnalyzer<adt::UnsortedExplicitSequenceTable<int, int>>>("uest-contains"));
            this->addAnalyzer(std::make_unique<TableAnalyzer<adt::HashTable<int, int>>>("ht-contains"));
        }
    };

    template<class Table>
    inline TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
        ComplexityAnalyzer<Table>(name, [this](Table& structure, size_t n) {
        this->insertNElements(structure, n);

            }),
        rngIndex_(std::random_device()()),
                rngKey_(std::random_device()()),
                keyList_(),
                key_(0) {
    }

            template<class Table>
            inline void TableAnalyzer<Table>::executeOperation(Table& structure) {
                std::uniform_int_distribution<int> distKey(INT_MIN, INT_MAX);
                int key = distKey(this->rngKey_);
                structure.insert(key, key);

            }

            template<class Table>
            inline void TableAnalyzer<Table>::beforeOperation(Table& structure) {
               /* std::uniform_int_distribution<size_t> distIndex(0, this->keyList_.size() - 1);
                size_t index = distIndex(this->rngIndex_);
                this->key_ = this->keyList_.access(index);*/
                static int key = INT_MIN;
                structure.insert(key, key);
                key++; 

            }

            template<class Table>
            inline void TableAnalyzer<Table>::afterReplication(Table& structure) {
                this->keyList_.clear();
            }

            template<class Table>
            inline void TableAnalyzer<Table>::insertNElements(Table& structure, size_t n) {
                std::uniform_int_distribution<int> distKey(INT_MIN, INT_MAX);

                for (size_t i = 1; i <= n; ++i) {
                    int key = distKey(this->rngKey_);
                    bool newKey = true;
                    try {
                        structure.insert(key, key);
                    }
                    catch (...) {
                        --i;
                        newKey = false;
                    }
                    if (newKey) {
                        this->keyList_.insertLast(key);
                    }

                }
            }
}