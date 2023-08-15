// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include "iostream"

#define LENGTH_ERROR "length_error"
#define RUNTIME_ERROR "runtime error"
#define OUT_OF_RANGE "out of range"
#define DEF_SIZE 1
#define PROB 0.1

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

class Matrix
{
 private:
  int _rows;
  int _cols;
  float *_matrix;

 public:
  Matrix (int rows, int cols)
  {
    if (rows <= 0 || cols <= 0)
      {
        throw std::length_error (LENGTH_ERROR);
      }
    _rows = rows;
    _cols = cols;
    _matrix = new float[_rows * _cols] ();
  }

  /**
   * default constructor
   */
  Matrix () : Matrix (DEF_SIZE, DEF_SIZE)
  {}
  /**
   * constructor
   * @param m
   */
  Matrix (Matrix const &m);

  /**
   * destructor
   */
  ~Matrix ()
  {
    delete[] _matrix;
  }

  /**
   *
   * @return num of rows in this matrix
   */
  int get_rows () const
  { return _rows; }

  /**
   *
   * @return num of cols in this matrix
   */
  int get_cols () const
  { return _cols; }

  /**
   *
   * @return a transposed matrix
   */
  Matrix &transpose ();

  /**
   *
   * @return turn a given matrix into one vector
   */
  Matrix &vectorize ();

  /**
   *    print the matrix
   */
  void plain_print () const;

  /**
   *
   * @param m
   * @return multiply each element in the same index element in the other
   * matrix
   */
  Matrix dot (const Matrix &m) const;

  /**
   *
   * @return  square of the sum of all cells ^2
   */
  float norm () const;

  /**
   *
   * @param b
   * @return this + b matrix
   */
  Matrix &operator+= (const Matrix &b);

  /**
   *
   * @param b
   * @return this + b matrix
   */
  Matrix operator+ (const Matrix &b) const;

  /**
   *    assigment
   * @param b
   * @return
   */
  Matrix &operator= (const Matrix &b);

  /**
   *
   * @param b
   * @return    this * b matrix
   */
  Matrix operator* (const Matrix &b) const;

  /**
   *
   * @param b
   * @return this * b matrix
   */
  Matrix operator* (float b) const;

  /**
   *
   * @param b
   * @param a
   * @return a * b matrix
   */
  friend Matrix operator* (float b, const Matrix &a);

  /**
   * index
   * @param row
   * @param col
   * @return this[row][col]
   */
  float &operator() (int row, int col);

  /**
   *
   * @param row
   * @param col
   * @return this[row][col]
   */
  float &operator() (int row, int col) const;

  /**
   *
   * @param i
   * @return this[i]
   */
  float &operator[] (int i);

  /**
   *
   * @param i
   * @return  this[i]
   */
  float &operator[] (int i) const;

  /**
   * << operator
   * @param s
   * @param a
   * @return
   */
  friend std::ostream &operator<< (std::ostream &s, const Matrix &a);

  /**
   * >> operator
   * @param s
   * @param a
   * @return
   */
  friend std::istream &operator>> (std::istream &s, Matrix &a);
};

#endif //MATRIX_H