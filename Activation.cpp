#include <cmath>
#include "Activation.h"

Matrix activation::relu (const Matrix &m)
{
  Matrix new_m = Matrix (m);
  for (int i = 0; i < new_m.get_rows () * new_m.get_cols (); ++i)
    {
      if (new_m[i] < 0)
        {
          new_m[i] = 0;
        }
    }
  return new_m;
}

Matrix activation::softmax (const Matrix &m)
{
  Matrix new_m = Matrix (m);
  float sum = 0;
  for (int i = 0; i < new_m.get_rows () * new_m.get_cols (); ++i)
    {
      new_m[i] = std::exp (new_m[i]);
      sum += new_m[i];
    }
  return new_m * (1 / sum);
}

