#ifndef PAV_ANALYSIS_H
#define PAV_ANALYSIS_H

/* COMPUTE POWER
 * Compute the power of a signal using the mathematical definition
 * @input x : vector, signal to compute the power from.
 * @input N : Size of the vector x.
 * @return The power value in dB (10log(p)).
*/
float compute_power(const float *x, unsigned int N);

/* COMPUTE AMPLITUDE AVERAGE
 * Compute the amplitude average of a signal.
 * @input x : vector, signal.
 * @input N : Size of the vector x.
 * @return The amplitude average value.
*/
float compute_am(const float *x, unsigned int N);

/* COMPUTE ZERO CROSSING RATE
 * Compute the ZCR of a signal using the mathematical definition.
 * @input x : vector, signal.
 * @input N : Size of the vector x.
 * @return The ZCR value.
*/
float compute_zcr(const float *x, unsigned int N, float fm);

#endif	/* PAV_ANALYSIS_H	*/



