#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct  {
    char nom[50];
    char prenom[50];
    char mp[50];
    int role ;
} compte;

typedef struct {
    char nom[50];
    char prenom[50];
    int age ;
    char adress[50];
    int niveauetude;
    char sexe[50];
} Candidat;

typedef struct {
    char nomU[50];
    char prenomU[50];
    char nomE[50];
    char nomCandidat[50];
    char prenomCandidat[50];
} Vote;

int verifierCompteAdmin(char nom[], char prenom[]) {
    FILE *fichierComptes = fopen("comptes.txt", "r");
    if (fichierComptes == NULL) {
        printf("Erreur lors de l'ouverture du fichier des comptes.\n");
        return 0; 
    }
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichierComptes) != NULL) {
        char nomFichier[50], prenomFichier[50], motDePasse[50];
        int role;
        sscanf(ligne, "%s %s %s %d", nomFichier, prenomFichier, motDePasse, &role);
        if (strcmp(nom, nomFichier) == 0 && strcmp(prenom, prenomFichier) == 0 && role == 0) {
            int i=0; 
            printf("\nvous etes un administrateur s'il vous plait entrer votre mot de passe :   ");
            char utilpasse[50];
            while (i==0){
                scanf("%s",&utilpasse);
                if(strcmp(utilpasse,motDePasse) == 0){
                    return 1;  
                }
                printf("\nessayer de nouveau : ");
                i++;}
            fclose(fichierComptes);
            return 0; 
        }
    }
    fclose(fichierComptes);
    return 0; 
}


void creercompte() {
    compte utilisateur;
    printf("Nom : ");
    scanf("%s", utilisateur.nom);
    printf("Prenom : ");
    scanf("%s", utilisateur.prenom);
    printf("Mot de passe : ");
    scanf("%s", utilisateur.mp);
    printf("Role (0 pour admin, 1 pour candidat) : ");
    scanf("%d", &utilisateur.role);
    FILE *file = fopen("comptes.txt", "a");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    fprintf(file, "%s %s %s %d\n", utilisateur.nom, utilisateur.prenom, utilisateur.mp, utilisateur.role);
    fclose(file);
    if (utilisateur.role == 1) {
        Candidat candidat;
        printf("Age : ");
        scanf("%d", &candidat.age);
        printf("Adresse : ");
        scanf("%s", candidat.adress);
        printf("Niveau d'etude (nombre d'annee d'etude): ");
        scanf("%d", &candidat.niveauetude);
        printf("Sexe : ");
        scanf("%s", candidat.sexe);
        FILE *candidatsFile = fopen("candidats.txt", "a");
        if (candidatsFile == NULL) {
            printf("Erreur lors de l'ouverture du fichier des candidats.\n");
            return;
        }
        fprintf(candidatsFile, "%s %s %d %s %d %s\n", utilisateur.nom, utilisateur.prenom, candidat.age, candidat.adress, candidat.niveauetude, candidat.sexe);
        fclose(candidatsFile);
        printf("Candidat ajoutee avec succes.\n");
    }
    printf("Compte cree avec succes.\n");
    printf("Cliquez sur Enter pour revenir au menu principal");
    getchar();
    getchar(); 
}


