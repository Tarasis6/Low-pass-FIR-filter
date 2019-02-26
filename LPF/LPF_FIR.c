/* 
  Low pas equiripple FIR filter  with 128 coeffs
  F pass ~ 1000 Hz
  Fs = 48 kHz
*/

#include <stdio.h>
#include <stddef.h>

#define SIZE 240000
const int BL = 128;
const int B[128] = {
    -1442,    317,    292,    274,    261,    253,    248,    245,    243,
      241,    238,    234,    228,    220,    208,    194,    176,    156,
      131,    104,     73,     41,      4,    -31,    -68,   -107,   -144,
     -179,   -212,   -243,   -270,   -292,   -308,   -317,   -320,   -315,
     -302,   -281,   -251,   -213,   -165,   -109,    -45,     27,    106,
      192,    284,    379,    479,    580,    683,    786,    887,    986,
     1081,   1170,   1253,   1328,   1395,   1452,   1498,   1534,   1558,
     1570,   1570,   1558,   1534,   1498,   1452,   1395,   1328,   1253,
     1170,   1081,    986,    887,    786,    683,    580,    479,    379,
      284,    192,    106,     27,    -45,   -109,   -165,   -213,   -251,
     -281,   -302,   -315,   -320,   -317,   -308,   -292,   -270,   -243,
     -212,   -179,   -144,   -107,    -68,    -31,      4,     41,     73,
      104,    131,    156,    176,    194,    208,    220,    228,    234,
      238,    241,    243,    245,    248,    253,    261,    274,    292,
      317,  -1442
};


int load_wav_file(int sz);
int filter(short wav_samples[SIZE]);
int write_wav_file(short filt_samples[SIZE], short sz, short head[44]);


int main(){

  short sz; // size of file in bytes
  short head[44]; // 43 bytes of wav file header (from 0 byte to 43 byte)
  short wav_samples[SIZE];
  short filt_samples [SIZE];

  waw_samples[SIZE] = load_wav_file(sz);
  filter(wav_samples);
  write_wav_file(filt_samples,sz,head);

  return 0;
}



int load_wav_file(short sz){


 FILE *fp = fopen("tese.wav", "r");

 if(fp != NULL)
 {
  printf("ok\n"); // check if file is ok
 }

 fseek(fp, 0L, SEEK_END); // puts the pointer to the end of file, to know
 sz = ftell(fp); // tells the adress of last element(size of all file )

 fread(head, sizeof(char), 43, fp); // load header to the variable "head"


  fseek(fp, 44, SEEK_SET); // put the pointer to the 44 byte
  fread(wav_samples, sizeof(short), sz, fp); // load wav samples to "wav_samples" array
  fclose(fp);

  return waw_samples[SIZE];
}

int filter(short wav_samples[SIZE] ){

  int count = 0;
  short *p;
  int j = 0;
  int i = 0;
  p = &wav_samples[0];

 for(i=0;i<SIZE;i++)
 {
   *(p+count) = wav_samples[i];
  for (j=0; j<128;j++)
  {
   filt_samples[i] += wav_samples[(j+count)&0x7f] * B[j]; // filtering samples

  }
   count = (count+1)&0x7f; //  multiplicate with mask (0x7f = 127 (number of filter coeffs -1)) to reset counter

  // fprintf(f1, "%d\n", filt_samples[i]);
   printf("%d\n", filt_samples[i]);
 }


return 0;

}

int write_wav_file(short filt_samples[SIZE], short sz, short head[44]){

  FILE *f1  = fopen("tese_mod.wav", "w") ;

  fwrite(head, sizeof(short), 43, f1);
  fwrite(filt_samples, sizeof(short), sz, f1);
  fclose(f1);

  return 0;

}
