#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense
{
 private:
  Matrix _weight;
  Matrix _bias;
  ActivationFunc _activationfunction;

 public:
  Matrix get_weights () const
  { return _weight; }

  Matrix get_bias () const
  { return _bias; }

  ActivationFunc get_activation () const
  { return _activationfunction; }

  /**
   * constructor
   * @param weights
   * @param bias
   * @param activationfunction
   */
  Dense (const Matrix &weights, const Matrix &bias,
         ActivationFunc activationfunction);
  /**
   *
   * @param x matrix
   * @return a new matrix with weight and bias
   */
  Matrix operator() (Matrix const &x) const;
};

#endif //DENSE_H