void miseajourCandidat() {
    FILE *fichierCandidats = fopen("candidats.txt", "r");
    if (fichierCandidats == NULL) {
        printf("Erreur lors de l'ouverture du fichier des candidats.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), fichierCandidats) != NULL) {
        printf("%s", line);
    }

    fclose(fichierCandidats);

    Candidat candidat;
    char nomCandidat[50];
    char prenomCandidat[50];
    printf("Nom du candidat a mettre a jour : ");
    scanf("%s", nomCandidat);
    printf("Prenom du candidat a mettre a jour : ");
    scanf("%s", prenomCandidat);

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erreur lors de la creation du fichier temporaire.\n");
        return;
    }

    int candidatTrouve = 0;

    fichierCandidats = fopen("candidats.txt", "r");
    if (fichierCandidats == NULL) {
        printf("Erreur lors de l'ouverture du fichier des candidats.\n");
        fclose(tempFile);
        return;
    }

    while (fscanf(fichierCandidats, "%s %s %d %s %d %s",
                  candidat.nom, candidat.prenom, &candidat.age,
                  candidat.adress, &candidat.niveauetude, candidat.sexe) == 6) {

        if (strcmp(nomCandidat, candidat.nom) == 0 && strcmp(prenomCandidat, candidat.prenom) == 0) {
            candidatTrouve = 1;
            printf("Nouveau nom : ");
            scanf("%s", candidat.nom);
            printf("Nouvel prenom : ");
            scanf("%s", candidat.prenom);
            printf("Nouvel age : ");
            scanf("%d", &candidat.age);
            printf("Nouvelle adresse : ");
            scanf("%s", candidat.adress);
            printf("Nouveau niveau d'etude : ");
            scanf("%d", &candidat.niveauetude);
            printf("Nouveau sexe : ");
            scanf("%s", candidat.sexe);
            fprintf(tempFile, "%s %s %d %s %d %s\n", candidat.nom, candidat.prenom, candidat.age, candidat.adress, candidat.niveauetude, candidat.sexe);
            printf("Informations du candidat mises a jour avec succes.\n");
        } else {
            fprintf(tempFile, "%s %s %d %s %d %s\n", candidat.nom, candidat.prenom, candidat.age, candidat.adress, candidat.niveauetude, candidat.sexe);
        }
    }

    fclose(fichierCandidats);
    fclose(tempFile);
    remove("candidats.txt");
    rename("temp.txt", "candidats.txt");

    if (!candidatTrouve) {
        printf("Aucun candidat trouve avec le nom et le prenom fournis.\n");
    }
    printf("Cliquez sur Enter pour revenir au menu principal");
    getchar();
    getchar(); 
}



void creerelection() {
    char nomElection[50];
    printf("Nom de l'election : ");
    scanf("%s", nomElection);
    FILE *fichierlisteElection = fopen("liste election.txt", "a");
    if (fichierlisteElection == NULL) {
        printf("Erreur lors de l'ouverture du fichier liste election.\n");
        return;
    }
    fprintf(fichierlisteElection, "%s\n", nomElection);
    fclose(fichierlisteElection);
    char nomFichierElection[50];
    sprintf(nomFichierElection, "%s.txt", nomElection);
    FILE *fichierCandidatsElection = fopen(nomFichierElection, "w");
    if (fichierCandidatsElection == NULL) {
        printf("Erreur lors de la creation du fichier pour les candidats de l'election.\n");
        return;
    }
    int nombreCandidats;
    printf("Nombre de candidats : ");
    scanf("%d", &nombreCandidats);
    for (int i = 0; i < nombreCandidats; ++i) {
        Candidat candidat;
        printf("Nom du candidat %d : ", i + 1);
        scanf("%s", candidat.nom);
        printf("Prenom du candidat %d : ", i + 1);
        scanf("%s", candidat.prenom);
        fprintf(fichierCandidatsElection, "%s %s \n", candidat.nom, candidat.prenom);
    }
    fclose(fichierCandidatsElection);
    printf("Election '%s' creee avec succes.\n", nomElection);
    printf("Cliquez sur Enter pour revenir au menu principal");
    getchar();
    getchar(); 
}

void afficherelectionvotes(const char *electionName) {
    char nomFichierVote[50];
    sprintf(nomFichierVote, "%s_vote.txt", electionName);
    FILE *fichierVote = fopen(nomFichierVote, "r");
    if (fichierVote == NULL) {
        printf("Erreur lors de l'ouverture du fichier des votes pour l'election '%s'.\n", electionName);
        return;
    }
    printf("\nVotes pour l'election '%s' :\n", electionName);
    Vote vote;
    while (fscanf(fichierVote, "%s %s %s %s %s", vote.nomU, vote.prenomU, vote.nomE, vote.nomCandidat,vote.prenomCandidat) == 5) {
        printf("- Utilisateur : %s %s, Candidat choisi : %s %s \n", vote.nomU, vote.prenomU, vote.nomCandidat,vote.prenomCandidat);
    }

    fclose(fichierVote);
}

