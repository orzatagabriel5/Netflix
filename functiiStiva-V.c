/* ORZATA Gabriel-Nicusor-313 */
#include "TStiva-V.h"
#include "functii.h"

/* creeaza stiva vida cu elemente de dimensiune d;
este necesar si un al doilea parametru = numar maxim elemente in coada */
void *InitS(size_t d,...)      
{ 
	ASt a = (ASt)malloc(sizeof (TStiva));
  	va_list ap;
  	if (!a){
		return NULL; 
	}
  	va_start(ap,d);
  	a->maxe = va_arg(ap,size_t);  
  	va_end(ap);

  	a->dime = d;

  	a->b = (char*)calloc(a->maxe, d);         
  	if (!a->b) 
	{ 
		free(a); 
		return NULL; 
	}     

  	a->vf = a->b;  
  	a->sv = a->b + d * a->maxe; 

  	return (void *)a;
}

// Fucntia de afisare a stivelor.
void AfiS(TF3 AfiElem, void *a, FILE* out, int ID)
{
	if(ID == 6){
		fprintf(out, "Categoria watching: [");
	} else if (ID == 7){
		fprintf(out, "Categoria history: [");
	}
	AfiElem(a, out);
	fprintf(out, "].\n");
}

int afisare_seriale_stiva(void *x, FILE* out)
{
	if(BS(x) == SVS(x)){
		return 0;
	}
	ASt *episod = (ASt*)x;
	char *p = BS(episod);
	int contor = 0;
	// Parcurg stiva de la varf si printez serialul in fisierul out.
	for(p = VF(x); (p -= DIMES(x)) >= BS(x); ){
		fprintf(out, "(%s, %.1f)", ((Serial*)p)->nume, ((Serial*)p)->rating);
		contor++;
		if(NrES(x) > contor){
			fprintf(out, ", ");
		}
	}
	return 1;
}

/* pune element in varful stivei */
int Push(void *a, void *ae)     
{ 
	if (PLINAS(a)) 
		return 0;
  	memcpy (VF(a), ae, DIMES(a));
  	VF(a) += DIMES(a);
  	return 1;
}

/* extrage elementul din varful stivei la adresa ae */
int Pop(void *a, void *ae)      
{ 
	if(VIDAS(a)) 
		return 0;
  	VF(a) -= DIMES(a);
  	memcpy(ae, VF(a), DIMES(a));
  	return 1;
}

/* test stiva vida */
int VidaS(void *a)               
{ 
	return VF(a) == BS(a); 
}

/* numarul de elemente din stiva */
size_t NrES(void *a)          
{ 
	return (VF(a) - BS(a)) / DIMES(a); 
}

/* dimensiunea elementelor din stiva */
size_t DimES(void *a)           
{ 
	return DIMES(a); 
}

/* elibereaza intregul spatiu ocupat de stiva */
void DistrS(void **aa)           
{ 
	free(BS(*aa));
	free(*aa);
  	*aa = NULL;         
}


/* prelucreaza de la Baza spre Varf */
size_t Prel_B_V(void *a, TF1 f)  
{ 
	size_t k = 0;
  	char *p;
  	for(p = BS(a); p < VF(a); p += DIMES(a)){
    	if(f(p)) 
		k++;
	}
  	return k;
}

/* prelucreaza de la Varf spre Baza */
size_t Prel_V_B(void *a, TF1 f)  
{ 
	size_t k = 0;
  	char *p;
  	for(p = VF(a); (p -= DIMES(a)) >= BS(a); )
    	if(f(p)) 
			k++;
  	return k;
}

/* suprapune inversul sursei destinatie */
int Rastoarna(void *ad, void *as)  
{ 
	size_t n = VF(as) - BS(as);
  	if(DIMDIFS(as,ad)) 
		return -1;      	/* dimensiuni diferite */
  	if(VIDAS(as)) 
		return 0;           /* sursa vida */
  	if(VF(ad) + n > SVS(ad)) 
		return -2;			/* nu exista spatiu pentru mutarea in destinatie */
  	/* cat timp mai exista elemente in sursa -> muta din varf sursa in varf destinatie */
 	 while(VF(as) > BS(as))
  	{ 
		VF(as) -= DIMES(as);  					/* actualizeaza varful stivei sursa */
    	memcpy(VF(ad), VF(as), DIMES(as)); 		/* muta elementul curent */
    	VF(ad) += DIMES(as);						/* actualizeaza varful stivei destinatie */
  	}
  	return 1;
}
