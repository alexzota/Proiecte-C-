#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

template <class T>
class data
{
protected:
    T zi,luna,an;
public:
    data(T x = 0, T y = 0, T z = 0) : zi(x), luna(y), an(z) {}
    void set_zi(T a)  { zi = a; }
    void set_luna(T a)  {luna = a;}
    void set_an(T a)  { an = a;}

    T get_zi(){return zi; }
    T get_an() {return an; }
    T get_luna() {return luna; }

    void afisare() { cout << zi << "." << luna << "." << an; }

    ~data() {}
};

class participant
{
protected:
    string nume;
    string CNP;
    float punctaj;
public:
    participant(string n = "", string c = "", float p = 0) : nume(n), CNP(c), punctaj(p) { }
    string get_nume() {return nume;}
    string get_CNP() { return CNP; }
    float get_punctaj() {return punctaj;}
    void set_nume(string a) { nume = a; }
    void set_CNP(string a) {CNP = a; }
    void set_punctaj(float a) { punctaj = a; }
    friend istream& operator >> ( istream& in, participant& x)
    {
        string aux;
        cout << "Nume : "; in >> aux; x.set_nume(aux);
        cout << "CNP : "; in >> aux; x.set_CNP(aux);
        cout << "Punctaj : "; in >> x.punctaj;
        return in;
    }
    friend ostream& operator<<(ostream& out, participant& x)
    {
        out << "Nume : " << x.nume;
        out << "\nCNP : " << x.CNP << endl;
        out << "Punctaj : " << x.punctaj << endl << endl;
    }
    ~participant(){}
};
int comp_alf(participant a, participant b)
{
    return ( a.get_nume() < b.get_nume() );
}
int comp_med(participant a, participant b)
{
    return (a.get_punctaj() < b.get_punctaj());
}


class activitate
{
protected:
    static int nr_participanti;
    string denumire;
    data<int> data_inceput;
    vector<participant> participanti;
    vector<participant> premiati;
public:
    activitate(string den = "", data<int> d = {0,0,0}  )
    {
        denumire = den;
        data_inceput = d;
    }
    friend istream& operator>>(istream& in, activitate& x)
    {
        cout << "\nIntrodu data : dd\mm\yyyy (/ = enter)\n";
        int zi,luna,an;
        in >> zi >> luna >> an;
        x.data_inceput.set_zi(zi);
        x.data_inceput.set_luna(luna);
        x.data_inceput.set_an(an);
        cout << "\nNr participanti = "; in >> x.nr_participanti;
        x.participanti.resize(x.nr_participanti);
        for(int i = 0; i < x.nr_participanti; i++) {
                try{
                in >> x.participanti[i];
                string cnp = x.participanti[i].get_CNP();
                int opt = 0;
                for(int j = 0; j < x.participanti.size() && opt == 0 && j!=i; j++){
                    if(x.participanti[i].get_CNP() == cnp ) { cout << "CNP deja folosit"; opt = 1; throw 1; }
                 }
                }
                catch(...) {
                    cout << "Reintroduceti candidatul cu un CNP valid.\n";
                    in >> x.participanti[i];
                        }
        }



        return in;
    }
    friend ostream& operator<<(ostream& out, activitate& x)
    {
        out << "Data : " << x.data_inceput.get_zi() << "." << x.data_inceput.get_luna() << "." << x.data_inceput.get_an() << endl;
        out << "Nr participanti : " << x.nr_participanti << endl;
        for(int i = 0; i < x.nr_participanti; i++) out << x.participanti[i];
        return out;
    }
    void adaugare_participant()
    {
        nr_participanti++;
        participant aux;
        cin >> aux;
        participanti.push_back(aux);
    }
    void calcul_premiati()
    {
        vector<int> medii;
        int medii_dif = 0, opt = 0;
        sort(participanti.begin(), participanti.end(), comp_med);
        for(int i = 0; medii_dif != 4 ; i++){
                int medie = participanti[i].get_punctaj();
                for(int j = 0; j < premiati.size() && opt == 0; j++){
                    if( medie == premiati[i].get_punctaj()) opt = 1;
                }
            if ( opt == 0 )   {
                premiati.push_back(participanti[i]);
                medii_dif++;
            }
            else premiati.push_back(participanti[i]);
        }
    }
    void afisare_part()
    {
        cout << *this;
    }
    void afisare_alfabetica()
    {
        sort(participanti.begin(), participanti.end(), comp_alf);
        cout << *this;
    }
    void afisare_prem()
    {
        if(premiati.size() != 0) sort(premiati.begin(), premiati.end(), comp_med);
        for(int i = 0; i < premiati.size(); i++) cout << premiati[i];
    }
    ~activitate(){}

};
int activitate::nr_participanti = 0;


