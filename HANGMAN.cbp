#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <time.h>
#include <random>
#include <Windows.h>
using namespace std;

ifstream f("HANGMAN_cuvinte.txt");

int main()
{
    srand(time(NULL));
    int random = rand()% 1000;
    string cuv;
    for(int i = 0; i < random; i++)
        f >> cuv;

    string cuv_ghicit = cuv;
    char ch;
    ch = cuv[0];
    for(int i = 0; i < cuv_ghicit.length(); i++)
    {
        if (cuv_ghicit[i] != ch)
        {
            cuv_ghicit[i] = '_';
        }

    }
    int contor = 12;
    vector<char> folosite;
    while(cuv_ghicit!= cuv && contor > 0)
    {

        system("CLS");
        cout << "\t\tSALUT, VEI PARTICIPA LA UN JOC DE TIP SPANZURATOARE, SCOPUL TAU ESTE SA GHICESTI CUVANTUL \n";
        cout <<  "\t\t\t\tMAI AI ";
        cout << contor <<  " INCERCARI RAMASE ";
        cout << endl;
        cout << "\n\n\n\n\n\n\n    \t\t";
        cout << endl <<"\t\t\t\t" <<  cuv_ghicit;


        cout << "\nLITERE DEJA FOLOSITE : ";
        for(int i = 0; i < folosite.size(); i++)
            cout << folosite[i] << " ";
        cout << "\nIntrodu o litera : ";
        ch = _getch();
        int optt = 0;
        for(int i = 0; i < folosite.size(); i++)
            if (ch == folosite[i])
            {
                cout << " AI MAI FOLOSIT LITERA DEJA";
                optt = 1;
            }
        if(optt == 0)
        {
            int opt = 0;
            for(int i = 0; i < cuv.length(); i++)
            {
                if (cuv[i] == ch)
                {
                    cuv_ghicit[i] = ch;
                    opt = 1;
                }
            }
            if (opt == 0)
            {
                contor--;
                folosite.push_back(ch);
            }
        }
    }

    if( contor == 0 && cuv_ghicit != cuv )
    {
        system("CLS");
        cout << "MAI MULT NOROC DATA VIITOARE, CUVANTUL ERA : " << cuv;
    }
    else if ( contor > 0 && cuv_ghicit == cuv)
    {
        system("CLS");
        cout << "\t\tSALUT, VEI PARTICIPA LA UN JOC DE TIP SPANZURATOARE, SCOPUL TAU ESTE SA GHICESTI CUVANTUL \n";
        cout <<  "\t\t\t\tMAI AI ";
        cout << contor <<  " INCERCARI RAMASE ";
        cout << endl;
        cout << "\n\n\n\n\n\n\n    \t\t";
        cout << endl <<"\t\t\t\t" <<  cuv_ghicit;


        cout << "\nLITERE DEJA FOLOSITE : ";
        for(int i = 0; i < folosite.size(); i++)
            cout << folosite[i] << " ";

        cout  << "\n\n\n\nFELICITARI, AI GHICIT CUVANTUL "<<cuv <<" CU " << contor << " INCERCARI RAMASE\n\n\n\n";
    }


    return 0;
}
