#include<iostream>
#include <fstream>

using namespace std;

ifstream f ("xsizero.in");
ofstream g ("xsizero.out");

int m[5][5];
int answer[60000];
char ch;

int convert(char ch)
{
    if(ch == '.')
        return 0;

    if(ch == 'X')
        return 1;

    return 2;
}

int mat_toCode(int m[5][5])
{
  int cod = 0;

    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        cod = cod * 3 + m[i][j];
    }

  return cod;
}

void code_toMat(int cod)
{
    for(int i = 3; i >= 1; i--)
    {
        for(int j = 3; j >= 1; j--)
        {
            m[i][j] = cod % 3;
            cod /= 3;
        }
    }
}

int getAnswer(int m[5][5])
{
    for(int i = 1; i <= 3; i++)
    {
        if(m[i][1] == m[i][2] && m[i][2] == m[i][3] && m[i][1] != 0)
            return m[i][1];

        if(m[1][i] == m[2][i] && m[2][i] == m[3][i] && m[1][i] != 0)
            return m[1][i];
    }

    if(m[1][1] == m[2][2] && m[2][2] == m[3][3] && m[1][1] != 0)
        return m[1][1];

    if(m[1][3] == m[2][2] && m[2][2] == m[3][1] && m[1][3] != 0)
        return m[1][3];

    return 3;
}

void bkt(int cod, int l)
{

    if(answer[cod]) //deja am trecut prin cazul asta
        return;

    if(getAnswer(m) <= 2 || l == 10)  //ori pot sa zic deja raspunsul si numai are sens sa continui
    {                                   //ori am terminaat matricea si tot nu am gasit un answer <= 2 => answerfinal = draw
        answer[cod] = getAnswer(m);
        return;
    }

    int x, y;

    if(l % 2)
        x = 1, y = 2;   //este randul lui x si apoi al lui 0
    else
        x = 2, y = 1;   //este randul lui 0 si apoi al lui x

    code_toMat(cod);

    bool v[4];

    v[0] = v[1] = v[2] = v[3] = 0;

    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            if(m[i][j] == 0)
            {
                m[i][j] = x;
                bkt(mat_toCode(m), l + 1);  //marchez orice posibilitate de completare a celui care e la rand ( toate posibilitatile de a pune un 0 /respectiv x )
                v[answer[mat_toCode(m)]] = 1 ;  //memorez raspunsurile intalnite
                m[i][j] = 0;    //o pastrez nemodificata
            }
        }
    }

    if(v[x])
        answer[cod] = x;

    else if(v[3])
        answer[cod] = 3;

    else
        answer[cod] = y;
}

int main()
{
    bkt(0, 1);

    int c = 1;

    while(f >> ch)
    {
        m[1][1] = convert(ch);

        for(int i = 1; i <= 3; i++)
        {
            for(int j = 1 + (i == 1); j <= 3; j++)
            {
                f >> ch;
                m[i][j] = convert(ch);
            }
        }

        int val = mat_toCode(m);

        if(!answer[val])    //matricile invalide sunt cele ramase nemarcate
            g << "Testul #" << c << ": invalid\n";
        else if(answer[val] == 1)
            g << "Testul #" << c << ": win\n";
        else if(answer[val] == 2)
            g << "Testul #" << c << ": lose\n";
        else
            g << "Testul #" << c << ": draw\n";
        c++;
  }

  return 0;
}
