#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
using namespace std;

class Examen
{
protected:
    static int nr_examen_static;
    int nr_examen;
    char *materie = NULL;
    float nota_scris;
public:
    Examen( char* = "", float = 0);
    Examen(Examen&);
    virtual void Afisare();
    Examen& operator=(Examen&);
    friend istream& operator>>(istream&, Examen&);
    friend ostream& operator<<(ostream&, Examen&);
    virtual ~Examen();

};
int Examen::nr_examen_static = 1;
Examen::Examen(char* s, float f) {
    nr_examen = nr_examen_static;
    nr_examen_static++;
    materie = new char [strlen(s)];
    strcpy(materie, s);
    nota_scris = f;
}
Examen::Examen(Examen& x)
{
    nr_examen = x.nr_examen;
    delete materie;
    materie = new char [strlen(x.materie)];
    strcpy(materie, x.materie);
    nota_scris = x.nota_scris;
}
void Examen::Afisare() {
    cout << "Nr examen: " << nr_examen << endl;
    cout << "Materie: " << materie << endl;
    cout << "Nota la scris: " << nota_scris << endl;
}
Examen& Examen::operator=(Examen& x) {
    nr_examen = x.nr_examen;
    delete materie;
    materie = new char [strlen(x.materie)];
    strcpy(materie, x.materie);
    nota_scris = x.nota_scris;
    return *this;
}
istream& operator>>(istream& in, Examen& x) {
    char s[50];
    cout << "Materia : ";
    in.getline(s, 50);
    delete x.materie;
    x.materie = new char [strlen(s)];
    strcpy(x.materie, s);
    cout << "Nota la scris : ";
    in >> x.nota_scris;
    return in;
}
ostream& operator<<(ostream& out, Examen& x) {
    out << "Nr examen: " << x.nr_examen << endl;
    out << "Materie: " << x.materie << endl;
    out << "Nota la scris: " << x.nota_scris << endl;
    return out;
}
Examen::~Examen() { delete materie; }




class Partial : public Examen {
protected:
    float nota_oral;
public:
    Partial(char* = "", float = 0, float = 0);
    Partial(Partial&);
    virtual void Afisare();
    Partial& operator=(Partial&);
    friend istream& operator>>(istream&, Partial&);
    friend ostream& operator<<(ostream&, Partial&);
    virtual ~Partial();
};
Partial::Partial(char* s, float f1, float f2) : Examen(s, f1) {
    nota_oral = f2;
}
Partial::Partial(Partial& x)
{
    Examen::operator=(x);
    nota_oral = x.nota_oral;
}
void Partial::Afisare() {
    Examen::Afisare();
    cout << "Nota la oral: " << nota_oral << endl;
}
Partial& Partial::operator=(Partial& x) {
    Examen::operator=(x);
    nota_oral = x.nota_oral;
    return *this;
}
istream& operator>>(istream& in, Partial& x) {
    in >> static_cast<Examen&>(x);
    cout << "Nota la oral : ";
    in >> x.nota_oral;
    return in;
}
ostream& operator<<(ostream& out, Partial& x) {
    out << static_cast<Examen&>(x);
    out << "Nota oral : " << x.nota_oral << endl;
    return out;
}
Partial::~Partial() {}

class Examen_final: public Partial
{
protected:
    float puncte_proiect;
public:
    Examen_final(char* = "", float = 0, float = 0, float = 0);
    Examen_final(Examen_final&);
    virtual void Afisare();
    void refacere_partial();
    float medie_e_f();
    Examen_final& operator=(Examen_final&);
    friend istream& operator>>(istream&, Examen_final&);
    friend ostream& operator<<(ostream&, Examen_final&);
    virtual ~Examen_final();
};
Examen_final::Examen_final(char *s , float ns, float no, float pp ) : Partial(s, ns, no){
    puncte_proiect = pp;
}
Examen_final::Examen_final(Examen_final& x)
{
    Partial::operator=(x);
    puncte_proiect = x.puncte_proiect;
}
void Examen_final::Afisare(){
    Partial::Afisare();
    cout << "Puncte pe proiect : " << puncte_proiect << endl;
}
void Examen_final::refacere_partial(){
    if(nota_oral+nota_scris < 10 && nota_oral+nota_scris!= 0 ){
    cout << "Partial picat. Reluare test.\n";
    cout << "Noile note :\nscris : "; cin >> nota_scris;
    cout << "oral: "; cin >> nota_oral;
    cout << endl;
    }
}
float Examen_final::medie_e_f()
{
    if( ((nota_oral+nota_scris)/2+puncte_proiect ) >10) return 10;
    else return ((nota_oral+nota_scris)/2+puncte_proiect );
}
Examen_final& Examen_final::operator=(Examen_final& x) {
    Partial::operator=(x);
    puncte_proiect = x.puncte_proiect;
    return *this;
}
istream& operator>>(istream& in, Examen_final& x) {
    in >> static_cast<Partial&>(x);
    cout << "Puncte bonus proiect : ";
    in >> x.puncte_proiect;
    return in;
}
ostream& operator<<(ostream& out, Examen_final& x) {
    out << static_cast<Partial&>(x);
    out << "Puncte pe proiect : " << x.puncte_proiect << endl;
    return out;
}
Examen_final::~Examen_final() {}




