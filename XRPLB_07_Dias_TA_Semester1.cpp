#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib> 

using namespace std;

const int LEBAR = 30;
const int TINGGI = 20;

int posisiPemain;
int skor;
int coba;
bool gameOver;

struct Objek 
{
    int x, y;
};

vector<Objek> daftarObjek;

void Setup() 
{
    srand(time(0));
    gameOver = false;
    posisiPemain = LEBAR / 2; 
    skor = 0;
    daftarObjek.clear();
}


void gambar() 
{
    
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    
    for (int i = 0; i < LEBAR + 2; i++)
	cout << "-";
    cout << endl;

    
    for (int y = 0; y < TINGGI; y++) 
	{
        cout << "|"; 
        for (int x = 0; x < LEBAR; x++)
		{
            if (y == TINGGI - 1 && x == posisiPemain)
			{
                cout << "X"; 
            }
			else
			{
                bool adaObjek = false;
                for (size_t i = 0; i < daftarObjek.size(); i++)
				{
                    if (daftarObjek[i].x == x && daftarObjek[i].y == y)
					{
                        cout << "V"; 
                        adaObjek = true;
                        break;
                    }
                }
                if (!adaObjek)
				cout << " ";
            }
        }
        cout << "|" << endl; 
    }

   
    for (int i = 0; i < LEBAR + 2; i++)
	cout << "-";
    cout << endl;

    
    cout << "SKOR: " << skor << endl;
    cout << "Tekan 'A' (Kiri), 'D' (Kanan), atau 'X' untuk keluar." << endl;
}


void Input()
{
    if (_kbhit())
	{
        switch (_getch())
		{
            case 'a':
            case 'A':
                if (posisiPemain > 0) posisiPemain--;
                break;
            case 'd':
            case 'D':
                if (posisiPemain < LEBAR - 1) posisiPemain++;
                break;
            case 'x':
            case 'X':
                gameOver = true;
                break;
        }
    }
}


void Logic()
{
    
    if (rand() % 2 == 0)
	{
        Objek baru; 
        baru.x = rand() % LEBAR;
        baru.y = 0;
        daftarObjek.push_back(baru);
    }

    for ( size_t i = 0; i < daftarObjek.size(); i++)
	{
        daftarObjek[i].y++;

        
        if (daftarObjek[i].y >= TINGGI)
		{
            daftarObjek.erase(daftarObjek.begin() + i);
            skor += 10; 
            i--;
            continue;
        }

        
        if (daftarObjek[i].y == TINGGI - 1 && daftarObjek[i].x == posisiPemain)
		{
            gameOver = true;
        }
    }
}

int main()
{
	
    
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    system("cls");

    Setup();

    
    while (!gameOver) 
	{
        gambar();
        Input();
        Logic();
        Sleep(0.1); 
    }

    system("cls");
    cout << "=========================" << endl;
    cout << "       GAME OVER!        " << endl;
    cout << "=========================" << endl;
    cout << "Skor Akhir Anda: " << skor << endl;
    cout << "Terima kasih sudah bermain!" << endl;
	
	system ("pause");
    return 0;
}
