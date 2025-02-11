//
// Created by tomer on 10/24/19.
//

#ifndef CLION_CODE_PD_H
#define CLION_CODE_PD_H

#include "Header.h"
#include "Body.h"


class PD {
    Header header;
    Body body;
    size_t capacity;
    const size_t max_capacity;

public:
    PD(size_t m, size_t f, size_t l);

    virtual ~PD();
//    virtual ~PD();

    bool lookup(size_t quotient, FP_TYPE remainder);

    void insert(size_t quotient, FP_TYPE remainder);

    /**
     *
     * @param quotient
     * @param remainder
     * Error will occur if the element is not in the body.
     */
    void remove(size_t quotient, FP_TYPE remainder);


    /**
     * Removes the element only if it is in the PD.
     * @param quotient
     * @param remainder
     * @return true if the element was removed, false otherwise.
     */
    bool conditional_remove(size_t quotient, FP_TYPE remainder);

    void header_pp();

    void print();

    bool is_full();

    size_t get_capacity() const;

private:

    uint8_t
    get_body_abstract_start_index(size_t header_interval_start_index, size_t header_interval_end_index,
                                  size_t quotient);

    uint8_t
    get_body_abstract_end_index(size_t header_interval_start_index, size_t header_interval_end_index, size_t quotient);

};


#endif //CLION_CODE_PD_H
