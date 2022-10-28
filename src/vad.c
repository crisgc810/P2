#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "vad.h"
#include "pav_analysis.h"

const float FRAME_TIME = 10.0F; /* in ms. */

/* 
 * As the output state is only ST_VOICE, ST_SILENCE, or ST_UNDEF,
 * only this labels are needed. You need to add all labels, in case
 * you want to print the internal state in string format
 */

const char *state_str[] = {
  "UNDEF", "S", "V", "INIT", "MV", "MS"
};

const char *state2str(VAD_STATE st) {
  return state_str[st];
}

/* Define a datatype with interesting features */
typedef struct {
  float zcr;
  float p;
  float am;
} Features;

/* Compute signal x features. Used only in this file*/
Features compute_features(const float *x, int N) {
  Features feat;
  feat.p = compute_power(x,N);
  feat.zcr = compute_zcr(x,N,16000);
  feat.am = compute_am(x,N);
  return feat;
}

VAD_DATA * vad_open(float rate, float alfa1, float alfa2,) {
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA));
  vad_data->state = ST_INIT;
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
  vad_data->alfa1=alfa1;
  vad_data->alfa2=alfa2;
  vad_data->contador=0;
  vad_data->VCn=VCn;
  vad_data->VCm=VCm;
  return vad_data;
}

VAD_STATE vad_close(VAD_DATA *vad_data) {
  /* 
   * TODO: decide what to do with the last undecided frames
   */
  VAD_STATE state = vad_data->state;

  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data) {
  return vad_data->frame_length;
}


/* 
 * TODO: Implement the Voice Activity Detection 
 * using a Finite State Automata
 */
VAD_STATE vad(VAD_DATA *vad_data, float *x) {

  /* 
   * TODO: You can change this, using your own features,
   * program finite state automaton, define conditions, etc.
   */

  Features f = compute_features(x, vad_data->frame_length);
  vad_data->last_feature = f.p; /* save feature, in case you want to show */

  switch (vad_data->state) {
  case ST_INIT:
    vad_data->state = ST_SILENCE;
    break;

  case ST_SILENCE:
    if (f.p > 0.95)
      vad_data->state = ST_VOICE;
    break;

  case ST_VOICE:
    if (f.p < 0.01)
      vad_data->state = ST_SILENCE;
    break;

  case ST_UNDEF:
    break;
  }
  if (vad_data->state == ST_SILENCE ||
      vad_data->state == ST_VOICE)
    return vad_data->state;
  else
    return ST_UNDEF;
}

void vad_show_state(const VAD_DATA *vad_data, FILE *out) {
  fprintf(out, "%d\t%f\n", vad_data->state, vad_data->last_feature);
}