int estelectionouverte(const char *nomElection) {
    FILE *fichierEtatElections = fopen("etat_elections.txt", "r");
    if (fichierEtatElections == NULL) {
        perror("Erreur lors de l'ouverture du fichier etat_elections.txt");
        return 1;
    }

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichierEtatElections) != NULL) {
        size_t len = strlen(ligne);
        while (len > 0 && (ligne[len - 1] == '\n' || ligne[len - 1] == ' ' || ligne[len - 1] == '\t')) {
            ligne[--len] = '\0';
        }


        char electionNameFromFile[50];
        char status[10];
        if (sscanf(ligne, "%49s %9s", electionNameFromFile, status) == 2) {
            if (strcmp(electionNameFromFile, nomElection) == 0) {
                fclose(fichierEtatElections);
                int isElectionOpen = (strcmp(status, "ferme") != 0) ? 1 : 0;
                printf("Election status: %s\n", isElectionOpen ? "ouvert" : "ferme");  
                return isElectionOpen;
            }
        }
    }

    fclose(fichierEtatElections);
    

    return 1;
}







void miseajourresultat(const char *election, const char *candidatnom, const char *candidatprenom) {
    char nomFichierResultats[50];
    sprintf(nomFichierResultats, "%s_resultats.txt", election);
    FILE *fichierResultats = fopen(nomFichierResultats, "r+");
    if (fichierResultats == NULL) {
        printf("Erreur lors de l'ouverture ou la creation du fichier des resultats.\n");
        return;
    }

    int votesActuels;
    int candidatTrouve = 0;

    FILE *tempFile = fopen("temp_resultats.txt", "w");
    if (tempFile == NULL) {
        printf("Erreur lors de la creation du fichier temporaire pour les resultats.\n");
        fclose(fichierResultats);
        return;
    }

    while (fscanf(fichierResultats, "%d", &votesActuels) == 1) {
        char fnomCandidat[50];
        char fprenomCandidat[50];
        fscanf(fichierResultats, "%s %s", fnomCandidat, fprenomCandidat);

        if ((strcmp(candidatnom, fnomCandidat) == 0) && (strcmp(candidatprenom, fprenomCandidat) == 0)) {
            candidatTrouve = 1;
            votesActuels += 1;
            fprintf(tempFile, "%d %s %s\n", votesActuels, fnomCandidat, fprenomCandidat);
        } else {
            fprintf(tempFile, "%d %s %s\n", votesActuels, fnomCandidat, fprenomCandidat);
        }
    }

    if (!candidatTrouve) {
        fprintf(tempFile, "1 %s %s\n", candidatnom, candidatprenom);
    }

    fclose(fichierResultats);
    fclose(tempFile);

    remove(nomFichierResultats);
    rename("temp_resultats.txt", nomFichierResultats);
}



