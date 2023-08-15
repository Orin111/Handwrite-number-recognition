#include "MlpNetwork.h"
#include "Activation.h"

MlpNetwork::MlpNetwork (Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE])
{
  for (int i = 0; i < MLP_SIZE; ++i)
    {
      _weights[i] = weights[i];
      _biases[i] = biases[i];
    }
}

digit MlpNetwork::operator() (const Matrix &x) const
{
  Dense r1 (_weights[0], _biases[0], activation::relu);
  Dense r2 (_weights[1], _biases[1], activation::relu);
  Dense r3 (_weights[2], _biases[2], activation::relu);
  Dense r4 (_weights[3], _biases[3], activation::softmax);

  Matrix layer1 = r1 (x);
  Matrix layer2 = r2 (layer1);
  Matrix layer3 = r3 (layer2);
  Matrix layer4 = r4 (layer3);

  digit max{0, layer4[0]};
  for (int i = 0; i < layer4.get_cols () * layer4.get_rows (); ++i)
    {
      if (layer4[i] > max.probability)
        {
          max = {(unsigned int) i, layer4[i]};
        }
    }
  return max;
}