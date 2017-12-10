#ifndef ROBOT_H
#define ROBOT_H
#include "modelo3D.h"
#include<vector>
#include <cstdlib>
///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com
class Robot
{
    public:
        Robot();
        ~Robot();

        modelo3D *base;
           modelo3D *e1;
              modelo3D *e2;
                modelo3D *e3;
                    modelo3D *e4;
                        modelo3D *e5;


void inicializar();
void renderizar();
void configurarTH();

void AplicarTHx(float theta, vector3d d);
void AplicarTHy(float theta, vector3d d);
void AplicarTHz(float theta, vector3d d);
Matrix THx,THy,THz,TH;

std::vector<Matrix> THList;
std::vector<vector3d> Origenes;
std::vector<modelo3D*> modelos;


float theta1, theta2, theta3,theta4, theta5, theta6,theta7;
float z3;
vector3d d1,d2,d3,d4,d5,d6,d7;

Matrix J;
void DefinirJacobian(float q1, float q2,float q3, float q4);
void Newton_Rapshon(float &q1,float &q2,float &q3,float &q4);
void PrepararNewtonRapshon();
void parametrica();

Matrix  F(float q1,float q2,float q3,float q4);
float Xg,Yg,Zg; ///posición global de efector final
float t;///parámetro de ecuacion parametrica a seguir por el efector final

private :
void DefinirTHx(float theta, vector3d d);
void DefinirTHy(float theta, vector3d d);
void DefinirTHz(float theta, vector3d d);
void  Drawarrow3D( vector3d A,  vector3d B, vector3d color, double cota1,double R) ;


};

#endif // ROBOT_H