void voter(const char *nomU, const char *prenomU) {
    char electionChoisie[50];
    printf("Liste des elections disponibles :\n");

    FILE *listeElections = fopen("liste election.txt", "r");
    if (listeElections == NULL) {
        printf("Erreur lors de l'ouverture du fichier liste election.\n");
        return;
    }
    char nomElection[50];
    while (fscanf(listeElections, "%s", nomElection) == 1) {
        printf("- %s\n", nomElection);
    }
    fclose(listeElections);
    printf("\nChoisissez une election : ");
    scanf("%s", electionChoisie);
    if (!estelectionouverte(electionChoisie)) {
        printf("Desole, l'election '%s' est fermee. Vous ne pouvez pas voter.\n", electionChoisie);
        printf("Cliquez sur Enter pour revenir au menu principal");
        getchar();
        getchar(); 
        return;
    }
    char nomFichierElection[50];
    sprintf(nomFichierElection, "%s.txt", electionChoisie);
    FILE *fichierCandidatsElection = fopen(nomFichierElection, "r");
    if (fichierCandidatsElection == NULL) {
        printf("Erreur lors de l'ouverture du fichier de l'election choisie.\n");
        return;
    }
    printf("\nCandidats de l'election '%s' :\n", electionChoisie);
    char nomCandidat[50], prenomCandidat[50];
    while (fscanf(fichierCandidatsElection, "%s %s", nomCandidat, prenomCandidat) == 2) {
        printf("- %s %s\n", nomCandidat, prenomCandidat);
    }
    fclose(fichierCandidatsElection);
    char choixCandidatnom[50];
    char choixCandidatprenom[50];
    printf("Choisissez un candidat en entrant son nom : ");
    scanf("%s",&choixCandidatnom);
    scanf("%s",&choixCandidatprenom);

    if (strncmp(choixCandidatnom, "0", sizeof("0")) != 0)  {
        char nomFichierVote[50];
        sprintf(nomFichierVote, "%s_vote.txt", electionChoisie);
        FILE *fichierVote = fopen(nomFichierVote, "a");
        if (fichierVote == NULL) {
            printf("Erreur lors de l'ouverture du fichier pour enregistrer le vote.\n");
            return;
        }
        fprintf(fichierVote, "%s %s %s %s %s\n",nomU, prenomU,electionChoisie,choixCandidatnom,choixCandidatprenom);
        printf("\nVote enregistre avec succes pour le candidat %s %s dans l'election '%s'.\n", choixCandidatnom,choixCandidatprenom, electionChoisie);
        fclose(fichierVote);
        miseajourresultat(electionChoisie, choixCandidatnom,choixCandidatprenom);

    } else {
        printf("Vote annule.\n");
    }
    printf("Cliquez sur Enter pour revenir au menu principal");
    getchar();
    getchar(); 
}

void affichervotes() {
    printf("Liste des elections disponibles :\n");
    FILE *listeElections = fopen("liste election.txt", "r");
    if (listeElections == NULL) {
        printf("Erreur lors de l'ouverture du fichier liste election.\n");
        return;
    }
    char nomElection[50];
    while (fscanf(listeElections, "%s", nomElection) == 1) {
        printf("- %s\n", nomElection);
    }
    fclose(listeElections);
    char electionChoisie[50];
    printf("\nChoisissez une election pour afficher les votes : ");
    scanf("%s", electionChoisie);
    afficherelectionvotes(electionChoisie);
    printf("Cliquez sur Enter pour revenir au menu principal");
    getchar();
    getchar(); 
}

void afficherResultat() {
    char electionChoisie[50];
    printf("Liste des elections disponibles :\n");
    FILE *listeElections = fopen("liste election.txt", "r");
    if (listeElections == NULL) {
        printf("Erreur lors de l'ouverture du fichier liste election.\n");
        return;
    }
    char nomElection[50];
    while (fscanf(listeElections, "%s", nomElection) == 1) {
        printf("- %s\n", nomElection);
    }
    fclose(listeElections);
    printf("\nChoisissez une election pour afficher les resultats : ");
    scanf("%s", electionChoisie);
    char nomFichierResultats[50];
    sprintf(nomFichierResultats, "%s_resultats.txt", electionChoisie);
    FILE *fichierResultats = fopen(nomFichierResultats, "r");
    if (fichierResultats == NULL) {
        printf("Erreur lors de l'ouverture du fichier des resultats.\n");
        return;
    }
    printf("\nResultats de l'election '%s' :\n", electionChoisie);
    printf("%-20s %-20s %-20s %-20s\n", "Nom Candidat", "Prenom Candidat", "Votes", "Statut");
    char nomCandidat[50];
    char prenomCandidat[50];
    int votes;
    int maxVotes = 0;
    char gagnant[50];

    while (fscanf(fichierResultats, "%d %s %s ",&votes, &nomCandidat, &prenomCandidat ) == 3) {
        printf("%-20s %-20s %-20d ", nomCandidat, prenomCandidat, votes);
        if (votes > maxVotes) {
            maxVotes = votes;
            strcpy(gagnant, nomCandidat);
        }
        printf("\n");
    }

    if (feof(fichierResultats)) {
        printf("\nLe gagnant de l'election '%s' est : %s avec %d votes.\n", electionChoisie, gagnant, maxVotes);
    } else if (ferror(fichierResultats)) {
        printf("Erreur lors de la lecture du fichier des resultats.\n");
    } else {
        printf("Format du fichier des resultats incorrect.\n");
    }

    fclose(fichierResultats);


    while (getchar() != '\n');

    printf("Cliquez sur Enter pour revenir au menu principal");
    getchar();
    getchar(); 
}


