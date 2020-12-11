#pragma once
#include<complex>
#include <iostream>
#include <valarray>
#include <array>
#define M_PI 3.14159
using namespace std;

class FFT
{
public:
	/*void fft(array<long, sizeof(long)> &x, long N)
	{

		N = x.size();

		
		if (N <= 1) return;

		// divide
		std::complex<int> even = x[std::slice(0, N / 2, 2)];
		std::complex<int> odd = x[std::slice(1, N / 2, 2)];

		// conquer
		fft(even , N);
		fft(odd , N);

		// combine
		for (size_t k = 0; k < N / 2; ++k)
		{
			Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
			x[k] = even[k] + t;
			x[k + N / 2] = even[k] - t;
		}
	}*/
	void fft_help(complex<int> *v, int n, complex<int> *tmp) {
		if (n > 1) { /* otherwise, do nothing and return */
			int k, m;
			complex<int> z, w, *vo, *ve;
			ve = tmp;
			vo = tmp + n / 2;

			for (k = 0; k < n / 2; k++) {
				ve[k] = v[2 * k];
				vo[k] = v[2 * k + 1];
			}

			fft_help(ve, n / 2, v); /* FFT on even-indexed elements of v[] */
			fft_help(vo, n / 2, v); /* FFT on odd-indexed elements of v[] */

			for (m = 0; m < n / 2; m++) {
				w.real(cos(2 * M_PI * m / (double)n));
				w.imag(-sin(2 * M_PI * m / (double)n));
				z.real(w._Re * vo[m]._Re - w._Im * vo[m]._Im); /* Re(w*vo[m]) */
				z.imag(w._Re * vo[m]._Im + w._Im * vo[m]._Re); /* Im(w*vo[m]) */
				v[m].real(ve[m]._Re + z._Re);
				v[m].imag(ve[m]._Im + z._Im);
				v[m + n / 2].real(ve[m]._Re - z._Re);
				v[m + n / 2].imag(ve[m]._Im - z._Im);
			}
		}
		return;
	}

};

