#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

typedef Matrix (*ActivationFunc) (const Matrix &m);

namespace activation
{
    /**
     *
     * @param m matrix
     * @return a new matrix, any negative zero->0
     */
    Matrix relu (const Matrix &m);

    /**
     *
     * @param m matrix
     * @return a new matrix, any val-> exp(val)
     */
    Matrix softmax (const Matrix &m);
}

#endif //ACTIVATION_H