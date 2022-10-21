#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N) {
	float count=1e-12;
	int i;
	float res;
	
	for(i=0; i<N; i++){
		count+=x[i]*x[i];
	}
	
	res=10*log10(count/N);	
	return res;
}

float compute_am(const float *x, unsigned int N) {
	int i;
	float count=0;
	float res;
	
	for(i=0; i<N; i++){
		count=count+fabs(x[i]);
	}
	
	res=count/N;
     	return res;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
	int i;
	int canvi=0;
	float cte;
	float aux;
	float res;
	
	for(i = 1; i < N; i ++){
		if((x[i] < 0 && x[i - 1] > 0) || (x[i] > 0 && x[i - 1] < 0)){
			canvi = 1;
		}
	
		if (canvi==1){
			aux ++;
			canvi = 0;
		}
	}

	cte = fm/(2*(N-1));
	res = cte*aux;
	
	return res;
}