class curs : public activitate
{
protected:
    int durata;
    int nr_credite;
public:
    curs(string den = "", data<int> d = {0,0,0}, int da = 0, int nr = 0) : activitate(den, d), durata(da), nr_credite(nr) {}
    void afis_prof()
    {
        sort(participanti.begin(), participanti.end(), comp_alf);
        for(int i = 0; i < participanti.size(); i++){
            string zi, luna,an;
            zi = participanti[i].get_CNP().substr(2,2);
            luna = participanti[i].get_CNP().substr(4,2);
            an = participanti[i].get_CNP().substr(6,2);
           /* int zii = stoi(zi);
            int lunaa = stoi(luna);
            int ann = stoi (an); */

            //if ( data_inceput.get_an() < ann+18 ) cout << participanti[i];
            /*
                else if ( get_an == ann+18)
                    if( get_luna() < lunaa ) cout << participanti[i];
                        else if( get_luna == luna)
                            if( get_zi() < zii ) cout << participanti[i];
                                */

        }
    }
    ~curs() {}
};



class concurs : public activitate
{
protected:
    int durata;
    bool online;
    string URL;
public:
    concurs(string den = "", data<int> d = {0,0,0}, bool on = 0, int dur = 0, string UR  = "") : activitate(den, d), durata(dur), online(on) , URL(UR){}

    friend istream& operator>>(istream& in, concurs& x)
    {

        in >> static_cast<activitate&>(x);
        cout << "\nConcursul e online? "; in >> x.online;
        if(x.online == 0) {cout << "Durata:"; in >> x.durata;}
        else if(x.online == 1) {cout << "URL : "; in >> x.URL;}
        return in;
    }
    friend ostream& operator<<(ostream& out, concurs& x)
    {
        out <<  static_cast<activitate&>(x);
        if(x.online == 1) {out << "Concursul este online\nURL = " << x.URL;}
        else out << "Concursul este offline si are durata de " <<x.durata << "zile";
        return out;
    }

    ~concurs(){}
};


class serie_activitati
{
private:
    static int nr_concursuri, nr_cursuri;
    vector<concurs> concursuri;
    vector<curs> cursuri;
public:
    serie_activitati(){}
    void afis_prem_con()
    {
        for(int i = 0; i < concursuri.size(); i++) concursuri[i].afisare_prem();
    }
    friend istream& operator>>(istream& in, serie_activitati& x)
    {
        cout << "\nCate concursuri vrei sa adaugi : "; in >> x.nr_concursuri;
        x.concursuri.resize(nr_concursuri);
        for(int i = 0; i < x.nr_concursuri; i++){
            in >> x.concursuri[i];
        }
        cout << "\nCate cursuri vrei sa adaugi : "; in >> x.nr_cursuri;
        for(int i = 0; i < x.nr_cursuri; i++){
            curs c1;
            in >> c1;
            x.cursuri.push_back(c1);
        }
        return in;
    }
    friend ostream& operator<<(ostream& out , serie_activitati &x)
    {
        out << "\nParticipanti cursuri : \n";
        for(int i = 0; i < x.nr_cursuri; i++) out << x.cursuri[i];
        out << "\nParticipanti concursuri : \n";
        for(int i = 0; i < x.nr_cursuri; i++) out << x.concursuri[i];
    }
    ~serie_activitati(){}
};
int serie_activitati::nr_concursuri = 0;
int serie_activitati::nr_cursuri = 0;

int main()
{
    int x;
    curs c1;
    serie_activitati sa;

    cout << "1 - Adaugare n participanti la curs\n";
    cout << "2 - Adaugare n participanti la n activitati de tipul dorit";
    cout << endl << "3 - Afisare participanti grupati pe activitati";
    cout << endl << "4 - Afisare premianti concurs ";
    cout << "\nIntrodu opt\n";
    cin >> x;
    while( x)
    {
        switch(x){
         case 1: {cin >> c1;break;}
         case 2: {cin >>sa; break;}
         case 3: {cout << sa; break;}
         case 4: { sa.afis_prem_con(); break;  }
        }
        cout << "introdu opt : "; cin >> x;
    }

    return 0;
}
