/* ORZATA Gabriel-Nicusor-313 */
#include "tlg.h"
#include "functii.h"

// Functia de inserare in liste.
int InsLG(TLG* aL, void* ae){
	TLG aux = malloc(sizeof(TCelulaG)), p, ant;
	int contor = 1;
	if(!aux){
	    return 0;
	}
	// Copiez informatia in noua "celula" cu informatia de tip serial.
	aux->info = ae;
	// Daca lista era vida pun celula la inceputul acesteia.
	if(*aL == NULL){
		aux->urm = *aL;
		*aL = aux;
	} else{
		for(p = *aL, ant = NULL; p != NULL; ant = p, p = p->urm){
			if(strcmp(((Serial*)p->info)->nume,((Serial*)ae)->nume) == 0){
				// Daca serialul se afla deja in lista ies din functie.
				return -1;
			}
			if(((Serial*)p->info)->rating < ((Serial*)ae)->rating){
				// In functie de rating-ul serialului la care
				// am ajuns cu iteratia introduc serialul nou.
				if(ant == NULL){
					// Daca se afla la inceputul listei refac vectorul catre
					// inceputul acesteia.
					aux->urm = *aL;
					*aL = aux;
				}else {
					aux->urm = p;
					ant->urm = aux;
				}
				// Dupa ce am introdus serialul ma opresc din a mai cauta.
				break;
			} else if (((Serial*)p->info)->rating == ((Serial*)ae)->rating){
				// Daca rating-urile sunt egale fac acelasi lucru,
				// dar in functie de nume.
				if(strcmp(((Serial*)p->info)->nume, ((Serial*)ae)->nume) > 0){
					if(ant == NULL){
					aux->urm = *aL;
					*aL = aux;
				}else {
					aux->urm = p;
					ant->urm = aux;
					}
				break;
				}
			}
			// De fiecare daca cand trec de un serial in lista
			// cresc contorul pentru a retine pozitia la care se afla.
			contor++;
			if(p->urm == NULL){
				// Daca ratingul este mai mic decat al tuturor serialelor
				// din lista il introduc la final.
				p->urm = aux;
				aux->urm = NULL;
				break;
			}
			
		}
	}
	// Returnez pozitia serialului in lista.
	return contor;
}


// Functia de adaugare in lista top10.
int InsLGTop(TLG* aL, void* ae){
	// Procedez la fel ca la InsLG.
	TLG aux = malloc(sizeof(TCelulaG)), p, ant;
	int flag = 0;
	if(!aux){
	    return 0;
	}
	aux->info = ae;
	if(*aL == NULL){
		aux->urm = *aL;
		*aL = aux;
	} else{
		for(p = *aL, ant = NULL; p != NULL; ant = p, p = p->urm){
			if(((Serial*)p->info)->top >= ((Serial*)ae)->top && flag == 0){
				flag = 1;
				if(ant == NULL){
					aux->urm = *aL;
					*aL = aux;
				}else {
					aux->urm = p;
					ant->urm = aux;
				}
			}
			if(flag == 1){
				// Dupa ce am adaugat un serial in top10
				// trebuie sa actualizez pozitia celorlale seriale in top.
				for(ant = aux; p != NULL; ant = p, p = p->urm){
					// Cat timp serialul nu se afla pe poztia 10
					// il pun cu o pozitie mai in spate, crescandu-i
					// variabila top.
					if(((Serial*)p->info)->top < 10){
						((Serial*)p->info)->top += 1;
					} else{
						// Daca serialul se afla pe pozitia 10 il scot din top.
						ant->urm = NULL;
					}
				}
				break;
			}

			if(p->urm == NULL && flag == 0){
				p->urm = aux;
				aux->urm = NULL;
				break;
			}
			
		}
	}
	return 1;
}