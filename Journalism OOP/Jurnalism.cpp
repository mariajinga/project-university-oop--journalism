//Jinga Maria, grupa 1054, seria D
//Proiectul cu tema "JURNALISM" - intialele "J" si "M"

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <sstream>
#include <ctime>
using namespace std;

class IFile { //"I" = intervata
	virtual void writeToFile(fstream& f) = 0; //metoda virtuala pura
	virtual void readFromFile(fstream& f) = 0; //metoda virtuala pura
};

//clasa 1
class Stire: public IFile{
private:
	const int id; //id-ul respectivei stiri
	static int nrStiri; //numarul total de stiri
	char* subiect; //subiect stire
	string locatie; //locatie stire
	int idReporter; //id reporter
	int idOperator; //id operator
	int idEditor; //id editor 
	int idSunetist; //id sunetist
	float buget; //bugetul total
	bool breakingNews; //daca stirea este de Breaking News sau nu
	int nrRatinguri; //numarul de ratinguri
	float ratinguri[100]; //ratingurile
public:
	//constructor fara parametri
	Stire() :id(0) {
		//cout << "\nApel constructor fara parametri STIRE: " << endl;
		nrStiri++;
		subiect = new char[strlen("Necunoscut") + 1];
		strcpy(subiect, "Necunoscut");
		locatie = "inexistenta";
		idReporter = 0;
		idOperator = 0;
		idEditor = 0;
		idSunetist = 0;
		buget = 0;
		breakingNews = false;
		nrRatinguri = 0;
	}

	//constructor cu un parametru
	Stire(int id) :id(id) {
		//cout << "\nApel constructor cu un parametru STIRE:" << endl;
		subiect = new char[strlen("Necunoscut") + 1];
		strcpy(subiect, "Necunoscut");
		locatie = "inexistenta";
		nrStiri++;
		idReporter = 0;
		idOperator = 0;
		idEditor = 0;
		idSunetist = 0;
		buget = 0;
		breakingNews = false;
		nrRatinguri = 0;
	}

	//constructor cu toti parametri
	Stire(int id, const char* subiect, string locatie, int idReporter, int idOperator, int idEditor, int idSunetist, float buget, bool breakingNews, int nrRatinguri, float* ratinguri) :id(id) {
		//cout << "\nApel constructor cu toti parametri STIRE:" << endl;
		nrStiri++;
		this->subiect = new char[strlen(subiect) + 1];
		strcpy(this->subiect, subiect);
		this->locatie = locatie;
		this->idReporter = idReporter;
		this->idOperator = idOperator;
		this->idEditor = idEditor;
		this->idSunetist = idSunetist;
		this->buget = buget;
		this->breakingNews = breakingNews;
		this->nrRatinguri = nrRatinguri;
		for (int i = 0; i < nrRatinguri; i++) {
			this->ratinguri[i] = ratinguri[i];
		}
	}

	//fisiere binare
	void writeToFile(fstream& f) {
		//scriere id(int)
		f.write((char*)&this->id, sizeof(int));

		//scriere numar de stiri (int)
		f.write((char*)&this->nrStiri, sizeof(int));

		//scriere subiect (char*)
		int lungimeSubiect = strlen(this->subiect) + 1;
		f.write((char*)&lungimeSubiect, sizeof(int));
		f.write(this->subiect, lungimeSubiect * sizeof(char));
		
		//scriere locatie (string)
		int lungimeLocatie = this->locatie.length() + 1;
		f.write((char*)&lungimeLocatie, sizeof(int));
		f.write(this->locatie.data(), lungimeLocatie * sizeof(char));

		//scriere idReporter (int)
		f.write((char*)&this->idReporter, sizeof(int));

		//scriere idOperator (int)
		f.write((char*)&this->idOperator, sizeof(int));

		//scriere idEditor (int)
		f.write((char*)&this->idEditor, sizeof(int));

		//scriere idSunetist (int)
		f.write((char*)&this->idSunetist, sizeof(int));

		//scriere buget (float)
		f.write((char*)&this->buget, sizeof(float));

		//scriere breakingNews (bool)
		f.write((char*)&this->breakingNews, sizeof(bool));

		//scriere nrRatinguri (int)
		f.write((char*)&this->nrRatinguri, sizeof(int));

		//scriere ratinguri (float)
		for (int i = 0; i < this->nrRatinguri; i++)
		{
			f.write((char*)&this->ratinguri[i], sizeof(float));
		}
	}

	void readFromFile(fstream& f) {
		f.read((char*)&this->id, sizeof(int));
		f.read((char*)&this->nrStiri, sizeof(int)); 
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		delete[] this->subiect;
		this->subiect = new char[lg];
		strcpy(this->subiect, buffer);
		delete[] buffer;
		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		this->locatie = buffer;
		delete[] buffer;
		f.read((char*)&this->idReporter, sizeof(int));
		f.read((char*)&this->idOperator, sizeof(int));
		f.read((char*)&this->idEditor, sizeof(int));
		f.read((char*)&this->idSunetist, sizeof(int));
		f.read((char*)&this->buget, sizeof(float));
		f.read((char*)&this->breakingNews, sizeof(bool));
		f.read((char*)&this->nrRatinguri, sizeof(int));
		for (int i = 0; i < this->nrRatinguri; i++)
		{
			f.read((char*)&this->ratinguri[i], sizeof(int));
		}
	}

	//afisare
	void afisare() {
		cout << "\n-------------------------";
		cout << "\nID Stire: " << id;
		cout << "\nNumar Total de Stiri: " << nrStiri;
		cout << "\nSubiect Stire: " << subiect;
		cout << "\nLocatie Stire: " << locatie;
		cout << "\nId Reporter: " << idReporter;
		cout << "\nId Operator: " << idOperator;
		cout << "\nId Editor: " << idEditor;
		cout << "\nId Sunetist: " << idSunetist;
		cout << "\nBuget: " << buget;
		cout << "\nEste BreakingNews? (1 = da, 0 = nu) --> " << breakingNews;
		cout << "\nNumar de ratinguri: " << nrRatinguri;
		cout << "\nRatinguri: ";
		for (int i = 0; i < nrRatinguri; i++)
			cout << ratinguri[i] << "  ";
		cout << "\n-------------------------" << endl;
	}


	//get
	int getId() {
		return this->id;
	}

	static int getNrStiri() {
		return Stire::nrStiri;
	}

	char* getSubiect() {
		return this->subiect;
	}

	string getLocatie() {
		return this->locatie;
	}

	int getIdReporter() {
		return this->idReporter;
	}

	int getIdOperator() {
		return this->idOperator;
	}

	int getIdEditor() {
		return this->idEditor;
	}

	int getIdSunetist() {
		return this->idSunetist;
	}

	float getBuget() {
		return this->buget;
	}

	bool getBreakingNews() {
		return this->breakingNews;
	}

	int getNrRatinguri() {
		return this->nrRatinguri;
	}

	float* getRatinguri() {
		return this->ratinguri;
	}


	//set
	void setNrStiri(int ns) {
		if (ns > 0) {
			nrStiri = ns;
		}
	}

	void setSubiect(const char* subiect) {
		delete[] this->subiect;
		if (subiect != NULL) {
			this->subiect = new char[strlen(subiect) + 1];
			strcpy(this->subiect, subiect);
		}
	}

	void setLocatie(string locatie) {
		if (locatie != " ") {
			this->locatie = locatie;
		}
	}

	void setIdReporter(int idReporter) {
		if (idReporter > 0) {
			this->idReporter = idReporter;
		}
	}

	void setIdOperator(int idOperator) {
		if (idOperator > 0) {
			this->idOperator = idOperator;
		}
	}

	void setIdEditor(int idEditor) {
		if (idEditor > 0) {
			this->idEditor = idEditor;
		}
	}

	void setIdSunetist(int idSunetist) {
		if (idSunetist > 0) {
			this->idSunetist = idSunetist;
		}
	}

	void setBuget(float buget) {
		if (buget > 0) {
			this->buget = buget;
		}
	}

	void setBreakingNews(bool BN) {
		if (BN != NULL) {
			this->breakingNews = BN;
		}
	}

	void setNrRatinguri(int nrRatinguri) {
		if (nrRatinguri >= 0) {
			this->nrRatinguri = nrRatinguri;
		}
	}

	void setRatinguri(float rating[100])
	{
		if (this->nrRatinguri >= 0) {
			for (int i = 0; i < this->nrRatinguri; i++)
				if (rating[i] <= 5 && rating[i] >= 0)
					this->ratinguri[i] = rating[i];
				else
					this->ratinguri[i] = 0;
		}
	}


	//constructor de copiere
	Stire(const Stire& s) :id(s.id) {
		//cout << "\nApel constructor de copiere STIRE";
		nrStiri++;
		this->subiect = new char[strlen(s.subiect) + 1];
		strcpy(this->subiect, s.subiect);
		this->locatie = s.locatie;
		this->idReporter = s.idReporter;
		this->idOperator = s.idOperator;
		this->idEditor = s.idEditor;
		this->idSunetist = s.idSunetist;
		this->buget = s.buget;
		this->breakingNews = s.breakingNews;
		if (s.nrRatinguri >= 0 && s.ratinguri != NULL)
		{
			this->nrRatinguri = s.nrRatinguri;
			for (int i = 0; i < this->nrRatinguri; i++)
				this->ratinguri[i] = s.ratinguri[i];
		}
	}


	//operator =
	Stire& operator=(const Stire& s) {
		//cout << "\nApel operator =";
		if (this != &s) {
			delete[] this->subiect;
			this->subiect = new char[strlen(s.subiect) + 1];
			strcpy(this->subiect, s.subiect);
			this->locatie = s.locatie;
			this->idReporter = s.idReporter;
			this->idOperator = s.idOperator;
			this->idEditor = s.idEditor;
			this->idSunetist = s.idSunetist;
			this->buget = s.buget;
			this->breakingNews = s.breakingNews;
			if (s.nrRatinguri >= 0)
			{
				this->nrRatinguri = s.nrRatinguri;
				for (int i = 0; i < this->nrRatinguri; i++)
					this->ratinguri[i] = s.ratinguri[i];
			}
			else {
				this->nrRatinguri = 0;
			}
		}
		return *this;
	}

	// operator ++ pre-incrementare; +1000 la buget
	Stire& operator++() {
		this->buget = this->buget + 1000;
		return *this;
	}

	// operator++ post-incrementare; +1000 la buget
	Stire operator++(int) {
		Stire copie;
		copie = *this;
		this->buget = this->buget + 1000;
		return copie;
	}

	// s + 1200; buget + 1200
	Stire operator+ (int x) {
		Stire copie;
		copie = *this;
		copie.buget = copie.buget + x;
		return copie;
	}

	// s1 + s2; buget s1 + buget s2 
	Stire operator+ (Stire s) {
		Stire copie;
		copie = *this;
		copie.buget = copie.buget + s.buget;
		return copie;
	}

	//cin
	friend istream& operator>> (istream& in, Stire& s) {
		cout << "Denumire Stire: ";
		char den[200];
		in.getline (den, 200);
		delete[] s.subiect;
		s.subiect = new char[strlen(den) + 1];
		strcpy(s.subiect, den);
		cout << "Locatie: ";
		in >> s.locatie;
		cout << "ID Reporter: ";
		in >> s.idReporter;
		cout << "ID Operator: ";
		in >> s.idOperator;
		cout << "ID Editor: ";
		in >> s.idEditor;
		cout << "ID Sunetist: ";
		in >> s.idSunetist;
		cout << "Buget alocat: ";
		in >> s.buget;
		cout << "Breaking News? (1 = da, 0 = nu): ";
		in >> s.breakingNews;
		cout << "Numar Ratinguri: ";
		in >> s.nrRatinguri;
		if (s.nrRatinguri >= 0)
			for (int i = 0; i < s.nrRatinguri; i++) {
				cout << "Rating " << i + 1 << ": ";
				in >> s.ratinguri[i];
			}
		nrStiri++;
		return in;
	}

	//cout
	friend ostream& operator<<(ostream& out, const Stire& s) {
		out << "\n-------------------------";
		out << "\nID Stire: " << s.id;
		out << "\nNumar Stiri: " << nrStiri;
		out << "\nSubiect Stire: " << s.subiect;
		out << "\nLocatie Stire: " << s.locatie;
		out << "\nId Reporter: " << s.idReporter;
		out << "\nId Operator: " << s.idOperator;
		out << "\nId Editor: " << s.idEditor;
		out << "\nId Sunetist: " << s.idSunetist;
		out << "\nBuget: " << s.buget;
		out << "\nEste BreakingNews? (1 = da, 0 = nu) --> " << s.breakingNews;
		out << "\nNumar de ratinguri: " << s.nrRatinguri;
		out << "\nRatinguri: ";
		for (int i = 0; i < s.nrRatinguri; i++)
			out << s.ratinguri[i] << "  ";
		out << "\n-------------------------" << endl;
		return out;
	}

	//Operator de indexare
	float& operator[](int index) {
		index = index - 1;
		if (index >= 0 && index < this->nrRatinguri) {
			return this->ratinguri[index];
		}
	}

	//Cast explicit
	explicit operator float() {
		return this->buget;
	}

	//Operator negatie 
	bool operator!() {
		if (this->nrRatinguri > 0) {
			return true;
		}
		return false;
	}

	//Operator >=
	bool operator>=(Stire s) {
		return this->buget >= s.buget;
	}

	//Operator ==
	friend int operator==(Stire& x, Stire& y) {
		int ok = 1;
		if (strcmp(x.subiect, y.subiect) == 0)
		{
			if (x.idReporter == y.idReporter)
			{
				if (x.locatie == y.locatie)
				{
					if (x.idOperator == y.idOperator)
					{
						if (x.idEditor == y.idEditor)
						{
							if (x.idSunetist == y.idSunetist)
							{
								if (x.buget == y.buget)
								{
									if (x.breakingNews == y.breakingNews)
									{
										if (x.nrRatinguri == y.nrRatinguri)
										{
											for (int i = 0; i < x.nrRatinguri; i++)
											{
												if (x.ratinguri[i] == y.ratinguri[i])
												{

												}
												else
													return 0;
											}
										}
										else
											return 0;
									}
									else
										return 0;
								}
								else
									return 0;
							}
							else
								return 0;
						}
						else
							return 0;
					}
					else
						return 0;
				}
				else
					return 0;
			}
			else
				return 0;
		}
		else
			return 0;
		return ok;
	}


	//metoda de prelucrare
	void adaugaRating(float rating) {
		if (rating >= 0 && rating <= 5){
			this->nrRatinguri++;
			this->ratinguri[this->nrRatinguri - 1] = rating;
		}
		else{
			cout << "Nu se poate adauga" << endl;
		}
	}

	//raport ratinguri pozitive
	int ratinguriPozitive() 
	{
		ofstream g("ratinguripozitive.txt");
		int nr = 0;
		for (int i = 0; i < this->nrRatinguri; i++)
		{
			if (this->ratinguri[i] >= 2.5)
			{
				nr++;
				g << this->ratinguri[i] << " ; ";
			}
		}
		return nr;
	}

	//pentru CSV
	void CitireCSV(fstream& f) {
		string line;
		while (getline(f, line)) {
			stringstream lineStream(line);
			string cell;
			getline(lineStream, cell, ',');
			delete[] this->subiect;
			this->subiect = new char[cell.size() + 1];
			strcpy(this->subiect, cell.c_str());
			getline(lineStream, cell, ',');
			this->locatie = cell;
			getline(lineStream, cell, ',');
			this->idReporter = stoi(cell);
			getline(lineStream, cell, ',');
			this->idOperator = stoi(cell);
			getline(lineStream, cell, ',');
			this->idEditor = stoi(cell);
			getline(lineStream, cell, ',');
			this->idSunetist = stoi(cell);
			getline(lineStream, cell, ',');
			this->buget = stof(cell);
			getline(lineStream, cell, ',');
			if (cell == "true" || cell == "True" || cell == "1" || cell == "TRUE")
				this->breakingNews = true;
			else
				this->breakingNews = false;
			getline(lineStream, cell, ',');
			this->nrRatinguri = stoi(cell);
			for (int i = 0; i < this->nrRatinguri; i++) {
				getline(lineStream, cell, ',');
				this->ratinguri[i] = stof(cell);
			}
		}
	}

	//operator <
	friend bool operator<(const Stire& s1, const Stire& s2) {
		return s1.buget < s2.buget;
	}

	//destructor
	~Stire() {
		delete[] this->subiect;
		nrStiri--;
	}

};
int Stire::nrStiri = 0;


//clasa 9 (noua) - pt faza 3
class Angajat :public IFile { //clasa de baza cu clasele derivate: reporter, operator, editor, sunetist
private:
	string CNP = "INACCESIBIL";
protected:
	int aniPanaLaPensie = 0;
	float bonus = 0; //bonus anual 

public:
	void writeToFile(fstream& f) {
		//scriere nume
		//scriere lungime sir
		int lg = this->CNP.length() + 1;
		f.write((char*)&lg, sizeof(int));
		//scriere sir de caracter efectiv
		f.write(this->CNP.data(), lg);
		//scriere vechime
		f.write((char*)&this->aniPanaLaPensie, sizeof(int));
		//scriere salariu
		f.write((char*)&this->bonus, sizeof(float));
	}

	void readFromFile(fstream& f) {
		//citire nume
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->CNP = buffer;
		delete[] buffer;
		//citire vechime
		f.read((char*)&this->aniPanaLaPensie, sizeof(int));
		//citire salariu
		f.read((char*)&this->bonus, sizeof(float));
	}

	Angajat() {
		//cout << "\nConstructor fara parametri ANGAJAT";
	}

	Angajat(string CNP, int aniPanaLaPensie, float bonus) {
		//cout << "\nConstructor cu toti parametri ANGAJAT";
		this->CNP = CNP;
		this->aniPanaLaPensie = aniPanaLaPensie;
		this->bonus = bonus;
	}

	Angajat(const Angajat& a) {
		//cout << "\nConstructor copiere ANGAJAT";
		this->CNP = a.CNP;
		this->aniPanaLaPensie = a.aniPanaLaPensie;
		this->bonus = a.bonus;
	}

	Angajat& operator=(const Angajat& a) {
		//cout << "\nOperator = ANGAJAT";
		this->CNP = a.CNP;
		this->aniPanaLaPensie = a.aniPanaLaPensie;
		this->bonus = a.bonus;
		return *this;
	}

	friend istream& operator>> (istream& in, Angajat& a) {
		cout << "\nCNP: ";
		in >> a.CNP;
		cout << "\nAni ramasi pana la pensie: ";
		in >> a.aniPanaLaPensie;
		cout << "\nBonus acumulat pe parcursul unui an: ";
		in >> a.bonus;
		return in;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a) {
		out << "\nCNP: " << a.CNP;
		out << "\nAni ramasi pana la pensie: " << a.aniPanaLaPensie;
		out << "\nBonus acumulat pe parcursul unui an: " << a.bonus;
		return out;
	}

	~Angajat() {
		//cout << "\nDestructor ANGAJAT";
	}

	//metoda virtuala
	virtual float bonusAnual() {
		return this->bonus;
	}
};


//clasa 2
class Reporter: public Angajat {
private:
	const int idReporter;
	char* nume;
	int experienta; //in luni
	string judet;
	int nrStiri;
	float* plataStiri; //plata per stire
	int nrColegiEchipa;
	int echipa[4];
public:
	//constructor fara parametri
	Reporter() : idReporter(0) {
		//cout << "\nApel constructor fara parametri REPORTER: " << endl;
		nume = new char[strlen("Necunoscut") + 1];
		strcpy(nume, "Necunoscut");
		experienta = 0;
		judet = "inexistent";
		nrStiri = 0;
		float* plataStiri = NULL;
		nrColegiEchipa = 0;
	}

	//constructor cu un parametru
	Reporter(int idReporter) : idReporter(idReporter), Angajat() {
		//cout << "\nApel constructor cu un parametru REPORTER: " << endl;
		nume = new char[strlen("Necunoscut") + 1];
		strcpy(nume, "Necunoscut");
		experienta = 0;
		judet = "inexistent";
		nrStiri = 0;
		float* plataStiri = NULL;
		nrColegiEchipa = 0;
	}

