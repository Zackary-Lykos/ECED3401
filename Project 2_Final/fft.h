#include <iostream>
#include <valarray>
#include <vector>
#include <complex>
#include <cmath>
#include <fstream>
#include <string.h>
/*fft header: this header file is used to convert a vector of Wav file data to fft coefficents and
	return the  the largest coefficient in a segment of 1024 samples*/
const double PI = 3.141592653589793238460;
using namespace std;
typedef complex<double> Complex;
typedef valarray<Complex> CArray;

//typedef std::complex<double> Complex;
//typedef std::valarray<Complex> CArray;

//std::complex<double> Temp;

// Cooley¨CTukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void fft(CArray& x)
{
	const size_t N = x.size();
	if (N <= 1) return;

	// divide
	CArray even = x[std::slice(0, N / 2, 2)];
	CArray  odd = x[std::slice(1, N / 2, 2)];


	// conquer
	fft(even);
	fft(odd);

	// combine
	for (size_t k = 0; k < N / 2; ++k)
	{
		Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}


void ifft(CArray& x)
{
	// conjugate the complex numbers
	x = x.apply(std::conj);

	// forward fft
	fft(x);

	// conjugate the complex numbers again
	x = x.apply(std::conj);

	// scale the numbers
	x /= x.size();
}

vector<int> get_index(vector<int> data) {

	int segments = data.size() / 1024; // number of segments this data will create
	if (segments * 1024 < data.size()) { // since the last channel will not be exactly 1024 samples
		segments++; // add a addtional segment to account for this
	}

	int count = 0; // counter 
	vector<vector<double>> vec_segments; // organizes that data into a list of the 1024 segments
	vector<int> index; // index of the coefficients this function will return
	for (int i = 0; i < segments; i++) { // loop for each segment
		vector <double> temp2; // temp vector
		for (int j = 0; j < 1024; j++) { // loop to assign data to one segment
			temp2.push_back(data.at(count));
			count++;
			if (count == data.size()) { // once we have reached the size of the data vector there is no more data 
				break;
			}
		}
		vec_segments.push_back(temp2);// assign the vector to the segment vector
	}
		
	for (int x = 0; x < segments; x++) { // this loop is where the highest fft coefficient is getting assigned
		Complex temp[1024];// array of one temp complex segment 
		int y = 0; 
		int y_temp = 0;
		vector<double> temp3 = vec_segments.at(x);
		
		for (int k = 0; k < temp3.size(); k++) { // this loop converts the data to complex
			temp[k] = temp3.at(k);
			//cout << temp[k] <<" "<< temp3.at(k) << endl;
			
		}
		//temp3.clear();
		
		CArray fft_data(temp, temp3.size()); 
		complex<double> comp;
		
		//forward fft
		fft(fft_data);
		
		for (int q = 0; q < temp3.size(); q++) { // this loop will calulate the fft coefficient 
	
			comp = fft_data[q];
			y_temp = sqrt(comp.real() * comp.real() + comp.imag() * comp.imag());
			//cout << y_temp << endl; 
			if (y < y_temp) { // assigns the highest coefficient 
				y = y_temp;
			}
		}
		index.push_back(y); // assigns largest coefficient of the 1024 segemnt
		//cout << index.at(x) << endl;
	}
	
	//vec_segments.clear(); // reset the segment vector
	return index; // returns the index variable
}
	
	


	

/*
int main()
{	
	const Complex test[] = { 0.1787, 0.2577, 0.2431, -0.1078, 0.1555, -0.3288, 0.2060, -0.4682 };
	CArray data(test, 8);

	// forward fft
	_fft(data);
	float y;
	std::cout << "fft" << std::endl;
	for (int i = 0; i < 8; ++i)
	{
		std::cout << data[i] << std::endl;
		Temp = data[i];
		y = sqrt(Temp.real() * Temp.real() + Temp.imag() * Temp.imag());
		std::cout << y << std::endl;
	}

	// inverse fft
	ifft(data);

	/*	std::cout << std::endl << "ifft" << std::endl;
		for (int i = 0; i < 8; ++i)
		{
			std::cout << data[i] << std::endl;
			Temp = data[i];
			std::cout << Temp;
		}
	return 0;
}*/
