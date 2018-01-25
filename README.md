# TER : algorithme Rho de Pollard pour le logarithme discret

Le sujet, sur le site du Master CSI : [lien](https://mastercsi.labri.fr/wp-content/uploads/2018/01/TER18.pdf#16) .


## Rapport

Le rapport se trouve dans le dossier `rapport` du répertoire.
Essayons de le séparer en plusieurs fichiers `.tex` (un par chapitre semble raisonnable) pour faciliter la lisibilité et la rédaction.

```bash
# générer le rapport
pdflatex rapport/main.tex
```


## Aide

#### Git

```bash
# récupérer les commits du dépôt distant et mettre à jour la branche locale
git pull --rebase

# afficher le statut du dépôt local
git status

# ajouter ses changements à l'index
git add <nom de fichier>
# ou
git add -p

# sauvegarder les changements de l'index en local
git commit

# envoyer ses commits sur le dépôt distant
git push

# lire "l'historique" du projet (joliment)
git log --oneline --decorate --graph

# lire le contenu d'un commit
git show <numéro de commit>
```
