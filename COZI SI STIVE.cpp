#include <iostream>

using namespace std;

class Complex{
protected:
    float re, im;
    static int contor;
public:
    Complex();
    Complex(float);
    Complex (float, float);
    Complex(Complex&);

    Complex& operator=(Complex&);
    friend ostream& operator<<(ostream&, Complex&);
    friend istream& operator>>(istream&, Complex&);

    void set_re(float);
    float get_re();

    void set_im(float);
    float get_im();

    static int get_contor(){ return contor; }

    ~Complex();
};
int Complex::contor = 0;
Complex::Complex(){
    contor++;
    this->re = 0;
    this->im = 0;
}
Complex::Complex(float re){
    contor++;
    this->re = re;
    this->im = 0;
}
Complex::Complex(float re, float im){
    contor++;
    this->re = re;
    this->im = im;
}
Complex::Complex(Complex &a){
    this->re = a.re;
    this->im = a.im;
}
Complex& Complex::operator=(Complex &b)
{
    this->im = b.im;
    this->re = b.re;
    return *this;
}
ostream& operator<<(ostream& out, Complex& com)
{
    out << com.re;
    if ( com.im < 0) out << com.im <<"i" << endl;
    else if (com.im > 0) out << " + " << com.im << "i" << endl;
    return out;
}
istream& operator>>(istream& in, Complex& C)
{
    cout << "re = "; in >> C.re;
    cout << "im = "; in >> C.im;
    return in;
}
void Complex::set_re(float re)
{
    this->re = re;
}
float Complex::get_re()
{
    return this->re;
}
void Complex::set_im(float im)
{
    this->im = im;
}
float Complex::get_im()
{
    return this->im;
}
Complex::~Complex(){
    this->re = 0;
    this->im = 0;
}



// disclaimer : puteam sa fac functii virtuale pure aici dar nu stiam daca in barem trebuie sa fac adaugare/stergere si la vector
class Vector{
protected:
    int dim;
    Complex *v;
public:
    Vector();
    Vector(float, float);
    Vector(Vector&);
    void adaugare();
    virtual void adaugare(float, float);
    virtual void adaugare(Complex& );
    virtual void stergere() ;
    Complex* get_v(){ return this->v; }
    int get_dim() { return this->dim;}

    friend ostream& operator<<(ostream&, Vector&);
    friend istream& operator>>(istream&, Vector&);
    Vector& operator=(Vector&);

    void cout_cc() { cout << "cc1\n"; }

    void afisare();
    bool metoda() { for ( int i = 0; i < dim; i++) if (v[i].get_im() != 0 && v[i].get_re() == 0) return 1;
                                                    return 0;
                            }

    ~Vector();
};
Vector::Vector(){
    this->v = NULL;
    this->dim = 0;
}
Vector::Vector(float re, float im){
    dim = 1;
    v = new Complex[dim];
    v[0].set_re(re);
    v[0].set_im(im);
}
Vector::Vector(Vector& a){
    this->dim = a.dim;
    this->v = new Complex[this->dim];
    for (int i = 0; i < a.dim; i++) this->v[i] = a.v[i];
}
void Vector::adaugare()
{
    this->dim++;
    Complex co;
    cin >> co;
    Complex *newV = new Complex[this->dim];
    for (int i = 0; i < this->dim-1; i++) newV[i] = this->v[i];
    newV[this->dim-1] = co;
    delete this->v;
    this->v = new Complex[this->dim];
    this->v = newV;
}
void Vector::adaugare(float re, float im)
{
    this->dim++;
    Complex co(re, im);
    Complex *newV = new Complex[this->dim];
    for (int i = 0; i < this->dim-1; i++) newV[i] = this->v[i];
    newV[this->dim-1] = co;
    delete this->v;
    this->v = new Complex[this->dim];
    this->v = newV;
}
void Vector::adaugare(Complex& co)
{
    this->dim++;
    Complex *newV = new Complex[this->dim];
    for (int i = 0; i < this->dim-1; i++) newV[i] = this->v[i];
    newV[this->dim-1] = co;
    delete this->v;
    this->v = new Complex[this->dim];
    this->v = newV;
}
void Vector::stergere()
{
    if (this->v == NULL) cout << "Vectorul este deja gol\n";
    else{
    this->dim--;
    Complex *newV = new Complex[this->dim];

    int poz;
    cout << "Pozitia pe care se afla numarul pe care vrei sa-l stergi: "; cin >> poz;
    if (poz <= 0){
        for (int i = 0; i < this->dim; i++) newV[i] = this->v[i+1];
        delete this->v;
        this->v = new Complex[this->dim];
        this->v = newV;
        }
    else if ( poz >= this->dim){
        for (int i = 0; i < this->dim; i++) newV[i] = this->v[i];
        delete this->v;
        this->v = new Complex[this->dim];
        this->v = newV;
        }
    else{
        for ( int i = 0, j = 0; i < this->dim; i++) if ( i != poz ) { newV[j] = this->v[i]; j++;}
        delete this->v;
        this->v = new Complex[this->dim];
        this->v = newV;
        }
    }
}
ostream& operator<<(ostream& out, Vector& A)
{
    out << "\n-Afisare-\nDim = " << A.dim << "\n";
    for (int i = 0; i < A.dim; i++)
        out << A.v[i];
    return out;
}
istream& operator>>(istream& in, Vector& A)
{
    cout << "dim =  : ";
    in >> A.dim;
    A.v = new Complex[A.dim];
    for ( int i = 0; i < A.dim; i++) {cout << "w[" << i << "]\n"; in >> A.v[i];}
    return in;
}
void Vector::afisare()
{
    for ( int i = 0; i < this->dim; i++)
        cout << "re : " << this->v[i].get_re() << ", im :" << this->v[i].get_im()<< endl;
}
Vector::~Vector(){
    cout << "Vector distrus\n";
    this->dim = 0;
    delete this->v;
}





