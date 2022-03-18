/* ORZATA Gabriel-Nicusor-313 */
#include "functii.h"


// functia de afisare specifica structurii serial
void afisare_categorie(void* x, FILE* out)
{
	Serial *serial = (Serial*)x;
    fprintf(out, "(%s, %.1f)", serial->nume, serial->rating);
}

// Functia de afisare a listelor
void show(TLG* aL, TFile afiEL, int ID, FILE* out)
{
    // In fucntie de ID-ul categoriei printez antetul aferent
    if(ID == 4){
        fprintf(out, "Categoria top10: [");
    } else if(ID == 8){
        fprintf(out, "Categoria later: [");
    } else {
        fprintf(out, "Categoria %d: [", ID);
    }
    // Pentru fiecare element din lista apelez functia specifica de afisare
    if(*aL != NULL) {
        for(; *aL; aL = &(*aL)->urm) {
            afiEL((*aL)->info, out);
            if((*aL)->urm != NULL){
                fprintf(out, ", ");
            }
        }
    }
    fprintf(out, "].\n");
}

// Fucntia de adaugare.
void add(TLG* l, char **v, FILE* out)
{
    // Aloc memorie pentru o "celula" serial si apoi pentru numele serialului.
    Serial *serial = malloc(sizeof(Serial));
    int i, j, nr_episoade, contor = 5, time;
    serial->durata = 0;
    serial->nume = (char*)malloc(32 * sizeof(char));
    // Trec printre cuvintele din v si pun informatiile
    // corespunzatoare in structura serial.
    serial->ID = atoi(*(v+1));
    strcpy(serial->nume, *(v+2));
    serial->rating = atof(*(v+3));
    serial->nr_sezoane = atoi(*(v+4));
    // Initializez coada de cozi(sezon -> episoade).
    void* sez = InitQ(sizeof(TCoadaV), 10);
    serial->sezoane = sez;
    for(i = 0; i < serial->nr_sezoane; i++){
        // Folosesc contor ca sa iau informatiile din v
        //de unde am ramas ulterior.
        nr_episoade = atoi(*(v+contor));
        contor++;
        void *episoade;
        // Initializez coada de episoade.
        episoade = InitQ(sizeof(int), 20);
        if(episoade == NULL){
            printf("Eroare alocare\n");
        }
        for(j = 0; j < nr_episoade; j++){
            serial->durata += atoi(*(v+contor));
            // Adun la durata fiecare valoare a unui episod(durata lui).
            time = atoi(*(v+contor));
            // Introduc in lista de episoade timpul episoadelor.
            IntrQ(episoade, (void*)&time);
            // Cresc contorul pentru a merge mai departe in v.
            contor++;
        }
        // La final pun coada de episoade in coada de sezoane.
        IntrQ(sez, episoade);
    }
    // Inserez serialul in categoria sa.
    int pozitie = InsLG(l, (void*)serial);
    if(pozitie != -1){
        fprintf(out, "Serialul %s a fost adaugat la pozitia %d.\n", serial->nume, pozitie);
    }
}

// Functia de adaugare in Top10.
void add_top(TLG* l, char **v, FILE* out)
{
    Serial *serial = malloc(sizeof(Serial));
    int i, j, nr_episoade, contor = 5, time;
    serial->ID = 4;
    serial->durata = 0;
    serial->nume = (char*)malloc(32 * sizeof(char));
    serial->top = atoi(*(v+1));
    strcpy(serial->nume, *(v+2));
    serial->rating = atof(*(v+3));
    serial->nr_sezoane = atoi(*(v+4));
    void* sez = InitQ(sizeof(TCoadaV), 10);
    serial->sezoane = sez;
    for(i = 0; i < serial->nr_sezoane; i++){
        nr_episoade = atoi(*(v+contor));
        contor++;
        void *episoade;
        episoade = InitQ(sizeof(int), 20);
        if(episoade == NULL){
            printf("Nu a mers\n");
        }
        for(j = 0; j < nr_episoade; j++){
            serial->durata += atoi(*(v+contor));
            time = atoi(*(v+contor));
            IntrQ(episoade, (void*)&time);
            contor++;
        }
        IntrQ(sez, episoade);
    }
    // Pun informatiile in structura serial la fel ca la add
    // si inserez in Top10 cu o functie speciala.
    InsLGTop(l, (void*)serial);
    show(l, afisare_categorie, 4, out);
}

