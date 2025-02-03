#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 9
#define MAX_REVIEWS 5
#define MAX_REVIEW_LENGTH 200
#define TAILLE_TITRE 100
#define TAILLE_NOM 50
#define TAILLE_DOMAINE 50

typedef struct Livre {
    int id;
    char titre[TAILLE_TITRE];
    char auteur[TAILLE_NOM];
    int disponible;
    int idEtudiant;
    int popularite;
    char domaine[TAILLE_DOMAINE];
    struct Livre* suivant;
} Livre;

typedef struct Etudiant {
    int id;
    char nom[TAILLE_NOM];
    char prenom[TAILLE_NOM];
    char domaine[TAILLE_DOMAINE];
    struct Etudiant* suivant;
} Etudiant;

typedef struct {
    char title[100];
    char reviews[MAX_REVIEWS][MAX_REVIEW_LENGTH];
    int reviewCount;
} Book;

Livre* bibliotheque = NULL;
Etudiant* listeEtudiants = NULL;
int compteurIdLivre = 1;
int compteurIdEtudiant = 1;

int findBook(Book books[], int size, const char *title) {
    for (int i = 0; i < size; i++) {
        if (strcasecmp(books[i].title, title) == 0) {
            return i;
        }
    }
    return -1;
}

void ajouterLivresPopulaires() {
    Livre* livre1 = (Livre*)malloc(sizeof(Livre));
    livre1->id = compteurIdLivre++;
    strcpy(livre1->titre, "Principes de biologie");
    strcpy(livre1->auteur, "Campbell & Reece");
    strcpy(livre1->domaine, "Biologie");
    livre1->disponible = 1;
    livre1->idEtudiant = 0;
    livre1->popularite = 10;
    livre1->suivant = bibliotheque;
    bibliotheque = livre1;

    Livre* livre2 = (Livre*)malloc(sizeof(Livre));
    livre2->id = compteurIdLivre++;
    strcpy(livre2->titre, "Une histoire du monde moderne");
    strcpy(livre2->auteur, "John Merriman");
    strcpy(livre2->domaine, "Histoire");
    livre2->disponible = 1;
    livre2->idEtudiant = 0;
    livre2->popularite = 9;
    livre2->suivant = bibliotheque;
    bibliotheque = livre2;

    Livre* livre3 = (Livre*)malloc(sizeof(Livre));
    livre3->id = compteurIdLivre++;
    strcpy(livre3->titre, "Introduction à l'algorithmique");
    strcpy(livre3->auteur, "Thomas H. Cormen");
    strcpy(livre3->domaine, "Informatique");
    livre3->disponible = 1;
    livre3->idEtudiant = 0;
    livre3->popularite = 8;
    livre3->suivant = bibliotheque;
    bibliotheque = livre3;
}

void afficherLivres() {
    if (!bibliotheque) {
        printf("\nAucun livre dans la bibliothèque.\n");
        return;
    }

    printf("\nListe des livres dans la bibliothèque :\n");
    Livre* courant = bibliotheque;
    while (courant) {
        printf("ID: %d, Titre: %s, Auteur: %s, Domaine: %s, Disponible: %s, Popularité: %d\n",
               courant->id,
               courant->titre,
               courant->auteur,
               courant->domaine,
               courant->disponible ? "Oui" : "Non",
               courant->popularite);
        courant = courant->suivant;
    }
}

void afficherLivresPopulaires(const char* domaine) {
    if (!bibliotheque) {
        printf("\nAucun livre dans la bibliothèque.\n");
        return;
    }

    printf("\nLivres populaires dans le domaine '%s' :\n", domaine);
    Livre* courant = bibliotheque;
    Livre* livrePopulaire[10];
    int i = 0;

    while (courant) {
        if (strcmp(courant->domaine, domaine) == 0) {
            livrePopulaire[i++] = courant;
        }
        courant = courant->suivant;
    }

    for (int j = 0; j < i - 1; ++j) {
        for (int k = 0; k < i - j - 1; ++k) {
            if (livrePopulaire[k]->popularite < livrePopulaire[k + 1]->popularite) {
                Livre* temp = livrePopulaire[k];
                livrePopulaire[k] = livrePopulaire[k + 1];
                livrePopulaire[k + 1] = temp;
            }
        }
    }

    for (int j = 0; j < i && j < 10; ++j) {
        printf("Titre: %s, Auteur: %s, Popularité: %d\n",
               livrePopulaire[j]->titre,
               livrePopulaire[j]->auteur,
               livrePopulaire[j]->popularite);
    }
}

void addReview(Book books[], int size) {
    char title[100];
    printf("Entrez le titre du livre : ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    int index = findBook(books, size, title);
    if (index == -1) {
        printf("❌ Livre non trouvé !\n");
        return;
    }

    if (books[index].reviewCount >= MAX_REVIEWS) {
        printf("❌ Ce livre a déjà trop d'avis.\n");
        return;
    }

    printf("Ajoutez votre avis : ");
    fgets(books[index].reviews[books[index].reviewCount], MAX_REVIEW_LENGTH, stdin);
    books[index].reviewCount++;

    printf("✅ Avis ajouté avec succès !\n");
}

void showReviews(Book books[], int size) {
    char title[100];
    printf("Entrez le titre du livre pour voir les avis : ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    int index = findBook(books, size, title);
    if (index == -1) {
        printf("❌ Livre non trouvé !\n");
        return;
    }

    printf("\n📚 Avis pour \"%s\":\n", books[index].title);
    if (books[index].reviewCount == 0) {
        printf("ℹ️ Aucun avis pour ce livre.\n");
    } else {
        for (int i = 0; i < books[index].reviewCount; i++) {
            printf("- %s", books[index].reviews[i]);
        }
    }
    printf("\n");
}

int main() {
    Book books[MAX_BOOKS] = {
        {"Principes de biologie", {}, 0},
        {"Une histoire du monde moderne", {}, 0},
        {"Introduction à l'algorithmique", {}, 0},
        {"Biologie moléculaire", {}, 0},
        {"L'Informatique pour les nuls", {}, 0},
        {"Les grandes civilisations antiques", {}, 0},
        {"La révolution scientifique", {}, 0},
        {"La guerre de Cent Ans", {}, 0},
        {"La biologie du cancer", {}, 0}
    };
    int bookCount = 9;

    ajouterLivresPopulaires();

    int choice;
    do {
        printf("\n1. Ajouter un avis\n2. Voir les avis\n3. Afficher les livres populaires\n4. Quitter\nChoix : ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addReview(books, bookCount);
                break;
            case 2:
                showReviews(books, bookCount);
                break;
            case 3: {
                char domaine[TAILLE_DOMAINE];
                printf("Entrez le domaine pour voir les livres populaires : ");
                fgets(domaine, sizeof(domaine), stdin);
                domaine[strcspn(domaine, "\n")] = 0;
                afficherLivresPopulaires(domaine);
                break;
            }
            case 4:
                printf("👋 Au revoir !\n");
                break;
            default:
                printf("❌ Choix invalide.\n");
        }
    } while (choice != 4);

    return 0;
}