	//constructor cu toti parametri
	Reporter(int idReporter, const char* nume, int experienta, string judet, int nrStiri, float* plataStiri, int nrColegiEchipa, int echipa[4], string CNP, int aniPanaLaPensie, float bonus) : idReporter(idReporter), Angajat(CNP, aniPanaLaPensie, bonus) {
		//cout << "\nApel constructor cu toti parametri REPORTER: " << endl;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->experienta = experienta;
		this->judet = judet;
		this->nrStiri = nrStiri;
		this->plataStiri = new float[nrStiri];
		for (int i = 0; i < nrStiri; i++)
			this->plataStiri[i] = plataStiri[i];
		this->nrColegiEchipa = nrColegiEchipa;
		for (int i = 0; i < nrColegiEchipa; i++)
			this->echipa[i] = echipa[i];
	}
	
	//fisiere binare
	void writeToFile(fstream& f) {
		f.write((char*)&this->idReporter, sizeof(int));
		//scriere nume (char*)
		int lungimeNume = strlen(this->nume) + 1;
		f.write((char*)&lungimeNume, sizeof(int));
		f.write((char*)this->nume, lungimeNume * sizeof(char));

		//scriere experienta (int)
		f.write((char*)&this->experienta, sizeof(int));

		//scriere judet (string)
		int lungimeLocatie = this->judet.length() + 1;
		f.write((char*)&lungimeLocatie, sizeof(int));
		f.write(this->judet.data(), lungimeLocatie * sizeof(char));

		//scriere nrStiri (int)
		f.write((char*)&this->nrStiri, sizeof(int));

		//scriere plata stiri (float*)
		for (int i = 0; i < this->nrStiri; i++)
		{
			f.write((char*)&this->plataStiri[i], sizeof(float));
		}
		//scriere nr colegi de echipa (int)
		f.write((char*)&this->nrColegiEchipa, sizeof(int));

		//scriere echipa (int)
		for(int i = 0 ;i<this->nrColegiEchipa;i++)
		{
			f.write((char*)&this->echipa, sizeof(int));
		}
		//scriere aniPanaLaPensie (int)
		f.write((char*)&this->aniPanaLaPensie, sizeof(int));
		//scriere bonus (float)
		f.write((char*)&this->bonus, sizeof(float));
	}

	void readFromFile(fstream& f) {
		f.read((char*)&this->idReporter, sizeof(int));
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		delete[] this->nume;
		this->nume = new char[lg];
		strcpy(this->nume, buffer);
		delete[] buffer;
		f.read((char*)&this->experienta, sizeof(int));
		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		this->judet = buffer;
		delete[] buffer;
		f.read((char*)&this->nrStiri, sizeof(int));
		delete[] this->plataStiri;
		this->plataStiri = new float[nrStiri];
		for (int i = 0; i < this->nrStiri; i++) {
			f.read((char*)&this->plataStiri[i], sizeof(float));
		}
		f.read((char*)&this->nrColegiEchipa, sizeof(int));
		for (int i = 0; i < this->nrColegiEchipa; i++)
		{
			f.read((char*)&this->echipa[i], sizeof(int));
		}
		f.read((char*)&this->aniPanaLaPensie, sizeof(int));
		f.read((char*)&this->bonus, sizeof(float));
	}

	
	//afisare
	void afisare() {
		cout << "\n-------------------------";
		cout << "\nID Reporter: " << idReporter;
		cout << "\nNume Reporter: " << nume;
		cout << "\nExperienta: " << experienta;
		cout << "\nJudet: " << judet;
		cout << "\nNumar Stiri: " << nrStiri;
		cout << "\nPlata Stiri :";
		for (int i = 0; i < nrStiri; i++)
			cout << plataStiri[i] << " ; ";
		cout << "\nNumar Colegi Echipa : " << nrColegiEchipa;
		cout << "\nID Colegi Echipa : ";
		for (int i = 0; i < nrColegiEchipa; i++)
			cout << echipa[i] << " ; ";
		cout << "\n-------------------------" << endl;
	}

	//get
	int getID() {
		return this->idReporter;
	}

	char* getNume() {
		return this->nume;
	}

	int getExperienta()	{
		return this->experienta;
	}

	string getJudet() {
		return this->judet;
	}

	int getNrStiri() {
		return this->nrStiri;
	}

	float* getPlataStiri() {
		return this->plataStiri;
	}

	int getNrColegiEchipa() {
		return this->nrColegiEchipa;
	}

	int getEchipa(int i) {
		return this->echipa[i];
	}

	//set
	void setNume(const char* nume) {
		delete[] this->nume;
		if (nume != NULL) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}

	void setExperienta(int experienta) {
		if (experienta != NULL)
			this->experienta = experienta;
	}

	void setJudet(string judet) {
		if (judet != " ")
			this->judet = judet;
	}

	void setNrStiri(int nrStiri) {
		if (nrStiri >= 0) {
			this->nrStiri = nrStiri;
		}
	}

	void setPlataStiri(float* plataStiri) {
		delete[] this->plataStiri;
		if (this->nrStiri >= 0) {
			this->plataStiri = new float[this->nrStiri];
			for (int i = 0; i < this->nrStiri; i++) {
				if (plataStiri[i] >= 0)
					this->plataStiri[i] = plataStiri[i];
				else
					this->plataStiri[i] = 0;
			}
		}
	}

	void setNrColegiEchipa(int nrColegiEchipa) {
		if (nrColegiEchipa >= 0)
			this->nrColegiEchipa = nrColegiEchipa;
	}

	void setEchipa(int echipa[4]) {
		if (this->nrColegiEchipa >= 0)
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				if (echipa[i] >= 0)
					this->echipa[i] = echipa[i];
				else
					this->echipa[i] = 0;
			}
	}

	//constructor de copiere
	Reporter(const Reporter& r) :idReporter(r.idReporter), Angajat(r) {
		//cout << "\nApel constructor de copiere";
		delete[] this->nume;
		delete[] this->plataStiri;
		this->nume = new char[strlen(r.nume) + 1];
		strcpy(this->nume, r.nume);
		this->experienta = r.experienta;
		this->judet = r.judet;
		if (r.nrStiri >= 0 && r.plataStiri != NULL) {
			this->nrStiri = r.nrStiri;
			this->plataStiri = new float[this->nrStiri];
			for (int i = 0; i < this->nrStiri; i++)
				this->plataStiri[i] = r.plataStiri[i];
		}
		if (r.nrColegiEchipa >= 0 && r.echipa != NULL) {
			this->nrColegiEchipa = r.nrColegiEchipa;
			for (int i = 0; i < this->nrColegiEchipa; i++)
				this->echipa[i] = r.echipa[i];
		}
	}

	//operator =
	Reporter& operator=(Reporter& r) {
		Angajat::operator=(r);
		//cout << "\nApel operator =" << endl;
		if (this != &r) {
			delete[] this->nume;
			delete[] this->plataStiri;
			this->nume = new char[strlen(r.nume) + 1];
			strcpy(this->nume, r.nume);
			this->experienta = r.experienta;
			this->judet = r.judet;
			if (r.nrStiri >= 0 && r.plataStiri != NULL) {
				this->nrStiri = r.nrStiri;
				this->plataStiri = new float[r.nrStiri];
				for (int i = 0; i < this->nrStiri; i++)
					this->plataStiri[i] = r.plataStiri[i];
			}
			else {
				this->nrStiri = 0;
				this->plataStiri = NULL;
			}
			if (nrColegiEchipa >= 0) {
				this->nrColegiEchipa = r.nrColegiEchipa;
				for (int i = 0; i < this->nrColegiEchipa; i++)
					this->echipa[i] = r.echipa[i];
			}
			else {
				this->nrColegiEchipa = 0;
			}
		}
		return *this;
	}

	//cin
	friend istream& operator>> (istream& in, Reporter& r) {
		cin.get();
		cout << "Nume Reporter: ";
		char den[200];
		in.getline(den,200);
		delete[] r.nume;
		delete[] r.plataStiri;
		r.nume = new char[strlen(den) + 1];
		strcpy(r.nume, den);
		cout << "Experienta: ";
		in >> r.experienta;
		cout << "Judet: ";
		in >> r.judet;
		cout << "Numar Stiri: ";
		in >> r.nrStiri;
		r.plataStiri = new float[r.nrStiri];
		for (int i = 0; i < r.nrStiri; i++) {
			cout << "Plata stire " << i + 1 << ": ";
			in >> r.plataStiri[i];
		}
		cout << "Numar Colegi Echipa: ";
		in >> r.nrColegiEchipa;
		for (int i = 0; i < r.nrColegiEchipa; i++) {
			cout << "ID Coleg " << i + 1 << ": ";
			in >> r.echipa[i];
		}
		cout << "Ani pana la pensie: ";
		in >> r.aniPanaLaPensie;
		cout << "Bonus anual: ";
		in >> r.bonus;
		return in;
	}

	//cout
	friend ostream& operator<<(ostream& out, const Reporter& r) {
		out << (Angajat)r;
		out << "\n-------------------------";
		out << "\nID Reporter: " << r.idReporter;
		out << "\nNume: " << r.nume;
		out << "\nExperienta: " << r.experienta;
		out << "\nJudet: " << r.judet;
		out << "\nNumar Stiri: " << r.nrStiri;
		out << "\nPlati stiri: ";
		for (int i = 0; i < r.nrStiri; i++)
			out << r.plataStiri[i] << " ";
		out << "\nNumar Colegi Echipa: " << r.nrColegiEchipa;
		out << "\nID Colegi: ";
		for (int i = 0; i < r.nrColegiEchipa; i++)
			out << r.echipa[i] << " ; ";
		out << "\n-------------------------" << endl;
		return out;
	}

	// operator -- pre Incrementare; -1 la experienta
	Reporter& operator--() {
		this->experienta = this->experienta - 1;
		return *this;
	}

	// operator-- post incrementare; -1 la experienta
	Reporter operator--(int) {
		Reporter copie;
		copie = *this;
		this->experienta = this->experienta - 1;
		return copie;
	}

	// r - 2; experienta - 2
	Reporter operator- (int x) {
		Reporter copie;
		copie = *this;
		if (copie.experienta >= x) {
			copie.experienta = copie.experienta - x;
		}
		else {
			cout << "Nu se poate efectua operatia!" << endl;
		}
		return copie;
	}

	// r1 - r2; experienta r1 - experienta r2 (daca r1 > r2)
	Reporter operator+ (Reporter& r) {
		Reporter copie;
		copie = *this;
		if (copie.experienta >= r.experienta) {
			copie.experienta = copie.experienta + r.experienta;
		}
		else {
			cout << "Nu se poate efectua operatia!" << endl;
		}
		return copie;
	}

	//operator de indexare
	float& operator[](int index) {
		index = index - 1;
		if (index >= 0 && index < this->nrStiri) {
			return this->plataStiri[index];
		}
	}

	//cast explicit
	explicit operator int() {
		return this->experienta;
	}

	//operator negatie
	bool operator!() {
		if (this->nrStiri >= 0) {
			return true;
		}
		return false;
	}

	//operator <=
	bool operator<=(Reporter& r) {
		if (this->experienta <= r.experienta)
			return true;
		else
			return false;
	}

	//operator ==
	friend bool operator==(Reporter& x, Reporter& y) {
		if (strcmp(x.nume, y.nume) != 0) 
		{
			return 0;
		}
		if (x.experienta != y.experienta)
		{
			return 0;
		}
		if (x.judet != y.judet)
		{
			return 0;
		}
		if (x.nrStiri != y.nrStiri)
		{
			return 0;
		}
		else
		{
			for (int i = 0; i < x.nrStiri; i++)
			{
				if (x.plataStiri[i] != y.plataStiri[i])
				{
					return 0;
				}
			}
		}
		if (x.nrColegiEchipa != y.nrColegiEchipa)
		{
			return 0;
		}
		else
		{
			for (int i = 0; i < x.nrColegiEchipa; i++)
			{
				if (x.echipa[i] != y.echipa[i])
				{
					return 0;
				}
			}
		}
		return 1;
	}
	
	//metoda de prelucrare
	void adaugaPlataStire(float plataStire) {
		if (plataStire >= 0) {
			this->nrStiri++;
			float* aux = new float[this->nrStiri - 1];
			for (int i = 0; i < this->nrStiri - 1; i++)
				aux[i] = this->plataStiri[i];
			delete[] this->plataStiri;
			this->plataStiri = new float[this->nrStiri];
			for (int i = 0; i < this->nrStiri - 1; i++)
				this->plataStiri[i] = aux[i];
			this->plataStiri[this->nrStiri - 1] = plataStire;
			delete[] aux;
		}
		else {
			cout << "Nu se poate adauga" << endl;
		}
	}

	//raport salariu
	int salariuReporter()
	{
		int salariu = 0;
		ofstream g("salariuReporter.txt");
		for (int i = 0; i < this->nrStiri; i++) {
			if (this->plataStiri[i] != 0) {
				salariu = salariu + plataStiri[i];
				g << this->plataStiri[i] << ";";
			}
		}
		return salariu;
	}

	//pentru CSV
	void CitireCSV(fstream& f) {
		string line;
		while (getline(f, line)) {
			stringstream lineStream(line);
			string cell;
			getline(lineStream, cell, ',');
			delete[] this->nume;
			this->nume = new char[cell.size() + 1];
			strcpy(this->nume, cell.c_str());
			getline(lineStream, cell, ',');
			this->experienta = stoi(cell);
			getline(lineStream, cell, ',');
			this->judet = cell;
			getline(lineStream, cell, ',');
			this->nrStiri = stoi(cell);
			delete[] this->plataStiri;
			this->plataStiri = new float[this->nrStiri];
			for (int i = 0; i < this->nrStiri; i++) {
				getline(lineStream, cell, ',');
				this->plataStiri[i] = stof(cell);
			}
			getline(lineStream, cell, ',');
			this->nrColegiEchipa = stoi(cell);
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				getline(lineStream, cell, ',');
				this->echipa[i] = stoi(cell);
			}
		}
	}

	//destructor
	~Reporter() {
		delete[] this->nume;
		delete[] this->plataStiri;
	}

	//calcul salariu (overwrite)
	float marireSalariu() {
		return Angajat::bonusAnual() + salariuReporter() + 100; //100 reprezinta cadoul de iarna
	}
};


//clasa 3
class Operator: public Angajat {
private:
	const int idOperator;
	char* nume;
	int experienta; // in luni
	string judet;
	float salariuLunar;
	int nrColegiEchipa;
	int echipa[4];
public:
	//constructor fara parametri
	Operator() :idOperator(0){
		//cout << "\nApel constructor fara parametri OPEREATOR: " << endl;
		nume = new char[strlen("Necunoscut") + 1];
		strcpy(nume, "Necunoscut");
		experienta = 0;
		judet = "Necunoscut";
		salariuLunar = 0;
		nrColegiEchipa = 0;
	}

	//constructor cu un parametru
	Operator(int idOperator) :idOperator(idOperator), Angajat() {
		//cout << "\nApel constructor cu un parametru OPERATOR: " << endl;
		nume = new char[strlen("Necunoscut") + 1];
		strcpy(nume, "Necunoscut");
		experienta = 0;
		judet = "Necunoscut";
		salariuLunar = 0;
		nrColegiEchipa = 0;
	}

	//constructor cu toti parametri
	Operator(int idOperator, const char* nume, int experienta, string judet, float salariuLunar, int nrColegiEchipa, int echipa[4], string CNP, int aniPanaLaPensie, float bonus) : idOperator(idOperator), Angajat(CNP, aniPanaLaPensie, bonus) {
		//cout << "\n Apel constructor cu toti parametri OPERATOR: " << endl;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->experienta = experienta;
		this->judet = judet;
		this->salariuLunar = salariuLunar;
		this->nrColegiEchipa = nrColegiEchipa;
		for (int i = 0; i < nrColegiEchipa; i++) {
			this->echipa[i] = echipa[i];
		}
	}

	//fisiere binare
	void writeToFile(fstream& f) {
		f.write((char*)&this->idOperator, sizeof(int));
		//scriere nume (char*)
		int lungimeNume = strlen(this->nume) + 1;
		f.write((char*)&lungimeNume, sizeof(int));
		f.write((char*)this->nume, lungimeNume * sizeof(char));

		//scriere experienta (int)
		f.write((char*)&this->experienta, sizeof(int));

		//scriere judet (string)
		int lungimeLocatie = this->judet.length() + 1;
		f.write((char*)&lungimeLocatie, sizeof(int));
		f.write(this->judet.data(), lungimeLocatie * sizeof(char));

		//scriere salariul lunar (float)
		f.write((char*)&this->salariuLunar, sizeof(float));

		//scriere nr colegi de echipa (int)
		f.write((char*)&this->nrColegiEchipa, sizeof(int));

		//scriere echipa (int)
		for (int i = 0; i < this->nrColegiEchipa; i++) {
			f.write((char*)&this->echipa[i], sizeof(int));
		}

		//scriere aniPanaLaPensie (int)
		f.write((char*)&this->aniPanaLaPensie, sizeof(int));

		//scriere bonus (float)
		f.write((char*)&this->bonus, sizeof(float));
	}

	void readFromFile(fstream& f) {
		f.read((char*)&this->idOperator, sizeof(int));
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		delete[] this->nume;
		this->nume = new char[strlen(buffer)+1];
		strcpy(this->nume, buffer);
		delete[] buffer;
		f.read((char*)&this->experienta, sizeof(int));
		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		this->judet = buffer;
		delete[] buffer;
		f.read((char*)&this->salariuLunar, sizeof(float));
		f.read((char*)&this->nrColegiEchipa, sizeof(int));
		for (int i = 0; i < this->nrColegiEchipa; i++) {
			f.read((char*)&this->echipa[i], sizeof(int));
		}
		f.read((char*)&this->aniPanaLaPensie, sizeof(int));
		f.read((char*)&this->bonus, sizeof(float));
	}

	//afisare
	void afisare() {
		cout << "\n-------------------------";
		cout << "\nID Operator: " << idOperator;
		cout << "\nNume: " << nume;
		cout << "\nExperienta: " << experienta;
		cout << "\nJudet: " << judet;
		cout << "\nSalariu Lunar: " << salariuLunar;
		cout << "\nNumar Colegi Echipa: " << nrColegiEchipa;
		cout << "\nID Colegi Echipa: ";
		for (int i = 0; i < nrColegiEchipa; i++) {
			cout << echipa[i] << " ";
		}
		cout << "\n-------------------------" << endl;
	}

	//get
	int getID() {
		return this->idOperator;
	}

	char* getNume() {
		return this->nume;
	}

	int getExperienta() {
		return this->experienta;
	}

	string getJudet() {
		return this->judet;
	}

	float getSalariu() {
		return this->salariuLunar;
	}

	int getNrColegi() {
		return this->nrColegiEchipa;
	}

	int getEchipa(int i) {
		return this->echipa[i];
	}

	//set
	void setNume(const char* nume) {
		delete[] this->nume;
		if (nume != NULL) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}

	void setExperienta(int experienta) {
		if (experienta != NULL) {
			this->experienta = experienta;
		}
	}

	void setJudet(string judet) {
		if (judet != " ") {
			this->judet = judet;
		}
	}

	void setSalariu(float salariuLunar) {
		if (salariuLunar >= 0) {
			this->salariuLunar = salariuLunar;
		}
	}

	void setNrColegiEchipa(int nrColegiEchipa) {
		if (nrColegiEchipa >= 0) {
			this->nrColegiEchipa = nrColegiEchipa;
		}
	}

