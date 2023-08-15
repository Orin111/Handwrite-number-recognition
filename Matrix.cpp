#include "Matrix.h"
#include <iostream>
#include <cmath>

Matrix::Matrix (Matrix const &m) : Matrix (m._rows, m._cols)
{
  for (int i = 0; i < m._rows; ++i)
    {
      for (int j = 0; j < m._cols; ++j)
        {
          _matrix[i * _cols + j] = m._matrix[i * _cols + j];
        }
    }
}

Matrix &Matrix::transpose ()
{
  float *transpose = new float[_cols * _rows] ();
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          transpose[j * _rows + i] = (*this) (i, j);
        }
    }
  delete[] _matrix;
  _matrix = transpose;
  int temp = _cols;
  _cols = _rows;
  _rows = temp;
  return *this;
}

Matrix &Matrix::vectorize ()
{
  _rows = _cols * _rows;
  _cols = DEF_SIZE;
  return *this;
}

void Matrix::plain_print () const
{
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          std::cout << (*this) (i, j) << " ";
        }
      std::cout << std::endl;
    }
}

Matrix Matrix::dot (const Matrix &m) const
{
  if (_cols != m._cols || _rows != m._rows)
    {
      throw std::length_error (LENGTH_ERROR);
    }
  Matrix n_matrix = Matrix (m);
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          n_matrix (i, j) *= (*this) (i, j);
        }
    }
  return n_matrix;
}

float Matrix::norm () const
{
  Matrix n_matrix = this->dot (*this);
  float sum = 0;
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          sum += (n_matrix) (i, j);
        }
    }
  return (float) std::sqrt (sum);
}

Matrix &Matrix::operator+= (const Matrix &b)
{
  if (_cols != b._cols || _rows != b._rows)
    {
      throw std::length_error (LENGTH_ERROR);
    }
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          (*this) (i, j) += b (i, j);
        }
    }
  return *this;
}

Matrix Matrix::operator+ (const Matrix &b) const
{
  if (_cols != b._cols || _rows != b._rows)
    {
      throw std::length_error (LENGTH_ERROR);
    }
  Matrix n_matrix = Matrix (*this);
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          n_matrix (i, j) += b (i, j);
        }
    }
  return n_matrix;
}

Matrix &Matrix::operator= (const Matrix &b)
{
  if (this == &b)
    {
      return *this;
    }
  _cols = b._cols;
  _rows = b._rows;
  delete[] _matrix;
  _matrix = new float[_rows * _cols] ();
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          _matrix[i * _cols + j] = b._matrix[i * _cols + j];
        }
    }
  return *this;
}

Matrix Matrix::operator* (const Matrix &b) const
{
  if (_cols != b._rows)
    {
      throw std::length_error (LENGTH_ERROR);
    }
  Matrix n_matrix = Matrix (_rows, b._cols);
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < b._cols; ++j)
        {
          for (int k = 0; k < _cols; ++k)
            {
              n_matrix (i, j) += (*this) (i, k) * b (k, j);
            }
        }
    }
  return n_matrix;
}

Matrix Matrix::operator* (float b) const
{
  Matrix n_matrix = Matrix (*this);
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          n_matrix (i, j) *= b;
        }
    }
  return n_matrix;
}

Matrix operator* (float b, const Matrix &a)
{
  Matrix n_matrix = Matrix (a);
  for (int i = 0; i < a._rows; ++i)
    {
      for (int j = 0; j < a._cols; ++j)
        {
          n_matrix (i, j) *= b;
        }
    }
  return n_matrix;
}
float &Matrix::operator() (int row, int col)
{
  if (row >= _rows || col >= _cols || row < 0 || col < 0)
    {
      throw std::out_of_range (OUT_OF_RANGE);
    }
  return _matrix[row * _cols + col];
}

float &Matrix::operator() (int row, int col) const
{
  if (row >= _rows || col >= _cols || row < 0 || col < 0)
    {
      throw std::out_of_range (OUT_OF_RANGE);
    }
  return _matrix[row * _cols + col];
}

float &Matrix::operator[] (int i)
{
  if (i >= _rows * _cols || i < 0)
    {
      throw std::out_of_range (OUT_OF_RANGE);
    }
  return _matrix[i];
}

float &Matrix::operator[] (int i) const
{
  if (i >= _rows * _cols || i < 0)
    {
      throw std::out_of_range (OUT_OF_RANGE);
    }
  return _matrix[i];
}

std::ostream &operator<< (std::ostream &s, const Matrix &a)
{
  for (int i = 0; i < a._rows; ++i)
    {
      for (int j = 0; j < a._cols; ++j)
        {
          if (a (i, j) > PROB)
            {
              s << "**";
            }
          else
            {
              s << "  ";
            }
        }
      s << std::endl;
    }
  return s;
}

std::istream &operator>> (std::istream &s, Matrix &a)
{
  if (s)
    {
      //reading from the starts till the end and calculating the length
      s.seekg (0, std::istream::end);
      int length = (int) (s.tellg () / sizeof (float));
      if (length != a._rows * a._cols)
        {
          throw std::runtime_error (RUNTIME_ERROR);
        }
      //jumping back to the start
      s.seekg (0, std::istream::beg);
      for (int i = 0; i < length; ++i)
        {
          if (!(s.read ((char *) &a[i], sizeof (float))))
            {
              throw std::runtime_error (RUNTIME_ERROR);
            }
        }
    }
  return s;
}