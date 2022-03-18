Tema2 - Netlfix

Pentru rezolvarea acestei teme am folosit mai multe functii specifice
listelor simplu inlantuite generice, a cozilor si stivelor.

Citirea argumentelor am facut-o folosind argc si argv[].

Citirea din fisierul de input am facut-o folosind un string in care am pus
linia corepunsatoare din fisier si un vector de string-uri in care am pus
fiecare cuvant din linie.

Toate cele 4 categorii sunt puse intr-un vector de liste pe care il actualizez
dupa fiecare linie citita din fisierul de input.
Functia add:
	La functia add aloc o celula de tip serial in care pun valori
	din vectorul in care am retinut toate cuvintele din linia
	din aferenta din fisierul de input. 
	Aloc memorie dinamic pentru numele serialului si initializez
	coada de sezoane care are ca elemente cozi de episoade. Cozile
	de episoade au ca elemente valori intregi care reprezinta durata
	unui episod , pe care o adun la o durata totala a serialului.
	Dupa ce am pus toate informatiile in structura serial o introduc
	in lista aferenta.

	Functia InsLG:
	Aloc memorie pentru un nou element de tip TCelulaG si pun in campul
	lui info structura de tip serial data ca argument.
	In functie de starea listei(vida sau nu) si de locul unde trebuie
	inserat noul element in functie de rating-ul serialului, inserez 
	noul element in lista. Daca parcurgand lista ajung la un serial care
	are rating-ul mai mic decat al serialului care trebuie adaugat il
	inserez inaintea lui, iar daca rating-urile au aceeasi valoare
	il inserez alfabetic dupa nume.
	Functia returneaza pozitia la care a fost inserat noul serial.
Functia add_top:
	Procedez la fel ca la functia add in ceea ce priveste alocarea unei
	noi celule serial si punerea informatiilor aferente in ea, insa aici
	folosesc o functie de inserare in lista specifica.
	Functia InsLGTop:
	Functia face acelasi lucru ca InsLG, dar dupa ce introduce noul serial
	le muta pe restul cu o pozitie mai in spate(modificand campul top al
	structurii serial), iar daca un serial se afla pe pozitia 10 si trebuie
	mutat mai in spate acesta este scos din lista.
Functia cauta_serial:
	Aceasta cauta in 3 structuri diferite: liste simplu inalntuite, stive
	si cozi.
	Pentru liste trec prin vectorul de liste dat ca parametru si prin
	listele din interiorul sau, cautand serialul dupa nume.
	Pentru cozi parcurg coada watch_later de la baza si la fiecare
	iteratie mut elementul din coada intr-o coada auxiliara pe care o
	concateneaza la finalul cautarii cu coada initiala.
	Dupa cautare coada initiala deviine vida, iar coada auxiliara devine
	coada watch_later in intregime.
	Pentru stive fac acelasi lucru ca pentru cozi, doar ca parcurg stiva
	de la varf la baza si pentru concatenare folosesc functia rastoarna
	ca sa aduc stiva la forma initiala(si nu cu elementele inversate).
	Functia returneaza index-ul aferent fiecare categorii si in functie
	de acesta imi pot da seama ce lista/coada/stiva sa dau ca paramentru
	functiilor care presupun modificarea acestora.
Functia later:
	Acesta este folosita excluziv pentru a scoate seriale din cele 4
	categorii si a le introduce in coada watch_later.
	Caut in lista aferenta data ca paramantru serialul, iar atunci cand il
	gasesc il introduc in coada si retin pozitia la care se afla.
	In functie de starea listei(vida sau nu) si pozitia de unde trebuie
	scos elementul fac modificarile si legaturile necesare, iar daca
	scot din lista de top10 procedez la fel ca la add_top si schimb
	pozitia serialelor in top.
Functia add_sez:
	Aceasta este special facuta pentru liste.
	Caut in lista data ca paramentru pozitia serialului si cresc numarul 
	de sezoane ale sale. In rest procedez ca la functia add obisnuita.
Functia add_sez_coada:
	Parcurg coada de la inceput si procedez ca la functia add_sez.
Functia add_sez_stiva:
	Parcurg stiva de la baza si procedez ca la functia add_sez.
Functia watch:
	Aceasta este facuta pentru cazul in care serialul se afla
	intr-o lista.
	Caut in lista data ca paramentru pozitia serialului,apoi scad din
	durata totala a acestuia timpul care va fi vizionat din el.
	Introduc serialul in varful stivei currently_watching, apoi il scot
	la fel ca la functia later. 
	Daca serialul este vizionat complet il scot din lista si il introduc
	in history.
Functia watch1:
	Aceasta a fost facuta pentru cazul in care serialul se afla in coada
	watch_later.
	Parcurg coada de la inceput si procedez ca la functia watch pentru
	liste. Scot fiecare element din stiva si il pun in stiva auxiliara.
	Daca gasesc serialul ii modic durata si il pun inapoi in stiva.
	Atunci cand gasesc serialul sar peste operatia de introducere pentru
	a-l scoate din coada watch_later.
	Daca serialul este vizionat complet il scot din watch_later si il
	introduc in history.
	La final coada auxiliara o sa devina watch_later, dar fara serialul
	pe care l-am gasit si o concatenez inapoi in watch_later.
Functia watch2:
	La fel ca la watch1 parcurg stiva de la varf la baza, iar daca gasesc
	serialul ii actualizez durata, iar atunci cand este vizonat complet
	il scot din stiva currently_watching si il introduc in history.
	In cazul in care serialul vizionat era ultimul din currently_watching
	sau a fost vizionat complet rastorn aux peste stiva si eliberez
	memoria.
	In cazul in care serialul nu este vizionat completil scot din
	currently_watching si il pun dupa ce rastorn aux peste stiva pentru
	a ramane in varful stivei.
Functia show:
	In fucntie de ID-ul categoriei printez antetul aferent.
	Pentru fiecare element din lista apelez functia specifica de afisare
	cu parantezele si virgulele puse corepsunzator.
Functia AfiQ/AfiS:
	Functioneza pe acelasi principiu ca si show, doar ca parcurgerea se 
	face pentru coada/stiva.