	void setEchipa(int echipa[4]) {
		if (this->nrColegiEchipa >= 0)
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				if (echipa[i] >= 0)
					this->echipa[i] = echipa[i];
				else
					this->echipa[i] = 0;
			}
	}

	//constructor de copiere
	Operator(const Operator& o) :idOperator(o.idOperator), Angajat(o) {
		//cout << "\nApel constructor de copiere";
		delete[] this->nume;
		this->nume = new char[strlen(o.nume) + 1];
		strcpy(this->nume, o.nume);
		this->experienta = o.experienta;
		this->judet = o.judet;
		this->salariuLunar = o.salariuLunar;
		this->nrColegiEchipa = o.nrColegiEchipa;
		if (nrColegiEchipa >= 0 && echipa != NULL) {
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				this->echipa[i] = o.echipa[i];
			}
		}
	}

	//operator =
	Operator& operator=(Operator& o) {
		//cout << "\nApel operator =" << endl;
		Angajat::operator=(o);
		if (this != &o) {
			delete[] this->nume;
			this->nume = new char[strlen(o.nume) + 1];
			strcpy(this->nume, o.nume);
			this->experienta = o.experienta;
			this->judet = o.judet;
			this->salariuLunar = o.salariuLunar;
			this->nrColegiEchipa = o.nrColegiEchipa;
			if (nrColegiEchipa >= 0) {
				for (int i = 0; i < this->nrColegiEchipa; i++) {
					this->echipa[i] = o.echipa[i];
				}
			}
			else {
				this->nrColegiEchipa = 0;
			}
		}
		return *this;
	}

	//cin
	friend istream& operator>> (istream& in, Operator& o) {
		cin.get(); 
		cout << "Nume Operator: ";
		char den[200];
		in.getline(den,200);
		delete[] o.nume;
		o.nume = new char[strlen(den) + 1];
		strcpy(o.nume, den);
		cout << "Experienta: ";
		in >> o.experienta;
		cout << "Judet: ";
		in >> o.judet;
		cout << "Salariu Lunar: ";
		in >> o.salariuLunar;
		cout << "Numar Colegi Echipa: ";
		in >> o.nrColegiEchipa;
		for (int i = 0; i < o.nrColegiEchipa; i++) {
			cout << "ID Coleg " << i + 1 << ": ";
			in >> o.echipa[i];
		}
		cout << "Ani pana la pensie: ";
		in >> o.aniPanaLaPensie;
		cout << "Bonus anual: ";
		in >> o.bonus;
		return in;
	}

	//cout
	friend ostream& operator<<(ostream& out, const Operator& o) {
		out << (Angajat)o; 
		out << "\n-------------------------";
		out << "\nID Operator: " << o.idOperator;
		out << "\nNume: " << o.nume;
		out << "\nExperienta: " << o.experienta;
		out << "\nJudet: " << o.judet;
		out << "\nSalariu Lunar: " << o.salariuLunar;
		out << "\nNumar Colegi Echipa: " << o.nrColegiEchipa;
		out << "\nID Colegi: ";
		for (int i = 0; i < o.nrColegiEchipa; i++)
		{
			out << o.echipa[i] << " ; ";
		}
		out << "\n-------------------------" << endl;
		return out;
	}

	//operator ++ pre Incrementare; +100 la salariu
	Operator& operator++() {
		this->salariuLunar = this->salariuLunar + 100;
		return *this;
	}

	//operator ++ post Incrementare; +100 la salariu
	Operator operator++(int) {
		Operator copie;
		copie = *this;
		this->salariuLunar = this->salariuLunar + 100;
		return copie;
	}

	//o * 2; salariu * 2
	Operator operator*(int x) {
		Operator copie;
		copie = *this;
		copie.salariuLunar = copie.salariuLunar * x;
		return copie;
	}

	//o1 * o2; salariu o1 * (salariu o2 / 1000)
	Operator operator* (Operator o) {
		Operator copie;
		copie = *this;
		copie.salariuLunar = copie.salariuLunar * (o.salariuLunar / 1000);
		return copie;
	}

	//Operator de indexare
	int& operator[](int index) {
		index = index - 1;
		if (index >= 0 && index < this->nrColegiEchipa) {
			return this->echipa[index];
		}
	}

	//cast explicit
	explicit operator int() {
		return this->salariuLunar;
	}

	//Operator negatie
	bool operator!() {
		if (this->experienta >= 0) {
			return true;
		}
		return false;
	}

	//Operator <
	bool operator<(Operator& o)
	{
		return this->salariuLunar < o.salariuLunar;
	}

	//Operator ==
	friend int operator==(Operator& x, Operator& y) {
		if (strcmp(x.nume, y.nume) != 0)
		{
			return 0;
		}
		if (x.experienta != y.experienta)
		{
			return 0;
		}
		if (x.judet != y.judet)
		{
			return 0;
		}
		if (x.salariuLunar != y.salariuLunar)
		{
			return 0;
		}
		if (x.nrColegiEchipa != y.nrColegiEchipa)
		{
			return 0;
		}
		else
		{
			for (int i = 0; i < x.nrColegiEchipa; i++)
			{
				if (x.echipa[i] != y.echipa[i])
				{
					return 0;
				}
			}
		}
		return 1;
	}


	//metoda prelucrare
	void stergeColeg(int i) {
		if (this->echipa[i - 1] != 0) {
			for (int j = i - 1; j < this->nrColegiEchipa - 1; j++) {
				int aux = this->echipa[j];
				this->echipa[j] = this->echipa[j + 1];
				this->echipa[j + 1] = aux;
			}
		}
		this->nrColegiEchipa--;
	}

	//pentru CSV
	void CitireCSV(fstream& f) {
		string line;
		while (getline(f, line)) {
			stringstream lineStream(line);
			string cell;
			getline(lineStream, cell, ',');
			delete[] this->nume;
			this->nume = new char[cell.size() + 1];
			strcpy(this->nume, cell.c_str());
			getline(lineStream, cell, ',');
			this->experienta = stoi(cell);
			getline(lineStream, cell, ',');
			this->judet = cell;
			getline(lineStream, cell, ',');
			this->salariuLunar = stof(cell);
			getline(lineStream, cell, ',');
			this->nrColegiEchipa = stoi(cell);
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				getline(lineStream, cell, ',');
				this->echipa[i] = stoi(cell);
			}
		}
	}

	//raport salariu operator
	int salariuOperator(){
		int salariu = 0;
		ofstream g("salariuOperator.txt");
		if (this->salariuLunar != 0) {
			salariu = salariu + salariuLunar;
			g << this->salariuLunar;
		}
		return salariu;
	}

	//calcul salariu (overwrite)
	float marireSalariu() {
		return Angajat::bonusAnual() + salariuOperator() + 100; //100 reprezinta cadoul de iarna
	}

	//destructor
	~Operator() {
		delete[] this->nume;
	}
};


//clasa 4
class Editor: public Angajat {
private:
	const int idEditor;
	char* nume;
	int experienta; //pe luna
	string judet;
	float salariuLunar;
	int nrColegiEchipa;
	int echipa[4];

public:
	//constructor fara parametri
	Editor() :idEditor(0) {
		//cout << "\nApel constructor fara parametri EDITOR: " << endl;
		nume = new char[strlen("Necunoscut") + 1];
		strcpy(nume, "Necunoscut");
		experienta = 0;
		judet = "Necunoscut";
		salariuLunar = 0;
		nrColegiEchipa = 0;
	}

	//constructor cu un parametru
	Editor(int idEditor) :idEditor(idEditor), Angajat() {
		//cout << "\nApel constructor cu un parametru EDITOR: " << endl;
		nume = new char[strlen("Necunoscut") + 1];
		strcpy(nume, "Necunoscut");
		experienta = 0;
		judet = "Necunoscut";
		salariuLunar = 0;
		nrColegiEchipa = 0;
	}

	//constructor cu toti parametri
	Editor(int idEditor, const char* nume, int experienta, string judet, float salariuLunar, int nrColegiEchipa, int echipa[4], string CNP, int aniPanaLaPensie, float bonus) : idEditor(idEditor), Angajat(CNP, aniPanaLaPensie, bonus) {
		//cout << "\n Apel constructor cu toti parametri EDITOR: " << endl;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->experienta = experienta;
		this->judet = judet;
		this->salariuLunar = salariuLunar;
		this->nrColegiEchipa = nrColegiEchipa;
		for (int i = 0; i < nrColegiEchipa; i++) {
			this->echipa[i] = echipa[i];
		}
	}

	//fisiere binare
	void writeToFile(fstream& f) {
		f.write((char*)&this->idEditor, sizeof(int));
		//scriere nume (char*)
		int lungimeNume = strlen(this->nume) + 1;
		f.write((char*)&lungimeNume, sizeof(int));
		f.write((char*)this->nume, lungimeNume * sizeof(char));

		//scriere experienta (int)
		f.write((char*)&this->experienta, sizeof(int));

		//scriere judet (string)
		int lungimeLocatie = this->judet.length() + 1;
		f.write((char*)&lungimeLocatie, sizeof(int));
		f.write(this->judet.data(), lungimeLocatie * sizeof(char));

		//scriere salariul lunar (float)
		f.write((char*)&this->salariuLunar, sizeof(float));

		//scriere nr colegi de echipa (int)
		f.write((char*)&this->nrColegiEchipa, sizeof(int));

		//scriere echipa (int)
		for (int i = 0; i < this->nrColegiEchipa; i++)
		{
			f.write((char*)&this->echipa[i], sizeof(int));
		}

		//scriere aniPanaLaPensie (int)
		f.write((char*)&this->aniPanaLaPensie, sizeof(int));

		//scriere bonus (float)
		f.write((char*)&this->bonus, sizeof(float));
	}

	void readFromFile(fstream& f) {
		f.read((char*)&this->idEditor, sizeof(int));
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		delete[] this->nume;
		this->nume = new char[strlen(buffer) + 1];
		strcpy(this->nume, buffer);
		delete[] buffer;
		f.read((char*)&this->experienta, sizeof(int));
		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		this->judet = buffer;
		delete[] buffer;
		f.read((char*)&this->salariuLunar, sizeof(float));
		f.read((char*)&this->nrColegiEchipa, sizeof(int));
		for (int i = 0; i < this->nrColegiEchipa; i++)
		{
			f.read((char*)&this->echipa[i], sizeof(int));
		}
		f.read((char*)&this->aniPanaLaPensie, sizeof(int));
		f.read((char*)&this->bonus, sizeof(float));
	}

	//afisare
	void afisare() {
		cout << "\n-------------------------";
		cout << "\nID Editor: " << idEditor;
		cout << "\nNume: " << nume;
		cout << "\nExperienta: " << experienta;
		cout << "\nJudet: " << judet;
		cout << "\nSalariu Lunar: " << salariuLunar;
		cout << "\nNumar Colegi Echipa: " << nrColegiEchipa;
		cout << "\nID Colegi Echipa: ";
		for (int i = 0; i < nrColegiEchipa; i++) {
			cout << echipa[i] << " ";
		}
		cout << "\n-------------------------" << endl;
	}

	//get
	int getID() {
		return this->idEditor;
	}

	char* getNume() {
		return this->nume;
	}

	int getExperienta() {
		return this->experienta;
	}

	string getJudet() {
		return this->judet;
	}

	float getSalariu() {
		return this->salariuLunar;
	}

	int getNrColegi() {
		return this->nrColegiEchipa;
	}

	int getEchipa(int i) {
		return this->echipa[i];
	}

	//set
	void setNume(const char* nume) {
		delete[] this->nume;
		if (nume != NULL) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}

	void setExperienta(int experienta) {
		if (experienta != NULL) {
			this->experienta = experienta;
		}
	}

	void setJudet(string judet) {
		if (judet != " ") {
			this->judet = judet;
		}
	}

	void setSalariu(float salariuLunar) {
		if (salariuLunar >= 0) {
			this->salariuLunar = salariuLunar;
		}
	}

	void setNrColegiEchipa(int nrColegiEchipa) {
		if (nrColegiEchipa >= 0) {
			this->nrColegiEchipa = nrColegiEchipa;
		}
	}

	void setEchipa(int echipa[4]) {
		if (this->nrColegiEchipa >= 0)
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				if (echipa[i] >= 0)
					this->echipa[i] = echipa[i];
				else
					this->echipa[i] = 0;
			}
	}

	//constructor de copiere
	Editor(const Editor& e) :idEditor(e.idEditor), Angajat(e) {
		//cout << "\nApel constructor de coipere";
		delete[] this->nume;
		this->nume = new char[strlen(e.nume) + 1];
		strcpy(this->nume, e.nume);
		this->experienta = e.experienta;
		this->judet = e.judet;
		this->salariuLunar = e.salariuLunar;
		this->nrColegiEchipa = e.nrColegiEchipa;
		if (nrColegiEchipa >= 0 && echipa != NULL) {
			for (int i = 0; i < this->nrColegiEchipa; i++)
			{
				this->echipa[i] = e.echipa[i];
			}
		}
	}

	//operator =
	Editor& operator=(Editor& e) {
		//cout << "\nApel operator =" << endl;
		Angajat::operator=(e);
		if (this != &e) {
			delete[] this->nume;
			this->nume = new char[strlen(e.nume) + 1];
			strcpy(this->nume, e.nume);
			this->experienta = e.experienta;
			this->judet = e.judet;
			this->salariuLunar = e.salariuLunar;
			this->nrColegiEchipa = e.nrColegiEchipa;
			if (nrColegiEchipa >= 0) {
				for (int i = 0; i < this->nrColegiEchipa; i++) {
					this->echipa[i] = e.echipa[i];
				}
			}
			else {
				this->nrColegiEchipa = 0;
			}
		}
		return *this;
	}

	//cin
	friend istream& operator>> (istream& in, Editor& e) {
		cin.get(); 
		cout << "Nume Editor: ";
		char den[200];
		in.getline(den,200);
		delete[] e.nume;
		e.nume = new char[strlen(den) + 1];
		strcpy(e.nume, den);
		cout << "Experienta: ";
		in >> e.experienta;
		cout << "Judet: ";
		in >> e.judet;
		cout << "Salariu Lunar: ";
		in >> e.salariuLunar;
		cout << "Numar Colegi Echipa: ";
		in >> e.nrColegiEchipa;
		for (int i = 0; i < e.nrColegiEchipa; i++) {
			cout << "ID Coleg " << i + 1 << ": ";
			in >> e.echipa[i];
		}
		cout << "Ani pana la pensie: ";
		in >> e.aniPanaLaPensie;
		cout << "Bonus anual: ";
		in >> e.bonus;
		return in;
	}

	//cout
	friend ostream& operator<<(ostream& out, const Editor& e) {
		out << (Angajat)e;
		out << "\n-------------------------";
		out << "\nID Editor: " << e.idEditor;
		out << "\nNume: " << e.nume;
		out << "\nExperienta: " << e.experienta;
		out << "\nJudet: " << e.judet;
		out << "\nSalariu Lunar: " << e.salariuLunar;
		out << "\nNumar Colegi Echipa: " << e.nrColegiEchipa;
		out << "\nID Colegi: ";
		for (int i = 0; i < e.nrColegiEchipa; i++) {
			out << e.echipa[i] << " ; ";
		}
		out << "\n-------------------------" << endl;
		return out;
	}

	//operator -- pre Incrementare; -100 la salariu
	Editor& operator--() {
		this->salariuLunar = this->salariuLunar - 100;
		return *this;
	}

	//operator -- post Incrementare; -100 la salariu
	Editor operator--(int) {
		Editor copie;
		copie = *this;
		this->salariuLunar = this->salariuLunar - 100;
		return copie;
	}

	//e : 2; salariu : 2
	Editor operator/(int x) {
		Editor copie;
		copie = *this;
		copie.salariuLunar = copie.salariuLunar / x;
		return copie;
	}

	//e1 / e2; salariu e1 / (salariu e2 / 1000)
	Editor operator/ (Editor e) {
		Editor copie;
		copie = *this;
		copie.salariuLunar = copie.salariuLunar / (e.salariuLunar / 1000);
		return copie;
	}

	//Operator de indexare
	int& operator[](int index) {
		index = index - 1;
		if (index >= 0 && index < this->nrColegiEchipa) {
			return this->echipa[index];
		}
	}

	//cast explicit
	explicit operator int() {
		return this->salariuLunar;
	}

	//Operator negatie
	bool operator!() {
		if (this->experienta >= 0) {
			return true;
		}
		return false;
	}

	//Operator <
	bool operator<(Editor& e) {
		return this->salariuLunar < e.salariuLunar;
	}

	//Operator ==
	friend int operator==(Editor& x, Editor& y) {
		if (strcmp(x.nume, y.nume) != 0)
		{
			return 0;
		}
		if (x.experienta != y.experienta)
		{
			return 0;
		}
		if (x.judet != y.judet)
		{
			return 0;
		}
		if (x.salariuLunar != y.salariuLunar)
		{
			return 0;
		}
		if (x.nrColegiEchipa != y.nrColegiEchipa)
		{
			return 0;
		}
		else
		{
			for (int i = 0; i < x.nrColegiEchipa; i++)
			{
				if (x.echipa[i] != y.echipa[i])
				{
					return 0;
				}
			}
		}
		return 1;
	}


	//metoda prelucrare
	void stergeColeg(int i) {
		if (this->echipa[i - 1] != 0) {
			for (int j = i - 1; j < this->nrColegiEchipa - 1; j++) {
				int aux = this->echipa[j];
				this->echipa[j] = this->echipa[j + 1];
				this->echipa[j + 1] = aux;
			}
		}
		this->nrColegiEchipa--;
	}

	//pentru CSV
	void CitireCSV(fstream& f) {
		string line;
		while (getline(f, line)) {
			stringstream lineStream(line);
			string cell;
			getline(lineStream, cell, ',');
			delete[] this->nume;
			this->nume = new char[cell.size() + 1];
			strcpy(this->nume, cell.c_str());
			getline(lineStream, cell, ',');
			this->experienta = stoi(cell);
			getline(lineStream, cell, ',');
			this->judet = cell;
			getline(lineStream, cell, ',');
			this->salariuLunar = stof(cell);
			getline(lineStream, cell, ',');
			this->nrColegiEchipa = stoi(cell);
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				getline(lineStream, cell, ',');
				this->echipa[i] = stoi(cell);
			}
		}
	}

	//raport salariu editor
	int salariuEditor() {
		int salariu = 0;
		ofstream g("salariuEditor.txt");
		if (this->salariuLunar != 0) {
			salariu = salariu + salariuLunar;
			g << this->salariuLunar;
		}
		return salariu;
	}

	//calcul salariu (overwrite)
	float marireSalariu() {
		return Angajat::bonusAnual() + salariuEditor() + 100; //100 reprezinta cadoul de iarna
	}

	//destructor
	~Editor() {
		delete[] this->nume;
	}
};


//clasa 5
class Sunetist: public Angajat {
private:
	const int idSunetist;
	char* nume;
	int experienta; //pe  luna
	string judet;
	float salariuLunar;
	int nrColegiEchipa;
	int echipa[4];
public:
	//constructor fara parametri
	Sunetist() :idSunetist(0) {
		//cout << "\nApel constructor fara parametri SUNETIST: " << endl;
		nume = new char[strlen("Necunoscut") + 1];
		strcpy(nume, "Necunoscut");
		experienta = 0;
		judet = "Necunoscut";
		salariuLunar = 0;
		nrColegiEchipa = 0;
	}

	//constructor cu un parametru
	Sunetist(int idSunetist) :idSunetist(idSunetist), Angajat() {
		//cout << "\nApel constructor cu un parametru SUNETIST: " << endl;
		nume = new char[strlen("Necunoscut") + 1];
		strcpy(nume, "Necunoscut");
		experienta = 0;
		judet = "Necunoscut";
		salariuLunar = 0;
		nrColegiEchipa = 0;
	}

	//constructor cu toti parametri
	Sunetist(int idSunetist, const char* nume, int experienta, string judet, float salariuLunar, int nrColegiEchipa, int echipa[4], string CNP, int aniPanaLaPensie, float bonus) : idSunetist(idSunetist), Angajat(CNP, aniPanaLaPensie, bonus) {
		//cout << "\n Apel constructor cu toti parametri SUNETIST: " << endl;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->experienta = experienta;
		this->judet = judet;
		this->salariuLunar = salariuLunar;
		this->nrColegiEchipa = nrColegiEchipa;
		for (int i = 0; i < nrColegiEchipa; i++) {
			this->echipa[i] = echipa[i];
		}
	}

	//fisiere binare
	void writeToFile(fstream& f) {
		f.write((char*)&this->idSunetist, sizeof(int));
		//scriere nume (char*)
		int lungimeNume = strlen(this->nume) + 1;
		f.write((char*)&lungimeNume, sizeof(int));
		f.write((char*)this->nume, lungimeNume * sizeof(char));

		//scriere experienta (int)
		f.write((char*)&this->experienta, sizeof(int));

		//scriere judet (string)
		int lungimeLocatie = this->judet.length() + 1;
		f.write((char*)&lungimeLocatie, sizeof(int));
		f.write(this->judet.data(), lungimeLocatie * sizeof(char));

		//scriere salariul lunar (float)
		f.write((char*)&this->salariuLunar, sizeof(float));

		//scriere nr colegi de echipa (int)
		f.write((char*)&this->nrColegiEchipa, sizeof(int));

		//scriere echipa (int)
		for (int i = 0; i < this->nrColegiEchipa; i++)
		{
			f.write((char*)&this->echipa[i], sizeof(int));
		}

		//scriere aniPanaLaPensie (int)
		f.write((char*)&this->aniPanaLaPensie, sizeof(int));

		//scriere bonus(float)
		f.write((char*)&this->bonus, sizeof(float));
	}

