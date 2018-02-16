CRIPTAREA SI DECRIPTAREA MESAJELOR IN BAZA x

Pentru implementarea programului am creat trei stive cu numere, o lista cu numere si trei liste de cuvinte.
Pentru creare s-au folosit structurile: BAZA, MESAJ si CUVANT.

Lista cu numere contine defapt baza de numeratie cu elemente de la 0 pana la numarul bazei. Ex: pentru baza=0 lista este:0 1 2 3 4 5 6 7.
Aceasta lista este creata cu functia creare_baza() care va returna si numarul de cifre ale bazei.


Cele trei liste de cuvinte contin cuvintele citite din mesaj 1.txt, mesaj 2.txt si din baza.txt cu functia citire_fisier().
Ex: L1:nimic stele shaorma curea curent atipic candva negru;
    L2:candva curea stele;
    L3:negru atipic negru nimic;
Pentru a crea lista de cuvinte din baza dupa ce citesc numarul bazei, pastrez fisierul deschis pentru ca la urmatoarea citire sa pornesc 
de la primul cuvant din baza.
Aceste liste sunt create cu functia mesaj_text() care va returna si numarul total de cuvinte ale fiecarei liste.

Folosind functia mesaje() si apeland functia mesaj_text() am obtinut listele de cuvinte si numarul total de cuvinte din fiecare lista. 
Se parcurg listele de mesaje si se compara fiecare cuvant cu cele din baza pentru a adauga in stivele cu numere, element cu element
pozitia asociata cuvintelor din mesaje in baza. Ex: stiva mesaj 1:   6 3 1
                                                    stiva mesaj 2: 7 5 7 0 
Aceste stive sunt create tot in cadrul functiei mesaje() prin apelarea repetata a functiei creare_mesaj().
Am eliberat memoria pentru listele de cuvinte din mesaj 1 si mesaj 2 folosind functia elibere_lista() si am inchis fisierele, dar am pastrat 
lista de cuvinte a bazei ca la final sa fac o analogie intre rezultat si elementele din baza.

Functia citire_mesaj este realizata in asa fel incat nu este nevoie de functii suplimentare pentru a elibera definitv memoria alocata pentru 
stive.

In functia rezultat() se apeleaza toate functiile utile de mai sus si se obtin stivele cu mesaje, baza si lista de cuvinte din baza.
Cat timp exista elemente in una din stive execut algoritmul iar la final adaug in stiva rezultat valoarea pozitie transportului.
Daca valoarile din stivele mesaj, citite cu functie citire_mesaj(), nu se gasesc in baza deoarece au fost sterse cu functie stergere_baza(), 
se incrementeaza cu o unitatea aceste valori pana se gasesc in baza.
Transportul devine 1.
Se elimina restul impartirii lui(transport+mesaj 1+mesaj 2) la numarul total de elementele ale bazei cu functie stergere_baza() si se adauga 
in stiva rezultat cu functia creare_mesaj().

Dupa ce am obtinut stiva rezultat, apeland in main() functia creare_fisier() am facut o analogie intre elementele din stiva si lista de cuvinte
(elementele din baza), scriind in fisierul rezultat.txt cuvintele corespunzatoare pozitiei din baza gasite in sitva rezultat. La final eliberez 
memoria pentru lista cuvintelor din baza folosind functia eliberare_lista()

Informatii suplimentare legate de functii si modul de ultilizare vor aparea in cadrul codului.