// Funcite de cautare a unui serial.
int cauta_serial(char* nume, TLG* liste, void* watch_later, void* currently_watching)
{
    TLG p;
    Serial *serial;
    int i, flag;

    // Caut in cele 4 categorii.
    for(i = 0; i < 4; i++){
        if(liste[i] != NULL){
            for(p = liste[i]; p != NULL; p = p->urm){
                serial = (Serial*)p->info;
                if(strcmp(serial->nume, nume) == 0){
                    // returnez indexul specific categoriei.
                    return i;
                }
            }
        }
    }

    // Caut in coada watch_later.
    AQV *coada = (AQV*)watch_later;
    void *aux, *el;
	el = malloc(DimEQ(coada));
	aux = InitQ(DimEQ(coada), 150);
	if(!aux){
		return 1;
	}
	char *q = IC(coada);
    // Trec prin coada incepand de la baza sa si mut fiecare element din ea
    // intr-o coada auxiliara si gasesc serialul cautat setez un flag.
    for(; q != SC(coada); Avans(coada,q)){
		ExtrQ(coada, el);
        if(strcmp(((Serial*)q)->nume, nume) == 0){
            flag = 4;
	    }
        IntrQ(aux, el);
    }
    // Dupa ce am trecut toate elemntele in coada auxiliara
    // o pun in watch_later si eliberez memoria sa.
	ConcatQ(coada, aux);
	DistrQ(&aux);
	free(el);

    // Caut in stiva currently_watching.
    ASt *stiva = (ASt*)currently_watching;
    void *aux1, *el1;
	el1 = malloc(DimES(stiva));
	aux1 = InitS(DimES(stiva), 150);
	if(!aux1){
		return 1;
	}
    char* qs = BS(stiva);
    // La fel ca la coada trec prin toata stiva apoi rastorn stiva auxiliara
    // in cea initiala pentru a ramane ca la inceput.
    for(qs = VF(stiva); (qs -= DIMES(stiva)) >= BS(stiva); ){
        Pop(stiva, el1);
        if(strcmp(((Serial*)qs)->nume, nume) == 0){
            flag = 5;
	    }
        Push(aux1, el1);
    }
    Rastoarna(stiva, aux1);
	DistrS(&aux1);
	free(el1);

    // In fuctie de flag returnez un index specific.
    if(flag == 4){
        return 4;
    } else if(flag == 5){
        return 5;
    }
    return -1;
}

