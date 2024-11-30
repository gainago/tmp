
#include <chrono>

#include "classtosortint.h"
#include "ArraySequence.h"
#include "BubbleSorter.h"
#include "InsertionSorter.h"
#include "ShellSorter.h"
#include "MergeSorter.h"
#include "PiramidSorter.h"
#include "QuickSorter.h"
#include "AbstractSorter.h"
#include "Comporators.h"


ClassToSortInt::ClassToSortInt() {}

double ClassToSortInt::Sort(MutableArraySequence<int>* seqToSort, Sorters numberOfSorter)
{
    Sorter<int>* sorter;

    switch ((int)numberOfSorter) {
        case 1:{
            sorter = new BubbleSorter<int>(cmpInt);
            break;
        }
        case 2:{
            sorter = new InsertionSorter<int>(cmpInt);
            break;
        }
        case 3:{
            sorter = new ShellSorter<int>(cmpInt);
            break;
        }
        case 4:{
            sorter = new MergeSorter<int>(cmpInt);
            break;
        }
        case 5:{
            sorter = new PiramidSorter<int>(cmpInt);
            break;
        }
        case 6:{
            sorter = new QuickSorter<int>(cmpInt);
            break;
        }
    default:
        break;
    }


    auto start = std::chrono::high_resolution_clock::now();
    sorter->Sort(seqToSort);
    auto end = std::chrono::high_resolution_clock::now();
    //assert(CheckCorrectlySorted(seqToSort, cmpInt));
    const std::chrono::duration<double> diff = end - start;
    return std::chrono::duration<double>(diff).count();
}
