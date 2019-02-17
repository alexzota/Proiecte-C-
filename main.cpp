#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // getch fara sa astepti pt enter
#include <Windows.h> //grafica
#include <stack>
#define S 0
#define E 1

using namespace std;

void vecini(int &l, int &c, vector<vector<int> > &vizitat, stack< pair<int,int> > &st, int &marime_maze)
{

    if (c == 0 && l == 0)
    {
        if( vizitat[l+1][c] && vizitat[l][c+1])
        {
            st.pop();
        }
    }
    else if (c == 0 && l == marime_maze-1)
    {
        if( vizitat[l-1][c] && vizitat[l][c+1])
        {
            st.pop();
        }
    }
    else if (c == 0)
    {
        if(  vizitat[l+1][c] && vizitat[l-1][c] && vizitat[l][c+1])
        {
            st.pop();
        }
    }
    else if (l == 0 && c == marime_maze-1)
    {
        if(  vizitat[l+1][c] && vizitat[l][c-1])
        {
            st.pop();
        }
    }
    else if (l == 0)
    {
        if( vizitat[l+1][c] && vizitat[l][c-1] && vizitat[l][c+1])
        {
            st.pop();
        }
    }
    else if (l == marime_maze-1 && c == marime_maze-1)
    {

        if( vizitat[l-1][c] && vizitat[l][c-1])
        {
            st.pop();
        }
    }
    else if (c == marime_maze-1)
    {
        if(  vizitat[l-1][c] && vizitat[l][c-1] && vizitat[l+1][c] )
        {
            st.pop();
        }
    }
    else if (l == marime_maze-1)
    {
        if(  vizitat[l-1][c] && vizitat[l][c-1] && vizitat[l][c+1] )
        {
            st.pop();
        }
    }
    else if ( c > 0 && l > 0 && c < marime_maze-1 && l < marime_maze-1 && vizitat[l][c-1] && vizitat[l-1][c] && vizitat[l][c+1]&& vizitat[l+1][c])
    {
        st.pop();
    }
}


void afisare(vector< vector<int> > &maze, vector< vector< vector<int> > >&vecin, int l=0, int c=0)
{
    cout << "    ";
    for(int i = 1 ; i < maze.size(); i++)
        cout << "_ ";
    cout <<endl;
    for(int i = 0 ; i < maze.size(); i++)
    {
        for(int j = 0; j < maze[i].size(); j++)
        {
            if(j == 0)
                cout << "| ";

            if( j== c && i == l)
                cout << "X";
            if(vecin[i][j][S]==0)
                cout << "_";
            else
                cout << " ";
            if(vecin[i][j][E]==0)
                cout << "|";
            else
                cout << " ";

        }
        cout << endl;
    }


    cout << "A - stanga\nW - sus\nD - dreapta\nS - jos\nX - EXIT ";
}

void afisare_stack(stack < pair < int,int> > st, vector<vector<int> > vizitat)
{
    cout << endl << "Stack : ";
    while(st.empty() == 0)
    {
        pair<int,int> aux = st.top();
        if (vizitat[aux.first][aux.second])
            cout << "[" <<aux.first<<","<< aux.second << "] -  ";
        else
            cout <<aux.first<<","<< aux.second << " -  ";
        st.pop();
    }
    cout << endl;
}

