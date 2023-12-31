//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit
{
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64,  128},
                                    {20,  64},
                                    {10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
                                 {64,  1},
                                 {20,  1},
                                 {10,  1}};

class MlpNetwork
{
 private:
  Matrix _weights[MLP_SIZE];
  Matrix _biases[MLP_SIZE];

 public:
  /**
   * constructor
   * @param weights
   * @param biases
   */
  MlpNetwork (Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);

  /**
   *
   * @param x  matrix
   * @return the digit with highest probability after applying all layers
   */
  digit operator() (const Matrix &x) const;
};

#endif // MLPNETWORK_H