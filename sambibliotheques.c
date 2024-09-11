#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition des limites maximales pour les livres et les emprunteurs
#define MAX_BOOKS 100
#define MAX_BORROWERS 100

// Structure pour stocker les informations sur un livre
typedef struct {
    int id;             // Identifiant du livre
    char title[100];    // Titre du livre
    char author[100];   // Auteur du livre
    int year;           // Année de publication
    int is_borrowed;    // Indique si le livre est emprunté (1) ou non (0)
} Book;

// Structure pour stocker les informations sur un emprunt
typedef struct {
    int book_id;        // Identifiant du livre emprunté
    int borrower_id;    // Identifiant de l'emprunteur
    char borrow_date[11]; // Date de l'emprunt (format YYYY-MM-DD)
    char return_date[11]; // Date prévue de retour (format YYYY-MM-DD)
} Borrow;

// Structure pour stocker les informations sur un emprunteur
typedef struct {
    int id;             // Identifiant de l'emprunteur
    char name[100];     // Nom de l'emprunteur
} Borrower;

// Déclaration des tableaux pour stocker les livres, les emprunteurs et les emprunts
Book books[MAX_BOOKS];
Borrower borrowers[MAX_BORROWERS];
Borrow borrows[MAX_BOOKS];
int book_count = 0;       // Compteur de livres
int borrower_count = 0;   // Compteur d'emprunteurs
int borrow_count = 0;     // Compteur d'emprunts

// Fonction pour charger les livres à partir du fichier
void load_books() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier des livres!\n");
        return;
    }
    book_count = 0;
    while (fscanf(file, "%d %s %s %d %d\n", &books[book_count].id, books[book_count].title, books[book_count].author, &books[book_count].year, &books[book_count].is_borrowed) != EOF) {
        book_count++;
    }
    fclose(file);
}

// Fonction pour enregistrer les livres dans le fichier
void save_books() {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier des livres!\n");
        return;
    }
    for (int i = 0; i < book_count; i++) {
        fprintf(file, "%d %s %s %d %d\n", books[i].id, books[i].title, books[i].author, books[i].year, books[i].is_borrowed);
    }
    fclose(file);
}

// Fonction pour charger les emprunteurs à partir du fichier
void load_borrowers() {
    FILE *file = fopen("borrowers.txt", "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier des emprunteurs!\n");
        return;
    }
    borrower_count = 0;
    while (fscanf(file, "%d %s\n", &borrowers[borrower_count].id, borrowers[borrower_count].name) != EOF) {
        borrower_count++;
    }
    fclose(file);
}

// Fonction pour enregistrer les emprunteurs dans le fichier
void save_borrowers() {
    FILE *file = fopen("borrowers.txt", "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier des emprunteurs!\n");
        return;
    }
    for (int i = 0; i < borrower_count; i++) {
        fprintf(file, "%d %s\n", borrowers[i].id, borrowers[i].name);
    }
    fclose(file);
}

// Fonction pour charger les emprunts à partir du fichier
void load_borrows() {
    FILE *file = fopen("borrows.txt", "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier des emprunts!\n");
        return;
    }
    borrow_count = 0;
    while (fscanf(file, "%d %d %s %s\n", &borrows[borrow_count].book_id, &borrows[borrow_count].borrower_id, borrows[borrow_count].borrow_date, borrows[borrow_count].return_date) != EOF) {
        borrow_count++;
    }
    fclose(file);
}

// Fonction pour enregistrer les emprunts dans le fichier
void save_borrows() {
    FILE *file = fopen("borrows.txt", "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier des emprunts!\n");
        return;
    }
    for (int i = 0; i < borrow_count; i++) {
        fprintf(file, "%d %d %s %s\n", borrows[i].book_id, borrows[i].borrower_id, borrows[i].borrow_date, borrows[i].return_date);
    }
    fclose(file);
}

// Fonction pour ajouter un nouveau livre
void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Limite de livres atteinte!\n");
        return;
    }
    books[book_count].id = book_count + 1;
    printf("Entrez le titre: ");
    scanf("%s", books[book_count].title);
    printf("Entrez l'auteur: ");
    scanf("%s", books[book_count].author);
    printf("Entrez l'annee: ");
    scanf("%d", &books[book_count].year);
    books[book_count].is_borrowed = 0;
    book_count++;
    save_books();
    printf("Livre ajoute avec succes!\n");
}

// Fonction pour rechercher des livres par titre ou auteur
void search_books() {
    char query[100];
    printf("Entrez le titre ou l'auteur a rechercher: ");
    scanf("%s", query);
    for (int i = 0; i < book_count; i++) {
        if (strstr(books[i].title, query) || strstr(books[i].author, query)) {
            printf("ID: %d, Titre: %s, Auteur: %s, Annee: %d, Emprunte: %s\n",
                   books[i].id, books[i].title, books[i].author, books[i].year,
                   books[i].is_borrowed ? "Oui" : "Non");
        }
    }
}

