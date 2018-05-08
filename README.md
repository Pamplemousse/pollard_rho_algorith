# TER : algorithme Rho de Pollard pour le logarithme discret

[Le sujet, sur le site du Master CSI.](https://mastercsi.labri.fr/wp-content/uploads/2018/01/TER18.pdf#16)


## Rapport

Le rapport se trouve dans le dossier `rapport` du répertoire.
Essayons de le séparer en plusieurs fichiers `.tex` (un par chapitre semble raisonnable) pour faciliter la lisibilité et la rédaction.

```bash
# générer le rapport, sa TOC, sa bibliographie
cd rapport/
pdflatex main.tex
bibtex main
pdflatex main.tex
pdflatex main.tex
```


## Code

#### en C

On utilise la librairie GMP ([documentation](https://gmplib.org/manual/index.html)) pour manipuler de grands entiers.
```bash
# compiler l'éxécutable
cd c; make

# les nombres en entrée sont passés via `input.txt`
./pollard input.txt

# tests automatisés du code
cd c/test; make
./test_*
```


#### tester

```bash
# compiler les tests unitaires
cd c/test; make

# tester la fonction d'itération
./test_iteration

# tester plusieurs valeurs générées avec Sage
./bash_unit test/test_pollard_program.sh
```


#### mesurer

Nous souhaitons mesurer le nombre d'appels à la fonction d'itération pour la résolution d'un logarithme discret.
Nous avons déjà des données calculatoires dans le fichier `c/test/fixtures/inputs.txt`. En lançant `pollard` sur ces données, on peut récupérer avec [`gprof`](https://sourceware.org/binutils/docs/gprof/) le nombre d'appels à `f`, puis représenter tout cela sur un graphique.

```bash
cd graph
./generate_data.sh
python graph.py
```


#### avec Sage

```bash
cd sage
```
