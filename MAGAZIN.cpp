#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;

class produs
{
protected:
    string den;
    int bucati;
    int volum;
    int cantitate;
    int perioada_valab;
    int promotie;
public:
    produs(string = "", int = 0, int = 0, int = 0, int = 0, int = 0);
    produs(produs& );
    friend istream& operator>>(istream&, produs&);
    friend ostream& operator<<(ostream&, produs&);
    produs& operator=( produs&);
    virtual void afisare();
    virtual void adaugare();
    virtual ~produs(){}
};
produs::produs( string n, int b, int v, int c, int pv, int p) : den(n), bucati(b), volum(v), cantitate(c), perioada_valab(pv), promotie(p)  {}
produs::produs(produs& x) { *this = x; }
istream& operator>>(istream& in, produs& x)
{
    cout << "Nume produs : "; in >> x.den;
    cout << "Cantitatea este in (1 = bucati\ 2 = volum\ 3 = cantitate kg): ";
    int opt; cin >> opt;
    cout << "Nr cant : ";
    switch(opt){
        case 1:{in >> x.bucati;  break;}
        case 2:{in >> x.volum;  break;}
        case 3:{in >> x.cantitate;  break;}
    }
    cout << "Perioada valabilitate(0 altfel)"; in >> x.perioada_valab;
    cout << "Promotie(0 altfel) : "; in >> x.promotie;
    return in;
}
ostream& operator<<(ostream& out, produs& x)
{
    out << "Nume produs : " << x.den << endl;
    out << "Cantitate produs : ";
    if (x.bucati != 0) out << x.bucati << " bucati"<< endl;
    else if( x.volum != 0) out << x.volum << " L"<< endl;
    else if( x.cantitate != 0) out << x.cantitate << " KG"<< endl;
    if (x.perioada_valab != 0 ) out << "Perioada valabilitate : " << x.perioada_valab  << " zile"<< endl;
    if(x.promotie != 0) out << "Promotie : " << x.promotie << "% reducere" << endl;
}
produs& produs::operator=(produs& x)
{
    den = x.den;
    bucati = x.bucati;
    volum = x.volum;
    cantitate = x.cantitate;
    perioada_valab = x.perioada_valab;
    promotie = x.promotie;
}
void produs::afisare() { cout << *this; }
void produs::adaugare(){ cin  >> *this; }

class lot: public produs
{
protected:
    string data;
    float pret;
    float unitMasura;
public:
    lot(string = "", int = 0, int = 0, int = 0, int = 0, int = 0, string = "", float = 0, float = 0);
    lot( const lot& x){  *this = x;}
    friend istream& operator>>(istream&, lot&);
    friend ostream& operator<<(ostream&, lot&);
    lot& operator=( const lot& );
    void afisare();
    void adaugare();
    ~lot(){}
};
lot::lot( string n, int b, int v, int c, int pv, int p, string d , float pr , float um ) : produs(n,b, v, c, pv, p)
{
    data = d;
    pret = pr;
    unitMasura = um;
}
istream& operator>>(istream& in, lot& x)
{
    in >> static_cast<produs&>(x);
    cout << "Data primirii lotului (dd/mm/yyyy): "; in >> x.data;
    cout << "Pretul per unitate : "; in >>x.pret;
    cout << "Unitatea : "; in >> x.unitMasura;
}
ostream& operator<<(ostream& out , lot& x)
{
    out << static_cast<produs&>(x);
    out << "Data primirii lotului = " << x.data << endl;
    out << "Pretul per unitate : " << x.pret << " per " << x.unitMasura << endl;
}
lot& lot::operator=(const lot& x)
{
    den = x.den;
    bucati = x.bucati;
    volum = x.volum;
    cantitate = x.cantitate;
    perioada_valab = x.perioada_valab;
    promotie = x.promotie;
    data = x.data;
    pret = x.pret;
    unitMasura = x.unitMasura;
}
void lot::afisare() { cout << *this; }
void lot::adaugare(){ cin  >> *this; }


class magazin
{
private:
    static int nr_loturi;
    vector<lot> loturi;
public:
    magazin();
    magazin(magazin&);
    friend istream& operator>>(istream&, magazin&);
    friend ostream& operator<<(ostream&, magazin&);
    magazin& operator=( magazin&);
    void afisare();
    void adaugare();
    ~magazin(){}
};
int magazin::nr_loturi = 0;
magazin::magazin() {}

istream& operator>>(istream& in, magazin& x)
{
    cout << "nr loturi = "; in >> x.nr_loturi;
    for(int i = 0; i < x.nr_loturi; i++){
            lot aux;
            in >> aux;
            x.loturi.push_back(aux);
                }
    return in;
}
ostream& operator<<(ostream& out, magazin& x)
{
    for(int i = 0; i < x.nr_loturi; i++) out << x.loturi[i];
    return out;
}
void magazin::adaugare()
{
    lot aux;
    cin >> aux;
    loturi.push_back(aux);
    nr_loturi++;
}
void magazin::afisare()
{
    cout << *this;
}

int main()
{
    lot l1("Sarmale", 10, 0, 0, 5, 20, "22.07.2018", 10, 2);
    lot l2(l1);
    cout << l2;
    int n;
    cout << "1-Adauga un lot in magazin\n2-Adauga n loturi in magazin\n3 - Adauga un produs nou\n4-Afisare produse comercializate de magazin\n0- STOP\n";
    cin >> n;
    magazin m1;
    produs p1;
    while(n)
    {
        switch(n){
            case 1:{ m1.adaugare();break; }
            case 2: { cin >> m1 ; break; }
            case 3: { cin >> p1; break;}
            case 4: { cout << m1; break; }
        }
        cout << " optiunea : "; cin >> n;
    }
    return 0;
}
