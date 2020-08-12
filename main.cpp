//  main.cpp
//  TiCuB
//  Created by Adam M Seers on 2019-12-14.
//  Copyright © 2019 Seers Games. All rights reserved.

#include "conio.hpp"
#include <iostream>
#include <unistd.h>
//#include <curses.h>
#include <cstdlib>
#include <thread>
//#include <term.h>
#include <math.h>

using namespace std;

//------------------ Déclarations
string cube_skin = "🟥";
int box_size = 20;
int cube_position = box_size / 2;
bool random_teleportation_bool = true;
float cube_speed_modifier = 100;
float cube_speed = 150000;
short key_unknown = 0;
int after_square = -1;
char player_input;
int ci = 1;
int esk;
int p1;
int p2;
int p3;
int p4;

//------------------ Vider la console

void clr()
{
    //cout << "Clearing Console...\nERROR";
    cout << "\033[2J\033[0;0H"; 
}

//------------------ Box size

void chng()
{
	clr();
	cout << "\n\n\nQUELLE TAILLE VEUX-TU POUR LA BOITE?\npas trop gros.. (33, c'est assez)\n(TAILLE ACTUELLE: " << box_size << ")\n\nTON CHOIX: ";
	cin >> box_size;
}

//------------------ Afficher le tableau

void tb()
{
    p1 = floor(cube_position / box_size); //Y
    p2 = (cube_position % box_size); //X
    p3 = box_size - 1 - p1; //-Y
    p4 = box_size - 1 - p2; //-X

    //Vider la console
    clr();

    //Toit de la boîte
	cout << " ";
    for(int sid = 1; sid <= box_size; sid++)
    {
        cout << "__";
    }
	cout << "\n";

    //Premmières lignes
    for(int col = 1; col < p3; col++)
    {
		cout << "⎪";
        for(int fin = 1; fin <= box_size; fin++)
    	{
        	cout << "  ";
    	}
		cout << "⎪\n";
    }

    //Espaces avant le carré
    cout << "⎪";
	int before_portail = 1;
	if(cube_position < box_size)
	{
		cout << "🟪 ";
		before_portail = 2;
	}
    for(int sup = before_portail; sup <= p2; sup++)
    {
        cout << "  ";
    }

    //Affichage du carré 🟥🟥🟥🟥🟥🟥🟥🟥🟥🟥
    cout << cube_skin;

    //Espaces après la carré
	if(cube_position > box_size)
	{
		after_square = 1;
	}
    for(int apr = after_square; apr <= p4; apr++)
    {
        cout << "  ";
    }
    cout << " ⎪";
    
    //Le reste des lignes
    for(int tro = 2; tro <= p1; tro++)
    {
        cout << "\n⎪";
		for(int bar = 1; bar <= box_size; bar++)
    	{
       		cout << "  ";
    	}
		cout << "⎪";
    }

	//Ligne avec le portail
	if(cube_position >= box_size)
	{
		cout << "\n⎪🟪";
		for(int por = 2; por <= box_size; por++)
		{
    		cout << "  ";
		}
    	cout << " ⎪";
	}

	//Sol de la boite
	cout << "\n ";
	for(int bas = 1; bas <= box_size; bas++)
    {
        cout << "‾‾";
    }

	//Règle de la boîte
	cout << "\n ⎪";
	int lngt = 1;
	if(box_size % 10 > 5)
	{
		lngt = 0;
	}
	for(int reg = lngt; reg <= box_size / 10; reg++)
    {
        cout << " ⏐ ⏐ ⏐ ⏐ | ⏐ ⏐ ⏐ ⏐ ⎪";
    }
	cout << " coords = " << cube_position << "\n";
	// : Pos = " << pla << " : Gra = " << dw << " : Acc = " << dc << ";
}

//------------------ Apparence du carré