class Quiz: public Examen_final
{
protected:
    float puncte_quiz = 0;
public:
    Quiz(char* = "", float = 0, float = 0, float = 0, float = 0);
    Quiz(Quiz&);
    virtual void Afisare();
    void set_pct_quiz(float);
    float medie();
    Quiz& operator=(Quiz&);
    friend istream& operator>>(istream&, Quiz&);
    friend ostream& operator<<(ostream&, Quiz&);
    virtual ~Quiz();
};
Quiz::Quiz(char* s, float ns, float no, float pp, float pq) :Examen_final(s,ns,no,pp) {
    puncte_quiz = pq;
    if(medie()< 5 && medie() != 0 ) refacere_partial();
}
Quiz::Quiz(Quiz& x)
{
    Examen_final::operator=(x);
    puncte_quiz = x.puncte_quiz;
}
void Quiz::Afisare(){
    Examen_final::Afisare();
    cout << "Puncte pe quiz : " << puncte_quiz << endl;
    cout << "Media finala : " << medie() << endl;
}
float Quiz::medie()
{
        int med = 0;
        med = (nota_oral + nota_scris)/2 + puncte_proiect + puncte_quiz;
        if (med >= 10) return 10;
        else return med;
}
Quiz& Quiz::operator=(Quiz& x) {
    Examen_final::operator=(x);
    puncte_quiz = x.puncte_quiz;
    return *this;
}
istream& operator>>(istream& in, Quiz& x) {
    in >> static_cast<Examen_final&>(x);
    cout << "Puncte bonus quiz : ";
    in >> x.puncte_quiz;
    if(x.medie()< 5) x.refacere_partial();
    return in;
}
ostream& operator<<(ostream& out, Quiz& x) {
    out << static_cast<Examen_final&>(x);
    out << "Puncte pe quiz : " << x.puncte_quiz << endl;
    out << "Media finala : " <<  x.medie() << endl;
    return out;
}
Quiz::~Quiz(){}


template <class T>
class CatalogIndividual
{
protected:
    static int nr_matricol_static;
    int nr_matricol;
    int nr_examene = 0;
    Examen** v;
public:
    CatalogIndividual();
    CatalogIndividual(CatalogIndividual&);
    CatalogIndividual<T>& operator+=(Examen&);
    friend istream& operator>>(istream& in, CatalogIndividual<T>& x )
    {
        cout << "Nr examene : "; in >> x.nr_examene;
        delete x.v;
        x.v = new Examen*[x.nr_examene];
        for(int i = 0; i < x.nr_examene; i++){
            int opt;
            cout << "v["<<i<<"] \nTip examen(1 - Examen / 2 - Partial / 3 - Examen final / 4 - Quiz) : ";
            in >> opt;
            char q[20];
            switch(opt){
             case 1:{ in.getline(q, 20); x.v[i] = new Examen;       in >> static_cast<Examen&>(*(x.v[i]));      break;}
             case 2:{ in.getline(q, 20); x.v[i] = new Partial;      in >> static_cast<Partial&>(*(x.v[i]));     break;}
             case 3:{ in.getline(q, 20); x.v[i] = new Examen_final; in >> static_cast<Examen_final&>(*(x.v[i]));break;}
             case 4:{ in.getline(q, 20); x.v[i] = new Quiz;         in >> static_cast<Quiz&>(*(x.v[i]));        break;}
            }
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, CatalogIndividual<T>& x)
    {
        x.Afisare();
        return out;
    }

    void Afisare();
    ~CatalogIndividual();
};

template <class T>
int CatalogIndividual<T>::nr_matricol_static = 1;

template <class T>
CatalogIndividual<T>::CatalogIndividual()
{
    nr_matricol = nr_matricol_static;
    nr_matricol_static++;
}
template <class T>
CatalogIndividual<T>::CatalogIndividual(CatalogIndividual& x)
{
    nr_matricol = x.nr_matricol;
    nr_examene = x.nr_examene;
    delete v;
    v = new Examen*[x.nr_examene];
    for( int i = 0; i < x.nr_examene; i++) v[i] = x.v[i];
}
/*
template <class T>
CatalogIndividual<T>& CatalogIndividual<T>::operator+=(Examen& x) {
    nr_examene++;
    T **newV = new T*[nr_examene];
    for (int i = 0; i < nr_examene-1; i++) newV[i] = v[i];
    //Examen *a = &x;
    newV[nr_examene-1] = &x;
    delete v;
    v = new T*[nr_examene];
    v = newV;
    return *this;
}
*/
template <class T>
CatalogIndividual<T>& CatalogIndividual<T>::operator+=(Examen& x) {
    nr_examene++;
    Examen **newV = new Examen*[nr_examene];
    for (int i = 0; i < nr_examene-1; i++) newV[i] = v[i];
    //Examen *a = &x;
    newV[nr_examene-1] = &x;
    delete this->v;
    v = new Examen*[nr_examene];
    v = newV;

    return *this;
}

template <class T>
void CatalogIndividual<T>::Afisare()
{
    cout << "Numar Matricol Student : " << nr_matricol << endl;
    cout << "Examenele Studentului(" << nr_examene << ") : " << endl;
    for(int i = 0;i < nr_examene; i++){ v[i]->Afisare(); }
    cout << endl;
}
template <class T>
CatalogIndividual<T>::~CatalogIndividual(){
    delete v;
}




template <>
class CatalogIndividual<Examen_final>
{
protected:
    int medie_examen_final;
    static int nr_matricol_static;
    int nr_matricol;
    int nr_examene = 0;
    Examen_final **v;
public:
    CatalogIndividual()
    {
    nr_matricol = nr_matricol_static;
    nr_matricol_static++;
    }

