#ifndef MATRIX_H
#define MATRIX_H
#include"vector3d.h"
#include<iostream>
#include <stdlib.h>
#include <math.h>

class Matrix
{
public:
   double **aij;
   int n;
   int m;
   Matrix(vector3d v);
   Matrix (vector3d v, float w);
   double cofactor (int i, int j);
   Matrix inversa();
    Matrix pseudoinversa(int &contador);
   int size () const;
   Matrix Mij(int a,int b);
   vector3d operator *(const vector3d &P);
   Matrix(int nn,int mm);
   Matrix();
   void zero(int nn, int mm);
   void identity(int nn);
   void resetIdentity();
   void definir();
   void mostrar();
   double& ij(int i,int j)const;
   Matrix(const Matrix &B);
   float column_2norm(int col)const;
   void replace_submatrix1(int i0, int i1, int j0, int j1, const Matrix &S);
   Matrix submatrix(int i1, int i2, int j1, int j2)const;
   Matrix operator +( const Matrix &A)const;
   Matrix& operator =( const Matrix &A);
   Matrix operator -(const  Matrix &A)const;
   Matrix operator *(const  Matrix &B)const;
   void interchange_columns(int ii, int jj);
   void interchange_rows(int ii, int jj);

   double& entry(int i, int j)const;
   void FillRnd();
   Matrix transpose()const;
   friend  Matrix operator*(double tt, const Matrix &A);
  ~Matrix();
   double determinante();
};

#endif // MATRIX_H
