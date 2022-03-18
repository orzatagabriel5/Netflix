/* ORZATA Gabriel-Nicusor-313 */
#include "functii.h"


int main (int argc, char* argv[])
{
    // Am facut un vector pentru toate cele 4 categorii
    int i;
    TLG *liste;
    liste = (TLG*)malloc(4 * sizeof(TLG));
    TLG tendinte1 = NULL, documentare2 = NULL, tutoriale3 = NULL, top10 = NULL;
    void *watch_later5, *currently_watching6, *history7;
    // Am initializat fiecare coada/stiva
    watch_later5 = InitQ(sizeof(Serial), 500);
    currently_watching6 = InitS(sizeof(Serial), 500);
    history7 = InitS(sizeof(Serial), 500);
    // Am facut str[100] pentru a stoca fiecare linie din input
    // si **v pentru a stoca fiecare cuvant din linie.
    char str[100], *p, **v;
    v = malloc(100 * sizeof(char*));

    for(i = 0; i < 100; i++){
        v[i] = malloc(32 * sizeof(char));
    }

	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");

    while(fgets(str, 100, in)){
        i = 0;
        if(str[strlen(str) - 1] == '\n'){
			str[strlen(str) - 1] = 0;
		}
        p = strtok(str, " ");
        while(p != NULL){
            strcpy(v[i], p);
            p = strtok(NULL, " ");
			i++;
        }
        // Am folosit fgets ca sa copiez toata linia din input in str
        // si strtok ca sa pun fiecare cuvant in v.

        // In functie de comanda scrisa in input apelez functia specifica
        // pentru categoria specifica

        // --------ADD--------
        if(strcmp(v[0], "add") == 0){
            if(strcmp(v[1], "1") == 0){
                add(&tendinte1, v, out);
            } else if(strcmp(v[1], "2") == 0){
                add(&documentare2, v, out);
            } else if(strcmp(v[1], "3") == 0){
                add(&tutoriale3, v, out);
            }
        }
        
        // --------ADD_TOP--------
        if(strcmp(v[0], "add_top") == 0){
            add_top(&top10, v, out);
        }

        // Pentru adauagrea sezoanelor a trebuit sa fac functii separate
        // pentru cazul in care serilul se afla intr-o coada sau stiva.

         // --------ADD_SEZ--------
        if(strcmp(v[0], "add_sez") == 0){
            int aux = cauta_serial(v[1], liste, watch_later5, currently_watching6);
            // functia cauta serial intoarce indexul categoriei din care face parte
            // serialul cautat si in functie de acesta dau ca argument
            // lista, coada sau stiva aferenta.
            if(aux == 0){
                add_sez(&tendinte1, v, out);
            } else if (aux == 1){
                add_sez(&documentare2, v, out);
            }  else if (aux == 2){
                add_sez(&tutoriale3, v, out);
            }  else if (aux == 3){
                add_sez(&top10, v, out);
            }  else if (aux == 4){
                add_sez_coada(watch_later5, v, out);
            }  else if (aux == 5){
                add_sez_stiva(currently_watching6, v, out);
            }  else if (aux == 6){
                printf("Nu se pot adauga sezoane in history.\n");
            }
        }

        // Pentru cazul in care categoria care trebuie afisata este
        // stiva sau coada am facut functii specifice.
        // --------SHOW--------
        if(strcmp(v[0], "show") == 0){
            if(strcmp(v[1], "1") == 0){
                show(&tendinte1, afisare_categorie, 1, out);
            } else if(strcmp(v[1], "2") == 0){
                show(&documentare2, afisare_categorie, 2, out);
            } else if(strcmp(v[1], "3") == 0){
                show(&tutoriale3, afisare_categorie, 3, out);
            } else if(strcmp(v[1], "top10") == 0){
                show(&top10, afisare_categorie, 4, out);
            } else if(strcmp(v[1], "later") == 0){
                AfiQ(afisare_seriale, watch_later5, out);
            } else if(strcmp(v[1], "watching") == 0){
                AfiS(afisare_seriale_stiva, currently_watching6, out, 6);
            } else if(strcmp(v[1], "history") == 0){
                AfiS(afisare_seriale_stiva, history7, out, 7);
            }
        }

        // --------LATER--------
        if(strcmp(v[0], "later") == 0){
            int aux = cauta_serial(v[1], liste, watch_later5, currently_watching6);
            // Fucntia later poate se adreseaza doar serialelor
            // din cele 4 categorii, deci aux ia valori de la 0 la 3.
            if(aux == 0){
                later(v[1], &tendinte1, watch_later5, out);
            } else if (aux == 1){
                later(v[1], &documentare2, watch_later5, out);
            }  else if (aux == 2){
                later(v[1], &tutoriale3, watch_later5, out);
            }  else if (aux == 3){
                later(v[1], &top10, watch_later5, out);
            }
        }

        // --------WATCH--------
        if(strcmp(v[0], "watch") == 0){
            int aux = cauta_serial(v[1], liste, watch_later5, currently_watching6);
            
            if(aux == 0){
                watch(currently_watching6, history7, &tendinte1, v[1], atoi(v[2]), out);
            } else if (aux == 1){
                watch(currently_watching6, history7, &documentare2, v[1], atoi(v[2]), out);
            }  else if (aux == 2){
                watch(currently_watching6, history7, &tutoriale3, v[1], atoi(v[2]), out);
            }  else if (aux == 3){
                watch(currently_watching6, history7, &top10, v[1], atoi(v[2]), out);
            }  else if (aux == 4){
                watch1(currently_watching6, history7, watch_later5, v[1], atoi(v[2]), out);
            }  else if (aux == 5){
                watch2(currently_watching6, history7, v[1], atoi(v[2]), out);
            }
        }

        // Dupa fiecare comanda data actualizez vectorul de categorii.
        liste[0] = tendinte1;
        liste[1] = documentare2;
        liste[2] = tutoriale3;
        liste[3] = top10;
    }

    for(i = 0; i < 100; i++){
        free(v[i]);
    }
    free(v);

    fclose(in);
    fclose(out);
    
    return 0;
}
