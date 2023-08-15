#include "Dense.h"

Dense::Dense(const Matrix& weights, const Matrix& bias,
             ActivationFunc activationfunction)
{
  _weight = weights;
  _bias = bias;
  _activationfunction =  activationfunction;
}

Matrix Dense:: operator() (Matrix const &x) const
{
  return _activationfunction(_weight * x + _bias);
}
