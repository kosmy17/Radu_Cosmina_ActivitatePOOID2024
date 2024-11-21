#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Exceptie {
public:
	string mesaj;
	Exceptie(string mesaj) {
	this->mesaj = mesaj;
	}
};

	class Angajat {
	private:
		char* nume;
		int nrluni;
		float* salarii;
	public:
		//default
		Angajat() {
			this->nume = new char[strlen("Alin") + 1];
			strcpy(this->nume, "Alin");
			this->nrluni = 3;
			this->salarii = new float[3];
			this->salarii[0] = 200;
			this->salarii[1] = 500;
			this->salarii[2] = 400;
		}
		//cu  param
		Angajat(const char* n, int l, float* s) {
			this->nume = new char[strlen(n) + 1];
			strcpy(this->nume, n);
			this->nrluni = l;
			this->salarii = new float[l];
			for (int i = 0; i < this->nrluni; i++) {
				this->salarii[i] = s[i];
			}
		}
		//hibrid
		Angajat(int l, float* s) {
			this->nume = new char[strlen("ion") + 1];
			strcpy(this->nume, "ion");
			this->nrluni = l;
			this->salarii = new float[l];
			for (int i = 0; i < l; i++) {
				this->salarii[i] = s[i];
			}
		}
		//de copiere -se creza un ob nou in  baza  unui  vechi Angajat a2=a1;
		Angajat(const Angajat& a) {
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(this->nume, a.nume);
			this->nrluni = a.nrluni;
			this->salarii = new float[a.nrluni];
			for (int i = 0; i < a.nrluni; i++) {
				this->salarii[i] = a.salarii[i];
			}
		}
		//operatorul  egal a1=a2 ;egaleaza  2 obiecte  create deja
		Angajat& operator=(Angajat& a) {
			if (this->nume) {
				delete[] this->nume;
			}
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(this->nume, a.nume);
			this->nrluni = a.nrluni;
			if (this->salarii) {
				delete[] this->salarii;
			}
			this->salarii = new float[a.nrluni];
			for (int i = 0; i < a.nrluni; i++) {
				this->salarii[i] = a.salarii[i];
			}
			return*this;
		}
		//cout <<a1
		friend ostream& operator<< (ostream& out, Angajat& a) {
			out << endl << " Angajatul cu numele " << a.nume << " lucreaza de " << a.nrluni << " luni  si a  incasat urmatoarele salarii: ";
			for (int i = 0; i < a.nrluni; i++) {
				out << endl << i << ":" << a.salarii[i];
			}
			return out;
		}
		//cin >>a2
		friend istream& operator>>(istream& in, Angajat& a) {
			char buffer[50];
			cout << endl << "Introduceti numele: ";
			in >> buffer;
			if (a.nume) {
				delete[] a.nume;
			}
			a.nume = new char[strlen(buffer) + 1];
			strcpy(a.nume, buffer);
			cout << endl << "nr luni: ";
			in >> a.nrluni;
			if (a.salarii) {
				delete[] a.salarii;
			}
			a.salarii = new float[a.nrluni];
			for (int i = 0; i < a.nrluni; i++) {
				cout << endl << i << ":";
				in >> a.salarii[i];
			}
			return in;
		}
		//getteri ( returneaza) si setteri
		char* getnume() {
			return  this->nume;
		}
		void setnume(const char* n) {
			if (this->nume) {
				delete[] this->nume;
			}
			this->nume = new char[strlen(n) + 1];
			strcpy(this->nume, n);
		}
		int getnrluni() {
			return this->nrluni;
		}
		void setnrluni(int l) {
			this->nrluni = l;
		}
		//la vector avem  doar setter
		void setsalarii(int l, float* s) {
			if (l > 0) {
				this->nrluni = l;
				if (this->salarii) {
					delete[] this->salarii;
				}
				this->salarii = new float[l];
				for (int i = 0; i < l; i++) {
					this->salarii[i] = s[i];
				}
			}
			else {
				throw Exceptie("nr luni invalide");
			}
			
		}
		//  arata  pozitia 
		float geteelement(int poz) {
			return this->salarii[poz];
		}
		//operatorul indexare []
		float& operator[](int poz) {
			//conditie op indexare
			if (poz >= 0 && poz < nrluni) {
				return this->salarii[poz];
			}
			else {
				throw Exceptie("pozitie invalida");
			}
		}
		//cast explicit  - face conversia din int in double - facem  suma salariilor
		explicit operator double() {
			double s = 0;
			for (int i = 0; i < this->nrluni; i++) {
				s += this->salarii[i];
			}
			return s;
		}
		//op cast implicit -faci un cast  intr-o functie  dar sa nu iti dai seama  ca este   cast 
		double operator ()() {
			return  this->operator double();
		}
		//un alt exemplu de cast implicit - media  salariilor
		double medie() {
			return this->operator double() / this->nrluni;
		}

		//operator !=  
		bool  operator!= (Angajat& a) {
			if (this->operator()() != a()) {
				return  true;
			}
			else {
				return  false;
			}
		}
		//comparam  salarile
		bool operator> (Angajat& a) {
			if (this->salarii > a.salarii) {
				return  true;
			}
			else {
				return false;
			}
		}
		//comparam media salriilor
		bool operator>= (Angajat& a) {
			if (this->medie()>=a.medie()) {
				return  true;
			}
			else {
				return false;
			}
		}

	};
	//void main() {
	//	Angajat a;
	//	cout << endl << a;
	//	Angajat a1("alina", 3, new float[3] {200, 300, 400});
	//	cout << endl << a1;
	//	Angajat a2(2, new float[2] {400, 600});
	//	cout << endl << a2;
	//	//copiere
	//	Angajat a3 = a1;
	//	cout << endl << a3;
	//	//op egal
	//	a2 = a1;
	//	cout << endl << a2;
	//	//apelam getteri si  setteri
	//	cout << endl << a2.getnume();
	//	cout << endl << a2.getnrluni();
	//	a2.setnrluni(2);
	//	cout << endl << a2.getnrluni();
	//	a2.setnume("ion");
	//	cout << endl << a2.getnume();
	//	a2.setsalarii(2, new float[2] {200, 700});
	//	cout << endl << a2;
	//	cout << endl << a2.geteelement(1);
	//	cout << endl << a2[1];
	//	//cast explicit-
	//	cout << endl << (double)a2;
	//	//cast implicit functie
	//	cout << endl << a2();
	//	//cast mplicit medie
	//	cout << endl << a2.medie();
	//	//apelam  citirea la  tastura
	//	cin >> a2;
	//	cout << endl << "dupa citirea la  tastatura :";
	//	cout << endl << a2;
	//	//apelam !=
	//	if (a2 != a1) {
	//		cout << endl << a2.getnume() << " are  suma salariilor  diferite  fata de " << a1.getnume();
	//	}
	//	else {
	//		cout << endl << "invalid";
	//	}
	//	try {
	//		a2.setsalarii(0, new float[2] {200, 600});
	//	}
	//	catch (Exceptie e){
	//		cout << endl << e.mesaj;
	//	}
	//	cout << endl << a2;
	//	try {
	//		a2[3];
	//	}
	//	catch (Exceptie e) {
	//		cout << endl << e.mesaj;
	//	}
	//	//apelam a2>a3
	//	if (a2 > a1) {
	//		cout << endl << a2.getnume() << " are salariul mai mare decat " << a1.getnume();
	//	}
	//	else {
	//		cout << endl << a2.getnume() << " are salariul mai mic decat " << a1.getnume();
	//	}
	//	//apelam  a2>a1
	//	if (a1 >= a2) {
	//		cout << endl << a1.getnume() << " are media salariului mai mare sau egal decat " << a2.getnume();
	//	}
	//	else {
	//		cout << endl << a1.getnume() << " are media salariului mai mic decat " << a2.getnume();
	//	}
	//}