class Stiva : public Vector{
public:
    Stiva();
    Stiva(float, float);
    Stiva(Vector&);
    void adaugare(float, float);
    void adaugare(Complex&);
    void stergere();
    void cout_ss() { cout << "ss\n"; }
    ~Stiva(){cout << "Stiva distrusa\n"; this->dim = 0;delete this->v;};
};
Stiva::Stiva(): Vector() {}
Stiva::Stiva(float re, float im): Vector(re, im) {}
Stiva::Stiva( Vector& V): Vector(V) {}
void Stiva::adaugare(float re, float im)
{
    this->dim++;
    Complex co(re, im);
    Complex *newV = new Complex[this->dim];
    for (int i = 0; i < this->dim-1; i++) newV[i] = this->v[i];
    newV[this->dim-1] = co;
    delete this->v;
    this->v = new Complex[this->dim];
    this->v = newV;

}
void Stiva::adaugare(Complex& co){
    this->dim++;
    Complex *newV = new Complex[this->dim];
    for (int i = 0; i < this->dim-1; i++) newV[i] = this->v[i];
    newV[this->dim-1] = co;
    delete this->v;
    this->v = new Complex[this->dim];
    this->v = newV;
}
void Stiva::stergere()
{
    if ( dim == 0) cout << "Stiva este deja goala";
    else{
    this->dim--;
    Complex *newV = new Complex[this->dim];
    for (int i = 0; i < this->dim; i++) newV[i] = this->v[i];
    delete this->v;
    this->v = new Complex[this->dim];
    this->v = newV;
    }
}






class Coada : public Vector{
public:
    Coada();
    Coada(float, float);
    Coada(Vector&);
    void adaugare(float, float);
    void adaugare(Complex&);
    void stergere();
    void cout_cc2() { cout << "cc2\n"; }
    ~Coada(){cout << "Coada distrusa\n";this->dim = 0;delete this->v;};
};
Coada::Coada( ) : Vector() {}
Coada::Coada(float re, float im):Vector(re,im){ };
Coada::Coada(Vector& V) : Vector(V) {}
void Coada::adaugare(float re, float im)
{

    this->dim++;
    Complex *newV = new Complex[this->dim];
    for (int i = 0; i < this->dim-1; i++) newV[i] = this->v[i];
    Complex co(re, im);
    newV[this->dim-1] = co;
    delete this->v;
    this->v = new Complex[this->dim];
    this->v = newV;
}
void Coada::adaugare(Complex& co){
    this->dim++;
    Complex *newV = new Complex[this->dim];
    for (int i = 0; i < this->dim-1; i++) newV[i] = this->v[i];
    newV[this->dim-1] = co;
    delete this->v;
    this->v = new Complex[this->dim];
    this->v = newV;
}
void Coada::stergere()
{
    if ( dim == 0) cout << "Coada este deja goala";
    else{
    this->dim--;
    Complex *newV = new Complex[this->dim];
    for (int i = 1; i < this->dim+1; i++) newV[i-1] = this->v[i];
    delete this->v;
    this->v = new Complex[this->dim];
    this->v = newV;
    }
}

int main()
{
    int optiune;
    Coada coada;
    Stiva stiva;
    cout << "1 - Adaugare nr complex la stiva\n11 - CIN >> STIVA\n2 - Stergere nr stiva\n3 - COUT <<  STIVA\n4 - metoda() stiva\n";
    cout << "\n5 - Adaugare nr complex la coada\n55 - CIN >> COADA\n6 - Stergere nr coada\n7 - COUT << COADA\n8 - metoda() coada\n";
    cout << "\n9 - nr total de nr complexe(static var, functie)\n10 - memorarea a n cozi\n12 - upcast(stergere din coada)\n13 - downcast(adaugare vector)\n";
    cout << "Introdu optiunea : "; cin >> optiune;
    while(optiune){
        switch(optiune){
    case 1:{stiva.Vector::adaugare(); break;}
    case 11:{cin>>stiva; break;}
    case 2:{ stiva.stergere(); break;}
    case 3:{stiva.afisare();break;}
    case 4:{ cout << endl << stiva.metoda() << endl;break;}
    case 5:{coada.Vector::adaugare(); break;}
    case 55:{cin>>coada; break;}
    case 6:{ coada.stergere(); break;}
    case 7:{coada.afisare();break;}
    case 8:{ cout << endl << coada.metoda() << endl;break;}
    case 9 :{cout << Complex::get_contor();}
    case 10:{int n; cout << "n=";cin >> n; Coada *vectC = new Coada[n]; for(int i = 0; i < n; i++) cin >> vectC[i];break ;}
    case 12 :{Vector &vect = coada; vect.stergere(); break; }
    case 13 :{Vector vec(1,1); cout << vec; Coada *co = (Coada *)&vec; co->adaugare(2,2); cout << "Iar dupa : " << vec; break; }
        }
    cout << "\nIntrodu optiunea : "; cin >> optiune;
    }
    return 0;
}
