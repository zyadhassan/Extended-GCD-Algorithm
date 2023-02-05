#include <iostream>
#include <vector>
using namespace std;

// Function to Read the Polynomial
void readPoly(vector<float>& poly)
{
	int n;
	cout << "Enter the degree of the polynomial: ";
	cin >> n;
	poly.resize(n + 1);
	for (int i = 0; i <= n; i++)
	{
		cout << "Enter the coefficient of x^" << i << ": ";
		cin >> poly[i];
	}
}

// function to print polynomial
void printPoly(vector<float> poly)
{
	int n = poly.size();
	for (int i = 0; i < n; i++)
	{
		cout << poly[i];
		if (n == 1) {
			break;
		}
		if (i>0 )
			cout << "x^" << i;
		if (i != n - 1)
			cout << " + ";
	}
	cout << endl;

}

// function to divide two polynomials
vector<float> divPoly(vector<float> a, vector<float> b, int set)
{
	int n = a.size();
	int m = b.size();
	vector<float> q;
	if (n < m)
	{
		q.push_back(0);
		return q;
	}
	else
	{
		q.resize(n - m+1 );
		vector<float> temp;
		temp.resize(n);
		for (int i = 0; i < n; i++)
		{
			temp[i] = a[i];
		}
		int s = 0;
		for (int i = n - m ; i >= 0; i--)
		{
			q[i] =(float) temp[n-1-s] / b[b.size()-1];
			s++;
			/*for (int j = 0; j < m; j++)
			{
				temp[i + j] = temp[i + j] - q[i] * b[j];
			}*/
		}
		return q;
	}
}


//Function to subtract two polynomials
vector<float> subPoly(vector<float> a, vector<float> b, int set)
{
	int n = a.size();
	int m = b.size();
	vector<float> c;
	if (n > m)
	{
		c.resize(n);
		for (int i = 0; i < m; i++)
		{
			c[i] = a[i] - b[i];
		}
		for (int i = m; i < n; i++)
		{
			c[i] = a[i];
		}
	}
	else
	{
		c.resize(m);
		for (int i = 0; i < n; i++)
		{
			c[i] = a[i] - b[i];
		}
		for (int i = n; i < m; i++)
		{
			c[i] = -b[i];
		}
	}
	for (int i = 0; i < c.size(); i++)
	{
		c[i] = (int)c[i] % set;
		if (c[i] < 0) {
			c[i] = c[i] + set;
		}
	}
	return c;
}
//function to multiply two polynomials
vector<float> mulPoly(vector<float> a, vector<float> b, int set)
{
	int n = a.size();
	int m = b.size();
	vector<float> c;
	c.resize(n + m - 1);
	for (int i = 0; i < n + m - 1; i++)
	{
		c[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			c[i + j] = c[i + j] + a[i] * b[j];
			c[i + j] = (int)c[i + j] % set;
		}
	}
	return c;
}

// function to erase the zero elements from the end of the polynomial
vector<float> eraseZero(vector<float> a)
{
	int n = a.size();
	int i = n - 1;
	while (i >= 0 && a[i] == 0 )
	{
		i--;
	}
	if (i == -1)return{ 0 };
	vector<float> b;
	b.resize(i + 1);
	for (int j = 0; j < i + 1; j++)
	{
		b[j] = a[j];
	}
	return b;
}



// Implemnation of the EXtended Eculidean GCD algorithm
// Input: Two polynomials a and b
// Output: The multiplicative inverse of a mod b
void EXTENGCD(vector<float> a, vector<float> b, int set, bool flag) {
	vector<float> A1 = { 1 };
	vector<float> A2 = { 0 };
	vector<float> B1 = { 0 };
	vector<float> B2 = { 1 };
	vector<float> q;
	vector<float> r;
	vector<float> m;
	vector<float> n;
	vector<float> temp;
	while (b.size() != 1 ){
		
		q = divPoly(a, b, set);
		r = subPoly(a, mulPoly(q, b, set), set);
		m = subPoly(A1, mulPoly(q, B1, set), set);
		n = subPoly(A2, mulPoly(q, B2, set), set);
		a = b;
		b = r;
		A1 = B1;
		A2= B2;
		B1= m;
		B2 = n;
		a = eraseZero(a);
		b = eraseZero(b);
		
		
	}
	if (flag &&b.size()==1 && b[0] == 1) {
		cout << "Multiplicative Inverse of a mod b = ";
		B2 = eraseZero(B2);
		printPoly(B2);
	}
	if (b.size() == 0 || (b.size() == 1 && b[0] == 0)) {
		cout << "GCD(a,b) = ";
		printPoly(a);
	}
}

// main function
int main()
{

	// Enter The Cofficent set if you want 
	int set ;
	cout << "Enter the Coffeicent set ? example : enter 2 if you want set of Z2" << endl;
	cin >> set;

	

	// The first polynomial
	cout << "For finding the multiplicative inverse of a mod b enter the first polynomial as a and the second polynomial as b" << endl;
	
	cout << "Enter the First polynomial " << endl;
	vector<float> a ;
	readPoly(a);
	printPoly(a);


	// The second polynomial

	cout << "Enter the Second polynomial" << endl;
	vector<float> b ;
	readPoly(b);
	printPoly(b);

	if (a.size() > b.size()) {
		// a mod b
		a= subPoly(a, mulPoly(divPoly(a, b, set), b, set), set);	
		a = eraseZero(a);
	}

	
	EXTENGCD(b, a, set, true);
	


	return 0;
}