// Fonction pour afficher tous les livres disponibles
void display_books() {
    for (int i = 0; i < book_count; i++) {
        printf("ID: %d, Titre: %s, Auteur: %s, Annee: %d, Emprunte: %s\n",
               books[i].id, books[i].title, books[i].author, books[i].year,
               books[i].is_borrowed ? "Oui" : "Non");
    }
}

// Fonction pour ajouter un nouvel emprunteur
void add_borrower() {
    if (borrower_count >= MAX_BORROWERS) {
        printf("Limite d'emprunteurs atteinte!\n");
        return;
    }
    borrowers[borrower_count].id = borrower_count + 1;
    printf("Entrez le nom: ");
    scanf("%s", borrowers[borrower_count].name);
    borrower_count++;
    save_borrowers();
    printf("Emprunteur ajoute avec succes!\n");
}

// Fonction pour emprunter un livre
void borrow_book() {
    int book_id, borrower_id;
    if (borrow_count >= MAX_BOOKS) {
        printf("Limite d'emprunts atteinte!\n");
        return;
    }
    printf("Entrez l'ID du livre a emprunter: ");
    scanf("%d", &book_id);
    printf("Entrez l'ID de l'emprunteur: ");
    scanf("%d", &borrower_id);
    if (books[book_id - 1].is_borrowed) {
        printf("Le livre est dajà emprunte!\n");
        return;
    }
    borrows[borrow_count].book_id = book_id;
    borrows[borrow_count].borrower_id = borrower_id;
    printf("Entrez la date d'emprunt (YYYY-MM-DD): ");
    scanf("%s", borrows[borrow_count].borrow_date);
    printf("Entrez la date de retour prevue (YYYY-MM-DD): ");
    scanf("%s", borrows[borrow_count].return_date);
    books[book_id - 1].is_borrowed = 1;
    borrow_count++;
    save_books();
    save_borrows();
    printf("Livre emprunte avec succes!\n");
}

// Fonction pour retourner un livre
void return_book() {
    int book_id;
    printf("Entrez l'ID du livre a retourner: ");
    scanf("%d", &book_id);
    books[book_id - 1].is_borrowed = 0;
    save_books();
    printf("Livre retourne avec succes!\n");
}

// Fonction pour générer un rapport sur les livres empruntés
void generate_report() {
    printf("Livres actuellement empruntes:\n");
    for (int i = 0; i < borrow_count; i++) {
        if (books[borrows[i].book_id - 1].is_borrowed) {
            printf("ID du Livre: %d, ID de l'emprunteur: %d, Date d'emprunt: %s, Date de retour: %s\n",
                   borrows[i].book_id, borrows[i].borrower_id, borrows[i].borrow_date, borrows[i].return_date);
        }
    }
}

// Fonction pour supprimer un livre
void delete_book() {
    int book_id;
    printf("Entrez l'ID du livre a supprimer: ");
    scanf("%d", &book_id);
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == book_id) {
            // Supprimer le livre de la liste
            for (int j = i; j < book_count - 1; j++) {
                books[j] = books[j + 1];
            }
            book_count--;
            save_books();
            printf("Livre supprime avec succes!\n");
            return;
        }
    }
    printf("Livre non trouve!\n");
}

// Fonction pour archiver un livre
void archive_book() {
    int book_id;
    printf("Entrez l'ID du livre a archiver: ");
    scanf("%d", &book_id);
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == book_id) {
            // Créer un fichier pour l'archive
            char filename[100];
            sprintf(filename, "archive/%d_%s.txt", book_id, books[i].title);
            FILE *file = fopen(filename, "w");
            if (file == NULL) {
                printf("Erreur d'ouverture du fichier d'archive!\n");
                return;
            }
            fprintf(file, "Titre: %s\nAuteur: %s\nAnnee: %d\n", books[i].title, books[i].author, books[i].year);
            fclose(file);
            printf("Livre archive avec succes!\n");
            return;
        }
    }
    printf("Livre non trouve!\n");
}
// fonction pour faire la supression du livre
// 
// Fonction pour afficher le menu principal
void menu() {
    int choice;
    while (1) {
        printf("\nSysteme de Gestion de Bibliotheque\n");
        printf("1. Ajouter un livre\n");
        printf("2. Rechercher des livres\n");
        printf("3. Afficher tous les livres\n");
        printf("4. Ajouter un emprunteur\n");
        printf("5. Emprunter un livre\n");
        printf("6. Retourner un livre\n");
        printf("7. Generer un rapport\n");
        printf("8.  supprimer un livre\n");
        printf("9.  archiver un livre\n");
        printf("10. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                search_books();
                break;
            case 3:
                display_books();
                break;
            case 4:
                add_borrower();
                break;
            case 5:
                borrow_book();
                break;
            case 6:
                return_book();
                break;
            case 7:
                generate_report();
                break;
            case 8:
                delete_book();
            case 9:
                 delete_book();
                 break;
            case 10:
                exit(0);
            default:
                printf("Choix invalide!\n");
        }
    }
}
// Fonction principale
int main() {
    // Charger les données des fichiers
    load_books();
    load_borrowers();
    load_borrows();
    // Afficher le menu principal
    menu();
    
    return 0;
}


/*
une fonction pour faire la suppression et l'archivage de livre 
la disponibilites du livre 
*/