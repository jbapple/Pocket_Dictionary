//
// Created by tomer on 11/5/19.
//

#ifndef CLION_CODE_POW2C_NAIVE_FILTER_H
#define CLION_CODE_POW2C_NAIVE_FILTER_H

#include "../Naive_PD/naive_PD.h"
#include "../Hash/Hash.h"
#include "../Hash/Permutation.h"
//#include "pow2c_filter.h"

class pow2c_naive_filter {
    vector<naive_PD> pd_vec;
    size_t size, capacity;
    size_t fp_size, interval_length, single_pd_capacity;
    size_t quotient_length, pd_index_length;
    Hash h;
    Permutation perm;

public:
    pow2c_naive_filter(size_t size, size_t interval_length, size_t single_pd_capacity, size_t fp_size);

    bool lookup(string *s);

    void insert(string *s);

    void remove(string *s);

    void split(size_t hash_index, size_t *pd_index, D_TYPE *quotient, D_TYPE *remainder);

    void split_print(size_t hash_index, size_t *pd_index, D_TYPE *quotient, D_TYPE *remainder);

    size_t get_capacity();

};


#endif //CLION_CODE_POW2C_NAIVE_FILTER_H