	void readFromFile(fstream& f) {
		f.read((char*)&this->idSunetist, sizeof(int));
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		delete[] this->nume;
		this->nume = new char[strlen(buffer) + 1];
		strcpy(this->nume, buffer);
		delete[] buffer;
		f.read((char*)&this->experienta, sizeof(int));
		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		this->judet = buffer;
		delete[] buffer;
		f.read((char*)&this->salariuLunar, sizeof(float));
		f.read((char*)&this->nrColegiEchipa, sizeof(int));
		for (int i = 0; i < this->nrColegiEchipa; i++)
		{
			f.read((char*)&this->echipa[i], sizeof(int));
		}
		f.read((char*)&this->aniPanaLaPensie, sizeof(int));
		f.read((char*)&this->bonus, sizeof(float));
	}

	//afisare
	void afisare() {
		cout << "\n-------------------------";
		cout << "\nID Sunetist: " << idSunetist;
		cout << "\nNume: " << nume;
		cout << "\nExperienta: " << experienta;
		cout << "\nJudet: " << judet;
		cout << "\nSalariu Lunar: " << salariuLunar;
		cout << "\nNumar Colegi Echipa: " << nrColegiEchipa;
		cout << "\nID Colegi Echipa: ";
		for (int i = 0; i < nrColegiEchipa; i++) {
			cout << echipa[i] << " ";
		}
		cout << "\n-------------------------" << endl;
	}

	//get
	int getID() {
		return this->idSunetist;
	}

	char* getNume() {
		return this->nume;
	}

	int getExperienta() {
		return this->experienta;
	}

	string getJudet() {
		return this->judet;
	}

	float getSalariu() {
		return this->salariuLunar;
	}

	int getNrColegi() {
		return this->nrColegiEchipa;
	}

	int getEchipa(int i) {
		return this->echipa[i];
	}

	//set
	void setNume(const char* nume) {
		delete[] this->nume;
		if (nume != NULL) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}

	void setExperienta(int experienta) {
		if (experienta != NULL) {
			this->experienta = experienta;
		}
	}

	void setJudet(string judet) {
		if (judet != " ") {
			this->judet = judet;
		}
	}

	void setSalariu(float salariuLunar) {
		if (salariuLunar >= 0) {
			this->salariuLunar = salariuLunar;
		}
	}

	void setNrColegiEchipa(int nrColegiEchipa) {
		if (nrColegiEchipa >= 0) {
			this->nrColegiEchipa = nrColegiEchipa;
		}
	}

	void setEchipa(int echipa[4]) {
		if (this->nrColegiEchipa >= 0)
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				if (echipa[i] >= 0)
					this->echipa[i] = echipa[i];
				else
					this->echipa[i] = 0;
			}
	}

	//constructor de copiere
	Sunetist(const Sunetist& s) :idSunetist(s.idSunetist), Angajat(s) {
		//cout << "\nApel constructor de coipere";
		delete[] this->nume;
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		this->experienta = s.experienta;
		this->judet = s.judet;
		this->salariuLunar = s.salariuLunar;
		this->nrColegiEchipa = s.nrColegiEchipa;
		if (nrColegiEchipa >= 0 && echipa != NULL) {
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				this->echipa[i] = s.echipa[i];
			}
		}
	}

	//operator =
	Sunetist& operator=(Sunetist& s) {
		//cout << "\nApel operator =" << endl;
		Angajat::operator=(s);
		if (this != &s) {
			delete[] this->nume;
			this->nume = new char[strlen(s.nume) + 1];
			strcpy(this->nume, s.nume);
			this->experienta = s.experienta;
			this->judet = s.judet;
			this->salariuLunar = s.salariuLunar;
			this->nrColegiEchipa = s.nrColegiEchipa;
			if (nrColegiEchipa >= 0) {
				for (int i = 0; i < this->nrColegiEchipa; i++) {
					this->echipa[i] = s.echipa[i];
				}
			}
			else {
				this->nrColegiEchipa = 0;
			}
		}
		return *this;
	}

	//cin
	friend istream& operator>> (istream& in, Sunetist& s) {
		cin.get(); 
		cout << "Nume Sunetist: ";
		char den[200];
		in.getline(den, 200);
		delete[] s.nume;
		s.nume = new char[strlen(den) + 1];
		strcpy(s.nume, den);
		cout << "Experienta: ";
		in >> s.experienta;
		cout << "Judet: ";
		in >> s.judet;
		cout << "Salariu Lunar: ";
		in >> s.salariuLunar;
		cout << "Numar Colegi Echipa: ";
		in >> s.nrColegiEchipa;
		for (int i = 0; i < s.nrColegiEchipa; i++) {
			cout << "ID Coleg: " << i + 1 << ": ";
			in >> s.echipa[i];
		}
		cout << "Ani pana la pensie: ";
		in >> s.aniPanaLaPensie;
		cout << "Bonus anual: ";
		in >> s.bonus;
		return in;
	}

	//cout
	friend ostream& operator<<(ostream& out, const Sunetist& s) {
		out << (Angajat)s;
		out << "\n-------------------------";
		out << "\nID Sunetist: " << s.idSunetist;
		out << "\nNume: " << s.nume;
		out << "\nExperienta: " << s.experienta;
		out << "\nJudet: " << s.judet;
		out << "\nSalariu Lunar: " << s.salariuLunar;
		out << "\nNumar Colegi Echipa: " << s.nrColegiEchipa;
		out << "\nID Colegi: ";
		for (int i = 0; i < s.nrColegiEchipa; i++) {
			out << s.echipa[i] << " ; ";
		}
		out << "\n-------------------------" << endl;
		return out;
	}

	//operator ++ pre Incrementare; +100 la salariu
	Sunetist& operator++() {
		this->salariuLunar = this->salariuLunar + 100;
		return *this;
	}

	//operator ++ post Incrementare; +100 la salariu
	Sunetist operator++(int) {
		Sunetist copie;
		copie = *this;
		this->salariuLunar = this->salariuLunar + 100;
		return copie;
	}

	//s : 2; salariu : 2
	Sunetist operator/(int x) {
		Sunetist copie;
		copie = *this;
		copie.salariuLunar = copie.salariuLunar / x;
		return copie;
	}

	//s1 / s2; salariu s1 / (salariu s2 / 1000)
	Sunetist operator/ (Sunetist s) {
		Sunetist copie;
		copie = *this;
		copie.salariuLunar = copie.salariuLunar / (s.salariuLunar / 1000);
		return copie;
	}

	//Operator de indexare
	int& operator[](int index) {
		index = index - 1;
		if (index >= 0 && index < this->nrColegiEchipa) {
			return this->echipa[index];
		}
	}

	//cast explicit
	explicit operator int() {
		return this->salariuLunar;
	}

	//Operator negatie
	bool operator!() {
		if (this->experienta >= 0) {
			return true;
		}
		return false;
	}

	//Operator <
	bool operator<(Sunetist& s) {
		return this->salariuLunar < s.salariuLunar;
	}

	//Operator ==
	friend int operator==(Sunetist& x, Sunetist& y) {
		if (strcmp(x.nume, y.nume) != 0)
		{
			return 0;
		}
		if (x.experienta != y.experienta)
		{
			return 0;
		}
		if (x.judet != y.judet)
		{
			return 0;
		}
		if (x.salariuLunar != y.salariuLunar)
		{
			return 0;
		}
		if (x.nrColegiEchipa != y.nrColegiEchipa)
		{
			return 0;
		}
		else
		{
			for (int i = 0; i < x.nrColegiEchipa; i++)
			{
				if (x.echipa[i] != y.echipa[i])
				{
					return 0;
				}
			}
		}
		return 1;
	}


	//metoda prelucrare
	void stergeColeg(int i) {
		if (this->echipa[i - 1] != 0) {
			for (int j = i - 1; j < this->nrColegiEchipa - 1; j++) {
				int aux = this->echipa[j];
				this->echipa[j] = this->echipa[j + 1];
				this->echipa[j + 1] = aux;
			}
		}
		this->nrColegiEchipa--;
	}

	//pentru CSV
	void CitireCSV(fstream& f) {
		string line;
		while (getline(f, line)) {
			stringstream lineStream(line);
			string cell;
			getline(lineStream, cell, ',');
			delete[] this->nume;
			this->nume = new char[cell.size() + 1];
			strcpy(this->nume, cell.c_str());
			getline(lineStream, cell, ',');
			this->experienta = stoi(cell);
			getline(lineStream, cell, ',');
			this->judet = cell;
			getline(lineStream, cell, ',');
			this->salariuLunar = stof(cell);
			getline(lineStream, cell, ',');
			this->nrColegiEchipa = stoi(cell);
			for (int i = 0; i < this->nrColegiEchipa; i++) {
				getline(lineStream, cell, ',');
				this->echipa[i] = stoi(cell);
			}
		}
	}

	//raport salariu sunetist
	int salariuSunetist() {
		int salariu = 0;
		ofstream g("salariuSunetist.txt");
		if (this->salariuLunar != 0) {
			salariu = salariu + salariuLunar;
			g << this->salariuLunar;
		}
		return salariu;
	}

	//calcul salariu (overwrite)
	float marireSalariu() {
		return Angajat::bonusAnual() + salariuSunetist() + 100; //100 reprezinta cadoul de iarna
	}

	//destructor
	~Sunetist() {
		delete[] this->nume;
	}
};


//clasa 6
class Locatie: public IFile {
private:
	string judet;
	char* localitate;
	int nrStudiouri;
	int nrStiri;
	int idStiri[10];
public:
	//constructor fara parametri
	Locatie() {
		//cout << "\nApel constructor fara parametri LOCATIE: " << endl;
		judet = "Necunoscut";
		localitate = new char[strlen("Necunoscuta") + 1];
		strcpy(localitate, "Necunoscuta");
		nrStudiouri = 0;
		nrStiri = 0;
	}

	//constructor cu toti parametri
	Locatie(string judet, const char* localitate, int nrStudiouri, int nrStiri, int idStiri[10]) {
		//cout << "\nApel constructor cu toti parametri LOCATIE: " << endl;
		this->judet = judet;
		this->localitate = new char[strlen(localitate) + 1];
		strcpy(this->localitate, localitate);
		this->nrStudiouri = nrStudiouri;
		this->nrStiri = nrStiri;
		for (int i = 0; i < nrStiri; i++)
			this->idStiri[i] = idStiri[i];
	}

	//fisiere binare
	void writeToFile(fstream& f) {
		//scriere judet (string)
		int lungimeJudet = this->judet.length() + 1;
		f.write((char*)&lungimeJudet, sizeof(int));
		f.write(this->judet.data(), lungimeJudet * sizeof(char));
		
		//scriere localitate (char*)
		int lungimeLocalitate = strlen(this->localitate) + 1;
		f.write((char*)&lungimeLocalitate, sizeof(int));
		f.write((char*)this->localitate, lungimeLocalitate * sizeof(char));

		//scriere numar de studiouri (int)
		f.write((char*)&this->nrStudiouri, sizeof(int));

		//scriere nr de stiri (int)
		f.write((char*)&this->nrStiri, sizeof(int));

		//scriere id stiri (int)
		for (int i = 0; i < this->nrStiri; i++)
		{
			f.write((char*)&this->idStiri[i], sizeof(int));
		}
	}

	void readFromFile(fstream& f) {
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->judet = buffer;
		delete[] buffer;
		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		delete[] this->localitate;
		this->localitate = new char[strlen(buffer) + 1];
		strcpy(this->localitate, buffer);
		delete[] buffer;
		f.read((char*)&this->nrStudiouri, sizeof(int));
		f.read((char*)&this->nrStiri, sizeof(int));
		for (int i = 0; i < this->nrStiri; i++)
		{
			f.read((char*)&this->idStiri[i], sizeof(int));
		}
	}

	//afisare
	void afisare() {
		cout << "\n----------------------";
		cout << "\nJudet: " << judet;
		cout << "\nLocalitate: " << localitate;
		cout << "\nNumar Studiouri: " << nrStudiouri;
		cout << "\nNumar Stiri: " << nrStiri;
		cout << "\nID Stiri: ";
		for (int i = 0; i < nrStiri; i++)
			cout << idStiri[i] << " ; ";
		cout << "\n----------------------" << endl;
	}

	//get
	string getJudet() {
		return this->judet;
	}

	char* getLocalitate() {
		return this->localitate;
	}

	int getNrStudiouri() {
		return this->nrStudiouri;
	}

	int getNrStiri() {
		return this->nrStiri;
	}

	int getIdStire(int i) {
		return this->idStiri[i];
	}

	//set
	void setJudet(string judet) {
		if (judet != " ") {
			this->judet = judet;
		}
	}

	void setLocalitate(const char* localitate) {
		if (localitate != NULL) {
			delete[] this->localitate;
			this->localitate = new char[strlen(localitate) + 1];
			strcpy(this->localitate, localitate);
		}
	}

	void setNrStudiouri(int nrStudiouri) {
		if (nrStudiouri >= 0) {
			this->nrStudiouri = nrStudiouri;
		}
	}

	void setNrStiri(int nrStiri) {
		if (nrStiri >= 0) {
			this->nrStiri = nrStiri;
		}
	}

	void setIdStiri(int idStiri[10]) {
		if (this->nrStiri > 0) {
			for (int i = 0; i < this->nrStiri; i++) {
				if (idStiri[i] != NULL) {
					this->idStiri[i] = idStiri[i];
				}
				else {
					this->idStiri[i] = 0;
				}
			}
		}
	}

	//constructor de copiere
	Locatie(const Locatie& l) {
		//cout << "\nApel constructor de copiere";
		this->judet = l.judet;
		this->localitate = new char[strlen(l.localitate) + 1];
		strcpy(this->localitate, l.localitate);
		this->nrStudiouri = l.nrStudiouri;
		this->nrStiri = l.nrStiri;
		if (nrStiri >= 0 && idStiri != NULL) {
			for (int i = 0; i < l.nrStiri; i++) {
				this->idStiri[i] = l.idStiri[i];
			}
		}
	}

	//operator =
	Locatie& operator=(const Locatie& l) {
		//cout << "\nApel operator =";
		if (this != &l) {
			delete[] this->localitate;
			this->judet = l.judet;
			this->localitate = new char[strlen(l.localitate) + 1];
			strcpy(this->localitate, l.localitate);
			this->nrStudiouri = l.nrStudiouri;
			this->nrStiri = l.nrStiri;
			if (nrStiri >= 0) {
				for (int i = 0; i < l.nrStiri; i++) {
					this->idStiri[i] = l.idStiri[i];
				}
			}
			else {
				this->nrStiri = 0;
			}
		}
		return *this;
	}

	//operator -- pre incrementare; -1 nr studiouri
	Locatie& operator--() {
		this->nrStudiouri = this->nrStudiouri - 1;
		return *this;
	}

	//operator -- post incrementare; -1 nr studiouri
	Locatie operator--(int) {
		Locatie copie;
		copie = *this;
		this->nrStudiouri = this->nrStudiouri - 1;
		return copie;
	}

	//l + 2; nrstudiouri + 2;
	Locatie operator+ (int x) {
		Locatie copie;
		copie = *this;
		copie.nrStudiouri = copie.nrStudiouri + x;
		return copie;
	}

	//l1 + l2; nrstudiouri l1 + nrstudiouri l2;
	Locatie operator+ (Locatie l) {
		Locatie copie;
		copie = *this;
		copie.nrStudiouri = copie.nrStudiouri + l.nrStudiouri;
		return copie;
	}

	//cin
	friend istream& operator>> (istream& in, Locatie& l) {
		cout << "Judet: ";
		in >> l.judet;
		cout << "Localitate: ";
		char den[200];
		in.getline(den, 200);
		in.getline(den, 200);
		delete[] l.localitate;
		l.localitate = new char[strlen(den) + 1];
		strcpy(l.localitate, den);
		cout << "Numar Studiouri: ";
		in >> l.nrStudiouri;
		cout << "Numar Stiri: ";
		in >> l.nrStiri;
		for (int i = 0; i < l.nrStiri; i++)
		{
			cout << "ID Stire " << i + 1 << ": ";
			in >> l.idStiri[i];
		}
		return in;
	}

	//cout
	friend ostream& operator<<(ostream& out, const Locatie& l) {
		out << "\n-------------------------";
		out << "\nJudet: " << l.judet;
		out << "\nLocalitate: " << l.localitate;
		out << "\nNumar Studiouri: " << l.nrStudiouri;
		out << "\nNumar Stiri: " << l.nrStiri;
		out << "\nID Stiri: ";
		for (int i = 0; i < l.nrStiri; i++)
			cout << l.idStiri[i] << " ; ";
		out << "\n-------------------------";
		return out;
	}

	//operator de indexare
	int& operator[](int index) {
		index = index - 1;
		if (index >= 0 && index < this->nrStiri)
			return this->idStiri[index];
	}

	//cast explicit
	explicit operator int() {
		return this->nrStudiouri;
	}

	//operator negatie
	bool operator!() {
		if (this->nrStiri >= 0) {
			return true;
		}
		return false;
	}

	//operator <
	bool operator<(Locatie& l) {
		return this->nrStiri < l.nrStiri;
	}

	//operator ==
	friend int operator==(Locatie& x, Locatie& y) {
		if (x.judet != y.judet)
		{
			return 0;
		}
		if (strcmp(x.localitate, y.localitate) != 0)
		{
			return 0;
		}
		if (x.nrStudiouri != y.nrStudiouri)
		{
			return 0;
		}
		if (x.nrStiri != y.nrStiri)
		{
			return 0;
		}
		else
		{
			for (int i = 0; i < x.nrStiri; i++)
			{
				if (x.idStiri != y.idStiri)
				{
					return 0;
				}
			}
		}
		return 1;
	}

	//pentru CSV
	void CitireCSV(fstream& f) {
		string line;
		while (getline(f, line)) {
			stringstream lineStream(line);
			string cell;
			getline(lineStream, cell, ',');
			this->judet = cell; 
			getline(lineStream, cell, ',');
			delete[] this->localitate;
			this->localitate = new char[cell.size() + 1];
			strcpy(this->localitate, cell.c_str());
			getline(lineStream, cell, ',');
			this->nrStudiouri = stoi(cell);
			getline(lineStream, cell, ',');
			this->nrStiri = stoi(cell);
			for (int i = 0; i < this->nrStiri; i++) {
				getline(lineStream, cell, ',');
				this->idStiri[i] = stoi(cell);
			}
		}
	}

	//metoda prelucrare
	void adaugaStire(int idStire) {
		if (idStire > 0) {
			this->nrStiri++;
			this->idStiri[this->nrStiri - 1] = idStire;
		}
		else {
			cout << "\nNu se poate adauga" << endl;
		}
	}

	//destructor
	~Locatie() {
		delete[] this->localitate;
	}
};


//clasa 7
enum TIP {
	TELEVIZAT , LIVE, RADIO
};

class Studio: public IFile {
private:
	string locatieStudio;
	int nrAngajati;
	int nrCamere;
	float suprafataCamera[5]; //in metri patrati
	TIP tipStudio;
public:
	//constructor fara parametri
	Studio() {
		//cout << "\nApel constructor fara parametri STUDIO: ";
		locatieStudio = "Necunoscuta";
		nrAngajati = 0;
		nrCamere = 0;
		tipStudio = TIP::TELEVIZAT;
	}

	//constructor cu toti parametri
	Studio(string locatieStudio, int nrAngajati, int nrCamere, float suprafataCamera[5], TIP tipstudio) {
		//cout << "\nApel constructor cu toti parametri STUDIO: ";
		this->locatieStudio = locatieStudio;
		this->nrAngajati = nrAngajati;
		this->nrCamere = nrCamere;
		for (int i = 0; i < nrCamere; i++)
			this->suprafataCamera[i] = suprafataCamera[i];
		this->tipStudio = tipstudio;
	}

