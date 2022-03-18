/* ORZATA Gabriel-Nicusor-313 */
#include "TCoada-V.h"
#include "functii.h"

void* InitQ(size_t d,...)
{ 
	AQV a = (AQV)malloc(sizeof(TCoadaV));
  	va_list ap;
  	if (!a){
		return NULL; 
	}
	va_start(ap,d);             
	a->maxe = va_arg(ap,size_t); 
	va_end(ap); 

 	a->dime = d;

  	a->v = (char*)calloc(a->maxe+1,d); 
  	if(!a->v) 
	{ 
		free(a); 
		printf("Eroare de alocare\n");
		return NULL; 
	}    

  	a->sv = a->v + (a->maxe+1) * d; 
  	a->ic = a->sc = a->v;

  	return (void*)a;
}

// Fucntia de afisare a cozii.
void AfiQ(TF3 AfiElem, void *a, FILE* out)
{
	fprintf(out, "Categoria later: [");
	AfiElem(a, out);
	fprintf(out, "].\n");
}

int afisare_seriale(void *x, FILE* out)
{
	if(IC(x) == SC(x)){
		return 0;
	}
	AQV *episod = (AQV*)x;
	char *p = IC(episod);
	int contor = 0;
	// Parcurg coada de la inceput si printez serialul in fisierul out.
	for(; p != SC(episod); Avans(episod,p)){
		fprintf(out, "(%s, %.1f)", ((Serial*)p)->nume, ((Serial*)p)->rating);
		contor++;
		if(NrEQ(x) > contor){
			fprintf(out, ", ");
		}
	}
	return 1;
}


/* adauga element la sfarsitul cozii */
int IntrQ(void *a, void *ae)   
{ 
	if(PLINAC(a)) 
		return 0;
  	memcpy(SC(a), ae, DIMEC(a));
  	Avans(a,SC(a));
  	return 1;
}

/* extrage primul element din coada la adresa ae */
int ExtrQ (void *a, void *ae)  
{ 
	if(VIDAC(a)) 
		return 0;
	memcpy(ae, IC(a), DIMEC(a));
  	Avans(a,IC(a));
  	return 1;
}

/* copiaza primul element din coada la adresa ae */
int PrimQ(void *a, void *ae)  
{ 
	if(VIDAC(a)) 
		return 0;
  	memcpy(ae, IC(a), DIMEC(a));
	return 1;
}

/* test coada vida */
int VidaQ(void *a)         
{ 
	return VIDAC(a); 
}

/* numarul de elemente din coada */
size_t NrEQ(void *a)       
{ 
	return Ocupat(a) / DIMEC(a); 
}

/* dimensiunea elementelor din coada */
size_t DimEQ(void *a)      
{ 
	return DIMEC(a); 
}

/* elibereaza intregul spatiu ocupat de coada */
void DistrQ(void **aa)     
{ 
	free(V(*aa));
	// printf("c\n");  	/* elibereaza spatiul ocupat de vector 			*/
  	free(*aa);	
	// printf("c\n");	/* elibereaza spatiul alocat pentru descriptor 	*/
  	*aa = NULL;
}


/* concatenare (muta toate elem.din sursa) */
int ConcatQ(void *ad, void *as) 
{ 
	if(DIMDIFC(as,ad)) 
		return -1;  		/* dimensiuni diferite */
  	if(VIDAC(as)) 
		return 0;        	/* sursa vida */
  	if(Liber(ad) < Ocupat(as)) 
		return -2; 			/* nu exista spatiu pt mutarea sursei */
  	for(; IC(as) != SC(as); Avans(ad,SC(ad)), Avans(as,IC(as)))
    	memcpy(SC(ad), IC(as), DIMEC(as));   /* muta element */
  	return 1;
}

