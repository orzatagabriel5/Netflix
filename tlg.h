/* ORZATA Gabriel-Nicusor-313 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h> 
#include "TCoada-V.h"

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; /* tipurile Celula, Lista  */

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */
typedef void (*TFile)(void*, FILE*);
typedef void (*Test)(void**);

/* functii lista generica */
int InsLG(TLG* aL, void* ae);
int InsLGTop(TLG* aL, void* ae);

#endif
