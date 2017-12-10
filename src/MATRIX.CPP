#include "Matrix.h"
using namespace std;
///Copyright (C) <2017>  <Eliseo Rivera> curso.tareas@gmail.com
 int sign(float x) {
	return ((float(0)<x) - (x<float(0)));  //correcto, revisar QR,SVD es correcto

};
Matrix::Matrix(vector3d v){
int nn=3; int mm=1;

if (nn>0&&mm>0){
  aij=new double*[nn];
  for(int i = 0; i < nn; i++)  aij[i] = new double[mm];
  n=nn;
  m=mm;

  for( int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){
    //    coutincorrect <<"introduce ij ("<<i+1 <<","<<j+1<<")"<<endl;
           // cin>>ij(i,j);
aij[i][j]=0;
    };
}
ij(0,0)=v.x;
ij(1,0)=v.y;
ij(2,0)=v.z;
}
Matrix::Matrix(vector3d v,float w){
int nn=4; int mm=1;

if (nn>0&&mm>0){
  aij=new double*[nn];
  for(int i = 0; i < nn; i++)  aij[i] = new double[mm];
  n=nn;
  m=mm;

  for( int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){
    //    coutincorrect <<"introduce ij ("<<i+1 <<","<<j+1<<")"<<endl;
           // cin>>ij(i,j);
aij[i][j]=0;
    };
}

ij(0,0)=v.x;
ij(1,0)=v.y;
ij(2,0)=v.z;
ij(3,0)=1;
}
double Matrix::cofactor (int i, int j){
double c;
c=pow (-1,i+j)*Mij(i,j).determinante();  //cofactor
return c;
};

float Matrix::column_2norm(int col)const {
	float norm = 0.0L;
	for (int i = 0; i<n; i++) {
		norm = norm + entry(i, col)*entry(i, col);
	}
	return sqrt(norm);
};
Matrix Matrix::inversa(){
double d=(*this).determinante();

if (d==0) { Matrix B(1,1); cout<<" no existe la inversa"<<endl; return B;}
 if(n>2) {
    Matrix B(n,n);
     for( int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
         B.aij[j][i]=(1.0/d)*cofactor(i,j);


    }
    return B;

}
else if(n==2) {
    Matrix B(n,n);
     B.aij[0][0]=(1.0/d)*aij[1][1];

      B.aij[0][1]=-(1.0/d)*aij[0][1];
       B.aij[1][0]=-(1.0/d)*aij[1][0];
      B.aij[1][1]=(1.0/d)*aij[0][0];
    return B;

}
else if(n==1) {
    Matrix B(1,1);
     B.aij[0][0]=1/aij[0][0];


    return B;

}

};
	void Matrix::FillRnd(){
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			entry(i, j) = (rand() % 10)-5;
		};

	}

	void Matrix::replace_submatrix1(int i0, int i1, int j0, int j1, const Matrix &S) {
//usada comunmente
	int sr = S.n; int sc = S.m;
	int itam, jtam;
	itam = i1 - i0 + 1;
	jtam = j1 - j0 + 1;

	if ((itam>0 && jtam>0 && S.n>0 && S.m>0) && ((i1<n) && (j1<m)) && (itam == S.n) && (jtam == S.m)) {
		for (int i = 0; i<itam; i++)
			for (int j = 0; j<jtam; j++) {
				entry(i0 + i, j0 + j) = S.entry(i, j);
			}
	}
	else { cout << "no hay reemplzazo, quedò igual" << endl; }
}
Matrix Matrix::submatrix(int i1, int i2, int j1, int j2)const {

	int nn, mm;
	nn = i2 - i1 + 1; mm = j2 - j1 + 1;

	if(nn>=1&&mm>=1){
	Matrix M(nn, mm);

	for (int i = 0; i<nn; i++)
		for (int j = 0; j<mm; j++) {
			M.entry(i, j) = entry(i1 + i,j1 + j);

		}


	;

	return M;
	}

}
Matrix Matrix::pseudoinversa(int &contador){
//return (((transpose()*(*this)).inversa())*transpose());


Matrix U(*this);
Matrix V;
V.identity(n);
contador=0;
	float alpha,beta,gamma,eta,t,c,s;
	float s1,s2,s3;
	float epsilon=0.0000000001;
	do{

		for (int j =1; j<n; j++)
			for (int i = 0; i<=j - 1; i++) {
//				const clock_t begin_time = clock();
		s1=0,s2=0,s3=0;

		for  (int k=0;k<n;k++){//estas suma se puede hacer en paralelo
			s1 = s1 +U.entry(k,i)*U.entry(k, i);
			s2 = s2 + U.entry(k, j)*U.entry(k,j);
			s3= s3 + U.entry(k, i)*U.entry(k, j);

		}

		alpha=s1, beta=s2, gamma=s3;

		eta=(beta-alpha)/(2*gamma);
		t=sign(eta)/(fabs(eta)+sqrt(1+eta*eta));
		c=1.0/sqrt(1+t*t);
		s=c*t;

		for (int k=0;k<n;k++){
		t=U.entry(k,i);
		U.entry(k, i)=c*t-s*U.entry(k,j);
		U.entry(k, j) = s*t +c*U.entry(k, j);

		}

		for (int k = 0; k<n; k++) {
			t = V.entry(k, i);
			V.entry(k, i) = c*t - s*V.entry(k, j);
			V.entry(k, j) = s*t + c*V.entry(k, j);

		}
	//	std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
		}

contador++;
	}while((fabs(gamma)/sqrt(alpha*beta))>epsilon&&contador<15);
if (contador<20){
	Matrix D(V.n,V.n);
	for (int k = 0; k<n; k++) {
	D.entry(k,k)=U.column_2norm(k);

	U.replace_submatrix1(0,U.n-1,k,k, (1.0/D.entry(k,k))*U.submatrix(0, U.n - 1, k, k));
	}

	Matrix U1(U);
	Matrix V1(V);
	float menor;
	for (int j = D.m; j>0; j--) {
		menor = D.entry(0, 0);

		for (int i = 1; i<j; i++) {

			if (menor<D.entry(i, i)) {
				menor = D.entry(i, i);
				D.entry(i, i) = D.entry(i - 1, i - 1);
				D.entry(i - 1, i - 1) = menor;


				V1.interchange_rows(i - 1, i);
				U1.interchange_columns(i - 1, i);
			}
			menor = D.entry(i, i);

		}
	}






   for (int k = 0; k<n; k++) {
        if (D.entry(k,k)!=0)	D.entry(k,k)=1.0/(	D.entry(k,k));

	}






return (V*D*U.transpose());
}
else {
Matrix A;
A.identity(4);
        return  A;}


}

