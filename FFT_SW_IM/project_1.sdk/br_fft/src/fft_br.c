#include "fft_br.h"

//Complex Multiplication

cmplx cadd(cmplx a , cmplx b){
    cmplx c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;

    return c;
}

cmplx csub(cmplx a , cmplx b){
    cmplx c;
    c.real = a.real - b.real;
    c.imag = a.imag - b.imag;

    return c;
}

cmplx cmul(cmplx a , cmplx b){
    cmplx c;

    c.real = a.real * b.real - a.imag * b.imag;
    c.imag = a.real * b.imag + b.real * a.imag;

    return c;
}

void cooley_tukey(cmplx *arr, cmplx *oparr, int len){
    cmplx tmparr[len]; 
    int n=log2(len), bin[n];

    for (int i = 0; i < len; i++){

        int a = i, val = 0, base = 1;

        for(int j = 0; j < n; j++){
            bin[j] = a & 0x01 ? 1 : 0;
            a>>=1;
        }
        
       for (int k = n-1; k > -1; k--){
            val = val + bin[k] * base;
            base = base * 2;
        }

        tmparr[val].real = arr[i].real;
        tmparr[val].imag = arr[i].imag;
    }


    for (int i = 0; i < len; i++){
        oparr[i].real = tmparr[i].real;
        oparr[i].imag = tmparr[i].imag;
    }


    //Finished Bit reversal.



    for (int s = 1; s <= n; ++s){
        int m = 1 << s;
        int m2 = m >> 1;

        cmplx w; 
        w.real = 1;
        w.imag = 0;

        cmplx wm;
        wm.real = cos(M_PI/m2);
        wm.imag = sin(-M_PI/m2);

        for (int j = 0; j < m2; ++j) {
            for (int k = j; k < len; k += m){

                cmplx t, u;                
                t = cmul(w,oparr[k + m2]);
                u = oparr[k];

		        oparr[k] = cadd(u, t);
		        oparr[k + m2] = csub(u, t);
            }
            w = cmul(w,wm);
        }
    }

}

void FFT(cmplx *array, cmplx *oparray, int len){
    
    cooley_tukey(array,oparray,len);

}