void supprimerelection() {
    char electionChoisie[50];
    printf("Liste des elections disponibles :\n");
    FILE *listeElections = fopen("liste election.txt", "r");
    if (listeElections == NULL) {
        printf("Erreur lors de l'ouverture du fichier liste election.\n");
        return;
    }
    char nomElection[50];
    while (fscanf(listeElections, "%s", nomElection) == 1) {
        printf("- %s\n", nomElection);
    }
    fclose(listeElections);
    printf("\nChoisissez une election : ");
    scanf("%s", electionChoisie);
    FILE *fichierListeElection = fopen("liste election.txt", "r");
    if (fichierListeElection == NULL) {
        printf("Erreur lors de l'ouverture du fichier liste election.\n");
        return;
    }
    FILE *tempListeElection = fopen("temp_liste_election.txt", "w");
    if (tempListeElection == NULL) {
        printf("Erreur lors de la creation du fichier temporaire pour la liste des elections.\n");
        fclose(fichierListeElection);
        return;
    }
    while (fscanf(fichierListeElection, "%s", nomElection) == 1) {
        if (strcmp(nomElection, electionChoisie) != 0) {
            fprintf(tempListeElection, "%s\n", nomElection);
        }
    }
    fclose(fichierListeElection);
    fclose(tempListeElection);
    remove("liste election.txt");
    rename("temp_liste_election.txt", "liste election.txt");
    char nomFichierElection[50];
    sprintf(nomFichierElection, "%s.txt", electionChoisie);
    remove(nomFichierElection);
    char nomFichierVotes[50];
    sprintf(nomFichierVotes, "%s_vote.txt", electionChoisie);
    remove(nomFichierVotes);
    char nomFichierResultats[50];
    sprintf(nomFichierResultats, "%s_resultats.txt", electionChoisie);
    remove(nomFichierResultats);
    printf("L'election '%s' a ete supprimee avec succes.\n", electionChoisie);
    printf("Cliquez sur Enter pour revenir au menu principal");
    getchar();
    getchar(); 
}

void consulterinfocandidat() {
    char nomCandidat[50];
    char prenomCandidat[50];

    printf("Nom du candidat a consulter : ");
    scanf("%s", nomCandidat);
    printf("Prenom du candidat a consulter : ");
    scanf("%s", prenomCandidat);

    FILE *fichierCandidats = fopen("candidats.txt", "r");
    if (fichierCandidats == NULL) {
        printf("Erreur lors de l'ouverture du fichier des candidats.\n");
        return;
    }

    int candidatTrouve = 0;
    Candidat candidat;

    while (fscanf(fichierCandidats, "%s %s %d %s %d %s",
                  candidat.nom, candidat.prenom, &candidat.age,
                  candidat.adress, &candidat.niveauetude, candidat.sexe) == 6) {
        if (strcmp(nomCandidat, candidat.nom) == 0 && strcmp(prenomCandidat, candidat.prenom) == 0) {
            candidatTrouve = 1;
            printf("\nInformations du candidat %s %s :\n", nomCandidat, prenomCandidat);
            printf("Age : %d\n", candidat.age);
            printf("Adresse : %s\n", candidat.adress);
            printf("Niveau d'etude : %d\n", candidat.niveauetude);
            printf("Sexe : %s\n", candidat.sexe);
            break;
        }
    }

    fclose(fichierCandidats);

    if (!candidatTrouve) {
        printf("Aucun candidat trouve avec le nom et le prenom fournis.\n");
    }

    printf("Cliquez sur Enter pour revenir au menu principal");
    getchar();
    getchar(); 
}

