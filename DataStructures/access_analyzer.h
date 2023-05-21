#pragma once

#include <complexities/complexity_analyzer.h>
#include <libds/adt/list.h>
#include <random>

namespace ds::utils
{
    template<class ADS>
    class AccessAnalyzer : public ComplexityAnalyzer<ADS>
    {
    public:
        explicit AccessAnalyzer(const std::string& name);

    protected:
        void executeOperation(ADS& structure) override;
        void beforeOperation(ADS& structure) override;

    private:
        void insertNElements(ADS& structure, size_t n);

    private:
        std::default_random_engine rngData_;
        std::default_random_engine rngIndex_;
        size_t index_;
    };

    class AccessesAnalyzer : public CompositeAnalyzer
    {
    public:
        AccessesAnalyzer() :
            CompositeAnalyzer("Accesses")
        {
            this->addAnalyzer(std::make_unique<AccessAnalyzer<adt::ImplicitList<int>>>("implict_list-access"));
            this->addAnalyzer(std::make_unique<AccessAnalyzer<adt::SinglyLinkedList<int>>>("singly_linked_list-access"));
        }
    };

    template<class ADS>
    inline AccessAnalyzer<ADS>::AccessAnalyzer(const std::string& name) :
        ComplexityAnalyzer<ADS>(name, [this](ADS& ads, size_t size)
            {
                this->insertNElements(ads, size);
            }),
        rngData_(std::random_device()()),
                rngIndex_(std::random_device()()),
                index_(0)
    {
    }

            template<class ADS>
            inline void AccessAnalyzer<ADS>::executeOperation(ADS& structure)
            {
                structure.access(this->index_);
            }

            template<class ADS>
            inline void AccessAnalyzer<ADS>::beforeOperation(ADS& structure)
            {
                std::uniform_int_distribution<size_t> indexDist(0, structure.size() - 1);
                this->index_ = indexDist(rngIndex_);
            }

            template<class ADS>
            inline void AccessAnalyzer<ADS>::insertNElements(ADS& structure, size_t n)
            {
                std::uniform_int_distribution<int> dataDist(0, 100000);
                for (size_t i = 0; i < n; ++i)
                {
                    structure.insertLast(dataDist(rngData_));
                }
            }

}