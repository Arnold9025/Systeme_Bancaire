//9H 05;
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

const unsigned short TAILLE_NOM = 31;
const unsigned short TAILLE_PRENOM = 31;

struct compte {
	unsigned int noCompte;
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	double solde;
	bool actif;
};

enum TypeTransaction {
	DEPOT,
	RETRAIT
};

enum TypeDeTri {
	NO_COMPTE,
	NOM,
	PRENOM,
	SOLDE
};

enum OrdreDeTri {
	ASCENDANT,
	DESCENDANT
};
void nettoyerConsole();
void quitterProgramme(bool& programmeContinue);
void initialisation(compte comptes[], const int CAPACITE);
int saisirInt();
void choixMenuPrincinpal(int &choix, compte comptes[], unsigned int& nbComptes, bool& programmeContinue);
void afficherMenu(compte comptes[], unsigned int nbComptes);

void ajouterCompte(compte comptes[], unsigned int& nbComptesActuels);
void desactiverCompte(compte comptes[], unsigned int indice);
double saisirMontant();
double calculerSommeSoldes(compte comptes[], unsigned int nbComptes);

unsigned int recupererNombreCompteActif(compte comptes[], unsigned int nbComptes);

void afficherSoldeMoyen(compte comptes[], unsigned int nbComptes);
void afficherSommeSoldes(compte comptes[], unsigned int nbComptes);
int rechercherClient(compte comptes[], unsigned int nbComptes);
void afficherTousLesComptes(compte comptes[], unsigned int nbComptes);
void afficherCompte(compte compte);
void effectuerTransaction(TypeTransaction typeTransaction, compte &compte, double montant);
void effectuerDepot(compte &compte, double montant);
void effectuerRetrait(compte &compte, double montant);



int main() {
	int i = 0;
	unsigned int nbComptesActuels = 0;
	const int NB_MAX = 1000;
	
	compte comptes[NB_MAX];
	initialisation(comptes, NB_MAX);

	afficherMenu(comptes, nbComptesActuels);
	
   

	system("pause");
	return 0;
};

void afficherMenu(compte comptes[], unsigned int nbComptes) {
	bool programmeContinue = true;
	do {
	int choix;
	cout << "                          -----GESTION DE COMPTE-----"<< endl;
	cout << "                         Bonjour que voulez vous faire" << endl;
	cout << " ___________________________________________________________________________________" << endl;
	cout << "|                   [1] Ajouter un compte de la banque.                             |"<< endl;
	cout << "|___________________________________________________________________________________|" << endl;
	cout << "|                 [2] Desactiver un compte de la banque.                            |" << endl;
	cout << "|___________________________________________________________________________________|" << endl;
	cout << "| [3] Afficher l'information d'un compte client en particulier (par no de compte)   |" << endl;
	cout << "|___________________________________________________________________________________|" << endl;
	cout << "|  [4] Effectuer un depot dans un compte en particulier (par no de compte)          |" << endl;
	cout << "|___________________________________________________________________________________|" << endl;
	cout << "|     [5] Effectuer un retrait dans un compte en particulier (par no de compte)     |" << endl;
	cout << "|___________________________________________________________________________________|" << endl;
	cout << "|                    [6] Afficher la liste des clients.                             |" << endl;
	cout << "|___________________________________________________________________________________|" << endl;
	cout << "|          [7] Afficher la somme totale des soldes de tous les comptes              |" << endl;
	cout << "|___________________________________________________________________________________|" << endl;
	cout << "|                   [8] Afficher le solde moyen des comptes                         |" << endl;
	cout << "|___________________________________________________________________________________|" << endl;
	cout << "|                        [9] Quitter  l'application                                 |" << endl;
	cout << "|___________________________________________________________________________________|" << endl;
	cout << endl;
	choix = saisirInt();
	choixMenuPrincinpal(choix,comptes,nbComptes, programmeContinue);
	} while (programmeContinue);
};

int saisirInt() {
	int retour;
	cout << "                                   Saisir un numero : "<< endl;
	cout << endl;
	cout << "                                          "; cin >> retour;
	while (cin.fail() || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(512, '\n');
		cout << "                               Saisir un numero valide : " << endl;
		cout << endl;
		cout << "                                          "; cin >> retour;
	}
	cin.ignore(512, '\n');
	system("cls");
	return retour;
};