	//fisiere binare
	void writeToFile(fstream& f) {
		//scriere locatie studio (string)
		int lungimeLocatie = this->locatieStudio.length() + 1;
		f.write((char*)&lungimeLocatie, sizeof(int));
		f.write((char*)this->locatieStudio.data(), lungimeLocatie * sizeof(char));

		//scriere numar angajati (int)
		f.write((char*)&this->nrAngajati, sizeof(int));

		//scriere nr de camere (int)
		f.write((char*)&this->nrCamere, sizeof(int));

		//scriere suprafata camere (float)
		for (int i = 0; i < this->nrCamere; i++)
		{
			f.write((char*)&this->suprafataCamera[i], sizeof(float));
		}
		//scriere tip (TIP)
		int lungimeTip = this->getTipStudioString().length() + 1;
		f.write((char*)&lungimeTip, sizeof(int));
		f.write((char*)this->getTipStudioString().data(), lungimeTip * sizeof(char));
	}

	void readFromFile(fstream& f) {
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		f.read(buffer, lg);
		this->locatieStudio = buffer;
		delete[] buffer;
		f.read((char*)&this->nrAngajati, sizeof(int));
		f.read((char*)&this->nrCamere, sizeof(int));
		for (int i = 0; i < this->nrCamere; i++)
		{
			f.read((char*)&this->suprafataCamera[i], sizeof(float));
		}
		f.read((char*)&lg, sizeof(int));
		buffer = new char[lg];
		f.read(buffer, lg);
		string tip = buffer;
		delete[] buffer;
		setTipStudioString(tip);
	}

	//afisare
	void afisare() {
		cout << "\n-------------------------";
		cout << "\nLocatie studio: " << locatieStudio;
		cout << "\nNumar angajati: " << nrAngajati;
		cout << "\nNumar Camere: " << nrCamere;
		for (int i = 0; i < nrCamere; i++) {
			cout << "\nSuprafata camera " << i + 1 << ": " << suprafataCamera[i];
		}
		string tip;
		if (tipStudio == TIP::TELEVIZAT) {
			tip = "TELEVIZAT";
		}
		if (tipStudio == TIP::LIVE) {
			tip = "LIVE";
		}
		if (tipStudio == TIP::RADIO) {
			tip = "RADIO";
		}
		cout << "\nTip Studio: " << tip;
		cout << endl;
	}

	//get
	string getLocatieStudio() {
		return this->locatieStudio;
	}

	int getNrAngajati() {
		return this->nrAngajati;
	}

	int getNrCamere() {
		return this->nrCamere;
	}

	float getSuprafataCamera(int i) {
		return this->suprafataCamera[i];
	}

	TIP getTipStudio() {
		return this->tipStudio;
	}

	string getTipStudioString() {
		string tip;
		if (this->tipStudio==TIP::TELEVIZAT) {
			tip = "TELEVIZAT";
		}
		if (this->tipStudio == TIP::RADIO) {
			tip = "RADIO";
		}
		if (this->tipStudio == TIP::LIVE) {
			tip = "LIVE";
		}
		return tip;
	}

	//set
	void setLocatieStudio(string locatieStudio) {
		if (locatieStudio != " ") {
			this->locatieStudio = locatieStudio;
		}
	}

	void setNrAngajati(int nrAngajati) {
		if (nrAngajati > 0) {
			this->nrAngajati = nrAngajati;
		}
	}

	void setNrCamere(int nrCamere) {
		if (nrCamere > 0) {
			this->nrCamere = nrCamere;
		}
	}

	void setSuprafataCamere(float suprafataCamera[5]) {
		if (this->nrCamere > 0) {
			for (int i = 0; i < this->nrCamere; i++) {
				if (suprafataCamera[i] > 0)
					this->suprafataCamera[i] = suprafataCamera[i];
				else
					this->suprafataCamera[i] = 0;
			}
		}
	}

	void setTipStudio(TIP tipStudio) {
		if (tipStudio != NULL) {
			this->tipStudio = tipStudio;
		}
	}

	void setTipStudioString(string tip) {
		if (tip == "TELEVIZAT" || tip == "Televizat" || tip == "televizat") {
			this->tipStudio = TIP::TELEVIZAT;
		}
		if (tip == "LIVE" || tip == "Live" || tip == "live") {
			this->tipStudio = TIP::LIVE;
		}
		if (tip == "RADIO" || tip == "Radio" || tip == "radio") {
			this->tipStudio = TIP::RADIO;
		}
	}

	//constructor de copiere
	Studio(const Studio& s) {
		//cout << "\nApel constructor de copiere";
		this->locatieStudio = s.locatieStudio;
		this->nrAngajati = s.nrAngajati;
		this->nrCamere = s.nrCamere;
		if (nrCamere != 0 && suprafataCamera != NULL) {
			for (int i = 0; i < s.nrCamere; i++)
				this->suprafataCamera[i] = s.suprafataCamera[i];
		}
		this->tipStudio = s.tipStudio;
	}

	//operator =
	Studio& operator=(const Studio& s)
	{
		//cout << "\nApel operator = ";
		if (this != &s)
		{
			this->locatieStudio = s.locatieStudio;
			this->nrAngajati = s.nrAngajati;
			this->nrCamere = s.nrCamere;
			if (nrCamere != 0) {
				for (int i = 0; i < s.nrCamere; i++)
					this->suprafataCamera[i] = s.suprafataCamera[i];
			}
			else {
				this->nrCamere = 0;
			}
			this->tipStudio = s.tipStudio;
		}
		return *this;
	}

	//operator ++ pre Incrementare; +10 la nr angajati
	Studio& operator++() {
		this->nrAngajati = this->nrAngajati + 10;
		return *this;
	}

	//operator ++ post incrementare; +10 la nr angajati
	Studio operator++(int) {
		Studio copie;
		copie = *this;
		this->nrAngajati = this->nrAngajati + 10;
		return copie;
	}

	// s / 2; nr angajati / 2
	Studio operator/(int x) {
		Studio copie;
		copie = *this;
		copie.nrAngajati = copie.nrAngajati / x;
		return copie;
	}

	// s1 / s2; nr angajati s1 / nr angajati s2
	Studio operator / (Studio s) {
		Studio copie;
		copie = *this;
		copie.nrAngajati = copie.nrAngajati / s.nrAngajati;
		return copie;
	}

	//cin
	friend istream& operator>>(istream& in, Studio& s) {
		cout << "Locatie Studio: ";
		in >> s.locatieStudio;
		cout << "Numar Angajati: ";
		in >> s.nrAngajati;
		cout << "Numar Camere: ";
		in >> s.nrCamere;
		for (int i = 0; i < s.nrCamere; i++) {
			cout << "Suprafata camera " << i + 1 << ": ";
			in >> s.suprafataCamera[i];
		}
		cout << "Tip Studio: ";
		string tip;
		in >> tip;
		s.setTipStudioString(tip);
		return in;
	}

	//cout
	friend ostream& operator<<(ostream& out, const Studio& s) {
		out << "\n-------------------------";
		out << "\nLocatie studio: " << s.locatieStudio;
		out << "\nNumar angajati: " << s.nrAngajati;
		out << "\nNumar Camere: " << s.nrCamere;
		for (int i = 0; i < s.nrCamere; i++) {
			out << "\nSuprafata camera " << i + 1 << ": " << s.suprafataCamera[i];
		}
		string tip;
		if (s.tipStudio == TIP::TELEVIZAT) {
			tip = "TELEVIZAT";
		}
		if (s.tipStudio == TIP::LIVE) {
			tip = "LIVE";
		}
		if (s.tipStudio == TIP::RADIO) {
			tip = "RADIO";
		}
		out << "\nTip Studio: " << tip;
		return out;
	}

	//Operator de indexare
	float& operator[](int index) {
		index = index - 1;
		if (index >= 0 && index < this->nrCamere) {
			return this->suprafataCamera[index];
		}
	}

	//cast explicit
	explicit operator int() {
		return this->nrAngajati;
	}

	//operator negatie
	bool operator!() {
		if (this->nrCamere >= 0) {
			return true;
		}
		return false;
	}

	//Operator <
	bool operator<(Studio& s) {
		return this->nrAngajati < s.nrAngajati;
	}

	//Operator ==
	friend int operator==(Studio& x, Studio& y) {
		if (x.locatieStudio != y.locatieStudio)
		{
			return 0;
		}
		if (x.nrAngajati != y.nrAngajati)
		{
			return 0;
		}
		if (x.nrCamere != y.nrCamere)
		{
			return 0;
		}
		else
		{
			for (int i = 0; i < x.nrCamere; i++)
			{
				if (x.suprafataCamera[i] != y.suprafataCamera[i])
				{
					return 0;
				}
			}
		}
		if (x.tipStudio != y.tipStudio)
		{
			return 0;
		}
		return 1;
	}


	//metoda prelucrare
	void adaugaCamera(float suprafata) {
		if (suprafata >= 0) {
			this->nrCamere++;
			this->suprafataCamera[this->nrCamere - 1] = suprafata;
		}
		else
			cout << "Nu se poate adauga" << endl;
	}

	//raport suprafata totala
	int suprafataTotala()
	{
		ofstream g("suprafataTotala.txt");
		int suprafata = 0;
		for (int i = 0; i < this->nrCamere; i++)
		{
			if (this->suprafataCamera[i] > 0)
			{
				suprafata = suprafata + suprafataCamera[i];
				g << this->suprafataCamera[i] << " ; ";
			}
		}
		return suprafata;
	}

	//pentru CSV
	void CitireCSV(fstream& f) {
		string line;
		while (getline(f, line)) {
			stringstream lineStream(line);
			string cell;
			getline(lineStream, cell, ',');
			this->locatieStudio = cell;
			getline(lineStream, cell, ',');
			this->nrAngajati = stoi(cell);
			getline(lineStream, cell, ',');
			this->nrCamere = stoi(cell);
			for (int i = 0; i < this->nrCamere; i++) {
				getline(lineStream, cell, ',');
				this->suprafataCamera[i] = stof(cell);
			}
			getline(lineStream, cell, ',');
			setTipStudioString(cell);
		}
	}

	//destructor
	~Studio() {
		//nu am nimic alocat dinamic (de dezalocat)
	}

	
	//metoda virtuala
	virtual float suprafataMinima() {
		float sup_min = this->suprafataCamera[0];
		for (int i = 1; i < this->nrCamere; i++) {
			if (this->suprafataCamera[i] < sup_min)
				sup_min = this->suprafataCamera[i];
		}
		return sup_min;
	}

	friend class Cladire;
	
};


//clasa 8 - faza 3 - clasa pentru compunere - relatie has a
class Cladire { 
	int nrStudiouri = 0;
	float suprafataTotala = 0;
	Studio** listaStudiouri = NULL;
public:
	Cladire() {
		//cout << "\nCONSTRUCTOR FARA PARAM CATALOG CLADIRE";
	}
	Cladire(int nrStudiouri, float suprafataTotala, Studio** listaStudiouri) {
		//cout << "\nCONSTRUCTOR CU PARAM CATALOG CLADIRE";
		if (nrStudiouri > 0 && listaStudiouri != NULL) {
			this->nrStudiouri = nrStudiouri;
			this->listaStudiouri = new Studio * [this->nrStudiouri];
			//deep copy
			for (int i = 0; i < this->nrStudiouri; i++)
				this->listaStudiouri[i] = new Studio(*listaStudiouri[i]);
		}
	}

	Cladire(const Cladire& c) {
		//cout << "\nCONSTRUCTOR COPIERE CATALOG CLADIRI";
		if (nrStudiouri > 0 && c.listaStudiouri != NULL) {
			this->nrStudiouri = c.nrStudiouri;
			this->listaStudiouri = new Studio * [this->nrStudiouri];
			for (int i = 0; i < this->nrStudiouri; i++)
				this->listaStudiouri[i] = new Studio(*c.listaStudiouri[i]); //am alocat cate un studio pe fiecare pozitie in parte
		}
	}

	Cladire& operator=(const Cladire& c) {
		//cout << "\nOPERATOR = CLADIRI";
		if (this != &c) {
			for (int i = 0; i < this->nrStudiouri; i++)
				delete this->listaStudiouri[i];
			delete this->listaStudiouri;
			if (nrStudiouri > 0 && c.listaStudiouri != NULL) {
				this->nrStudiouri = c.nrStudiouri;
				this->listaStudiouri = new Studio * [this->nrStudiouri];
				for (int i = 0; i < this->nrStudiouri; i++)
					this->listaStudiouri[i] = new Studio(*c.listaStudiouri[i]);
			}
			else {
				this->listaStudiouri = NULL;
				this->nrStudiouri = 0;
			}
		}
		return *this;
	}

	~Cladire() {
		for (int i = 0; i < this->nrStudiouri; i++)
			delete this->listaStudiouri[i];
		delete this->listaStudiouri;
	}

	friend ostream& operator<<(ostream& out, const Cladire& c) {
		out << "\nNumar studiouri: " << c.nrStudiouri;
		out << "\Lista studiouri: ";
		for (int i = 0; i < c.nrStudiouri; i++) {
			out << *c.listaStudiouri[i];
		}
		return out;
	}

	//operator functie
	int operator()(int suprafataMaxima) {
		//contor = contor
		int contor = 0;
		for (int i = 0; i < this->nrStudiouri; i++)
			for (int j = 0; j < this->listaStudiouri[i]->nrCamere; j++) {
				if (this->listaStudiouri[i]->suprafataCamera[j] >= suprafataMaxima)
					contor++;
			}
		return contor;
	}
};


//clasa 10 - CLASA SITE - clasa colectiv
template <class TIP>
class siteStiri {
	int nrStirilor = 0;
	TIP* listaStiri = NULL;

public:
	siteStiri() {}
	siteStiri(int nrStirilor, TIP* listaStiri) {
		if (nrStirilor > 0 && listaStiri != NULL) {
			this->nrStirilor = nrStirilor;
			this->listaStiri = new TIP[this->nrStirilor];
			for (int i = 0; i < this->nrStirilor; i++) {
				this->listaStiri[i] = listaStiri[i];
			}
		}
	}

	siteStiri(const siteStiri& c) {
		if (c.nrStirilor > 0 && c.listaStiri != NULL) {
			this->nrStirilor = c.nrStirilor;
			this->listaStiri = new TIP[this->listaStiri];
			for (int i = 0; i < this->nrStirilor; i++) {
				this->listaStiri[i] = c.listaStiri[i];
			}
		}
	}

	siteStiri& operator=(const siteStiri& c) {
		if (this != &c) {
			delete[] this->listaStiri;
			this->nrStirilor = c.nrStirilor;
			this->listaStiri = new TIP[this->listaStiri];
			for (int i = 0; i < this->nrStirilor; i++)
				this->listaStiri[i] = c.listaStiri[i];
		}
		return *this;
	}

	~siteStiri() {
		delete[] this->listaStiri;
	}

	friend ostream& operator<<(ostream& out, const siteStiri& c) {
		out << "\nNr obiecte: " << c.nrStirilor;
		out << "\nLista obiecte: ";
		for (int i = 0; i < c.nrStirilor; i++)
			out << c.listaStiri[i] << " ";
		return out;
	}
};




