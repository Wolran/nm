
# Projet "nm"

## Description

Ce projet recrée la fonctionnalité de la commande `nm`, permettant d'afficher les symboles présents dans un fichier objet ou une bibliothèque. Cette réimplémentation fournit une vue détaillée des symboles en respectant les conventions du format ELF (Executable and Linkable Format).

## Fonctionnalités

- Affichage des symboles présents dans un fichier binaire (fichier objet ou bibliothèque partagée).
- Classement des symboles par adresse.
- Identification des types de symboles (global, local, etc.).
- Affichage des informations liées à chaque symbole : adresse, type et section.

## Utilisation

Pour utiliser cette réimplémentation de la commande `nm`, vous devez exécuter l'exécutable avec un fichier binaire comme argument :

```bash
./ft_nm <fichier_binaire>
```