void fermerelection() {
    char electionChoisie[50];
    printf("Liste des elections disponibles :\n");
    FILE *listeElections = fopen("liste election.txt", "r");
    if (listeElections == NULL) {
        printf("Erreur lors de l'ouverture du fichier liste election.\n");
        return;
    }
    char nomElection[50];
    while (fscanf(listeElections, "%s", nomElection) == 1) {
        printf("- %s\n", nomElection);
    }
    fclose(listeElections);
    printf("\nChoisissez une election : ");
    scanf("%s", electionChoisie);
    FILE *fichierEtatElections = fopen("etat_elections.txt", "a+");
    if (fichierEtatElections == NULL) {
        printf("Erreur lors de l'ouverture ou la creation du fichier pour l'etat des elections.\n");
        return;
    }


    fprintf(fichierEtatElections, "%s ferme\n", electionChoisie);

    fclose(fichierEtatElections);
    printf("Cliquez sur Enter pour revenir au menu principal");
    getchar();
    getchar(); 
}


void clear_screen() {

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    char utilnom[50];
    char utilprenom[50];
    printf("entrer votre nom et prenom : ");
    scanf("%s %s",utilnom,utilprenom);
    int choix=0 ;
    do {
        clear_screen();
        printf("\nMenu Principal\n");
        printf("1- voter\n");
        printf("2- consulter information des Candidat\n");
        printf(" les requete suivants sont reservees aux administrateurs :\n");
        printf("\n3- Creer un compte\n");
        printf("4- Creer une nouvelle election\n");
        printf("5- Mettre a jour les informations des candidats\n");
        printf("6- supprimer un ancienne election \n");
        printf("7- Afficher les resultats d'une election \n");
        printf("8- Afficher la liste des votes d'une election\n");
        printf("9- fermer une election \n");
        printf("0- Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);
        clear_screen();
        switch (choix) {
            case 1:
                voter(utilnom,utilprenom);
                break;
            case 2:
                consulterinfocandidat();
                break;
            case 3:
                if (verifierCompteAdmin(utilnom, utilprenom)) {
                    clear_screen();
                creercompte();}
                else{printf("desole vous ne pouvez pas creer un nouveau compte\nretour au menu principale\n");}
                break;
            case 4:
                if (verifierCompteAdmin(utilnom, utilprenom)) {
                    clear_screen();
                creerelection();}
                else{printf("desole vous ne pouvez pas creer une nouvelle election\nretour au menu principale\n");}
                break;
            case 5:
                if (verifierCompteAdmin(utilnom, utilprenom)) {
                    miseajourCandidat();}
                else{printf("desole vous ne pouvez pas mettre a jour les info d'un candidat\nretour au menu principale\n");}
                break;
            case 6:
                if (verifierCompteAdmin(utilnom, utilprenom)) {
                    clear_screen();
                supprimerelection();}
                else{printf("desole vous ne pouvez pas mettre a jour les info d'un candidat\nretour au menu principale\n");}
                break;
            case 7:
                if (verifierCompteAdmin(utilnom, utilprenom)) {
                    clear_screen();
                    afficherResultat();}
                else{printf("desole vous ne pouvez pas voir les votes\nretour au menu principale\n");}
                break;
            case 8:
                if (verifierCompteAdmin(utilnom, utilprenom)) {
                    clear_screen();
                    affichervotes();}
                else{printf("desole vous ne pouvez pas voir les votes\nretour au menu principale\n");}
                break;
            case 9:
                if (verifierCompteAdmin(utilnom, utilprenom)) {
                    clear_screen();
                    fermerelection();}
                else{printf("desole vous ne pouvez pas voir les votes\nretour au menu principale\n");}
                break;    
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 0);
    return 0;
}
