#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

template <class T>
class Matrix{
	public:
		Matrix(int rows, int cols);
		Matrix(Matrix &m);
		Matrix &operator+=(const Matrix &m);
		Matrix operator+(const Matrix &m) const;
		Matrix &operator*=(const Matrix &m);
		Matrix operator*(const Matrix &m) const;
		Matrix& operator=(const Matrix &m);
		T& at(int row, int col);
		T& at(int row, int col)const;
		int getcols()const{return cols;}
		int getrows()const{return rows;}
		template <class U>
		friend ostream &operator <<(ostream &OS, Matrix<U> m);
	private:
		T **matr;
		int cols;
		int rows;
};

template <class T>
Matrix<T>::Matrix(int rows, int cols){
	this->rows = rows;
	this->cols = cols;
	matr = new T*[rows];
	for (int i = 0; i<rows;i++) matr[i] = new T[cols];
	for (int i = 0; i<rows;i++)
		for (int j=0;j<cols;j++)
			matr[i][j] = rand()%10;
}

template <class T>
Matrix<T>::Matrix(Matrix &m){
	rows = m.getrows();
	cols = m.getcols();
	matr = new T*[rows];
	for (int i=0; i<rows;i++) matr[i]=new T[cols];
	for (int i = 0; i<rows;i++)
		for (int j=0;j<cols;j++)
			matr[i][j] = m.at(i,j);
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& m){
	for (int i=0; i<rows;i++)
		for(int j=0; j<cols;j++)
			this->matr[i][j] = m.at(i,j);
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix &m){
	if (cols!=m.cols || rows!=m.rows) cout << "Matrizengroessen stimmen nicht ueberein";
	else{
	for (int i=0; i<rows;i++)
		for(int j=0;j<cols;j++)
			this->matr[i][j] = m.matr[i][j];
}
return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix &m) const{
return Matrix(m);
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix &m){
	*this = *this*m;
	return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix &m)const{
	Matrix<T> temp(this->getrows(), m.getcols());
	for (int i = 0; i<temp.getrows();i++)
		for (int j=0; j<temp.getcols();j++)
			temp.at(i,j)=0;
	if (this->getcols()!=m.getrows()) {
		cout << "M1 Spaltenanzahl != M2 Zeilenanzahl" << endl;	
	}
	else{
		for (int i=0; i<this->rows;i++){
			for (int j=0; j<m.getcols();j++){
				for (int k=0; k<this->cols;k++){
					temp.at(i,j) += this->at(i,k)*m.at(k,j);
				}
			}
		}
	}
	return temp;
}

template <class T>
T& Matrix<T>::at(int row, int col){
	return matr[row][col];
}

template <class T>
T& Matrix<T>::at(int row, int col)const{
	return matr[row][col];
}

template <class U>
ostream &operator<<(ostream &OS, const Matrix<U> m){
	for (int i=0; i<m.rows;i++){
		for (int j=0; j<m.cols;j++)
			OS << m.matr[i][j] << " ";
		OS << "\n";
	}
	return OS;
}


int main(){
	srand(time(0));
	Matrix<int> m1(2,2);
	Matrix<int> m2(2,2);
	Matrix<int> m3(2,2);
	m3 = m1*m2;
	cout << m1 << endl << m2 << endl << m3 << endl;
	m1*=m2;
	cout << m1 << endl;
	return 0;
}

