#pragma once

#include <libds/amt/implicit_sequence.h>
#include <libds/adt/queue.h>
#include <libds/adt/array.h>
#include <functional>
#include <cmath>
#include <algorithm>
#include <type_traits>
#include <string_view>

namespace ds::adt
{
    template <typename T>
    struct Sort
    {
    public:
        virtual void sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare) = 0;
        void sort(ImplicitList<T>& is) { sort(is, [](const T& a, const T& b)->bool {return a < b; }); }
    };

    template <typename T>
    class SelectSort :
        public Sort<T>
    {
    public:
        void sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    template <typename T>
    class InsertSort :
        public Sort<T>
    {
    public:
        void sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    template <typename T>
    class BubbleSort :
        public Sort<T>
    {
    public:
        void sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    template <typename T>
    class QuickSort :
        public Sort<T>
    {
    public:
        void sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void quick(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max);
        int partition(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare, int low, int high);
        void swap(ImplicitList<T>& is, int i, int j);

    };

    template <typename T>
    class HeapSort :
        public Sort<T>
    {
    public:
        void sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    template <typename T>
    class ShellSort :
        public Sort<T>
    {
    public:
        void sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void shell(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare, size_t k);
    };

    template <typename Key, typename T>
    class RadixSort :
        public Sort<T>
    {
        static_assert(std::is_integral_v<Key>, "Radix sort supports only integral types.");

    public:
        RadixSort();
        RadixSort(std::function<Key(const T&)> getKey);

        void sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        std::function<Key(const T&)> getKey_;
    };

    template <typename T>
    class MergeSort :
        public Sort<T>
    {
    public:
        void sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void split(size_t n);
        void merge(std::function<bool(const T&, const T&)> compare, size_t n);

    private:
        ImplicitQueue<T>* queue1_ {nullptr};
        ImplicitQueue<T>* queue2_ {nullptr};
        ImplicitQueue<T>* mergeQueue_ {nullptr};
    };

    //----------

    template<typename T>
    void SelectSort<T>::sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void InsertSort<T>::sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void BubbleSort<T>::sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        bool swapped;
        do
        {
            swapped = false;
            for (size_t i = 0; i < is.size() - 1; ++i)
            {
                if (compare(is.access(i + 1), is.access(i)))
                {
                    using std::swap;
                    swap(*is.access(i + 1), *is.access(i));
                    swapped = true;
                }
            }
        }
        while (swapped);
    }

    template<typename T>
    void QuickSort<T>::sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        if (!is.isEmpty())
        {
            quick(is, compare, 0, is.size() - 1);
        }
    }

    template<typename T>
    void QuickSort<T>::quick(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max)
    {
        if (min < max) {
            int pivotIndex = partition(is, compare, min, max);
            if (pivotIndex > 0)
            quick(is, compare, min, pivotIndex - 1);
            if (pivotIndex < max)
            quick(is, compare, pivotIndex + 1, max);
        }
    }

    template<typename T>
    int QuickSort<T>::partition(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare, int low, int high) {
        T pivot = is.access(high);
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (compare(is.access(j), pivot)) {
                i++;
                if (i != j) {
                    swap(is, i, j);
                }
            }
        }
        if (i + 1 != high) {
            swap(is, i + 1, high);
        }
        return (i + 1);
    }

    
    template<typename T>
    void QuickSort<T>::swap(ImplicitList<T>& is, int i, int j) {
        T temp = is.access(i);
        is.set(i, is.access(j));
        is.set(j, temp);
    }

    template<typename T>
    void HeapSort<T>::sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void ShellSort<T>::sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        shell(is, compare, std::log10(is.size()));
    }

    template<typename T>
    void ShellSort<T>::shell(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare, size_t k)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort() :
        getKey_([](auto const& x) { return x; })
    {
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort(std::function<Key(const T&)> getKey) :
        getKey_(getKey)
    {
    }

    template<typename Key, typename T>
    void RadixSort<Key, T>::sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::sort(ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
    {

    }

    template<typename T>
    void MergeSort<T>::split(size_t n)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::merge(std::function<bool(const T&, const T&)> compare, size_t n)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }
}