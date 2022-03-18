/* ORZATA Gabriel-Nicusor-313 */
#include "TStiva.h"

#ifndef _STIVA_VECTOR_
#define _STIVA_VECTOR_
 
typedef struct
{ 
	size_t 	dime; 		/* dimensiunea unui element al stivei 			*/
	size_t 	maxe; 		/* numarul maxim de elemente in stiva 			*/
	char 	*b;			/* adresa de inceput a vectorului / baza stivei */
	char 	*sv; 		/* adresa de sfarsit a vectorului				*/
	char 	*vf; 		/* varful stivei 								*/
} TStiva, *ASt;

/*- macrodefinitii - acces campuri */
#define DIMES(a) (((ASt)(a))->dime)
#define BS(a) 	(((ASt)(a))->b)
#define SVS(a) 	(((ASt)(a))->sv)
#define VF(a) 	(((ASt)(a))->vf)


#define DIMDIFS(s,d)	(DIMES(s) != DIMES(d))
/* verifica daca o stiva este vida */
#define VIDAS(a)  	(VF(a) == BS(a))
/* verifica daca stiva este plina */
#define PLINAS(a) 	(VF(a) == SVS(a))

#define AvansS(a,p) 		((p) = ((p) += DIMES(a)) < SVS(a) ? (p) : BS(a))	

#endif