int main() {
	char heart = 3;


	//FAZA 1

	
	//***********************************************************************************************
	//CLASA 1 - STIRE
	cout << "* * * PENTRU CLASA STIRE * * *" << endl;
	//constructor fara parametri
	cout << "\n* Constructor fara parametri *";
	Stire s;
	s.afisare();

	//constructor cu un parametru
	cout << "\n* Constructor cu un parametru *";
	Stire s1(1);
	s1.afisare();

	//constructor cu toti parametri
	cout << "\n* Constructor cu toti parametri *";
	float vectorRatinguri[4] = {4, 2, 5, 3.2};
	Stire s2(2, "Incep targurile de Craciun", "Pitesti", 1, 1, 1, 1, 2508.7, true, 4, vectorRatinguri);
	s2.afisare();

	//operator =
	cout << "\n* Operator '=' *";
	Stire s3(3);
	s3 = s2;
	s3.afisare();

	//operator +
	cout << "\n* Operator '+' *";
	cout << s3 + 20000;

	//constructor de copiere
	cout << "\n* Constructor de copiere *";
	Stire s4(s3);
	s4.afisare();

	//metoda prelucrare - adaugare rating
	cout << "\n* Metoda prelucrare - adaugare rating *";
	s4.adaugaRating(5);
	s4.afisare();

	//citire si afisare
	cout << "\n* Citire si afisare *" << endl;
	Stire s5;
	cin >> s5;
	cout << s5;

	//operator ==
	cout << "\n* Operator '==' *" << endl;
	if (s3 == s2)
		cout << "Sunt egale\n";
	else
		cout << "Nu sunt egale\n";

	//operator >=
	cout << "\n* Operator '>=' *";
	if (s1 >= s2)
		cout << "\nBugetul stirii 1 >= Bugetul stirii 2" << endl;
	else
		cout << "\nBugetul stirii 2 >= Bugetul stirii 1" << endl;

	//operator de indexare
	cout << "\n* Operator de indexare *";
	float rating = s3[1];
	cout << "\nPrimul rating al stirii: " << rating;

	s3[1] = 4;
	s3.afisare();
	cout << endl;

	//operator ++
	cout << "\n* Operator '++' *";
	s1 = ++s3; //++ e prioritar lui =, returneaza obiectul actualizat
	s1.afisare();
	s3.afisare();

	s1 = s3++; //++ e prioritar lui =, afiseaza starea anterioara incrementarii
	s1.afisare();
	s3.afisare();
	cout << endl;

	//operator cast (conversia)
	cout << "\n* Operator cast *";
	float bugetul = (float)s3;
	cout << endl << "Bugetul: " << bugetul << endl;

	//operator ! (negatie)
	cout << "\n* Operator '!' *";
	if (!s3)
		cout << "\nStirea s3 are ratinguri" << endl;
	else
		cout << "\nStirea s3 nu are ratinguri" << endl;
	


	//***********************************************************************************************
	//CLASA 2 - REPORTER
	cout << endl << endl;
	cout << heart << "         " << heart << "         " << heart <<  "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         "  << heart;
	cout << "\n* * * PENTRU CLASA REPORTER * * *" << endl;
	//constructor fara parametri
	cout << "\n* Constructor fara parametri *";
	Reporter r;
	cout << r;

	//constructor cu un parametru
	cout << "\n* Constructor cu un parametru *"; 
	Reporter r1(1);
	cout << r1;

	//constructor cu toti parametri
	cout << "\n* Constructor cu toti parametri *";
	float vectorPlata[3] = { 55, 2.5, 6 };
	int vectorColegiReporter[3] = { 1, 5, 7 };
	Reporter r2(2, "Popescu Vasile", 25, "Arges", 3, vectorPlata , 3, vectorColegiReporter, "5040302847463", 12, 35.6);
	cout << r2;

	//operator =
	cout << "\n* Operator '=' *";
	Reporter r3(3);
	r3 = r2;
	cout << r3;

	//operator -
	cout << "\n* Operator '-' *";
	cout << r3 - 2;

	//constructor de copiere
	cout << "\n* Constructor de copiere *";
	Reporter r4(r3);
	r4.afisare();

	//metoda prelucrare - adaugare plata stire
	cout << "\n* Metoda prelucrare - adaugare plata stire *";
	r4.adaugaPlataStire(20);
	r4.afisare();

	//citire si afisare
	cout << "\n* Citire si afisare *" << endl;
	Reporter r5;
	cin >> r5;
	cout << r5;

	//operator ==
	cout << "\n* Operator '==' *" << endl;
	if (r3 == r2)
		cout << "Sunt egali\n";
	else
		cout << "Nu sunt egali\n";

	//operator <=
	cout << "\n* Operator '<=' *";
	if (r1 <= r2)
		cout << "\nReporterul 1 are experienta <= decat experienta reporterului 2" << endl;
	else
		cout << "\nReporterul 2 are experienta <= decat experienta reporterului 1" << endl;

	//operator de indexare
	cout << "\n* Operator de indexare *";
	float plataStiri = r3[1];
	cout << "\nPlata primei stiri: " << plataStiri;

	r3[1] = 1400;
	r3.afisare();
	cout << endl;

	//operator --
	cout << "\n* Operator '--' *";
	r1 = --r3; //-- e prioritar lui =, returneaza obiectul actualizat
	r1.afisare();
	r3.afisare();

	r3--;
	r1 = r3; //-- e prioritar lui =, afiseaza starea anterioara incrementarii
	r1.afisare();
	r3.afisare();
	cout << endl;

	//operator cast (conversia)
	cout << "\n* Operator cast *";
	int exper = (int)r3;
	cout << endl << "Experienta: " << exper << endl;

	//operator ! (negatie)
	cout << "\n* Operator '!' *";
	if (!r3)
		cout << "\nReporterul 3 a realizat stiri" << endl;
	else
		cout << "\nReporterul 3 nu a realizat stiri" << endl;
	


	//***********************************************************************************************
	//CLASA 3 - OPERATOR
	cout << endl << endl;
	cout << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart;
	cout << "\n* * * PENTRU CLASA OPERATOR * * *" << endl;
	//constructor fara parametri
	cout << "\n* Constructor fara parametri *";
	Operator o;
	cout << o;

	//constructor cu un parametru
	cout << "\n* Constructor cu un parametru *";
	Operator o1(1);
	cout << o1;

	//constructor cu toti parametri
	cout << "\n* Constructor cu toti parametri *";
	int vectorColegiOperator[3] = { 3,7,4 };
	Operator o2(2, "Ion Mihai", 10, "Olt", 1250.5, 3, vectorColegiOperator, "5051285738273", 7, 12.2);
	cout << o2;

	//operator =
	cout << "\n* Operator '=' *";
	Operator o3(3);
	o3 = o2;
	cout << o3;

	//operator *
	cout << "\n* Operator '*' *";
	cout << o3 * 2;

	//constructor de copiere
	cout << "\n* Constructor de copiere *";
	Operator o4(o3);
	o4.afisare();

	//metoda prelucrare - sterge un coleg de munca
	cout << "\n* Metoda prelucrare - sterge un coleg de munca *";
	o4.stergeColeg(2);
	o4.afisare();

	//citire si afisare
	cout << "\n* Citire si afisare *" << endl;
	Operator o5;
	cin >> o5;
	cout << o5;

	//operator ==
	cout << "\n* Operator '==' *" << endl;
	if (o3 == o2)
		cout << "Sunt egali\n";
	else
		cout << "Nu sunt egali\n";

	//operator <
	cout << "\n* Operator '<' *";
	if (o1 < o2)
		cout << "\nOperatorul 1 are salariul lunar < decat salariul lunar operatorul 2" << endl;
	else
		cout << "\nOperatorul 2 are salariul lunar < decat salariul lunar operatorul 1" << endl;

	//operator de indexare
	cout << "\n* Operator de indexare *";
	int idColeg = o3[2];
	cout << "\nId coleg: " << idColeg;

	o3[2] = 3;
	o3.afisare();
	cout << endl;

	//operator ++
	cout << "\n* Operator '++' *";
	o1 = ++o3; //++ e prioritar lui =, returneaza obiectul actualizat
	o1.afisare();
	o3.afisare();

	o3++;
	o1 = o3; //++ e prioritar lui =, afiseaza starea anterioara incrementarii
	o1.afisare();
	o3.afisare();
	cout << endl;

	//operator cast (conversia)
	cout << "\n* Operator cast *" << endl;
	int salariuLunar = (int)o3;
	cout << "Salariul lunar: " << salariuLunar << endl;

	//operator ! (negatie)
	cout << "\n* Operator '!' *";
	if (!o3)
		cout << "\nOperatorul 3 are experienta" << endl;
	else
		cout << "\nOperatorul 3 nu are experienta" << endl;

	


	//***********************************************************************************************
	//CLASA 4 - EDITOR
	cout << endl << endl;
	cout << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart;
	cout << "\n* * * PENTRU CLASA EDITOR * * *" << endl;
	//constructor fara parametri
	cout << "\n* Constructor fara parametri *";
	Editor e;
	cout << e;

	//constructor cu un parametru
	cout << "\n* Constructor cu un parametru *";
	Editor e1(1);
	cout << e1;

	//constructor cu toti parametri
	cout << "\n* Constructor cu toti parametri *";
	int vectorColegiEditor[1] = { 2 };
	Editor e2(2, "Sandu Andreea", 4, "Ilfov", 950.2, 1, vectorColegiEditor, "6040308374628", 6, 76.3);
	cout << e2;

	//operator =
	cout << "\n* Operator '=' *";
	Editor e3(3);
	e3 = e2;
	cout << e3;

	//operator /
	cout << "\n* Operator '/' *";
	cout << e3 / 2;

	//constructor de copiere
	cout << "\n* Constructor de copiere *";
	Editor e4(e3);
	e4.afisare();

	//metoda prelucrare - sterge un coleg de munca
	cout << "\n* Metoda prelucrare - sterge un coleg de munca *";
	e4.stergeColeg(2);
	e4.afisare();

	//citire si afisare
	cout << "\n* Citire si afisare *" << endl;
	Editor e5;
	cin >> e5;
	cout << e5;

	//operator ==
	cout << "\n* Operator '==' *" << endl;
	if (e3 == e2)
		cout << "Sunt egali\n";
	else
		cout << "Nu sunt egali\n";

	//operator <
	cout << "\n* Operator '<' *";
	if (e1 < e2)
		cout << "\nEditorul 1 are salariul lunar < decat salariul lunar editorul 2" << endl;
	else
		cout << "\nEditorul 2 are salariul lunar < decat salariul lunar editorul 1" << endl;

	//operator de indexare
	cout << "\n* Operator de indexare *";
	int idulColegului = e3[1];
	cout << "\nId coleg: " << idColeg;

	e3[1] = 5;
	e3.afisare();
	cout << endl;

	//operator --
	cout << "\n* Operator '--' *";
	e1 = --e3; //-- e prioritar lui =, returneaza obiectul actualizat
	e1.afisare();
	e3.afisare();

	e3--;
	e1 = e3;
	e1.afisare();
	e3.afisare();
	cout << endl;

	//operator cast (conversia)
	cout << "\n* Operator cast *" << endl;
	int salariulLunar = (int)e3;
	cout << "Salariul lunar: " << salariuLunar << endl;

	//operator ! (negatie)
	cout << "\n* Operator '!' *";
	if (!e3)
		cout << "\nEditorul 3 are experienta" << endl;
	else
		cout << "\nEditorul 3 nu are experienta" << endl;
	


	//***********************************************************************************************
	//CLASA 5 - SUNETIST
	cout << endl << endl;
	cout << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart;
	cout << "\n* * * PENTRU CLASA SUNETIST * * *" << endl;
	//constructor fara parametri
	cout << "\n* Constructor fara parametri *";
	Sunetist su;
	cout << su;

	//constructor cu un parametru
	cout << "\n* Constructor cu un parametru *";
	Sunetist su1(1);
	cout << su1;

	//constructor cu toti parametri
	cout << "\n* Constructor cu toti parametri *";
	int vectorColegiSunetist[4] = { 2,3,6,4 };
	Sunetist su2(2, "Cojocaru Alina", 70, "Covasna", 2000, 4, vectorColegiSunetist, "6041234274857", 3, 88.8);
	cout << su2;

	//operator =
	cout << "\n* Operator '=' *";
	Sunetist su3(3);
	su3 = su2;
	cout << su3;

	//operator /
	cout << "\n* Operator '/' *";
	cout << su3 / 2;

	//constructor de copiere
	cout << "\n* Constructor de copiere *";
	Sunetist su4(su3);
	su4.afisare();

	//metoda prelucrare - sterge un coleg de munca
	cout << "\n* Metoda prelucrare - sterge un coleg de munca *";
	su4.stergeColeg(2);
	su4.afisare();

	//citire si afisare
	cout << "\n* Citire si afisare *" << endl;
	Sunetist su5;
	cin >> su5;
	cout << su5;

	//operator ==
	cout << "\n* Operator '==' *" << endl;
	if (su3 == su2)
		cout << "Sunt egali\n";
	else
		cout << "Nu sunt egali\n";

	//operator <
	cout << "\n* Operator '<' *";
	if (su1 < su2)
		cout << "\nSunetistul 1 are salariul lunar < decat salariul lunar sunetistul 3" << endl;
	else
		cout << "\nSunetistul 3 are salariul lunar < decat salariul lunar sunetistul 1" << endl;

	//operator de indexare
	cout << "\n* Operator de indexare *";
	int idulColeg = su3[3];
	cout << "\nId coleg: " << idColeg;

	su3[3] = 3;
	su3.afisare();
	cout << endl;

	//operator ++
	cout << "\n* Operator '++' *";
	su1 = ++su3; //++ e prioritar lui =, returneaza obiectul actualizat
	su1.afisare();
	su3.afisare();

	su3++;
	su1 = su3;
	su1.afisare();
	su3.afisare();
	cout << endl;

	//operator cast (conversia)
	cout << "\n* Operator cast *" << endl;
	int salariuPerLuna = (int)su3;
	cout << "Salariul lunar: " << salariuLunar << endl;

	//operator ! (negatie)
	cout << "\n* Operator '!' *";
	if (!su3)
		cout << "\nSunetistul 3 are experienta" << endl;
	else
		cout << "\nSunetistul 3 nu are experienta" << endl;
	


	//***********************************************************************************************
	//CLASA 6 - LOCATIE
	cout << endl << endl;
	cout << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart;
	cout << "\n* * * PENTRU CLASA LOCATIE * * *" << endl;
	//constructor fara parametri
	cout << "\n* Constructor fara parametri *";
	Locatie l1;
	l1.afisare();

	//constructor cu toti parametri
	cout << "\n* Constructor cu toti parametri *";
	int vectorIdStiri[5] = { 1, 2, 3, 4, 5 };
	Locatie l2("Arges", "Pitesti", 3, 5, vectorIdStiri);
	l2.afisare();

	//operator =
	cout << "\n* Operator '=' *";
	Locatie l3;
	l3 = l2;
	l3.afisare();

	//operator +
	cout << "\n* Operator '+' *";
	cout << l3 + 2 << endl;

	//constructor de copiere
	cout << "\n* Constructor de copiere *";
	Locatie l4(l3);
	l4.afisare();

	//metoda prelucrare - adaugare stire
	cout << "\n* Metoda prelucrare - adaugare stire *";
	l4.adaugaStire(6);
	l4.afisare();

	//citire si afisare
	cout << "\n* Citire si afisare *" << endl;
	Locatie l5;
	cin >> l5;
	cout << l5 << endl;

	//operator ==
	cout << "\n* Operator '==' *" << endl;
	if (l3 == l2)
		cout << "Sunt identice\n";
	else
		cout << "Nu sunt identice\n";

	//operator <
	cout << "\n* Operator '<' *";
	if (l2 < l3)
		cout << "\nNumarul de stiri din locatia 2 < numarul de stiri din locatia 3" << endl;
	else
		cout << "\nNumarul de stiri din locatia 3 < numarul de stiri din locatia 2" << endl;

	//operator de indexare
	cout << "\n* Operator de indexare *";
	int nrStiri = l3[2];
	cout << "\nNumar de stiri: " << nrStiri;

	l3[2] = 5;
	l3.afisare();
	cout << endl;

	//operator --
	cout << "\n* Operator '--' *";
	l1 = --l3; //-- e prioritar lui =, returneaza obiectul actualizat
	l1.afisare();
	l3.afisare();

	l3--;
	l1 = l3;
	l1.afisare();
	l3.afisare();
	cout << endl;

	//operator cast (conversia)
	cout << "\n* Operator cast *" << endl;
	int nrStudiouri = (int)l3;
	cout << "Numarul de studiouri: " << nrStudiouri << endl;

	//operator ! (negatie)
	cout << "\n* Operator '!' *";
	if (!l3)
		cout << "\nLocatia 3 are stiri realizate" << endl;
	else
		cout << "\nLocatia 3 nu are stiri realizate" << endl;
	


	//***********************************************************************************************
	//CLASA 7 - STUDIO
	cout << endl << endl;
	cout << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart;
	cout << "\n* * * PENTRU CLASA STUDIO * * *" << endl;
	//constructor fara parametri
	cout << "\n* Constructor fara parametri *";
	Studio st1;
	st1.afisare();

	//constructor cu toti parametri
	cout << "\n* Constructor cu toti parametri *";
	float vectorDimensiune[2] = { 32.2, 14 };
	Studio st2("Bucuresti", 3, 2, vectorDimensiune, TELEVIZAT);
	st2.afisare();

	//operator =
	cout << "\n* Operator '=' *";
	Studio st3;
	st3 = st2;
	st3.afisare();

	//operator /
	cout << "\n* Operator '/' *";
	cout << st3 / 2 << endl;

	//constructor de copiere
	cout << "\n* Constructor de copiere *";
	Studio st4(st3);
	st4.afisare();

	//metoda prelucrare - adaugare camera
	cout << "\n* Metoda prelucrare - adaugare camera *";
	st4.adaugaCamera(12);
	st4.afisare();

	//citire si afisare
	cout << "\n* Citire si afisare *" << endl;
	Studio st5;
	cin >> st5;
	cout << st5 << endl;

	//operator ==
	cout << "\n* Operator '==' *" << endl;
	if (st3 == st2)
		cout << "Sunt identice\n";
	else
		cout << "Nu sunt identice\n";

	//operator <
	cout << "\n* Operator '<' *";
	if (st2 < st3)
		cout << "\nNumarul de angajati din studioul 2 < numarul de angajati din studioul 3" << endl;
	else
		cout << "\nNumarul de angajati din studioul 3 < numarul de angajati din studioul 2" << endl;

	//operator de indexare
	cout << "\n* Operator de indexare *";
	int nrCamere = st3[1];
	cout << "\nNr camere: " << nrCamere;

	st3[1] = 3;
	st3.afisare();
	cout << endl;

	//operator ++
	cout << "\n* Operator '++' *";
	st1 = ++st3; //++ e prioritar lui =, returneaza obiectul actualizat
	st1.afisare();
	st3.afisare();

	st1 = st3++; //++ e prioritar lui =, afiseaza starea anterioara incrementarii
	st1.afisare();
	st3.afisare();
	cout << endl;

	//operator cast (conversia)
	cout << "\n* Operator cast *" << endl;
	int nrAngajati = (int)st3;
	cout << "Numar angajati: " << nrAngajati << endl;

	//operator ! (negatie)
	cout << "\n* Operator '!' *";
	if (!st3)
		cout << "\nStudioul 3 are camere" << endl;
	else
		cout << "\nStudioul 3 nu are camere" << endl;






	cout << endl << endl;
	cout << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart << "         " << heart;

	//***********************************************************************************************
	//FAZA 2 + FAZA 3
	
	//meniu + rapoarte + fisiere text + fisiere binare + librarie STL + fisere CSV
	int alegere;
	Stire stireMeniu;
	Reporter reporterMeniu;
	Operator operatorMeniu;
	Editor editorMeniu;
	Sunetist sunetistMeniu;
	Locatie locatieMeniu;
	Studio studioMeniu;
	float v1[4] = { 4,2,5,3.2 };
	float v2[2] = { 3.3, 1 };
	float v3[3] = { 3, 1.7, 2.5 };
	ofstream datamine("dataMining.txt");
	time_t now;
	do {
		cout << "\nBuna! " << heart << " Verifica lista urmatoare de optiuni : \n" << endl
			<< " 0 - Populare.\n"
			<< " 1 - Aleg sa modific o STIRE.\n"
			<< " 2 - Aleg sa modific un REPORTER.\n"
			<< " 3 - Aleg sa modific un OPERATOR.\n"
			<< " 4 - Aleg sa modific un EDITOR.\n"
			<< " 5 - Aleg sa modific un SUNETIST.\n"
			<< " 6 - Aleg sa modific o LOCATIE.\n"
			<< " 7 - Aleg sa modific un STUDIO.\n"
			<< " 8 - Afisare clase.\n"
			<< " 9 - Operatiuni asupra claselor.\n"
			<< " 10 - Realizarea de rapoarte.\n"
			<< " 11 - Fisiere binare.\n"
			<< " 12 - Librarie STL.\n"
			<< " 13 - Fisiere CSV.\n"
			<< " 14 - Iesire.\n"
			<< "\nAlege o optiune prin selectia unui numar si apasa tasta ENTER ----> ";
		cin >> alegere;

		switch (alegere)
		{
		//********************************************************************************************
		case 0:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales populare" << " -> " << ctime(&now) << endl;
			cout << "Alegeti ce clasa doriti sa populati:\n1. Stire \n2. Reporter \n3. Operator \n4. Editor \n5. Sunetist \n6. Locatie \n7. Studio " << endl;
			cin >> optiune;
			if (optiune <= 7 && optiune >= 1)
			{
				if (optiune == 1)
				{
					int ok;
					now = time(0);
					datamine << "Utilizatorul a ales popularea clasei STIRE" << " -> " << ctime(&now) << endl;
					cout << "Alegeti metoda de populare: \n1. Din fisier \n2. De la tastatura " << endl;
					cin >> ok;
					if (ok == 1)
					{
						string fisier;
						cout << "Scrieti numele fisierului (stiri.txt):";
						cin >> fisier;
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei STIRE din fisier" << " -> " << ctime(&now) << endl;
						ifstream fisierStiri(fisier);
						fisierStiri >> stireMeniu;
					}
					if (ok == 2)
					{
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei STIRE de la tastatura" << " -> " << ctime(&now) << endl;
						cin.get();
						cin >> stireMeniu;
					}
				}
				if (optiune == 2)
				{
					int ok;
					now = time(0);
					datamine << "Utilizatorul a ales popularea clasei REPORTER" << " -> " << ctime(&now) << endl;
					cout << "Alegeti metoda de populare: \n1. Din fisier \n2. De la tastatura " << endl;
					cin >> ok;
					if (ok == 1)
					{
						string fisier;
						cout << "Scrieti numele fisierului (reporteri.txt):";
						cin >> fisier;
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei REPORTER de la tastatura" << " -> " << ctime(&now) << endl;
						ifstream fisierReporter(fisier);
						fisierReporter >> reporterMeniu;
					}
					if (ok == 2)
					{
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei REPORTER din fisier" << " -> " << ctime(&now) << endl;
						cin.get();
						cin >> reporterMeniu;
					}
				}
				if (optiune == 3)
				{
					int ok;
					now = time(0);
					datamine << "Utilizatorul a ales popularea clasei OPERATOR" << " -> " << ctime(&now) << endl;
					cout << "Alegeti metoda de populare: \n1. Din fisier \n2. De la tastatura " << endl;
					cin >> ok;
					if (ok == 1)
					{
						string fisier;
						cout << "Scrieti numele fisierului (operatori.txt):";
						cin >> fisier;
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei OPERATOR de la tastatura" << " -> " << ctime(&now) << endl;
						ifstream fisierOperator(fisier);
						fisierOperator >> operatorMeniu;
					}
					if (ok == 2)
					{
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei OPERATOR din fisier" << " -> " << ctime(&now) << endl;
						cin.get();
						cin >> operatorMeniu;
					}
				}
				if (optiune == 4)
				{
					now = time(0);
					datamine << "Utilizatorul a ales popularea clasei EDITOR" << " -> " << ctime(&now) << endl;
					int ok;
					cout << "Alegeti metoda de populare: \n1. Din fisier \n2. De la tastatura " << endl;
					cin >> ok;
					if (ok == 1)
					{
						string fisier;
						cout << "Scrieti numele fisierului (editori.txt):";
						cin >> fisier;
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei EDITOR de la tastatura" << " -> " << ctime(&now) << endl;
						ifstream fisierEditor(fisier);
						fisierEditor >> editorMeniu;
					}
					if (ok == 2)
					{
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei EDITOR din fisier" << " -> " << ctime(&now) << endl;
						cin.get();
						cin >> editorMeniu;
					}
				}
				if (optiune == 5)
				{
					int ok;
					now = time(0);
					datamine << "Utilizatorul a ales popularea clasei SUNETIST" << " -> " << ctime(&now) << endl;
					cout << "Alegeti metoda de populare: \n1. Din fisier \n2. De la tastatura " << endl;
					cin >> ok;
					if (ok == 1)
					{
						string fisier;
						cout << "Scrieti numele fisierului (sunetisti.txt):";
						cin >> fisier;
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei SUNETIST de la tastatura" << " -> " << ctime(&now) << endl;
						ifstream fisierSunetist(fisier);
						fisierSunetist >> sunetistMeniu;
					}
					if (ok == 2)
					{
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei SUNETIST din fisier" << " -> " << ctime(&now) << endl;
						cin.get();
						cin >> sunetistMeniu;
					}
				}
				if (optiune == 6)
				{
					now = time(0);
					datamine << "Utilizatorul a ales popularea clasei LOCATII" << " -> " << ctime(&now) << endl;
					int ok;
					cout << "Alegeti metoda de populare: \n1. Din fisier \n2. De la tastatura " << endl;
					cin >> ok;
					if (ok == 1)
					{
						string fisier;
						cout << "Scrieti numele fisierului (locatii.txt):";
						cin >> fisier;
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei LOCATII de la tastatura" << " -> " << ctime(&now) << endl;
						ifstream fisierLocatie(fisier);
						fisierLocatie >> locatieMeniu;
					}
					if (ok == 2)
					{
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei LOCATII din fisier" << " -> " << ctime(&now) << endl;
						cin >> locatieMeniu;
					}
				}
				if (optiune == 7)
				{
					int ok;
					now = time(0);
					datamine << "Utilizatorul a ales popularea clasei STUDIOURI" << " -> " << ctime(&now) << endl;
					cout << "Alegeti metoda de populare: \n1. Din fisier \n2. De la tastatura " << endl;
					cin >> ok;

					if (ok == 1)
					{
						string fisier;
						cout << "Scrieti numele fisierului (studiouri.txt):";
						cin >> fisier;
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei STUDIOURI de la statatura" << " -> " << ctime(&now) << endl;
						ifstream fisierStudio(fisier);
						fisierStudio >> studioMeniu;
					}
					if (ok == 2)
					{
						now = time(0);
						datamine << "Utilizatorul a ales popularea clasei STUDIOURI din fisier" << " -> " << ctime(&now) << endl;
						cin >> studioMeniu;
					}
				}

			}
			break;
		}

		//********************************************************************************************
		case 1:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales moficarea clasei STIRE" << " -> " << ctime(&now) << endl;
			cout << "";
			cout << "Alegeti ce doriti sa modificati din clasa STIRE:\n1. Numarul stirilor;\n2. Subiectul;\n3. Locatia;\n4. ID-ul reporterului;\n5. ID-ul operatorului;\n6. ID-ul editorului;\n7. ID-ul sunetistului;\n8. Bugetul;\n9. Daca este sau nu BreakingNews;\n10. ID-ul reporterului;\n11.Numarul de ratinguri;\n12. Ratingurile;" << endl;
			cin >> optiune;
			if (optiune == 1)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de stiri din clasa STIRE" << " -> " << ctime(&now) << endl;
				int newNrStiri;
				cout << "\nAlegeti un nou numar de Stiri: ";
				cin >> newNrStiri;
				stireMeniu.setNrStiri(newNrStiri);
				cout << "\nModificarea a fost un succes.";
			}
			if (optiune == 2)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea subiectului din clasa STIRE" << " -> " << ctime(&now) << endl;
				char newSubiect[200];
				cout << "\nAlegeti un nou Subiect pentru Stire: ";
				cin.getline(newSubiect, 200);
				stireMeniu.setSubiect(newSubiect);
			}
			if (optiune == 3)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea locatiei din clasa STIRE" << " -> " << ctime(&now) << endl;
				string newLocatie;
				cout << "\nAlegeti o noua locatie pentru Stire: ";
				cin >> newLocatie;
				stireMeniu.setLocatie(newLocatie);
			}
			if (optiune == 4)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea ID-ului reporter din clasa STIRE" << " -> " << ctime(&now) << endl;
				int newIdReporter;
				cout << "\nAlegeti un nou Id Reporter pentru Stire: ";
				cin >> newIdReporter;
				stireMeniu.setIdReporter(newIdReporter);
			}
			if (optiune == 5)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea ID-ului operator din clasa STIRE" << " -> " << ctime(&now) << endl;
				int newIdOperator;
				cout << "\nAlegeti un nou Id Operator pentru Stire: ";
				cin >> newIdOperator;
				stireMeniu.setIdOperator(newIdOperator);
			}
			if (optiune == 6)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea ID-ului editor din clasa STIRE" << " -> " << ctime(&now) << endl;
				int newIdEditor;
				cout << "\nAlegeti un nou Id Editor pentru Stire: ";
				cin >> newIdEditor;
				stireMeniu.setIdEditor(newIdEditor);
			}
			if (optiune == 7)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea ID-ului sunetist din clasa STIRE" << " -> " << ctime(&now) << endl;
				int newIdSunetist;
				cout << "\nAlegeti un nou Id Sunetist pentru Stire: ";
				cin >> newIdSunetist;
				stireMeniu.setIdSunetist(newIdSunetist);
			}
			if (optiune == 8)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea bugetului din clasa STIRE" << " -> " << ctime(&now) << endl;
				float newBuget;
				cout << "\nAlegeti un nou Buget pentru Stire: ";
				cin >> newBuget;
				stireMeniu.setBuget(newBuget);
			}
			if (optiune == 9)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea importantei stirii (BREAKING NEWS) din clasa STIRE" << " -> " << ctime(&now) << endl;
				bool newBreakingNews;
				cout << "\nAlegeti daca este sau nu Breaking News (1 = da; 0 = nu): ";
				cin >> newBreakingNews;
				stireMeniu.setBreakingNews(newBreakingNews);
			}
			if (optiune == 10)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de ratinguri din clasa STIRE" << " -> " << ctime(&now) << endl;
				int newNrRatinguri;
				cout << "\nAlegeti un nou Numar de Ratinguri: ";
				cin >> newNrRatinguri;
				stireMeniu.setNrRatinguri(newNrRatinguri);
			}
			if (optiune == 11)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea ratingurilor din clasa STIRE" << " -> " << ctime(&now) << endl;
				float newRatinguri[100];
				cout << "\nAlegeti noile ratinguri: ";
				for (int i = 0; i < stireMeniu.getNrRatinguri(); i++)
					cin >> newRatinguri[i];
				stireMeniu.setRatinguri(newRatinguri);
			}
			break;
		}

		//********************************************************************************************
		case 2:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales modificarea clasei REPORTER" << " -> " << ctime(&now) << endl;
			cout << "Alegeti ce doriti sa modificati din clasa REPORTER:\n1. Nume;\n2. Experienta (in luni);\n3. Judet;\n4. Numar de stiri;\n5. Plata per stire;\n6. Numar de colegi din echipa;\n7. ID-ul colegilor din echipa;" << endl;
			cin >> optiune;
			if (optiune == 1)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numelui reporterului din clasa REPORTER" << " -> " << ctime(&now) << endl;
				char newNume[200];
				cout << "\nAlegeti un nou Nume pentru Reporter: ";
				cin.getline(newNume, 200);
				reporterMeniu.setNume(newNume);
			}
			if (optiune == 2)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea experientei reporterului din clasa REPORTER" << " -> " << ctime(&now) << endl;
				int newExperienta;
				cout << "\nAlegeti o noua Experienta pentru Reporter: ";
				cin >> newExperienta;
				reporterMeniu.setExperienta(newExperienta);
			}
			if (optiune == 3)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea judetului din clasa REPORTER" << " -> " << ctime(&now) << endl;
				string newJudet;
				cout << "\nAlegeti un nou Judet pentru Reporter: ";
				cin >> newJudet;
				reporterMeniu.setJudet(newJudet);
			}
			if (optiune == 4)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de stiri din clasa REPORTER" << " -> " << ctime(&now) << endl;
				int newNrStiri;
				cout << "\nAlegeti un nou Numar de Stiri pentru Reporter: ";
				cin >> newNrStiri;
				reporterMeniu.setNrStiri(newNrStiri);
			}
			if (optiune == 5)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea platii stirilor din clasa REPORTER" << " -> " << ctime(&now) << endl;
				float* newPlataStiri;
				newPlataStiri = new float(reporterMeniu.getNrStiri());
				cout << "\nAlegeti nou plata a stirilor pentru Reporter: ";
				for (int i = 0; i < reporterMeniu.getNrStiri(); i++)
					cin >> newPlataStiri[i];
				reporterMeniu.setPlataStiri(newPlataStiri);
			}
			if (optiune == 6)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de colegi din clasa REPORTER" << " -> " << ctime(&now) << endl;
				int newNrColegi;
				cout << "\nAlegeti un nou numar de colegi pentru Reporter: ";
				cin >> newNrColegi;
				reporterMeniu.setNrColegiEchipa(newNrColegi);
			}
			if (optiune == 7)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea echipei din clasa REPORTER" << " -> " << ctime(&now) << endl;
				int newEchipa[4];
				cout << "\nAlegeti o noua echipa pentru Reporter: ";
				for (int i = 0; i < reporterMeniu.getNrColegiEchipa(); i++)
					cin >> newEchipa[i];
				reporterMeniu.setEchipa(newEchipa);
			}
			break;
		}

		//********************************************************************************************
		case 3:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales modificarea clasei OPERATOR" << " -> " << ctime(&now) << endl;
			cout << "Alegeti ce doriti sa modificati din clasa OPERATOR:\n1. Nume;\n2. Experienta (in luni);\n3. Judet;\n4. Salariu (lunar);\n5. Numar de colegi din echipa;\n6. ID-ul colegilor din echipa;" << endl;
			cin >> optiune;
			if (optiune == 1)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numelui operatorului din clasa OPERATOR" << " -> " << ctime(&now) << endl;
				char newNume[200];
				cout << "\nAlegeti un nou Nume pentru Operator: ";
				cin.getline(newNume, 200);
				operatorMeniu.setNume(newNume);
			}
			if (optiune == 2)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea experientei din clasa OPERATOR" << " -> " << ctime(&now) << endl;
				int newExperienta;
				cout << "\nAlegeti o noua experienta pentru Operator: ";
				cin >> newExperienta;
				operatorMeniu.setExperienta(newExperienta);
			}
			if (optiune == 3)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea judetului din clasa OPERATOR" << " -> " << ctime(&now) << endl;
				string newJudet;
				cout << "\nAlegeti un nou Judet pentru Operator: ";
				cin >> newJudet;
				operatorMeniu.setJudet(newJudet);
			}
			if (optiune == 4)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea salariului din clasa OPERATOR" << " -> " << ctime(&now) << endl;
				float newSalariu;
				cout << "\nAlegeti un nou Salariu pentru Operator: ";
				cin >> newSalariu;
				operatorMeniu.setSalariu(newSalariu);
			}
			if (optiune == 5)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de colegi din clasa OPERATOR" << " -> " << ctime(&now) << endl;
				int newNrColegi;
				cout << "\nAlegeti un nou numar de colegi pentru Operator: ";
				cin >> newNrColegi;
				operatorMeniu.setNrColegiEchipa(newNrColegi);
			}
			if (optiune == 6)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea echipei din clasa OPERATOR" << " -> " << ctime(&now) << endl;
				int newEchipa[4];
				cout << "\nAlegeti o noua echipa pentru Operator: ";
				for (int i = 0; i < operatorMeniu.getNrColegi(); i++)
					cin >> newEchipa[i];
				operatorMeniu.setEchipa(newEchipa);
			}
			break;
		}

		//********************************************************************************************
		case 4:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales modificarea clasei EDITOR" << " -> " << ctime(&now) << endl;
			cout << "Alegeti ce doriti sa modificati din clasa EDITOR:\n1. Nume;\n2. Experienta (in luni);\n3. Judet;\n4. Salariu (lunar);\n5. Numar de colegi din echipa;\n6. ID-ul colegilor din echipa;" << endl;
			cin >> optiune;
			if (optiune == 1)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numelui editorului din clasa EDITOR" << " -> " << ctime(&now) << endl;
				char newNume[200];
				cout << "\nAlegeti un nou Nume pentru Editor: ";
				cin.getline(newNume, 200);
				editorMeniu.setNume(newNume);
			}
			if (optiune == 2)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea experientei din clasa EDITOR" << " -> " << ctime(&now) << endl;
				int newExperienta;
				cout << "\nAlegeti o noua experienta pentru Editor: ";
				cin >> newExperienta;
				editorMeniu.setExperienta(newExperienta);
			}
			if (optiune == 3)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea judetului din clasa EDITOR" << " -> " << ctime(&now) << endl;
				string newJudet;
				cout << "\nAlegeti un nou Judet pentru Editor: ";
				cin >> newJudet;
				editorMeniu.setJudet(newJudet);
			}
			if (optiune == 4)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea salariului din clasa EDITOR" << " -> " << ctime(&now) << endl;
				float newSalariu;
				cout << "\nAlegeti un nou Salariu pentru Editor: ";
				cin >> newSalariu;
				editorMeniu.setSalariu(newSalariu);
			}
			if (optiune == 5)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de colegi din clasa EDITOR" << " -> " << ctime(&now) << endl;
				int newNrColegi;
				cout << "\nAlegeti un nou numar de colegi pentru Editor: ";
				cin >> newNrColegi;
				editorMeniu.setNrColegiEchipa(newNrColegi);
			}
			if (optiune == 6)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea echipei din clasa EDITOR" << " -> " << ctime(&now) << endl;
				int newEchipa[4];
				cout << "\nAlegeti o noua echipa pentru Operator: ";
				for (int i = 0; i < editorMeniu.getNrColegi(); i++)
					cin >> newEchipa[i];
				editorMeniu.setEchipa(newEchipa);
			}
			break;
		}

		//********************************************************************************************
		case 5:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales moficarea clasei SUNETIST" << " -> " << ctime(&now) << endl;
			cout << "Alegeti ce doriti sa modificati din clasa SUNETIST:\n1. Nume;\n2. Experienta (in luni);\n3. Judet;\n4. Salariu (lunar);\n5. Numar de colegi din echipa;\n6. ID-ul colegilor din echipa;" << endl;
			cin >> optiune;
			if (optiune == 1)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numelui sunetistului din clasa SUNETIST" << " -> " << ctime(&now) << endl;
				char newNume[200];
				cout << "\nAlegeti un nou Nume pentru Sunetist: ";
				cin.getline(newNume, 200);
				sunetistMeniu.setNume(newNume);
			}
			if (optiune == 2)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea experientei din clasa SUNETIST" << " -> " << ctime(&now) << endl;
				int newExperienta;
				cout << "\nAlegeti o noua experienta pentru Sunetist: ";
				cin >> newExperienta;
				sunetistMeniu.setExperienta(newExperienta);
			}
			if (optiune == 3)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea judetului din clasa SUNETIST" << " -> " << ctime(&now) << endl;
				string newJudet;
				cout << "\nAlegeti un nou Judet pentru Sunetist: ";
				cin >> newJudet;
				sunetistMeniu.setJudet(newJudet);
			}
			if (optiune == 4)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea salariului din clasa SUNETIST" << " -> " << ctime(&now) << endl;
				float newSalariu;
				cout << "\nAlegeti un nou Salariu pentru Sunetist: ";
				cin >> newSalariu;
				sunetistMeniu.setSalariu(newSalariu);
			}
			if (optiune == 5)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de colegi din clasa SUNETIST" << " -> " << ctime(&now) << endl;
				int newNrColegi;
				cout << "\nAlegeti un nou numar de colegi pentru Sunetist: ";
				cin >> newNrColegi;
				sunetistMeniu.setNrColegiEchipa(newNrColegi);
			}
			if (optiune == 6)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea echipei din clasa SUNETIST" << " -> " << ctime(&now) << endl;
				int newEchipa[4];
				cout << "\nAlegeti o noua echipa pentru Sunetist: ";
				for (int i = 0; i < sunetistMeniu.getNrColegi(); i++)
					cin >> newEchipa[i];
				sunetistMeniu.setEchipa(newEchipa);
			}
			break;
		}

		//********************************************************************************************
		case 6:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales moficarea clasei LOCATIE" << " -> " << ctime(&now) << endl;
			cout << "Alegeti ce doriti sa modificati din clasa LOCATIE:\n1. Judet;\n2. Localitate;\n3. Numar de studiouri;\n4. Numar de stiri;\n5. ID-ul stirilor;" << endl;
			cin >> optiune;
			if (optiune == 1)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea judetului din clasa LOCATIE" << " -> " << ctime(&now) << endl;
				string newJudet;
				cout << "\nAlegeti un nou Judet pentru Locatie: ";
				cin >> newJudet;
				locatieMeniu.setJudet(newJudet);
			}
			if (optiune == 2)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea localitatii din clasa LOCATIE" << " -> " << ctime(&now) << endl;
				char newLocalitate[200];
				cout << "\nAlegeti o noua Localitate pentru Locatie: ";
				cin.getline(newLocalitate, 200);
				locatieMeniu.setLocalitate(newLocalitate);
			}
			if (optiune == 3)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de studio din clasa LOCATIE" << " -> " << ctime(&now) << endl;
				int newNrStudio;
				cout << "\nAlegeti un nou numar de Studiouri pentru Locatie: ";
				cin >> newNrStudio;
				locatieMeniu.setNrStudiouri(newNrStudio);
			}
			if (optiune == 4)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de stiri din clasa LOCATIE" << " -> " << ctime(&now) << endl;
				int newNrStiri;
				cout << "\nAlegeti un nou numar de Stiri pentru Locatie: ";
				cin >> newNrStiri;
				locatieMeniu.setNrStiri(newNrStiri);
			}
			if (optiune == 5)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea ID-urilor stirilor din clasa LOCATIE" << " -> " << ctime(&now) << endl;
				int newIdStiri[10];
				cout << "\nAlegeti noi Id-uri de Stiri pentru Locatie: ";
				for (int i = 0; i < locatieMeniu.getNrStiri(); i++)
					cin >> newIdStiri[i];
				locatieMeniu.setIdStiri(newIdStiri);
			}
			break;
		}

		//********************************************************************************************
		case 7:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales moficarea clasei STUDIO" << " -> " << ctime(&now) << endl;
			cout << "Alegeti ce doriti sa modificati din clasa STUDIO:\n1. Locatie studio;\n2. Numar de angajati;\n3. Numar de camere;\n4. Suprafata camere (in m patrati);\n5. Tip de studio (1 - TELEVIZAT, 2 - LIVE, 3 - RADIO);" << endl;
			cin >> optiune;
			if (optiune == 1)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea locatiei din clasa STUDIO" << " -> " << ctime(&now) << endl;
				string newLocatieStudio;
				cout << "\nAlegeti o noua locatie pentru Studio: ";
				cin >> newLocatieStudio;
				studioMeniu.setLocatieStudio(newLocatieStudio);
			}
			if (optiune == 2)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de angajati din clasa STUDIO" << " -> " << ctime(&now) << endl;
				int newNrAngajati;
				cout << "\nAlegeti un nou Numar de Angajati pentru Studio: ";
				cin >> newNrAngajati;
				studioMeniu.setNrAngajati(newNrAngajati);
			}
			if (optiune == 3)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea numarului de camere din clasa STUDIO" << " -> " << ctime(&now) << endl;
				int newNrCamere;
				cout << "\nAlegeti un nou Numar de Camere pentru Studio: ";
				cin >> newNrCamere;
				studioMeniu.setNrCamere(newNrCamere);
			}
			if (optiune == 4)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea suprafetelor camerelor din clasa STUDIO" << " -> " << ctime(&now) << endl;
				float newSuprafataCamere[5];
				cout << "\nAlegeti noi suprafete pentru camerele din Studio: ";
				for (int i = 0; i < studioMeniu.getNrCamere(); i++)
					cin >> newSuprafataCamere[i];
				studioMeniu.setSuprafataCamere(newSuprafataCamere);
			}
			if (optiune == 5)
			{
				now = time(0);
				datamine << "Utilizatorul a ales modificarea tipului de studio din clasa STUDIO" << " -> " << ctime(&now) << endl;
				string newTipStudio;
				cout << "\nAlegeti un nou Tip de Studio: ";
				cin >> newTipStudio;
				studioMeniu.setTipStudioString(newTipStudio);
			}
			break;
		}

		//********************************************************************************************
		case 8:
		{
			now = time(0);
			datamine << "Utilizatorul a ales afisarea claselor" << " -> " << ctime(&now) << endl;
			int optiune;
			cout << "Alegeti ce clasa doriti sa afisati:\n1. Stire \n2. Reporter \n3. Operator \n4. Editor \n5. Sunetist \n6. Locatie \n7. Studio " << endl;
			cin >> optiune;
			if (optiune <= 7 && optiune >= 1)
			{
				if (optiune == 1)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei STIRE" << " -> " << ctime(&now) << endl;
					stireMeniu.afisare();
				}
				if (optiune == 2)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei REPORTER" << " -> " << ctime(&now) << endl;
					cout << reporterMeniu;
				}
				if (optiune == 3)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei OPERATOR" << " -> " << ctime(&now) << endl;
					cout << operatorMeniu;
				}
				if (optiune == 4)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei EDITOR" << " -> " << ctime(&now) << endl;
					cout << editorMeniu;
				}
				if (optiune == 5)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei SUNETIST" << " -> " << ctime(&now) << endl;
					cout << sunetistMeniu;
				}
				if (optiune == 6)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei LOCATIE" << " -> " << ctime(&now) << endl;
					locatieMeniu.afisare();
				}
				if (optiune == 7)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei STUDIO" << " -> " << ctime(&now) << endl;
					studioMeniu.afisare();
				}

			}
			break;
		}

		//********************************************************************************************
		case 9:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales prelucrarea claselor" << " -> " << ctime(&now) << endl;
			cout << "Alegeti o clasa pentru metoda de prelucrare:\n1. STIRE;\n2. REPORTER;\n3. OPERATOR;\n4. EDITOR;\n5. SUNETIST;\n6. LOCATIE;\n7. STUDIO;" << endl;
			cin >> optiune;
			if (optiune == 1)
			{
				now = time(0);
				datamine << "Utilizatorul a ales prelucrarea clasei STIRE" << " -> " << ctime(&now) << endl;
				cout << "Ati ales clasa STIRE pentru care se va adauga un rating suplimentar.";
				float newRating;
				cout << "\nAlegeti un nou rating: ";
				cin >> newRating;
				stireMeniu.adaugaRating(newRating);
			}
			if (optiune == 2)
			{
				now = time(0);
				datamine << "Utilizatorul a ales prelucrarea clasei REPORTER" << " -> " << ctime(&now) << endl;
				cout << "Ati ales clasa REPORTER pentru care se va adauga plata unei stiri.";
				float newPlataStire;
				cout << "\nAlegeti o noua plata: ";
				cin >> newPlataStire;
				reporterMeniu.adaugaPlataStire(newPlataStire);
			}
			if (optiune == 3)
			{
				now = time(0);
				datamine << "Utilizatorul a ales prelucrarea clasei OPERATOR" << " -> " << ctime(&now) << endl;
				cout << "Ati ales clasa OPERATOR pentru care se va sterge un coleg din echipa.";
				int id;
				cout << "\nAlegeti Id-ul colegului care urmeaza a fi sters: ";
				cin >> id;
				operatorMeniu.stergeColeg(id);
			}
			if (optiune == 4)
			{
				now = time(0);
				datamine << "Utilizatorul a ales prelucrarea clasei EDITOR" << " -> " << ctime(&now) << endl;
				cout << "Ati ales clasa EDITOR pentru care se va sterge un coleg din echipa.";
				int id;
				cout << "\nAlegeti Id-ul colegului care urmeaza a fi sters: ";
				cin >> id;
				editorMeniu.stergeColeg(id);
			}
			if (optiune == 5) {
				now = time(0);
				datamine << "Utilizatorul a ales prelucrarea clasei SUNETIST" << " -> " << ctime(&now) << endl;
				cout << "Ati ales clasa SUNETIST pentru care se va sterge un coleg din echipa.";
				int id;
				cout << "\nAlegeti Id-ul colegului care urmeaza a fi sters: ";
				cin >> id;
				sunetistMeniu.stergeColeg(id);
			}
			if (optiune == 6) {
				now = time(0);
				datamine << "Utilizatorul a ales prelucrarea clasei LOCATIE" << " -> " << ctime(&now) << endl;
				cout << "Ati ales clasa LOCATIE pentru care se va adauga o stire.";
				int id;
				cout << "\nAlegeti Id-ul stirii care urmeaza a fi adaugata: ";
				cin >> id;
				locatieMeniu.adaugaStire(id);
			}
			if (optiune == 7) {
				now = time(0);
				datamine << "Utilizatorul a ales prelucrarea clasei STUDIO" << " -> " << ctime(&now) << endl;
				cout << "Ati ales clasa STUDIO pentru care se va adauga o camera.";
				float suprafata;
				cout << "\nAlegeti suprafata camerei adaugate: ";
				cin >> suprafata;
				studioMeniu.adaugaCamera(suprafata);
			}
			break;
		}

		//********************************************************************************************
		case 10:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales utilizarea de rapoarte asupra claselor" << " -> " << ctime(&now) << endl;
			cout << "Alegeti un raport:\n1. Raport asupra numarului de ratinguri pozitive;\n2. Raport asupra salariului total;\n3. Raport asupra suprafetei totale ale unui studio;" << endl;
			cin >> optiune;
			cout << "\n____________Raport clase____________" << endl;
			if (optiune == 1) {
				now = time(0);
				datamine << "Utilizatorul a ales utilizarea de rapoarte asupra clasei STIRE" << " -> " << ctime(&now) << endl;
				cout << "\nAti ales un raport asupra numarului de ratinguri pozitive care va determina numarul ratingurilor pozitive ale unei stiri.";
				cout << "\nNumar ratinguri pozitive este: " << stireMeniu.ratinguriPozitive() << " ";
			}

			if (optiune == 2) {
				now = time(0);
				datamine << "Utilizatorul a ales utilizarea de rapoarte asupra claselor REPORTER, OPERATOR, EDITOR, SUNETIST" << " -> " << ctime(&now) << endl;
				cout << "\nAti ales un raport asupra salariului total care va determina intregul salariu al tuturor angajatilor/bugetul necesar alocat salariatilor.";
				cout << "\nSalariul total este: " << reporterMeniu.salariuReporter() + operatorMeniu.salariuOperator() + editorMeniu.salariuEditor() + sunetistMeniu.salariuSunetist() << " RON";
			}

			if (optiune == 3) {
				now = time(0);
				datamine << "Utilizatorul a ales utilizarea de rapoarte asupra clasei STUDIO" << " -> " << ctime(&now) << endl;
				cout << "\nAti ales un raport asupra suprafetei totale ale unui studio care va determina intreaga suprafata a studioului ales.";
				cout << "\nSuprafata totala a studioului este: " << studioMeniu.suprafataTotala();
			}
			break;
		}

		//********************************************************************************************
		case 11:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales afisarea claselor" << " -> " << ctime(&now) << endl;
			cout << "Alegeti ce clasa doriti sa afisati:\n1. Stire \n2. Reporter \n3. Operator \n4. Editor \n5. Sunetist \n6. Locatie \n7. Studio " << endl;
			cin >> optiune;
			if (optiune <= 7 && optiune >= 1)
			{
				if (optiune == 1)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei STIRE" << " -> " << ctime(&now) << endl;
					//pentru clasa STIRE
					IFile* sf;
					Stire s(2, "Incep targurile de Craciun", "Pitesti", 1, 1, 1, 1, 2508.7, true, 4, v1);

					fstream StireOut("fisierStire.txt", ios::out | ios::binary);
					s.writeToFile(StireOut);
					StireOut.close();

					Stire sNoua;
					fstream StireIn("fisierStire.txt", ios::in | ios::binary);
					sNoua.readFromFile(StireIn);
					StireIn.close();
					cout << sNoua;
				}

				if (optiune == 2)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei REPORTER" << " -> " << ctime(&now) << endl;
					//pentru clasa REPORTER
					IFile* rf;
					float vRep[3] = { 55, 2.5, 6 };
					int vRepEc[3] = { 1, 5, 7 };
					Reporter r(2, "Popescu Vasile", 25, "Arges", 3, new float[3]{ 55, 2.5, 6 }, 3, vRepEc, "5020523235643", 4, 73.5);

					fstream ReporterOut("fisierReporter.txt", ios::out | ios::binary);
					r.writeToFile(ReporterOut);
					ReporterOut.close();

					Reporter rNou;
					fstream ReporterIn("fisierReporter.txt", ios::in | ios::binary);
					rNou.readFromFile(ReporterIn);
					ReporterIn.close();
					cout << rNou;
				}

				if (optiune == 3)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei OPERATOR" << " -> " << ctime(&now) << endl;
					//pentru clasa OPERATOR
					IFile* of;
					int vOp[3] = { 3,7,4 };
					Operator o(2, "Ion Mihai", 10, "Olt", 1250.5, 3, vOp, "5030304283766", 10, 23.7);

					fstream OperatorOut("fisierOperator.txt", ios::out | ios::binary);
					o.writeToFile(OperatorOut);
					OperatorOut.close();

					Operator oNou;
					fstream OperatorIn("fisierOperator.txt", ios::in | ios::binary);
					oNou.readFromFile(OperatorIn);
					OperatorIn.close();
					cout << oNou;
				}

				if (optiune == 4)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei EDITOR" << " -> " << ctime(&now) << endl;
					//pentru clasa EDITOR
					IFile* ef;
					int vEd[3] = { 2,5,9 };
					Editor e(2, "Ion Maria", 10, "Arad", 1350, 3, vEd, "6382736475643", 13, 23.4);

					fstream EditorOut("fisierEditor.txt", ios::out | ios::binary);
					e.writeToFile(EditorOut);
					EditorOut.close();

					Editor eNou;
					fstream EditorIn("fisierEditor.txt", ios::in | ios::binary);
					eNou.readFromFile(EditorIn);
					EditorIn.close();
					cout << eNou;
				}

				if (optiune == 5)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei SUNETIST" << " -> " << ctime(&now) << endl;
					//pentru clasa SUNETIST
					IFile* suf;
					int vSu[4] = { 2,3,6,4 };
					Sunetist su(2, "Cojocaru Alina", 70, "Covasna", 2000, 4, vSu, "6030201738473", 5, 44.8);

					fstream SunetistOut("fisierEditor.txt", ios::out | ios::binary);
					su.writeToFile(SunetistOut);
					SunetistOut.close();

					Sunetist suNou;
					fstream SunetistIn("fisierEditor.txt", ios::in | ios::binary);
					suNou.readFromFile(SunetistIn);
					SunetistIn.close();
					cout << suNou;
				}

				if (optiune == 6)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei LOCATIE" << " -> " << ctime(&now) << endl;
					//pentru clasa LOCATIE
					IFile* lf;
					int vLoc[5] = { 1,2,3,4,5 };
					Locatie l("Arges", "Pitesti", 3, 5, vLoc);

					fstream LocatieOut("fisierLocatie.txt", ios::out | ios::binary);
					l.writeToFile(LocatieOut);
					LocatieOut.close();

					Locatie lNoua;
					fstream LocatieIn("fisierLocatie.txt", ios::in | ios::binary);
					lNoua.readFromFile(LocatieIn);
					LocatieIn.close();
					cout << lNoua;
				}

				if (optiune == 7)
				{
					now = time(0);
					datamine << "Utilizatorul a ales afisarea clasei STUDIO" << " -> " << ctime(&now) << endl;
					//pentru clasa STUDIO
					IFile* stf;
					float vSt[2] = { 32.2,14 };
					Studio st("Bucuresti", 3, 2, vSt, RADIO);

					fstream StudioOut("fisierStudio.txt", ios::out | ios::binary);
					st.writeToFile(StudioOut);
					StudioOut.close();

					Studio stNou;
					fstream StudioIn("fisierStudio.txt", ios::in | ios::binary);
					stNou.readFromFile(StudioIn);
					StudioIn.close();
					cout << stNou;
				}

			}
			break;
		}

		//********************************************************************************************
		case 12:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales gestionarea datelor din clasa STIRE" << " -> " << ctime(&now) << endl;
			cout << "Alegeti o metoda de gestionare a datelor din clasa Stire: \n1.Vector \n2.List \n3.Set \n4.Map" << endl;
			cin >> optiune;
			if (optiune <= 4 && optiune >= 1) {
				if (optiune == 1) {
					now = time(0);
					datamine << "Utilizatorul a ales gestionarea datelor (VECTOR) din clasa STIRE" << " -> " << ctime(&now) << endl;
					Stire s1(2, "Incep targurile de Craciun", "Pitesti", 1, 1, 1, 1, 2508.7, true, 4, v1);
					Stire s2(3, "Evenimentele acestui an", "Bucuresti", 2, 3, 4, 3, 1500, false, 2, v2);
					Stire s3(4, "Ce e de facut?", "Brasov", 3, 3, 2, 6, 2200, true, 3, v3);
					vector<Stire> stiri;
					stiri.push_back(s1);
					stiri.push_back(s2);
					stiri.push_back(s3);


					cout << "Scriere cu Iterator:" << endl;
					vector<Stire>::iterator iterator_Vector;
					for (iterator_Vector = stiri.begin(); iterator_Vector != stiri.end(); iterator_Vector++) {
						cout << *iterator_Vector << " ";
					}
				}

				if (optiune == 2) {
					now = time(0);
					datamine << "Utilizatorul a ales gestionarea datelor (LIST) din clasa STIRE" << " -> " << ctime(&now) << endl;
					Stire s1(2, "Incep targurile de Craciun", "Pitesti", 1, 1, 1, 1, 2508.7, true, 4, v1);
					Stire s2(3, "Evenimentele acestui an", "Bucuresti", 2, 3, 4, 3, 1500, false, 2, v2);
					Stire s3(4, "Ce e de facut?", "Brasov", 3, 3, 2, 6, 2200, true, 3, v3);
					list<Stire> listaStiri;
					listaStiri.push_back(s2);
					listaStiri.push_front(s1);
					listaStiri.push_front(s3);


					cout << "Scriere cu Iterator invers:" << endl;
					list<Stire>::reverse_iterator rev_iterator_Lista;
					for (rev_iterator_Lista = listaStiri.rbegin(); rev_iterator_Lista != listaStiri.rend(); rev_iterator_Lista++)
						cout << *rev_iterator_Lista << " ";

				}

				if (optiune == 3) {
					now = time(0);
					datamine << "Utilizatorul a ales gestionarea datelor (SET) din clasa STIRE" << " -> " << ctime(&now) << endl;
					Stire s1(2, "Incep targurile de Craciun", "Pitesti", 1, 1, 1, 1, 2508.7, true, 4, v1);
					Stire s2(3, "Evenimentele acestui an", "Bucuresti", 2, 3, 4, 3, 1500, false, 2, v2);
					Stire s3(4, "Ce e de facut?", "Brasov", 3, 3, 2, 6, 2200, true, 3, v3);
					set<Stire> setStiri;
					setStiri.insert(s1);
					setStiri.insert(s2);
					setStiri.insert(s3);

					set<Stire>::iterator iterator_Set;
					int cautare;
					cout << "Cautare in set: " << endl;
					cout << "Alegeti ce Stire doriti sa cautati (stirile din set sunt 1,2,3): ";
					cin >> cautare;
					if (cautare) {
						if (cautare == 1) {
							iterator_Set = setStiri.find(s1);
							if (iterator_Set != setStiri.end()) {
								cout << "\nS-a gasit";
								break;
							}
						}
						if (cautare == 2) {
							iterator_Set = setStiri.find(s2);
							if (iterator_Set != setStiri.end()) {
								cout << "\nS-a gasit";
								break;
							}
						}
						if (cautare == 3) {
							iterator_Set = setStiri.find(s3);
							if (iterator_Set != setStiri.end()) {
								cout << "\nS-a gasit";
								break;
							}
						}
						else
							cout << "\nNu s-a gasit";
					}
					else
						cout << "\nNu s-a gasit";
				}

				if (optiune == 4) {
					now = time(0);
					datamine << "Utilizatorul a ales gestionarea datelor (MAP) din clasa STIRE" << " -> " << ctime(&now) << endl;
					Stire s1(1, "Incep targurile de Craciun", "Pitesti", 1, 1, 1, 1, 2508.7, true, 4, v1);
					Stire s2(2, "Evenimentele acestui an", "Bucuresti", 2, 3, 4, 3, 1500, false, 2, v2);
					Stire s3(3, "Ce e de facut?", "Brasov", 3, 3, 2, 6, 2200, true, 3, v3);
					map<int, Stire> mapStiri;
					mapStiri[10] = s1;
					mapStiri[12] = s2;
					mapStiri[10] = s3;

					map<int, Stire>::iterator iterator_map;
					for (iterator_map = mapStiri.begin(); iterator_map != mapStiri.end(); iterator_map++)
						cout << iterator_map->first << " " << iterator_map->second << " ";
				}
			}
			break;
		}
		
		
		//********************************************************************************************
		case 13:
		{
			int optiune;
			now = time(0);
			datamine << "Utilizatorul a ales utilizarea datelor din fisierele CSV" << " -> " << ctime(&now) << endl;
			cout << "Alegeti in ce clasa doriti sa utilizati incarcarea de date din fisierele CSV:\n1. Stire \n2. Reporter \n3. Operator \n4. Editor \n5. Sunetist \n6. Locatie \n7. Studio " << endl;
			cin >> optiune;
			if (optiune <= 7 && optiune >= 1)
			{
				if (optiune == 1)
				{
					now = time(0);
					datamine << "Utilizatorul a ales utilizarea datelor clasei STIRE din fisierele CSV" << " -> " << ctime(&now) << endl;
					Stire stireCSV(5);
					fstream fStire("stireCSV.txt");
					stireCSV.CitireCSV(fStire);
					cout << "\nCitirea a fost efectuata cu succes!" << endl;
					stireCSV.afisare();
				}
				if (optiune == 2)
				{
					now = time(0);
					datamine << "Utilizatorul a ales utilizarea datelor clasei REPORTER din fisierele CSV" << " -> " << ctime(&now) << endl;
					Reporter reporterCSV(5);
					fstream fReporter("reporterCSV.txt");
					reporterCSV.CitireCSV(fReporter);
					cout << "\nCitirea a fost efectuata cu succes!" << endl;
					cout << reporterCSV;
				}
				if (optiune == 3)
				{
					now = time(0);
					datamine << "Utilizatorul a ales utilizarea datelor clasei OPERATOR din fisierele CSV" << " -> " << ctime(&now) << endl;
					Operator operatorCSV(5);
					fstream fOperator("operatorCSV.txt");
					operatorCSV.CitireCSV(fOperator);
					cout << "\nCitirea a fost efectuata cu succes!" << endl;
					cout << operatorCSV;
				}
				if (optiune == 4)
				{
					now = time(0);
					datamine << "Utilizatorul a ales utilizarea datelor clasei EDITOR din fisierele CSV" << " -> " << ctime(&now) << endl;
					Editor editorCSV(5);
					fstream fEditor("editorCSV.txt");
					editorCSV.CitireCSV(fEditor);
					cout << "\nCitirea a fost efectuata cu succes!" << endl;
					cout << editorCSV;
				}
				if (optiune == 5)
				{
					now = time(0);
					datamine << "Utilizatorul a ales utilizarea datelor clasei SUNETIST din fisierele CSV" << " -> " << ctime(&now) << endl;
					Sunetist sunetistCSV(5);
					fstream fSunetist("sunetistCSV.txt");
					sunetistCSV.CitireCSV(fSunetist);
					cout << "\nCitirea a fost efectuata cu succes!" << endl;
					cout << sunetistCSV;
				}
				if (optiune == 6)
				{
					now = time(0);
					datamine << "Utilizatorul a ales utilizarea datelor clasei LOCATIE din fisierele CSV" << " -> " << ctime(&now) << endl;
					Locatie locatieCSV;
					fstream fLocatie("locatieCSV.txt");
					locatieCSV.CitireCSV(fLocatie);
					cout << "\nCitirea a fost efectuata cu succes!" << endl;
					locatieCSV.afisare();
				}
				if (optiune == 7)
				{
					now = time(0);
					datamine << "Utilizatorul a ales utilizarea datelor clasei STUDIOURI din fisierele CSV" << " -> " << ctime(&now) << endl;
					Studio studioCSV;
					fstream fStudio("studiouriCSV.txt");
					studioCSV.CitireCSV(fStudio);
					cout << "\nCitirea a fost efectuata cu succes!" << endl;
					studioCSV.afisare();
				}

			}
			break;
			
		}
		
		case 14:
		{
			now = time(0);
			datamine << "Utilizatorul a ales iesirea din program" << " -> " << ctime(&now) << endl;
			cout << "\n      " << heart << "             " << heart << "             " << heart << "             " << heart;
			cout << "\n* * * * * Finalul programului. Va multumim! * * * * *\n";
			cout << "      " << heart << "             " << heart << "             " << heart << "             " << heart;
			break;
		}
		default:
		{
			cout << "Nu este o varianta valabila! \n"
				<< "Alegeti din nou!\n";
			break;
		}
		}

	} while (alegere != 14);
	
	return 0;

}