// Funcctia later.
void later(char* nume, TLG* l, void* watch_later, FILE* out)
{
    TLG p, ant;
    int pozitie;
    for(p = *l, ant = NULL; p != NULL; ant = p, p = p->urm){
        Serial* serial = (Serial*)p->info;
        // Creez o strucutra serial pentru a lucra mai usor.
        if(strcmp(serial->nume, nume) == 0){
            if(ant == NULL){
                if(p->urm != NULL){
                    // Daca serialul era primul in lista sa
                    // modific inceputul listei.
                    p = (*l)->urm;
                    *l = p;
                } else {
                    // Daca lista are un singur element modific pointerul
                    // catre inceputul listei.
                    *l = NULL;
                }
                // Introduc serialul in coada watch_later
                // si retin pozitia la care se afla.
                IntrQ(watch_later, (void*)serial);
                pozitie = NrEQ(watch_later);
            }else {
                // Daca serialul se afla la mijlocul listei sau la final,
                // exculzand momentul in care este singur in lista,
                // refac legaturile in felul urmator.
                ant->urm = p->urm;
                IntrQ(watch_later, (void*)serial);
                pozitie = NrEQ(watch_later);
            }

            // Daca lista din care face parte serialul este Top10
            // Dupa ce scot un serial din ea actualizez pozitia celorlalte
            // in top.
            if(((Serial*)p->info)->ID == 4){
                for(; p != NULL; ant = p, p = p->urm){
                    if(((Serial*)p->info)->top <= 10){
                        ((Serial*)p->info)->top -= 1;
                    }
                }
            }
            fprintf(out, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", serial->nume, pozitie);
            // Cand il gasesc ma opresc din a mai cauta in lista.
            break;
        }
    }
}

// Fucntia add_sez pentru liste.
void add_sez(TLG* l, char **v, FILE* out)
{
    TLG p;
    int ep, i, contor = 3, time;
    for(p = *l; p !=NULL; p = p->urm){
        Serial* serial = (Serial*)p->info;
        if(strcmp(v[1], serial->nume) == 0){
            // Caut in lista data ca paramentru pozitia serialului
            // si cresc numarul de sezoane ale sale.
            // In rest procedez ca la functia add obisnuita.
            serial->nr_sezoane += 1;
            ep = atoi(v[2]);
            void *episoade;
            episoade = InitQ(sizeof(int), 20);
            for(i = 0; i < ep; i++){
                serial->durata += atoi(*(v+contor));
                time = atoi(v[contor + i]);
                IntrQ(episoade, (void*)&time);
                contor++;
            }
            IntrQ(serial->sezoane, episoade);
            fprintf(out, "Serialul %s are un sezon nou.\n", serial->nume);
            break;
        }
    }
}

// Functia add_sez pentru coada.
void add_sez_coada(void* watch_later, char **v, FILE* out)
{
    AQV *coada = (AQV*)watch_later;
    char *p;
    int ep, i, contor = 3, time;
    // Parcurg coada de la inceput si procedez ca la functia add_sez
    // pentru liste.
    for(p = IC(coada); p != SC(coada); Avans(coada,p)){
        Serial* serial = (Serial*)p;
        if(strcmp(v[1], serial->nume) == 0){
            serial->nr_sezoane += 1;
            ep = atoi(v[2]);
            void *episoade;
            episoade = InitQ(sizeof(int), 20);
            for(i = 0; i < ep; i++){
                serial->durata += atoi(*(v+contor));
                time = atoi(v[contor + i]);
                IntrQ(episoade, (void*)&time);
                contor++;
            }
            IntrQ(serial->sezoane, episoade);
            fprintf(out, "Serialul %s are un sezon nou.\n", serial->nume);
            break;
        }
    }
}

// Functia add_sez pentru stiva.
void add_sez_stiva(void* currently_watching, char **v, FILE* out)
{
    AQV *stiva = (AQV*)currently_watching;
    char *p;
    int ep, i, contor = 3, time;
    // Parcurg stiva de la baza si procedez la fel ca la functia add_sez
    // pentru liste.
    for(p = BS(stiva); p != SVS(stiva); AvansS(stiva,p)){
        Serial* serial = (Serial*)p;
        if(strcmp(v[1], serial->nume) == 0){
            serial->nr_sezoane += 1;
            ep = atoi(v[2]);
            void *episoade;
            episoade = InitQ(sizeof(int), 20);
            for(i = 0; i < ep; i++){
                serial->durata += atoi(*(v+contor));
                time = atoi(v[contor + i]);
                IntrQ(episoade, (void*)&time);
                contor++;
            }
            IntrQ(serial->sezoane, episoade);
            fprintf(out, "Serialul %s are un sezon nou.\n", serial->nume);
            break;
        }
    }
}

// Functia watch.
void watch(void* currently_watching, void* history, TLG* l, char* nume, int durata, FILE* out)
{
    TLG p, ant;
    // Pentru cazul in care seriaul se afla intr-o lista.
    for(p = *l, ant = NULL; p != NULL; ant = p, p = p->urm){
        Serial *serial = (Serial*)p->info;
        if(strcmp(nume, serial->nume) == 0){
            // Caut in lista data ca paramentru pozitia serialului.
            // apoi scad din durata totala a acestuia timpul care
            // va fi vizionat din el.
            serial->durata -= durata;
            // Introduc serialul in varful stivei currently_watching.
            // apoi il scot la fel ca la functia later. 
            Push(currently_watching, (void*)serial);
            if(ant == NULL){
                    if(p->urm != NULL){
                        p = (*l)->urm;
                        *l = p;
                    } else {
                        *l = NULL;
                    }
                }else {
                    ant->urm = p->urm;
                }
                if(((Serial*)p->info)->ID == 4){
                    for(; p != NULL; ant = p, p = p->urm){
                        if(((Serial*)p->info)->top <= 10){
                            ((Serial*)p->info)->top -= 1;
                        }
                    }
                }
                // Daca serialul este vizionat complet il scot
                // din currently_watching si il introduc in history.
            if(serial->durata <= 0){
                fprintf(out, "Serialul %s a fost vizionat integral.\n", nume);
                Pop(currently_watching, (void*)serial);
                Push(history, (void*)serial);
            }
            // Dupa ce am gasit serialul ma opresc din a mai cauta in lista.
            break;
        }
    }
}

// Functia watch pentru coada watch_later.
void watch1(void* currently_watching, void* history, void* watch_later, char* nume, int durata, FILE* out)
{
    AQV *episod = (AQV*)watch_later;
	char *p = IC(episod);
    int flag = 0;
    void *aux;
	void* el;
	el = malloc(DimEQ(watch_later));
	aux = InitQ(DimEQ(watch_later), 150);
	if(!aux){
		return;
	}
    // Parcurg coada de la inceput si procedez ca la
    // functia watch pentru liste.
	for(; p != SC(episod); Avans(episod,p)){
        Serial *serial = (Serial*)(p);
        ExtrQ(watch_later, el);
        // Scot fiecare element din stiva si il pun in stiva auxiliara.
        if(strcmp(nume, serial->nume) == 0){
            // Daca gasesc serialul ii modic durata si il pun inapoi in stiva.
            flag = 1;
            serial->durata -= durata;
            Push(currently_watching, (void*)serial);
            if(serial->durata <= 0){
                fprintf(out, "Serialul %s a fost vizionat integral.\n", nume);
                Pop(currently_watching, (void*)serial);
                Push(history, (void*)serial);
            } 
        }
        // Daca serialul a fost gasit sar peste operatia de adaugare
        // in aux pentru a il scoate din coada watch_later.
        if(flag == 1){
            flag = 0;
        } else {

            IntrQ(aux, el);
        }
    }
    // Pun aux in coada watch_later care a ajuns vida in urma for-ului.
    ConcatQ(watch_later, aux);
    DistrQ(&aux);
    free(el);
}

// Functia watch pentru cazul in care serialul este deja in currently_watching.
void watch2(void* currently_watching, void* history, char* nume, int durata, FILE* out)
{
    ASt *episod = (ASt*)currently_watching;
	char *p = BS(episod);
    void *aux;
	void* el;
    int flag = 0;
	el = malloc(DimES(currently_watching));
	aux = InitS(DimES(currently_watching), 150);
	if(!aux){
		return;
	}
    // Parcurg stiva de la varf la baza.
    for(p = VF(episod); (p -= DIMES(episod)) >= BS(episod); ){
        Serial *serial = (Serial*)p;
        Pop(currently_watching, el);
        // Scot fiecare serial din ea.
        if(strcmp(nume, serial->nume) == 0){
            serial->durata -= durata;
            // Daca gasesc serialul ii modific durata si il pun inapoi
            // in stiva.
            Push(currently_watching, (void*)serial);
            if(serial->durata <= 0){
                // Daca serialul a fost vizionat complet il scot din
                // currently_watching si il introduc in history.
                fprintf(out, "Serialul %s a fost vizionat integral.\n", nume);
                Pop(currently_watching, (void*)serial);
                Push(history, (void*)serial);
                flag = 1;
            }
            // Daca am gasit serialul ma opresc si nu il mai adaug in aux.
            break;
        }
        Push(aux, el);
    }
    if(NrES(currently_watching) == 0 || flag == 1){
        // In cazul in care serialul vizionat era ultimul
        // din currently_watching sau a fost vizionat complet
        // rastorn aux peste stiva si eliberez memoria.
        Rastoarna(currently_watching, aux);
        DistrS(&aux);
        free(el);
    } else {
        // In cazul in care serialul nu este vizionat complet
        // il scot din currently_watching si il pun dupa ce
        // rastorn aux peste stiva pentru a ramane in
        // varful stivei.
        Pop(currently_watching, el);
        Rastoarna(currently_watching, aux);
        Push(currently_watching, el);
        DistrS(&aux);
        free(el);
    }
}