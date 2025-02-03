#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_TITRE 100
#define TAILLE_NOM 50

typedef struct Livre {
    int id;
    char titre[TAILLE_TITRE];
    char auteur[TAILLE_NOM];
    int disponible;
    int idEtudiant;
    struct Livre* suivant;
} Livre;

typedef struct Etudiant {
    int id;
    char nom[TAILLE_NOM];
    char prenom[TAILLE_NOM];
    struct Etudiant* suivant;
} Etudiant;

Livre* bibliotheque = NULL;
Etudiant* listeEtudiants = NULL;
int compteurIdLivre = 1;
int compteurIdEtudiant = 1;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void attendreEntree() {
    printf("\nAppuyez sur Entree pour revenir au menu...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

Etudiant* trouverEtudiant(int id);
void afficherLivres();

void ajouterLivre() {
    Livre* nouveauLivre = (Livre*)malloc(sizeof(Livre));
    if (!nouveauLivre) {
        clearScreen();
        printf("Erreur d'allocation de memoire.\n");
        attendreEntree();
        return;
    }

    nouveauLivre->id = compteurIdLivre++;
    
    clearScreen();
    printf("Entrez le titre du livre : ");
    fgets(nouveauLivre->titre, TAILLE_TITRE, stdin);
    nouveauLivre->titre[strcspn(nouveauLivre->titre, "\n")] = 0;
    
    clearScreen();
    printf("Entrez le nom de l'auteur : ");
    fgets(nouveauLivre->auteur, TAILLE_NOM, stdin);
    nouveauLivre->auteur[strcspn(nouveauLivre->auteur, "\n")] = 0;
    
    nouveauLivre->disponible = 1;
    nouveauLivre->idEtudiant = 0;
    nouveauLivre->suivant = bibliotheque;
    bibliotheque = nouveauLivre;

    clearScreen();
    printf("Livre ajoute avec succes !\n");
    attendreEntree();
}

void afficherLivres() {
    clearScreen();
    if (!bibliotheque) {
        printf("Aucun livre dans la bibliotheque.\n");
    } else {
        printf("Liste des livres dans la bibliotheque :\n");
        Livre* courant = bibliotheque;
        while (courant) {
            printf("ID: %d, Titre: %s, Auteur: %s, Disponible: %s",
                   courant->id,
                   courant->titre,
                   courant->auteur,
                   courant->disponible ? "Oui" : "Non");
            if (!courant->disponible) {
                Etudiant* etudiant = trouverEtudiant(courant->idEtudiant);
                if (etudiant) {
                    printf(", Emprunte par : ID: %d, Nom: %s, Prenom: %s",
                           etudiant->id,
                           etudiant->nom,
                           etudiant->prenom);
                } else {
                    printf(", Emprunte par un etudiant inconnu (ID: %d)", courant->idEtudiant);
                }
            }
            printf("\n");
            courant = courant->suivant;
        }
    }
    attendreEntree();
}

Etudiant* trouverEtudiant(int id) {
    Etudiant* courant = listeEtudiants;
    while (courant) {
        if (courant->id == id) {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}

void emprunterLivre() {
    int idLivre, idEtudiant;
    clearScreen();
    printf("Entrez l'ID du livre a emprunter : ");
    scanf("%d", &idLivre);
    while (getchar() != '\n');

    Livre* courantLivre = bibliotheque;
    while (courantLivre) {
        if (courantLivre->id == idLivre) {
            if (!courantLivre->disponible) {
                clearScreen();
                printf("Ce livre est deja emprunte.\n");
                attendreEntree();
                return;
            }
            clearScreen();
            printf("Entrez l'ID de l'etudiant : ");
            scanf("%d", &idEtudiant);
            while (getchar() != '\n');

            if (!trouverEtudiant(idEtudiant)) {
                clearScreen();
                printf("Etudiant introuvable.\n");
                attendreEntree();
                return;
            }

            courantLivre->disponible = 0;
            courantLivre->idEtudiant = idEtudiant;
            clearScreen();
            printf("Vous avez emprunte le livre : %s\n", courantLivre->titre);
            attendreEntree();
            return;
        }
        courantLivre = courantLivre->suivant;
    }

    clearScreen();
    printf("ID de livre invalide.\n");
    attendreEntree();
}

void retournerLivre() {
    int id;
    clearScreen();
    printf("Entrez l'ID du livre a retourner : ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Livre* courant = bibliotheque;
    while (courant) {
        if (courant->id == id) {
            if (courant->disponible) {
                clearScreen();
                printf("Ce livre est deja disponible dans la bibliotheque.\n");
                attendreEntree();
                return;
            }
            courant->disponible = 1;
            courant->idEtudiant = 0;
            clearScreen();
            printf("Vous avez retourne le livre : %s\n", courant->titre);
            attendreEntree();
            return;
        }
        courant = courant->suivant;
    }

    clearScreen();
    printf("ID invalide.\n");
    attendreEntree();
}

void supprimerLivre() {
    int id;
    clearScreen();
    printf("Entrez l'ID du livre a supprimer : ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Livre* courant = bibliotheque;
    Livre* precedent = NULL;

    while (courant) {
        if (courant->id == id) {
            if (precedent) {
                precedent->suivant = courant->suivant;
            } else {
                bibliotheque = courant->suivant;
            }
            free(courant);
            clearScreen();
            printf("Le livre a ete supprime avec succes.\n");
            attendreEntree();
            return;
        }
        precedent = courant;
        courant = courant->suivant;
    }

    clearScreen();
    printf("ID invalide.\n");
    attendreEntree();
}

void ajouterEtudiant() {
    Etudiant* nouvelEtudiant = (Etudiant*)malloc(sizeof(Etudiant));
    if (!nouvelEtudiant) {
        clearScreen();
        printf("Erreur d'allocation de memoire.\n");
        attendreEntree();
        return;
    }

    nouvelEtudiant->id = compteurIdEtudiant++;
    
    clearScreen();
    printf("Entrez le nom de l'etudiant : ");
    fgets(nouvelEtudiant->nom, TAILLE_NOM, stdin);
    nouvelEtudiant->nom[strcspn(nouvelEtudiant->nom, "\n")] = 0;
    
    clearScreen();
    printf("Entrez le prenom de l'etudiant : ");
    fgets(nouvelEtudiant->prenom, TAILLE_NOM, stdin);
    nouvelEtudiant->prenom[strcspn(nouvelEtudiant->prenom, "\n")] = 0;
    
    nouvelEtudiant->suivant = listeEtudiants;
    listeEtudiants = nouvelEtudiant;

    clearScreen();
    printf("Etudiant ajoute avec succes !\n");
    attendreEntree();
}

void afficherEtudiants() {
    clearScreen();
    if (!listeEtudiants) {
        printf("Aucun etudiant enregistre.\n");
    } else {
        printf("Liste des etudiants :\n");
        Etudiant* courant = listeEtudiants;
        while (courant) {
            printf("ID: %d, Nom: %s, Prenom: %s\n",
                   courant->id,
                   courant->nom,
                   courant->prenom);
            courant = courant->suivant;
        }
    }
    attendreEntree();
}

void rechercherEtudiant() {
    char nom[TAILLE_NOM];
    char prenom[TAILLE_NOM];
    int trouve = 0;

    clearScreen();
    printf("Entrez le nom de l'etudiant : ");
    scanf("%s", nom);
    printf("Entrez le prenom de l'etudiant : ");
    scanf("%s", prenom);
    while (getchar() != '\n');

    Etudiant* courant = listeEtudiants;

    clearScreen();
    printf("=== Resultat de la recherche ===\n");
    while (courant) {
        if (strcmp(courant->nom, nom) == 0 && strcmp(courant->prenom, prenom) == 0) {
            printf("ID : %d, Nom : %s, Prenom : %s\n", courant->id, courant->nom, courant->prenom);
            trouve = 1;
        }
        courant = courant->suivant;
    }

    if (!trouve) {
        printf("Aucun etudiant trouve avec le nom '%s' et le prenom '%s'.\n", nom, prenom);
    }
    attendreEntree();
}

void afficherEtudiantParId() {
    int id;
    clearScreen();
    printf("Entrez l'ID de l'etudiant : ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Etudiant* etudiant = trouverEtudiant(id);

    clearScreen();
    if (etudiant) {
        printf("=== Resultat de la recherche ===\n");
        printf("ID : %d, Nom : %s, Prenom : %s\n", etudiant->id, etudiant->nom, etudiant->prenom);
    } else {
        printf("Aucun etudiant trouve avec l'ID %d.\n", id);
    }
    attendreEntree();
}

void supprimerEtudiant() {
    int id;
    clearScreen();
    printf("Entrez l'ID de l'etudiant a supprimer : ");
    scanf("%d", &id);
    while (getchar() != '\n');

    Livre* courantLivre = bibliotheque;
    while (courantLivre) {
        if (courantLivre->idEtudiant == id) {
            clearScreen();
            printf("Impossible de supprimer cet etudiant. Il a emprunte un ou plusieurs livres.\n");
            attendreEntree();
            return;
        }
        courantLivre = courantLivre->suivant;
    }

    Etudiant* courant = listeEtudiants;
    Etudiant* precedent = NULL;

    while (courant) {
        if (courant->id == id) {
            if (precedent) {
                precedent->suivant = courant->suivant;
            } else {
                listeEtudiants = courant->suivant;
            }
            free(courant);
            clearScreen();
            printf("L'etudiant a ete supprime avec succes.\n");
            attendreEntree();
            return;
        }
        precedent = courant;
        courant = courant->suivant;
    }

    clearScreen();
    printf("ID invalide.\n");
    attendreEntree();
}

void libererMemoire() {
    Livre* courantLivre = bibliotheque;
    while (courantLivre) {
        Livre* tempLivre = courantLivre;
        courantLivre = courantLivre->suivant;
        free(tempLivre);
    }

    Etudiant* courantEtudiant = listeEtudiants;
    while (courantEtudiant) {
        Etudiant* tempEtudiant = courantEtudiant;
        courantEtudiant = courantEtudiant->suivant;
        free(tempEtudiant);
    }
}

void menu() {
    printf("\n=== Menu Bibliotheque Virtuelle ===\n");
    printf("1. Ajouter un livre\n");
    printf("2. Afficher les livres\n");
    printf("3. Emprunter un livre\n");
    printf("4. Retourner un livre\n");
    printf("5. Supprimer un livre\n");
    printf("6. Ajouter un etudiant\n");
    printf("7. Afficher les etudiants\n");
    printf("8. Supprimer un etudiant\n");
    printf("9. Rechercher un etudiant par nom et prenom\n");
    printf("10. Rechercher un etudiant par ID\n");
    printf("0. Quitter\n");
    printf("===================================\n");
    printf("Entrez votre choix : ");
}

int main() {
    int choix;

    do {
        clearScreen();
        menu();

        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        clearScreen();
        switch (choix) {
            case 1:
                ajouterLivre();
                break;
            case 2:
                afficherLivres();
                break;
            case 3:
                emprunterLivre();
                break;
            case 4:
                retournerLivre();
                break;
            case 5:
                supprimerLivre();
                break;
            case 6:
                ajouterEtudiant();
                break;
            case 7:
                afficherEtudiants();
                break;
            case 8:
                supprimerEtudiant();
                break;
            case 9:
                rechercherEtudiant();
                break;
            case 10:
                afficherEtudiantParId();
                break;
            case 0:
                printf("\nAu revoir !\n");
                break;
            default:
                clearScreen();
                printf("Choix invalide. Veuillez reessayer.\n");
                attendreEntree();
        }
    } while (choix != 0);

    libererMemoire();
    return 0;
}