void Matrix::interchange_rows(int ii, int jj) {

	if (ii<n&&ii >= 0 && jj<n&&jj >= 0) {
		Matrix f1(1, m);

		for (int i = 0; i<m; i++) {
			f1.entry(0, i) = entry(ii, i);
			entry(ii, i) = entry(jj, i);
			entry(jj, i) = f1.entry(0, i);
		}
	}

}
void Matrix::interchange_columns(int ii, int jj) {
	if (ii<m&&ii >= 0 && jj<m&&jj >= 0) {
		Matrix f1(n, 1);

		for (int i = 0; i<n; i++) {
			f1.entry(i, 0) = entry(i, ii);
			entry(i, ii) = entry(i, jj);
			entry(i, jj) = f1.entry(i, 0);
		}
	}

}
Matrix Matrix::transpose()const {
	Matrix T(m, n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			T.entry(j, i) = entry(i, j);
		}
	return T;

};
    int Matrix::size () const{return n*m;};
    Matrix Matrix::Mij(int a,int b){ //menor de una matriz
        if (n==m&&size()>0){ // eliminar fila a y columna b

    int s=n-1;
    Matrix B(s,s); //matriz de tamaño reducido
    for (int i=0; i<a;i++)
    for (int j=0; j<b;j++)

    {
      B.aij[i][j]=aij[i][j]; //primera parte
    }

      for (int i=0; i<a;i++)
    for (int j=b+1; j<m;j++)

    {
      B.aij[i][j-1]=aij[i][j];  //se recorren las columnas
    }

        for (int i=a+1; i<n;i++)
    for (int j=0; j<b;j++)

    {
      B.aij[i-1][j]=aij[i][j];  //se recorren las columnas
    }


        for (int i=a+1; i<n;i++)
    for (int j=b+1; j<m;j++)

    {
      B.aij[i-1][j-1]=aij[i][j];   //se recorren las columnas
    }
    return B;
}
};
vector3d Matrix::operator *(const vector3d &P){//operacion multiplicacion por punto
Matrix A(3,1);
A.aij[0][0]=P.x;
A.aij[1][0]=P.y;
A.aij[2][0]=P.z;

Matrix T((*this)*A);

vector3d Pr;
Pr.x=T.aij[0][0];
Pr.y=T.aij[1][0];
Pr.z=T.aij[2][0];
return Pr;
}
Matrix::Matrix(int nn,int mm){ //constructor a partir de n y m
if (nn>0&&mm>0){
  aij=new double*[nn];
  for(int i = 0; i < nn; i++)  aij[i] = new double[mm];
  n=nn;
  m=mm;

  for( int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){
    //    coutincorrect <<"introduce ij ("<<i+1 <<","<<j+1<<")"<<endl;
           // cin>>ij(i,j);
aij[i][j]=0;
    };
} ;   //numero de filas
//coutincorrect<<"\n"<<endl;
};
Matrix::Matrix(){



n=m=0;
  //numero de filas

};
void Matrix::zero(int nn, int mm){
     n=nn;
        m=mm;
     //constructor de mat


if (n>0&&m>0){



  aij=new double*[n];
  for(int i = 0; i < n; i++)  aij[i] = new double[m];


  for( int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){

        ij(i,j)=0.0;;

    };
} ;   //numero de filas
//coutincorrect<<"\n"<<endl;
};
 void Matrix::resetIdentity(){

  for( int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){
if(  i==j)ij(i,j)=1.0;
else ij(i,j)=0.0;

    };
 }

