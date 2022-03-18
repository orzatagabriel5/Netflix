/* ORZATA Gabriel-Nicusor-313 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef _FUNCTII_ 
#define _FUNCTII_
  typedef int (*TF1)(void *);
  typedef int (*TF3)(void *, FILE*);
  typedef int (*TF2)(const void *, const void *);
#endif

#ifndef COADA
#define COADA

void* InitQ(size_t d,...); /* creeaza coada vida cu elemente de dimensiune d;
							               anumite implementari pot necesita si alti parametri */
void AfiQ(TF3 AfiElem, void *a, FILE* out);
int afisare_int(void *x);
int afisare_seriale(void *x, FILE* out);
int IntrQ(void* a, void* ae); /* adauga element la sfarsitul cozii */
int ExtrQ(void* a, void* ae); /* extrage primul element din coada la adresa ae */
int VidaQ(void* a);           /* test coada vida */
size_t NrEQ(void* a);         /* numarul de elemente din coada */
size_t DimEQ(void* a);        /* dimensiunea elementelor din coada */
int ConcatQ(void *ad, void *as);	/* concatenare (muta toate elem.din sursa) */
void DistrQ(void **aa);
#endif
