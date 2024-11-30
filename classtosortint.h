#ifndef CLASSTOSORTINT_H
#define CLASSTOSORTINT_H


#include "ArraySequence.h"
#include "enumsorters.h"

class ClassToSortInt
{
public:
    ClassToSortInt();
    double Sort(MutableArraySequence<int>* seqToSort, Sorters sorter);
};

#endif // CLASSTOSORTINT_H
