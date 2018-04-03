#include <iostream>
using namespace std;

const int N = 10;

template <class T>
inline T sum(T d[],int d_size)
{
	T result = 0;
	for(int i = 0 ; i < d_size ; i++)
		result += d[i];
	return result;
}

int main()
{
	int data[N];
	for (int i = 0; i < N ; i++)
		data[i] = i;
	cout << "Sum : " << sum(data,sizeof(data)/sizeof(data[0])) << endl;
	double new_data[] = {0.1,0.2,0.3,0.4,0.5};
	cout << "Sum : " << sum(new_data,sizeof(new_data)/sizeof(new_data[0])) << endl;
	return 0;
}