void Matrix::identity(int nn){
     n=nn;
        m=nn;
     //constructor de mat


if (n>0&&m>0){



  aij=new double*[n];
  for(int i = 0; i < n; i++)  aij[i] = new double[m];


  for( int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){
if(  i==j)ij(i,j)=1.0;
else ij(i,j)=0.0;

    };
} ;   //numero de filas
//coutincorrect<<"\n"<<endl;
};

void Matrix::definir(){
    cout <<"Creando Matriz "<<endl;
     cout <<"introduce el numero de filas "<<endl;
     cin>> n;
         cout <<"introduce  el numero de columnas "<<endl;
              cin>> m;
     //constructor de mat


if (n>0&&m>0){



  aij=new double*[n];
  for(int i = 0; i < n; i++)  aij[i] = new double[m];


  for( int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){
        cout<<"introduce ij ("<<i+1 <<","<<j+1<<")"<<endl;
        cin>>ij(i,j);

    };
} ;   //numero de filas
//coutincorrect<<"\n"<<endl;
};
void Matrix::mostrar(){
  if (this->n>0&&this->m>0){


  cout<<"\n"<<endl;
for( int i = 0; i < n; i++){
    for( int j = 0; j < m; j++){

      cout<<ij(i,j)<<"  "<<flush;
    }
    cout<<"\n"<<endl;
    }
}
}
double& Matrix::ij(int i,int j)const{ //devuelve la direccion
if (i>=0&&j>=0&&i<n&&j<m) return aij[i][j]; //c++ numera las ijs de una matrix a partir de cero, nosotros a partir de 1

};
Matrix::Matrix(const Matrix &B){
if(B.size()!=0){
        n=B.n;
        m=B.m;


        aij=new double*[n];
  for(int i = 0; i < n; i++)  aij[i] = new double[m];

    for( int i = 0; i < n; i++)
    for( int j = 0; j < m; j++){

       aij[i][j]=B.aij[i][j];

    }

}
};
Matrix Matrix::operator +( const Matrix &A)const{
if (n>0&&m>0){
 if (n==A.n&&m==A.m){

Matrix B(n,m);

for( int i = 0; i < n; i++)
    for( int j = 0; j < m; j++){

        B.aij[i][j]= aij[i][j]+A.aij[i][j];

    }

      return B;
    }
    else{Matrix B(1,1); cout<<" Tamaños diferentes"<<endl;  return B;};

    }


};
Matrix& Matrix::operator =( const Matrix &A){
if (A.n>0&&A.m>0&&n==A.n&&m==A.m){

Matrix B(n,m);
for( int i = 0; i < n; i++)
    for(int j = 0; j < m; j++){

       aij[i][j]=A.aij[i][j];
    }
      return *this;

     }   else{Matrix B(1,1); cout<<" Tamaños diferentes"<<endl;  return *this;}

};
Matrix Matrix::operator -(const Matrix &A)const{
if (this->n>0&&this->m>0){
 if (this->n==A.n&&this->m==A.m){
Matrix B(n,m);
for( int i = 0; i < this->n; i++)
    for(int j = 0; j < this->m; j++){

        B.ij(i,j)= ij(i,j)-A.ij(i,j);
    }
      return B;
    }    else{Matrix B(1,1); cout<<" Tamaños diferentes"<<endl;  return B;}
}

};
Matrix Matrix::operator *(const  Matrix &B)const{ //multiplicaciion de matrices
if (size()>0&&B.size()>0){
 if (m==B.n){
Matrix A(n,B.m);

for( int i = 0; i < n; i++)
    for(int j = 0; j < B.m; j++){
            float s=0;
    for(int k=0;k<m;k++){s=s+ij(i,k)*B.ij(k,j); }
        A.ij(i,j)= s;
    }
      return A;
    }    else{Matrix B(1,1); cout<<" Tamaños diferentes"<<endl;  return B;} }


};
Matrix operator*(double tt, const Matrix &A){
if (A.n>0&&A.m>0){

Matrix B(A.n,A.m);
for(int i = 0; i < A.n; i++)
    for( int j = 0; j < A.m; j++){

        B.ij(i,j)= tt*A.ij(i,j);
    }


    return B;
     }


};
Matrix::~Matrix(){


			if (n>0){
				for (int i = 0; i<n; i++){
					delete[] aij[i];  //se elimnan las columnas
				}
				delete[] aij; //eliminar las filas
				aij = NULL;
			}
	}

double Matrix::determinante(){  //se define en forma recursiva
double d=0;
if (n!=m) {cout<<"la matriz no es cuadrada"<<endl; return 0; }
 if (n>2){
for (int j=0; j<m;j++){

    d=d+aij[0][j]*pow (-1,j)*Mij(0,j).determinante();

}
return d;
} else if (n==2) {
    d=aij[0][0]*aij[1][1]-aij[0][1]*aij[1][0];
    return d;

} else if(n==1){

return aij[0][0];
};

}

double& Matrix::entry(int i, int j)const{
return aij[i][j];
}