void choixMenuPrincinpal(int& choix, compte comptes[], unsigned int& nbComptes, bool& programmeContinue){
	int indice;
	double montant;
	switch (choix)
	{
	case 1: ajouterCompte(comptes, nbComptes);
		break;
	case 2: indice = rechercherClient(comptes,nbComptes);
		    desactiverCompte(comptes, indice);
		break;
	case 3:  indice = rechercherClient(comptes, nbComptes);
		if (indice == -1)
		{
			cout << "Le compte que vous cherchez a afficher est inactive. Veuillez l'activer pour l'afficher " << endl;
		}
		else {
			 afficherCompte(comptes[indice]);
		};
		break;
	case 4:   indice = rechercherClient(comptes, nbComptes);
		if (indice == -1)
		{
			cout << "Le compte que vous cherchez a afficher est inactive. Veuillez l'activer pour l'afficher " << endl;
		}
		else {
			montant = saisirMontant();
			//effectuerDepot(compte, montant);
			effectuerTransaction(TypeTransaction::DEPOT, comptes[indice], montant);
		};
		break;
	case 5: indice = rechercherClient(comptes, nbComptes);
		if (indice == -1)
		{
			cout << "Le compte que vous cherchez a afficher est inactive. Veuillez l'activer pour l'afficher " << endl;
		}
		else {
			
			montant = saisirMontant();
			effectuerTransaction(TypeTransaction::RETRAIT, comptes[indice], montant);
		};;
		break;
	case 6:  afficherTousLesComptes(comptes, nbComptes);
		break;
	case 7:   afficherSommeSoldes(comptes, nbComptes);
		break;
	case 8:  afficherSoldeMoyen(comptes, nbComptes);
		break;
	case 9: quitterProgramme(programmeContinue);
		break;
		default:
	break;
	}
}
void nettoyerConsole() {
	system("cls");
};

void ajouterCompte(compte comptes[], unsigned int& nbComptes){
	int i = 0;
	/*if (comptes[i].noCompte != 2000)
	{
		i++;
	}*/
	while (comptes[i].noCompte != 2000)
	{
		i++;
	}
			comptes[i].noCompte = i;
			cout << "                          -----GESTION DE COMPTE-----" << endl;
			cout << "                            Pour le compte Numero: " << comptes[i].noCompte << endl;
			cout << " ___________________________________________________________________________________" << endl;
			cout << "|                Veuillez saisir le nom de l'utilisateur du compte                  | " << endl ;
			cout << "|___________________________________________________________________________________|" << endl;
			cout << "                                          "; cin.getline(comptes[i].nom, 31);
			cout << " ___________________________________________________________________________________" << endl;
			cout << "|                Veuillez saisir le prenom de l'utilisateur du compte               | " << endl;
			cout << "|___________________________________________________________________________________|" << endl;
			cout << "                                          "; cin.getline(comptes[i].prenom, 31);
			cout << " ___________________________________________________________________________________" << endl;
			cout << "|                Veuillez saisir le solde actuel du compte                          | " << endl;
			cout << "|___________________________________________________________________________________|" << endl;
			cout << "                                          "; cin >> comptes[i].solde;
			cout << " ___________________________________________________________________________________" << endl;

			comptes[i].actif = true;
			nbComptes++;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "                         Le nombre de compte actuel est " << nbComptes << endl;
			Sleep(5000);
			system("cls");
};

void initialisation(compte comptes[], const int CAPACITE) {
	for (int i = 0; i < CAPACITE; i++)
	{
		comptes[i].noCompte = 2000;
	}
	
};

void quitterProgramme(bool& programmeContinue) {
	programmeContinue = false;
	nettoyerConsole();
	cout << "                          -----GESTION DE COMPTE-----" << endl;
	cout << endl;
	cout << "                                    Aurevoir " << endl;
};

int rechercherClient(compte comptes[], unsigned int nbComptes) {
	int numeroARechercher, retour;
	cout << "                                                   -----GESTION DE COMPTE-----" << endl;

	cout << "                                Quel compte cherchez vous ? Veuillez saisir le numero de compte" << endl;
	cout << "                                                               "; cin >> numeroARechercher;
	while (cin.fail() || cin.peek() != '\n' ) {
			cin.clear();
			cin.ignore(512, '\n');
			cout << "Saisir un numero de compte valide : ";
			cin >> numeroARechercher;
		}
	cin.ignore(512, '\n');
	
	retour = comptes[numeroARechercher].actif == false || comptes[numeroARechercher].noCompte == 2000 ? -1 : numeroARechercher;
	return retour;
};
void desactiverCompte(compte comptes[], unsigned int indice) {
	char reponse;
	if (indice == -1)
	{
		cout << "                          -----GESTION DE COMPTE-----" << endl;
		cout << endl;
		cout << "                                Compte inactif" << endl;
		Sleep(3000);
		system("cls");
	}
	else
	{

		cout << "                          -----GESTION DE COMPTE-----" << endl;
		cout << endl;
	cout << "            Voulez vous vraiment desactiver le compte de " << comptes[indice].nom << " " << comptes[indice].prenom << " ? Oui (O) / Non (N)" << endl;
	cin >> reponse;
	while (cin.fail() || cin.peek() != '\n' || reponse != 'O' && reponse !='N') {
		cin.clear();
		cin.ignore(512, '\n');
		cout << "Saisir une option valide : " << endl;
		cin >> reponse;
	}
	if (reponse == 'O')
	{
		comptes[indice].actif = false;
		cout << "Le compte a ete desactive avec succes" << endl;
		Sleep(3000);
		system("cls");
	}
	else if (reponse == 'N') {
		cout << "compte non desactive";
		Sleep(3000);
		system("cls");
	}
	
	}
};

