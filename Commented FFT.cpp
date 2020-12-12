

void fft_help(complex<int> *v, int n, complex<int> *tmp) {
		if (n > 1) { // verifies that there are elements in the array
			int k, m; // counters 
			complex<int> z, w, *vo, *ve; // declaration of complex variables for indexing 
			ve = tmp; // even part of the signal. Var tmp is temporary space needed to define ve 
			vo = tmp + n / 2; // odd part of the signal

			for (k = 0; k < n / 2; k++) { // loop to store even and odd elements (data ) in both vo and ve 
				ve[k] = v[2 * k]; // collects even indexed samples 
				vo[k] = v[2 * k + 1]; // collects odd indexed samples 
			}
			
			//(I believe this function is recursive to get a better approximation of the signal)
			fft_help(ve, n / 2, v); // FFT on even-indexed elements of v[] 
			fft_help(vo, n / 2, v); // FFT on odd-indexed elements of v[] 



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

