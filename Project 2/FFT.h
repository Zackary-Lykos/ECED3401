//
//  fft.h
//  Wav File Editor
//
//  Created by Zackary Lykos on 2020-12-12.
//
#ifndef _FFT_H_
#define _FFT_H_
#include<complex>
#include <iostream>
#include <valarray>
#include <array>
#define M_PI 3.14159
using namespace std;
#endif
class FFT
{
public:
	void fft_help(complex<int>* v, int n, complex<int>* tmp) { // v Ϊ�������ݣ�nΪ��Ƭ������ tmpΪ�����ݵȳ��Ŀ�����
		if (n > 1) { // verifies that there are elements in the array
			int k, m; // counters ����������
			complex<int> z, w, * vo, * ve; // declaration of complex variables for indexing //��ʼ����������

			//��һ�ֳ�ʼ�������壬�ڶ��ֳ�ʼ������
			ve = tmp; // even part of the signal. Var tmp is temporary space needed to define ve  //ʵ������
			vo = tmp + n / 2; // odd part of the signal ��������

			//Example wave file data: 11 22 33 44 55 66
			//wave file data format: s1c1: real 11 + complex 22; s1c2: real 33 + complex 44; s2c1: real 55 + complex 66;

			for (k = 0; k < n / 2; k++) { // loop to store even and odd elements (data) in both vo and ve ����д�롣��ʽ����
				ve[k] = v[2 * k]; // collects even indexed samples real
				vo[k] = v[2 * k + 1]; // collects odd indexed samples complex
			}

			//(I believe this function is recursive to get a better approximation of the signal) �ݹ飬���岻��
			fft_help(ve, n / 2, v); // FFT on even-indexed elements of v[] 
			fft_help(vo, n / 2, v); // FFT on odd-indexed elements of v[] 

			for (m = 0; m < n / 2; m++) {// n/2��ȡһ�����fft����512
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