void afficherCompte(compte compte) {
	cout << " _________________________________________________________________________________________________________________" << endl;
	cout << "|                                          Informations du compte saisI                                           |" << endl;
	cout << "|_________________________________________________________________________________________________________________|" << endl;

	cout << "|        Numero de compte : " << "        Nom : " << "        Prenom : " << "        Solde du compte: " << "        Etat du Compte:       |" << endl;
	cout << "|_________________________________________________________________________________________________________________|" << endl;

	cout <<"               " <<compte.noCompte << "                  "<< compte.nom << "       " << compte.prenom << "               " << compte.solde ;

	switch (compte.actif)
	{
	case 0: cout << "                   inactive" << endl;  break;
	case 1: cout << "                   active" << endl; break;

	}
	cout << " _________________________________________________________________________________________________________________" << endl;

	cout << endl;
	Sleep(10000);
	system("cls");
};
void afficherTousLesComptes(compte comptes[], unsigned int nbComptes) {
	for (unsigned int i = 0; i < nbComptes; i++)
	{
		afficherCompte(comptes[i]);
	}
};

void effectuerDepot(compte &compte, double montant) {
	compte.solde = compte.solde + montant;
};
void effectuerRetrait(compte &compte, double montant) {
	compte.solde = compte.solde - montant;
};

double saisirMontant() {
	double retour;
	cout << "                                               Saisir le montant de la transaction: ";
	cout << "                                                                                                     ";  cin >> retour;
	while (cin.fail() || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(512, '\n');
		cout << "                                            Saisir un montant valide : ";
		cin >> retour;
	}
	cin.ignore(512, '\n');
	return retour;
}
void effectuerTransaction(TypeTransaction typeTransaction, compte &compte, double montant) {
	switch (typeTransaction)
	{
	case TypeTransaction::DEPOT : 
		Sleep(2000);
		cout << "                                                          Depot effectue";
		effectuerDepot(compte, montant);
		break;
	case TypeTransaction::RETRAIT :
		Sleep(2000);
	cout << "                                                            Retrait effectue";
	effectuerRetrait(compte, montant); break;
	default:
		break;
	}
	Sleep(3000);
	system("cls");
};
double calculerSommeSoldes(compte comptes[], unsigned int nbComptes) {
	double retour = 0;
	for (int i = 0; i < nbComptes; i++)
	{if(comptes[i].actif){
		retour += comptes[i].solde;
	};
	}
	return retour;
};
unsigned int recupererNombreCompteActif(compte comptes[], unsigned int nbComptes){
	int retour = 0;
		for (int i = 0; i < nbComptes; i++)
		{
			if (comptes[i].actif)
			{
				retour++;
			};
		};
		return retour;
}
void afficherSommeSoldes(compte comptes[], unsigned int nbComptes) {
	double sommeTotaleDesSoldesDeTousLesComptes = 0;

	sommeTotaleDesSoldesDeTousLesComptes = calculerSommeSoldes(comptes, nbComptes);
	cout << "La somme totale des soldes de tous les comptes est:" << sommeTotaleDesSoldesDeTousLesComptes << endl;
	Sleep(3000);
	system("cls");
};
void afficherSoldeMoyen(compte comptes[], unsigned int nbComptes) {
	double sommeTotaleDesSoldesDeTousLesComptes = 0;
	double SoldeMoyen = 0;
	int nbComptesActifs = 0;
	sommeTotaleDesSoldesDeTousLesComptes = calculerSommeSoldes(comptes, nbComptes);
	nbComptesActifs = recupererNombreCompteActif(comptes, nbComptes);
	SoldeMoyen = sommeTotaleDesSoldesDeTousLesComptes / nbComptesActifs;
	cout << "Le solde moyen des comptes est : " << SoldeMoyen;
	Sleep(3000);
	system("cls");
};