void colr()
{
	clr();
    cout << "POUR CHANGER LA TAILLE DE LA BOITE, APPUIE SUR [ZERO][0]\n\n\nQUEL CARRÉ\nVAS-TU CHOISIR?\n\n\nCOULEURS\n\n 1 - 🟥, 2 - 🟧, 3 - 🟨,\n 4 - 🟩, 5 - 🟦, 6 - 🟪,\n 7 - 🟫, 8 - ⬛️, 9 - ⬜️\n\nIMAGES\n\n 10 - 🗾, 11 - 🎑, 12 - 🏞,\n 13 - 🌅, 14 - 🌄, 15 - 🌠,\n 16 - 🎇, 17 - 🎆, 18 - 🌇,\n 19 - 🌆, 20 - 🏙, 21 - 🌃,\n 22 - 🌌, 23 - 🌉, 24 - 🌁,\n 25 - 🖼, 26 - 📅, 27 - 🧮,\n 28 - 🎛, 29 - 💾, 30 - 🏢\n\nMOTIFS\n\n 31 - 🌫, 32 - 🔲, 33 - 🔳\n\n\n\'Q\' pour quitter\n\nTON CHOIX: ";
    cin >> ci;
    switch(ci)
    {
		case 0: chng(); break;

        //LIGNE VIERGE:
            //case : cube_skin = ""; break;
    
    //COULEURS
        case 2: cube_skin = "🟧"; break;
        case 3: cube_skin = "🟨"; break;
        case 4: cube_skin = "🟩"; break;
        case 5: cube_skin = "🟦"; break;
        case 6: cube_skin = "🟪"; break;
        case 7: cube_skin = "🟫"; break;
        case 8: cube_skin = "⬛️"; break;
        case 9: cube_skin = "⬜️"; break;
        //case : emj = ""; break;

    //IMAGES
        case 10: cube_skin = "🗾"; break;
        case 11: cube_skin = "🎑"; break;
        case 12: cube_skin = "🏞"; break;
        case 13: cube_skin = "🌅"; break;
        case 14: cube_skin = "🌄"; break;
        case 15: cube_skin = "🌠"; break;
        case 16: cube_skin = "🎇"; break;
        case 17: cube_skin = "🎆"; break;
        case 18: cube_skin = "🌇"; break;
        case 19: cube_skin = "🌆"; break;
        case 20: cube_skin = "🏙"; break;
        case 21: cube_skin = "🌃"; break;
        case 22: cube_skin = "🌌"; break;
        case 23: cube_skin = "🌉"; break;
        case 24: cube_skin = "🌁"; break;
        case 25: cube_skin = "🖼"; break;
        case 26: cube_skin = "📅"; break;
        case 27: cube_skin = "🧮"; break;
        case 28: cube_skin = "🎛"; break;
        case 29: cube_skin = "💾"; break;
        case 30: cube_skin = "🏢"; break;
        //case : emj = ""; break;

    //MOTIFS
        case 31: cube_skin = "🌫"; break;
        case 32: cube_skin = "🔲"; break;
        case 33: cube_skin = "🔳"; break;
        //case : emj = ""; break;


		case 'q': break;

        default: cube_skin = "🟥"; break;
    }
    tb();
	cube_position = box_size / 2;
}

//------------------ Fait descendre le carré

void down()
{
    while(1)
    {
		//Téléportation du carré
		if(cube_position == 0)
		{
			int min = 2;
			int teleporting;
			int max_teleportation = box_size * box_size - box_size - 1;
			while(teleporting % 10 != 0 || max_teleportation % 10 != 1)
			{
				teleporting = rand() % (max_teleportation - min + 1) + min;
			}
			cube_position = teleporting;
		}

		//Déscente du carré
        if(cube_position >= box_size)
        {
            usleep(cube_speed);
            cube_position -= box_size;
            tb();
        }
    }
}

//------------------ Interraction avec le carré

void play()
{
    while(1)
    {
        player_input = getch();
        esk = (cube_position % box_size);

        //Déplacements (Gauche/Droite)
        if(player_input == 'a' || player_input == 'A')
        {
            cube_position = (esk == 2) ? cube_position - 2 : cube_position = (esk == 1) ? cube_position - 1 : cube_position = (esk == 0) ? cube_position : cube_position - 3;;;
        }

        else if(player_input == 'd' || player_input == 'D')
        {
            cube_position = (esk == box_size - 2) ? cube_position + 1 : cube_position = (esk == box_size - 1) ? cube_position : cube_position + 2;;
        }

        //Modification de l'apparence du carré
        else if(player_input == ' ')
        {
            colr();
        }

        else
        {
            key_unknown = 1;
        }

        //Fais monter le carré
		int box_size_times_two = box_size * 2;

        cube_position = (p1 < box_size - 3 && key_unknown != 1) ? cube_position + box_size_times_two : (p1 < box_size - 2 && key_unknown != 1) ? cube_position + box_size : cube_position;;
        key_unknown = 0;

        tb();

        //change la vitesse du carré
		if(cube_speed >= 5000)
        {
			cube_speed_modifier = cube_speed_modifier / 1.1;
        	cube_speed -= cube_speed_modifier;
		}
    }
}

//------------------ Éxecution du programme

int main()
{
	srand(time(NULL));
	colr();
	tb();
	thread jeu(play);
  	thread low(down);
  	jeu.join();
  	low.join();
  return 0;
}

//------------------ Commentaires

/*{

 cube_position = emplacement
 low = "tread" pour down();
 jeu = "tread" pour play();
 cube_speed = vitesse que le cube descent
 cube_speed_modifier = diminue "dw"
 ci = choix du carré
 p1 = premières lignes
 p2 = espaces avant le carré
 p3 = dernières lignes
 p4 = espaces après le carré
 cube_skin = appapence du carré
 tb = tableau
 player_input = input du joueur
 col = premières lignes (boucle for)
 sup = espaces avant le carré (boucle for)
 tro = dernières lignes (boucle for)
 apr = espaces après le carré (boucle for
 down = fais descendre le carré
 play = boucle du jeu
 colr = menu pour le choix du carré
 clr = vide la console
 key_unknown = si une touche autre que 'a' ou 'd' est pressée
 esk = dernier chiffre de pla

}*/