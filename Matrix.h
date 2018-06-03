#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <fstream>

using namespace std;

template <typename type, size_t N, size_t M>
class Matrix 
{
private:
	type * * ptr;
public:
	Matrix();
	Matrix(initializer_list<type> list);
	Matrix(const Matrix&);
	auto swap(Matrix&) -> void;
	auto operator=(const Matrix& q)->Matrix&;
	auto empty() -> bool;
	auto columns()->size_t;
	auto rows()->size_t;
	auto operator-(const Matrix&)->Matrix;
	auto operator+(const Matrix&)->Matrix;
	auto operator[](size_t index)->type*;
	bool operator==(const Matrix&);
	template <typename T2, size_t N2, size_t M2>
	friend ostream& operator<<(ostream&, const Matrix<T2, N2, M2>&);
	template <typename T3, size_t N3, size_t M3>
	friend istream& operator>>(istream&, Matrix<T3, N3, M3>&);
	~Matrix();
};

template <typename type, size_t N, size_t M>
Matrix<type, N, M>::Matrix() : ptr(nullptr) 
{

}

template <typename type, size_t N, size_t M>
Matrix<type, N, M>::Matrix(initializer_list<type> list) {
	ptr = new type*[N];
	auto p = list.begin();
	for (unsigned int i = 0; i < N; i++)
	{
		ptr[i] = new type[M];
	}
	for (unsigned int i = 0; i < N; i++) 
	{
		for (unsigned int j = 0; j < M; j++, p++)
		{
			ptr[i][j] = *p;
		}	
	}
}

template <typename type, size_t N, size_t M>
Matrix<type, N, M>::Matrix(const Matrix& m_matrix) 
{
	ptr = new type *[N];
	for (unsigned int i = 0; i < N; i++) 
	{
		ptr[i] = new type[M];
		for (unsigned int j = 0; j < M; j++)
		{
			ptr[i][j] = m_matrix.ptr[i][j];
		}
	}
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::empty() -> bool 
{
	if (ptr == nullptr)
		return true;
	else
		return false;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::columns() -> size_t 
{
	return M;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::rows() -> size_t 
{
	return N;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::operator[](size_t index) -> type* 
{
	return ptr[index];
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::operator-(const Matrix& m_matrix) -> Matrix 
{
	for (unsigned int i = 0; i < N; i++) 
	{
		for (unsigned int j = 0; j < M; j++)
		{
			ptr[i][j] = ptr[i][j] - m_matrix.ptr[i][j];
		}
	}
	return *this;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::operator+(const Matrix& m_matrix) -> Matrix 
{
	for (unsigned int i = 0; i < N; i++) 
	{
		for (unsigned int j = 0; j < M; j++)
		{
			ptr[i][j] = ptr[i][j] + m_matrix.ptr[i][j];
		}
	}
	return *this;
}

template <typename type, size_t N, size_t M>
bool Matrix<type, N, M>::operator==(const Matrix& m_matrix) 
{
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < M; j++) 
		{
			if (ptr[i][j] != m_matrix.ptr[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

template <typename type, size_t N, size_t M>
ostream& operator<<(ostream& fout, const Matrix<type, N, M>& m_matrix) {
	fout << N << " " << M << endl;
	for (unsigned int i = 0; i < N; i++) {
		for (unsigned int j = 0; j < M; j++)
			fout << m_matrix.ptr[i][j] << "  ";
		fout << endl;
	}
	return fout;
}

template <typename type, size_t N, size_t M>
istream& operator>>(istream& fin, Matrix<type, N, M>& m_matrix) {
	if (fin) {
		m_matrix.ptr = new type*[N];
		for (unsigned int i = 0; i < N; i++)
			m_matrix.ptr[i] = new type[M];
		for (unsigned int i = 0; i < N; i++) {
			for (unsigned int j = 0; j < M; j++)
				fin >> m_matrix.ptr[i][j];
		}
	}
	return fin;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::swap(Matrix& m_matrix) -> void 
{
	type **curr;
	curr = new type *[N];
	for (unsigned int i = 0; i < N; i++) 
	{
		curr[i] = new type[M];
		for (unsigned int j = 0; j < M; j++)
		{
			curr[i][j] = m_matrix.ptr[i][j];
		}
	}
	for (unsigned int i = 0; i < N; i++) 
	{
		for (unsigned int j = 0; j < M; j++)
		{
			m_matrix.ptr[i][j] = this->ptr[i][j];
		}
	}
	for (unsigned int i = 0; i < N; i++) 
	{
		for (unsigned int j = 0; j < M; j++)
		{
			m_matrix.ptr[i][j] = this->ptr[i][j];
		}
	}
	for (unsigned int i = 0; i < N; i++)
		delete[] curr[i];
	delete[] curr;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::operator=(const Matrix& m_matrix) -> Matrix& 
{
	if (ptr != nullptr)
	{
		for (unsigned int i = 0; i < N; i++)
		{
			delete[] ptr[i];
		}
		delete[] ptr;
		return *this;
	}
	ptr = new type*[N];
	for (unsigned int i = 0; i < N; i++)
	{
		ptr[i] = new type[M];
	}
	for (unsigned int i = 0; i < N; i++) 
	{
		for (unsigned int j = 0; j < M; j++)
		{
			ptr[i][j] = m_matrix.ptr[i][j];
		}
	}
	return *this;
}

template <typename type, size_t N, size_t M>
Matrix<type, N, M>::~Matrix() 
{
	for (unsigned int i = 0; i < N; i++)
	{
		delete[] ptr[i];
	}
	delete[] ptr;
}