void generare_labirint(vector< vector<int> > &maze, vector< vector< vector<int> > >&vecin)
{
    stack< pair<int,int> > st;
    st.push(make_pair(0,0));
    int marime_maze = maze.size();
    vector< vector< int> > vizitat(marime_maze, vector<int>(marime_maze));
    vizitat[0][0] = 1;
    int contor = 0;
    while(st.empty()== 0 && contor < 200)
    {
        int random = rand()%4;
        pair<int,int> top = st.top();
        //afisare_stack(st, vizitat);
        int l = top.first;
        int c = top.second;
        //afisare(maze,vecin, l, c);
        // cout << contor++ << " top : " << l << ", " << c << " ";
        switch(random)
        {
        case 0:
        {
            //cout << "left ";
            if(c > 0 && vizitat[l][c-1] == 0)
            {
                st.push(make_pair(l, c-1));    // left
                vizitat[l][c-1] = 1;
                vecin[l][c-1][E] = 1;
            }
            else
                vecini(l,c,vizitat,st,marime_maze);
            cout << endl;
            break;
        }
        case 1:
        {
            //cout << "up ";
            if(l > 0 && vizitat[l-1][c] == 0)
            {
                st.push(make_pair(l-1, c));    // up
                vizitat[l-1][c]= 1;
                vecin[l-1][c][S] = 1;
            }
            else
                vecini(l,c,vizitat,st,marime_maze);
            cout << endl;
            //if ( vizitat[l][c-1] && vizitat[l-1][c] && vizitat[l][c+1]&& vizitat[l+1][c])

            break;
        }
        case 2:
        {
            //cout << "right ";
            if(c < marime_maze-1 && vizitat[l][c+1]==0)
            {
                st.push(make_pair(l, c+1));    // right
                vizitat[l][c+1]= 1;
                vecin[l][c][E] = 1;
            }
            else
                vecini(l,c,vizitat,st,marime_maze);
            cout << endl;
            break;
        }
        case 3:
        {
            //cout << "down ";
            if(l < marime_maze-1 && vizitat[l+1][c] == 0)
            {
                st.push(make_pair(l+1, c));    // down
                vizitat[l+1][c]= 1;
                vecin[l][c][S] = 1;
            }
            else
                vecini(l,c,vizitat,st,marime_maze);
            cout << endl;
            break;
        }
        }
    }
    vecin[marime_maze-1][marime_maze-1][E] = 1;
}


int main()
{
    srand (time(NULL));
    int marime_maze;
    system("CLS");
    string welcome_text1 = "SALUT, VEI PARTICIPA LA UN JOC DE TIP LABIRINT, SCOPUL TAU ESTE SA GASESTI IESIREA ";
    string welcome_text2 = "INTRODU MARIMEA LABIRINTULUI ( PREFERABIL > 10 )";
    cout << endl;
    cout << "\n\n\n\n\n\n\n    \t\t\t";
    for (auto ch : welcome_text1)
    {
        cout << ch;
        Sleep(5);
    }
    cout << endl << endl;
    cout << "    \t\t\t\t  ";
    for (auto ch : welcome_text2)
    {
        cout << ch;
        Sleep(5);
    }
    cout << endl << endl << endl;


    cin >> marime_maze;
    vector< vector<int> > maze(marime_maze, vector<int>(marime_maze));

    maze[0][0] = -1;
    maze[marime_maze-1][marime_maze-1] = 1;


    string begin_text1 = "LAYOUT-UL  LABIRINTULUI, MULT NOROC";
    cout << "    \t\t\t\t  ";
    for (auto ch : begin_text1)
    {
        cout << ch;
        Sleep(10);
    }
    cout << "\n\n\n";

    for(int i = 0 ; i < maze.size(); i++)
    {
        for(int j = 0; j < maze[i].size(); j++)
        {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    vector<vector<vector<int>>> vecin(marime_maze, vector<vector<int>>(marime_maze, vector<int>(2)));
    generare_labirint(maze, vecin);


    int l = 0, c = 0;
    system("CLS");
    afisare(maze, vecin, l, c);
    char in = _getch();
    while(l != marime_maze-1 || c != marime_maze-1 )
    {
        switch(in)
        {
        case 'a':
        {
            if ( c > 0 && vecin[l][c-1][E])
            {
                c--;
                afisare(maze, vecin, l, c);
            }
            break;
        }
        case 'w':
        {
            if ( l > 0 && vecin[l-1][c][S])
            {
                l--;
                afisare(maze, vecin, l, c);
            }
            break;
        }
        case 'd':
        {
            if ( c < marime_maze-1 && vecin[l][c][E])
            {
                c++;
                afisare(maze, vecin, l, c);
            }
            break;
        }
        case 's':
        {
            if ( l < marime_maze-1 && vecin[l][c][S])
            {
                l++;
            }
            break;
        }
        case 'x':{return 0;}
        }
        system("CLS");
        afisare(maze, vecin, l, c);
        if (l == marime_maze-1 && c== marime_maze-1){ cout << "\nFELICITARI, AI INVINS LABIRINTUL"; return 0;}
        in = _getch();
    }


    return 0;
}