    CatalogIndividual(CatalogIndividual& x)
    {
    nr_matricol = x.nr_matricol;
    nr_examene = x.nr_examene;
    medie_examen_final = x.medie_examen_final;
    delete v;
    v = new Examen_final*[nr_examene];
    for(int i = 0; i  < nr_examene; i++) v[i] = x.v[i];
    }

    CatalogIndividual<Examen_final>& operator+=(Examen_final& x)
    {
    nr_examene++;
    Examen_final **newV = new Examen_final*[nr_examene];
    for (int i = 0; i < nr_examene-1; i++) newV[i] = v[i];
    newV[nr_examene-1] = &x;
    delete this->v;
    v = new Examen_final*[nr_examene];
    v = newV;
    return *this;
    }
    friend istream& operator>>(istream& in, CatalogIndividual<Examen_final>& x)
    {
        cout << "Nr examene : "; in >> x.nr_examene;
        delete x.v;
        x.v = new Examen_final*[x.nr_examene];
        for(int i = 0; i < x.nr_examene; i++){
            int opt;
            cout << "v["<<i<<"] \nTip examen(1 - Examen final / 2 - Quiz ) : ";
            in >> opt;
            char q[20];
            switch(opt){
             case 1:{ in.getline(q, 20); x.v[i] = new Examen_final; in >> static_cast<Examen_final&>(*(x.v[i]));break;}
             case 2:{ in.getline(q, 20); x.v[i] = new Quiz;         in >> static_cast<Quiz&>(*(x.v[i]));        break;}
            }
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, CatalogIndividual<Examen_final>& x)
    {
        x.Afisare();
        return out;
    }
    void Afisare()
    {
    cout << "Numar Matricol Student : " << nr_matricol << endl;
    cout << "Mediile finale la examenele finale : (" << nr_examene << ") : ";
    for(int i = 0;i < nr_examene; i++){
    try{
        if(v[i]->medie_e_f() == 0) throw 1;
        cout << v[i]->medie_e_f() << ", ";
        }
        catch(...){
            cout << "eroare";
        }
    }
    cout << endl;

    }

    ~CatalogIndividual(){ delete v; }
};
template<>
int CatalogIndividual<Examen_final>::nr_matricol_static = 1;


int main()
{
    Examen e1("ASC", 7);
    Partial p1("Algebra", 5, 5);
    Examen_final ef1("LMC", 5, 6, 1);
    Quiz q1("LFA", 5, 5 ,1 , 1);
    CatalogIndividual<Partial> ci1;

    cin >> ci1;
    cout << ci1;


    Examen* ptr = &ef1;
    Quiz* pt1         = dynamic_cast<Quiz*>(ptr);
    Examen_final* pt2 = dynamic_cast<Examen_final*>(ptr);
    Partial* pt3      = dynamic_cast<Partial*>(ptr);
    if(pt1) cout << *pt1;
    else if(pt2) cout << *pt2;
    else cout << *pt3;



    int n;
    cout << "n obiecte, n = "; cin >> n;
    vector<CatalogIndividual<Examen_final> > ci2(n);
    for(int i = 0; i < n; i++){
        cin >> ci2[i];
    }
    for(int i = 0; i < n; i++){
        cout << ci2[i];
    }
    return 0;
}
