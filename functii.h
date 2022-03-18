/* ORZATA Gabriel-Nicusor-313 */
#include "TCoada-V.h"
#include "TStiva-V.h"
#include "tlg.h"

#define MAX_SERIALE = 2048;
#define MAX_SEZOANE = 10;
#define MAX_EPISOADE = 20;
#define MAX_DURATA_EPISOD = 120;
#define MAX_NUME_SERIAL = 32;

// typedef struct sezon
// {
//     AQV episoade;
// }Sezon;

typedef struct serial
{
    char* nume;
    float rating;
    int ID, nr_sezoane, top, durata;
    AQV sezoane, episoade;
}Serial;


void add(TLG* l, char **v, FILE* out);
void add_top(TLG* l, char **v, FILE* out);
void afisare_categorie(void* x, FILE* out);
void show(TLG* aL, TFile afiEL,  int ID, FILE* out);
int cauta_serial(char *nume, TLG *liste, void *watch_later, void* currently_watching);
void later(char* nume, TLG* l, void* later, FILE* out);
void add_sez(TLG* l, char **v, FILE* out);
void add_sez_stiva(void* currently_watching, char **v, FILE* out);
void add_sez_coada(void* watch_later, char **v, FILE* out);
void watch(void* currently_watching, void* history, TLG* l, char* nume, int durata, FILE* out);
void watch1(void* currently_watching, void* history, void* later, char* nume, int durata, FILE* out);
void watch2(void* currently_watching, void* history, char* nume, int durata, FILE* out);
