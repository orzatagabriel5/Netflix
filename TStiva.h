/* ORZATA Gabriel-Nicusor-313 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h> 

#ifndef _FUNCTII_
#define _FUNCTII_
  typedef int (* TF1)(void *,...);
  typedef int (* TF2)(const void *, const void *);
  typedef int (* TF3)(void *, FILE*);
#endif

#ifndef STIVA
#define STIVA

void* InitS(size_t d,...);    /* initializeaza stiva cu elem.de dimensiune d;*/
int Push(void* a, void* ae);  /* pune element in varful stivei */
int Pop (void* a, void* ae);  /* extrage elementul din varful stivei la adresa ae */
int Top (void* a, void* ae);  /* copiaza elementul din varful stivei la adresa ae */
int VidaS(void* a);           /* test stiva vida */
size_t NrES (void* a);        /* numarul de elemente din stiva */
size_t DimES(void* a);        /* dimensiunea elementelor din stiva */
void DistrS (void** aa);      /* elibereaza intregul spatiu ocupat de stiva */
size_t Prel_V_B(void* a, TF1 f); /* prelucreaza de la Varf spre Baza */
size_t Prel_B_V(void* a, TF1 f); /* prelucreaza de la Baza spre Varf */
int Rastoarna(void* ad, void* as); /* suprapune inversul sursei peste destinatie */
int afisare_seriale_stiva(void *x, FILE* out);
void AfiS(TF3 AfiElem, void *a, FILE* out, int ID);

#endif
