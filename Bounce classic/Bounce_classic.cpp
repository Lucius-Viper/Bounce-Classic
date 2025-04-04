// biral aka capocaps
#include "iGraphics.h"
#include <windows.h>
#include <time.h>
#include <string.h>

// points and ball coordinates
int pre_x, pre_y, X_coordinate_ball = 20, Y_coordinate_ball = 90;
const int horizontal_velocity = 20, downward_pull = 2;
const int thorn_loss = 8, thorn_loss2 = 16, hoop_gain = 25, coin_gain = 6;
int health_bar = 3, gamepoint = 0, jump_velocity = 0;
int voids = 0, brick = 1, hoops = 2, obsta = 3, vhoop = 5, coins = 6, vcoin = 7;
// keys for gray conversion
int hoop_key_level1[4] = {0, 0, 0, 0};
int hoop_key_level2[3] = {0, 0, 0};
int MUSIC_CONTROL_INGAME = 1; // music control

char Coins[9][100]; // for coin animation
int rest = 0;		// for coin animation
int ispopped = 0;	// for ball pop delay
int write_mode = 0; // for namepage activation of box
int Length_of_str = 0;
int entered = 0;
char str[100], str2[100];
int bu = 0;
int counterrrrrr;

FILE *fp = fopen("LeaderBoard.txt", "a");
// leaderboardq
int Scoore[100];
char Name[100][100];
// changing game pages
int game_state = 1;
// Gs-1 == menu page, Gs-2 == level change, Gs-3 == level 1 page, Gs-4 == level 2 page, Gs-5 == Game over
// Gs-6 == instruction, Gs-7 == riddle, Gs-8 == leaderboard, Gs-9 == congratulations, Gs-10 == namepage, gs-15 == buffer

// functions
void Update_ball_posy();
void showCoinAnimation();
void upstars();
void stop();

// the Worlds
// level 2
int block_arr1[60][55] = {
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, voids, voids, voids, brick, brick, coins, voids, voids, voids, obsta, voids, voids, voids, coins, brick, brick, voids, brick, brick, voids, voids, voids, coins, voids, coins, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, obsta, voids, voids, coins, voids, coins, brick},
	{brick, brick, brick, voids, voids, voids, brick, brick, coins, voids, voids, voids, obsta, voids, voids, voids, coins, brick, brick, voids, brick, brick, voids, voids, voids, coins, voids, coins, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, obsta, voids, voids, coins, voids, coins, brick},
	{brick, brick, brick, voids, voids, voids, brick, brick, brick, voids, voids, voids, obsta, voids, voids, voids, brick, brick, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, obsta, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, brick, brick, voids, voids, voids, obsta, voids, voids, voids, brick, brick, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, obsta, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, brick, brick, brick, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, coins, brick, brick, voids, voids, voids, brick, brick, coins, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, coins, brick, brick, voids, voids, voids, brick, brick, coins, voids, voids, voids, coins, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, hoops, voids, voids, voids, voids, voids, coins, coins, voids, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, obsta, voids, coins, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, obsta, voids, coins, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, obsta, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, obsta, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, coins, voids, coins, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, coins, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick},
	{voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick},
	{voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick},
	{voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, coins, voids, brick},
	{voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, coins, voids, brick},
	{voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, brick},
	{voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, brick},
	{voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, coins, voids, coins, voids, brick, brick, coins, voids, voids, voids, obsta, voids, voids, voids, coins, brick, brick, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, obsta, voids, voids, brick, brick, coins, voids, voids, voids, obsta, voids, voids, voids, coins, brick, brick, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, coins, voids, coins, voids, brick, brick, coins, voids, voids, voids, obsta, voids, voids, voids, coins, brick, brick, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, obsta, voids, voids, brick, brick, coins, voids, voids, voids, obsta, voids, voids, voids, coins, brick, brick, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, obsta, voids, voids, voids, voids, brick, brick, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, obsta, voids, voids, brick, brick, voids, voids, voids, voids, obsta, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, obsta, voids, voids, voids, brick, brick, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, obsta, voids, voids, brick, brick, brick, voids, voids, voids, obsta, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, obsta, voids, voids, voids, brick, brick, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, obsta, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, coins, brick, brick, voids, voids, voids, brick, brick, coins, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, coins, brick, brick, voids, voids, voids, brick, brick, coins, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, coins, brick, brick, voids, voids, voids, brick, brick, coins, voids, voids, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, coins, coins, voids, voids, voids, voids, voids, voids, coins, brick, brick, voids, voids, voids, brick, brick, coins, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, coins, coins, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick}

};
// level 2
int block_arr[60][55] = {

	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, obsta, voids, voids, voids, brick, brick, brick, voids, obsta, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, obsta, voids, coins, voids, voids, brick, brick, brick, brick, voids, coins, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, obsta, voids, voids, voids, brick, brick, brick, voids, obsta, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, obsta, voids, coins, voids, voids, brick, brick, brick, brick, voids, coins, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, obsta, voids, voids, voids, brick, brick, brick, voids, obsta, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, obsta, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, obsta, voids, voids, voids, brick, brick, brick, voids, obsta, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, obsta, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, coins, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, obsta, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, obsta, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, obsta, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, coins, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, coins, voids, voids, coins, voids, voids, voids, coins, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick, brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, hoops, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, voids, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},
	{brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick, brick},

};

void iDraw()
{
	// set game states assigned for various levels
	iClear();
	if (game_state == 1)
	{
		// drawing menu page

		X_coordinate_ball = 20;
		Y_coordinate_ball = 90;

		for (int i = 0; i < 4; i++)
			hoop_key_level1[i] = 0;
		for (int i = 0; i < 3; i++)
			hoop_key_level2[i] = 0;

		iShowBMP(0, 0, "GameImages\\Menu.bmp");
		iShowBMP(960, (600 - 495), "GameImages\\anda.bmp");
		if (MUSIC_CONTROL_INGAME)
			iShowBMP2(10, 560, "GameImages\\sound.bmp", 0);
		else
			iShowBMP2(10, 560, "GameImages\\sound2.bmp", 0);

		iShowBMP2(1060, 560, "GameImages\\cross.bmp", 0);
		health_bar = 3;
		gamepoint = 0;
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 55; j++)
			{
				if (block_arr[i][j] == vhoop)
					block_arr[i][j] = hoops;
			}
		}
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 55; j++)
			{
				if (block_arr[i][j] == vcoin)
					block_arr[i][j] = coins;
			}
		}

		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 55; j++)
			{
				if (block_arr1[i][j] == vhoop)
					block_arr1[i][j] = hoops;
			}
		}
		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 55; j++)
			{
				if (block_arr1[i][j] == vcoin)
					block_arr1[i][j] = coins;
			}
		}
	}

	else if (game_state == 3)
	{
		// drawing level 1
		iShowBMP(0, 0, "GameImages\\bg13.bmp");

		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 55; j++)
			{
				if (block_arr[i][j] == brick)
					iShowBMP((j * 20), (i * 10), "GameImages\\bricks.bmp");
				if (block_arr[i][j] == coins)
				{
					if (block_arr[i + 1][j] == coins)
						iShowBMP2(j * 20, i * 10, Coins[rest], 0);
				}
			}
		}

		// ring-1
		if (hoop_key_level1[0] == 0)
			iShowBMP2(230, 280, "GameImages\\ring.bmp", 0);
		else if (hoop_key_level1[0] == 1)
			iShowBMP(230, 280, "GameImages\\ringdone1.bmp");

		// ring -2- 750,220
		if (hoop_key_level1[2] == 0)
			iShowBMP2(750, 220, "GameImages\\ring.bmp", 0);
		else if (hoop_key_level1[2] == 1)
			iShowBMP(750, 220, "GameImages\\ringdone1.bmp");
		// third hoop upore alternate path e-670,430
		// iShowBMP2(670, 430, "C:\\Lucius' FIles\\Bounce classic\\GameImages\\ring.bmp", 0);
		if (hoop_key_level1[1] == 0)
			iShowBMP2(670, 430, "GameImages\\ring.bmp", 0);
		else if (hoop_key_level1[1] == 1)
			iShowBMP(670, 430, "GameImages\\ringdone1.bmp");

		// last right hoop
		// iShowBMP2(970, 270, "C:\\Lucius' FIles\\Bounce classic\\GameImages\\ring.bmp", 0);
		if (hoop_key_level1[3] == 0)
			iShowBMP2(970, 270, "GameImages\\ring.bmp", 0);
		else if (hoop_key_level1[3] == 1)
			iShowBMP(970, 270, "GameImages\\ringdone1.bmp");

		//  first thorn
		iShowBMP(200, 100, "GameImages\\thorn.bmp");
		// second thorn
		iShowBMP2(360, 100, "GameImages\\thorn3.bmp", 0);
		// 3rd thorn
		iShowBMP2(440, 360, "GameImages\\thorn3.bmp", 0);
		// fourth thorn
		iShowBMP(620, 160, "GameImages\\thorn.bmp");
		// fifth
		iShowBMP2(720, 100, "GameImages\\thorn3.bmp", 0);
		// sixth thorn
		iShowBMP2(880, 190, "GameImages\\thorn.bmp", 0);
		// ball
		// iShowBMP2(X_coordinate_ball, Y_coordinate_ball, "C:\\Lucius' FIles\\Bounce classic\\GameImages\\ball_big.bmp", 0);
		// star - 1040,270
		iShowBMP(1040, 270, "GameImages\\star.bmp");
		// health_bar start here
		int health_barX = 1010, health_barY = 500;
		if (health_bar == 0)
		{
			fprintf(fp, "%d %s\n", gamepoint, str2);
			fclose(fp);
			game_state = 5;
		}

		for (int i = 0; i < health_bar; i++)
		{
			iSetColor(91, 125, 220);
			iFilledCircle(health_barX + i * 25, health_barY, 10, 100);
		} // int health_barX = 1030, health_barY = 500;

		char gamepointText[50];
		sprintf(gamepointText, "score: %d", gamepoint);
		iSetColor(0, 0, 0);
		iText(990, 460, gamepointText);

		if (!ispopped)
		{
			// ball
			iShowBMP2(X_coordinate_ball, Y_coordinate_ball, "GameImages\\ball_big.bmp", 0);
		}
		else
		{

			iShowBMP2(pre_x, pre_y, "GameImages\\ball_pop.bmp", 0);
		}
	}
	else if (game_state == 5)
	{

		// drawing game over page
		// 452, 240
		char m[20];
		sprintf(m, "Your Score : %d", gamepoint);
		iShowBMP(0, 0, "GameImages\\game_over.bmp");
		iSetColor(230, 177, 34);
		iText(452, 250, m, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (game_state == 6)
	{
		iShowBMP(0, 0, "GameImages\\instruction page.bmp");
		iShowBMP2(1060, 560, "GameImages\\left arrow.bmp", 0);
	}

	else if (game_state == 7)
	{
		// easter egg
		iShowBMP(0, 0, "GameImages\\riddle.bmp");
		iShowBMP2(204,(600-446) ,"GameImages\\pirate ship.bmp", 0);
		iShowBMP2(1060, 560, "GameImages\\left arrow.bmp", 0);
	}
	else if (game_state == 2)
	{
		// transition to lvl 2
		iClear();
		iSetColor(250, 250, 250);
		iText(440 - 20, 480 - 10, "Processing Level Two.........", GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP2(200, 125 + 40, "GameImages\\dog.bmp", 0);
		iText(370, 95 + 40, "Working Hard to prepare your world!!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(370 + 40, 65 + 35, "Press \"Enter\" to Proceed!!", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	else if (game_state == 4)
	{
		// drawing lvl 2

		iShowBMP(0, 0, "GameImages\\bg4.bmp");
		iSetColor(0, 0, 0);

		for (int i = 0; i < 60; i++)
		{
			for (int j = 0; j < 55; j++)
			{
				if (block_arr1[i][j] == brick)
					iShowBMP((j * 20), (i * 10), "GameImages\\brick.bmp");
				if (block_arr1[i][j] == coins)
				{
					if (block_arr1[i + 1][j] == coins)

						iShowBMP2(j * 20, i * 10, Coins[rest], 0);
				}
			}
		}
		// first thorn - 240, 330
		iShowBMP(240, 330, "GameImages\\thorn2.bmp");

		// fourth thorn -  640  , 330
		iShowBMP(640, 330, "GameImages\\thorn3.bmp");
		// fifth thorn -  820  , 330
		iShowBMP(820, 330, "GameImages\\thorn2.bmp");
		// sixth thorn -  1000  , 240
		iShowBMP(1000, 240, "GameImages\\thorn3.bmp");
		// seventh thorn -  960  , 40
		iShowBMP(960, 40, "GameImages\\thorn3.bmp");
		// eight orn -  880  , 140
		iShowBMP(880, 140, "GameImages\\thorn2.bmp");
		// ninth thorn -  680  , 40
		iShowBMP(680, 40, "GameImages\\thorn2.bmp");
		// tenth thorn - 540, 170

		iShowBMP(540, 170, "GameImages\\thorn3.bmp");
		// 11th thorn -  240  , 40
		iShowBMP(240, 40, "GameImages\\thorn3.bmp");

		// first hoop - 1030, 470
		// iShowBMP2(1030, 470, "C:\\Lucius' FIles\\Bounce classic\\GameImages\\ring.bmp", 0);
		if (hoop_key_level2[2] == 0)
			iShowBMP2(1030, 470, "GameImages\\ring6.bmp", 0);
		else if (hoop_key_level2[2] == 1)
			iShowBMP(1030, 470, "GameImages\\ringdone2.bmp");

		// second hoop - 260, 120
		// iShowBMP2(210, 130, "C:\\Lucius' FIles\\Bounce classic\\GameImages\\ring.bmp", 0);
		if (hoop_key_level2[0] == 0)
			iShowBMP2(210, 130, "GameImages\\ring6.bmp", 0);
		else if (hoop_key_level2[0] == 1)
			iShowBMP(210, 130, "GameImages\\ringdone2.bmp");

		// third hoop - 160, `120
		// iShowBMP2(280, 130, "C:\\Lucius' FIles\\Bounce classic\\GameImages\\ring.bmp", 0);
		if (hoop_key_level2[1] == 0)
			iShowBMP2(280, 130, "GameImages\\ring6.bmp", 0);
		else if (hoop_key_level2[1] == 1)
			iShowBMP(280, 130, "GameImages\\ringdone2.bmp");

		// star
		iShowBMP(20, 210, "GameImages\\star2.bmp");

		// ball
		// iShowBMP2(X_coordinate_ball, Y_coordinate_ball, "C:\\Lucius' FIles\\Bounce classic\\GameImages\\ball_big.bmp", 0);

		int health_barX = 1020, health_barY = 555;
		for (int i = 0; i < health_bar; i++)
		{
			iSetColor(91, 125, 220);
			iFilledCircle(health_barX + i * 25, health_barY, 10, 100);
		}

		char gamepointText[50];
		sprintf(gamepointText, "score: %d", gamepoint);
		iSetColor(250, 250, 250);
		iText(1000, 530, gamepointText);

		if (health_bar == 0)
		{
			fprintf(fp, "%d %s\n", gamepoint, str2);
			fclose(fp);
			game_state = 5;
		}
		if (!ispopped)
		{
			// ball
			if (Y_coordinate_ball > 300)
				iShowBMP2(X_coordinate_ball, Y_coordinate_ball, "GameImages\\ball_3.bmp", 0);
			else
				iShowBMP2(X_coordinate_ball, Y_coordinate_ball, "GameImages\\ball_2.bmp", 0);
			// printf("hehe");
		}
		else
		{
			// iPauseTimer(1);
			iShowBMP2(pre_x, pre_y, "GameImages\\ball_pop.bmp", 0);
		}
	}
	else if (game_state == 9)
	{
		// display score after game over
		char d[20];
		sprintf(d, "%d", gamepoint);
		iShowBMP(0, 0, "GameImages\\congo.bmp");
		iShowBMP2(450, 50, "GameImages\\lucius.bmp", 0);
		iShowBMP2(1060, 560, "GameImages\\cross.bmp", 0);
		iSetColor(250, 250, 250);
		iText(860, 105, d, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (game_state == 8)
	{
		// leaderboard rendering

		iShowBMP(0, 0, "GameImages\\starboard.bmp");
		int i = 0, c = 0;
		fp = fopen("LeaderBoard.txt", "r");
		char ch;
		while (fscanf(fp, "%d %99s", &Scoore[i], Name[i]) == 2)
		{
			i++;
			c++;
		}

		for (int i = 0; i < c - 1; i++)
		{
			for (int j = i + 1; j < c; j++)
			{
				if (Scoore[i] < Scoore[j])
				{
					int temp = Scoore[i];
					Scoore[i] = Scoore[j];
					Scoore[j] = temp;
					char temp2[100];
					strcpy(temp2, Name[i]);
					strcpy(Name[i], Name[j]);
					strcpy(Name[j], temp2);
				}
			}
		}
		fclose(fp);
		char scorecheck[150];

		for (i = 0; i < 10; i++)
		{
			iSetColor(250, 250, 250);

			sprintf(scorecheck, "%d. %s : %d", i + 1, Name[i], Scoore[i]);
			if (i < 5)
				iText(270, 400 - i * 62, scorecheck);
			else
				iText(600, 400 - (i - 5) * 62, scorecheck);
		}
		iShowBMP2(1060, 560, "GameImages\\cross.bmp", 0);
		iShowBMP2(10, 10, "GameImages\\home 2.bmp", 0);

		//	for (int i = 0; i < c; i++)
		//	{
		//		printf("%s %d\n", player[i].name, player[i].points);

		//	}
	}
	else if (game_state == 10)
	{ // entering name

		if (write_mode)
		{
			iShowBMP(0, 0, "GameImages\\Name.bmp");
			iSetColor(0, 0, 0);
			iText(380, 320, str, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		else if (write_mode == 0 && entered == 0)
		{
			iShowBMP(0, 0, "GameImages\\Name1.bmp");
			// printf("Name1\n");
		}
		else if (write_mode == 0 && entered == 1)
		{
			iShowBMP(0, 0, "GameImages\\Name2.bmp");
		}
		for (int i = 0; i < 55; i++)
		{
			// iShowBMP(i*20, 590, "GameImages\\bricks.bmp");
			counterrrrrr++;
			// iShowBMP(i*20, 0, "GameImages\\bricks.bmp");
			// iShowBMP(i*20, 580, "GameImages\\bricks.bmp");
			// iShowBMP(i*20, 10, "GameImages\\bricks.bmp");
		}
		for (int i = 0; i < 60; i++)
		{
			// iShowBMP(0, i*10, "GameImages\\bricks.bmp");
			counterrrrrr--;
			// iShowBMP(1080, i*10, "GameImages\\bricks.bmp");
		}
		iShowBMP(1000, 0, "GameImages\\doggo.bmp");
		iShowBMP2(995, 50, "GameImages\\ball_big.bmp", 0);
		iSetColor(0, 0, 0);
		// iText(366+40, (600-391), "- Ball for Level-1 ", GLUT_BITMAP_TIMES_ROMAN_24);
		// iShowBMP2(366, (600-391-40), "GameImages\\ball_2.bmp", 0);
		// iShowBMP2(366 -30, (600-391-40), "GameImages\\ball_3.bmp", 0);
		iText(350, 200, "Press HOME button or the dog to proceed", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (game_state == 15)
	{
		game_state = 10;
		entered = 0;
	}
}

// menu = 1, level change = 2, level 1 = 3, level 2 = 4, game over = 5, instruction = 6, riddle = 7
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (game_state == 1)
		{ // controling buttons in menu page
			if (mx >= 450 && mx <= 650 && my <= (600 - 235) && my >= (600 - 295))
			{
				fp = fopen("LeaderBoard.txt", "a");
				game_state = 15;
			}
			if (mx >= 450 && mx <= 650 && my <= (600 - 319) && my >= (600 - 373))
			{
				game_state = 8;
			}
		}

		if (mx >= 1060 && mx <= 1090 && my >= 560 && my <= 590 && game_state == 1)
		{
			exit(0);
		}

		if (mx >= 450 && mx <= 650 && my <= (600 - 400) && my >= (600 - 455) && game_state == 1)
		{

			game_state = 6;
		}
		// system("notepad C:\\Users\\tanji\\OneDrive\\Desktop\\Instructions For Bounce Classic.txt");

		if (mx >= 10 && mx <= 50 && my >= 560 && my <= 600 && game_state == 1)
		{
			MUSIC_CONTROL_INGAME = 1 - MUSIC_CONTROL_INGAME;
			if (!MUSIC_CONTROL_INGAME)
			{
				PlaySound(0, 0, 0);
			}
			else
			{
				PlaySound("music\\funky-guitar-groove-ident-alternate-version-185817.wav", NULL, SND_LOOP | SND_ASYNC);
			}
		}
		if (mx >= 1060 && mx <= 1090 && my >= 560 && my <= 595 && game_state == 6)
		{
			// back to menu page
			game_state = 1;
		}
		if (mx >= 960 && mx <= 1000 && my >= (600 - 495) && my <= (600 - 445) && game_state == 1)
		{
			game_state = 7; // goes to riddle page
		}
		if (mx >= 1060 && mx <= 1090 && my >= 560 && my <= 595 && game_state == 7)
		{

			game_state = 1; // back to menu
		}
		if (mx >= 380 && mx <= 525 && my <= 208 && my >= 130 && game_state == 5)
		{
			game_state = 1; // back to menu
		}
		if (mx >= 570 && mx <= 690 && my <= 208 && my >= 130 && game_state == 5)
		{
			exit(0);
		}
		if (mx >= 1060 && mx <= 1090 && my >= 560 && my <= 590 && game_state == 9)
		{
			exit(0);
		}
		if (mx >= 450 && mx <= 650 && my >= 50 && my <= 250 && game_state == 9)
		{

			game_state = 8; // goes to leaderboard
		}
		if (mx >= 350 && mx <= 750 && my >= (600 - 317) && my <= (600 - 230) && game_state == 10)
		{
			write_mode = 1; // entering name
		}
		if (mx >= 980 && mx <= 1100 && my >= 0 && my <= 100 && game_state == 10)
		{
			game_state = 3; // level 1
		}
		if (mx >= 1060 && mx <= 1100 && my >= 560 && my <= 600 && game_state == 8)
		{
			exit(0);
		}
		if (mx >= 0 && mx <= 40 && my >= 0 && my <= 40 && game_state == 8)
		{
			game_state = 1; // back to menu
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
	}
}

void iKeyboard(unsigned char key)
{
	int i;
	if (key == 'q' and write_mode == 0)
	{
		exit(0);
	}
	if (key == 'm' && write_mode == 0)
	{
		// music control
		MUSIC_CONTROL_INGAME = 1 - MUSIC_CONTROL_INGAME;
		if (!MUSIC_CONTROL_INGAME)
		{
			PlaySound(0, 0, 0);
		}
		else
		{

			PlaySound("music\\funky-guitar-groove-ident-alternate-version-185817.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}
	if (key == 'd' && health_bar < 3 && write_mode == 0)
	{ // power up !!
		health_bar++;
	}
	if (game_state == 10 && write_mode == 1)
	{
		// name input
		if (key == '\r')
		{
			write_mode = 0;
			strcpy(str2, str);
			for (i = 0; i < Length_of_str; i++)
				str[i] = 0;
			Length_of_str = 0;
			entered = 1;
			bu = 0;
		}
		else if (key == '\b')
		{
			if (Length_of_str >= 0)
			{
				if (bu == 0)
					Length_of_str--;
				str[Length_of_str] = 0;
				Length_of_str--;
				bu = 1;
			}
		}
		else
		{
			if (bu == 1)
				Length_of_str++;
			str[Length_of_str] = key;
			Length_of_str++;
			bu = 0;
		}
	}
	if (game_state == 2 and key == '\r')
	{
		game_state = 4;
	}
	// place your codes for other keys here
}

void iSpecialKeyboard(unsigned char key)
{

	// Movement of the ball

	if (key == GLUT_KEY_RIGHT)
	{
		if (game_state == 3 && (block_arr[(Y_coordinate_ball / 10)][(X_coordinate_ball / 20) + 1] != brick && (block_arr[(Y_coordinate_ball / 10) + 1][(X_coordinate_ball / 20) + 1] != brick)))
			X_coordinate_ball += horizontal_velocity;
		else if (game_state == 4 && (block_arr1[(Y_coordinate_ball / 10)][(X_coordinate_ball / 20) + 1] != brick) && (block_arr1[(Y_coordinate_ball / 10) + 1][(X_coordinate_ball / 20) + 1] != brick))
			X_coordinate_ball += horizontal_velocity;
		// printf("Ball x :%d \nBall y : %d \n",X_coordinate_ball, Y_coordinate_ball);
	}

	else if (key == GLUT_KEY_LEFT)
	{
		if (game_state == 3 && (block_arr[(Y_coordinate_ball / 10)][(X_coordinate_ball / 20) - 1] != brick) && (block_arr[(Y_coordinate_ball / 10) + 1][(X_coordinate_ball / 20) - 1] != brick))
			X_coordinate_ball -= horizontal_velocity;
		else if (game_state == 4 && (block_arr1[(Y_coordinate_ball / 10)][(X_coordinate_ball / 20) - 1] != brick) && (block_arr1[(Y_coordinate_ball / 10) + 1][(X_coordinate_ball / 20) - 1] != brick))
			X_coordinate_ball -= horizontal_velocity;
	}

	else if (key == GLUT_KEY_UP)
	{ // Allow jumping only from the ground
		if (game_state == 3 && block_arr[(Y_coordinate_ball / 10) - 1][X_coordinate_ball / 20] == brick)
		{
			jump_velocity = 30; // Set upward velocity for the jump
			Y_coordinate_ball += 10;
		}

		else if (game_state == 4 && block_arr1[(Y_coordinate_ball / 10) - 1][X_coordinate_ball / 20] == brick)
		{
			jump_velocity = 30; // Set upward velocity for the jump
			Y_coordinate_ball += 10;
		}
	}
	else if (game_state == 10 && key == GLUT_KEY_HOME)
	{
		game_state = 3;
		write_mode = 0;
		// printf("hehe");
	}

	// place your codes for other keys here
}

int main()
{
	// place your own initialization codes here.

	showCoinAnimation();
	iSetTimer(90, upstars);
	iSetTimer(1, Update_ball_posy);
	if (MUSIC_CONTROL_INGAME == 1)
		PlaySound("music\\funky-guitar-groove-ident-alternate-version-185817.wav", NULL, SND_LOOP | SND_ASYNC);

	iInitialize(1100, 600, "Bounce Classic");

	return 0;
}
// coin animation
void showCoinAnimation()
{
	// change the animations
	for (int i = 0; i < 9; i++)
	{

		sprintf(Coins[i], "GameImages\\coins%d.bmp", i);
	}
}

void upstars()
{
	rest = (rest + 1) % 9;
}
// all the physics and collision detection
void Update_ball_posy()
{

	if (game_state == 3)
	{
		// jump logic for lvl 1
		int x = X_coordinate_ball / 20;
		int y = Y_coordinate_ball / 10;

		if (block_arr[(Y_coordinate_ball / 10) - 1][x] != brick)
		{
			jump_velocity -= downward_pull;
			Y_coordinate_ball += jump_velocity;
		}
		else if (block_arr[(Y_coordinate_ball / 10) - 1][x] == brick && (Y_coordinate_ball % 10) != 0)
		{
			int d = Y_coordinate_ball % 10;
			Y_coordinate_ball -= d;
		}

		else if (block_arr[Y_coordinate_ball / 10][X_coordinate_ball / 20] == brick)
		{
			jump_velocity = 0;

			if (block_arr[Y_coordinate_ball / 10][X_coordinate_ball / 20] == brick)
			{
				Y_coordinate_ball = 10 * ((Y_coordinate_ball / 10) + 1);
			}
		}

		if (block_arr[(Y_coordinate_ball / 10) + 3][X_coordinate_ball / 20] == brick)
			jump_velocity = -10;

		// first thorn
		if ((X_coordinate_ball > 180 && X_coordinate_ball <= 210) && (Y_coordinate_ball >= 100 && Y_coordinate_ball <= 140))
		{

			// PlaySound("C:\\Users\\tanji\\Downloads\\explosion-91872.wav", NULL, SND_FILength_of_strAME | SND_ASYNC);
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);
			X_coordinate_ball = 140;
			Y_coordinate_ball = 180;
			gamepoint -= thorn_loss;
		}
		// second thorn
		if ((X_coordinate_ball > 340 && X_coordinate_ball <= 370) && (Y_coordinate_ball >= 100 && Y_coordinate_ball <= 140))
		{

			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);
			X_coordinate_ball = 300;
			Y_coordinate_ball = 270;
			gamepoint -= thorn_loss2;
		}
		// third thorn
		if ((X_coordinate_ball > 420 && X_coordinate_ball <= 450) && (Y_coordinate_ball >= 360 && Y_coordinate_ball <= 400))
		{
			gamepoint -= thorn_loss2;
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 140;
			Y_coordinate_ball = 180;
		}
		// fourth thord
		if ((X_coordinate_ball > 600 && X_coordinate_ball <= 640) && (Y_coordinate_ball >= 160 && Y_coordinate_ball <= 200))
		{
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			gamepoint -= thorn_loss;
			X_coordinate_ball = 480;
			Y_coordinate_ball = 160;
		}

		// fifth thorn

		if ((X_coordinate_ball > 700 && X_coordinate_ball <= 740) && (Y_coordinate_ball >= 100 && Y_coordinate_ball <= 140))
		{
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			gamepoint -= thorn_loss2;
			X_coordinate_ball = 680;
			Y_coordinate_ball = 160;
		}

		// sixth thorn
		if ((X_coordinate_ball > 860 && X_coordinate_ball <= 890) && (Y_coordinate_ball >= 190 && Y_coordinate_ball <= 230))
		{

			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			gamepoint -= thorn_loss;
			X_coordinate_ball = 780;
			Y_coordinate_ball = 100;
		}

		if (block_arr[Y_coordinate_ball / 10][X_coordinate_ball / 20] == hoops)
		{
			if (X_coordinate_ball / 20 == 11)
				hoop_key_level1[0] = 1;
			if (X_coordinate_ball / 20 == 33)
				hoop_key_level1[1] = 1;
			if (X_coordinate_ball / 20 == 37)
				hoop_key_level1[2] = 1;
			if (X_coordinate_ball / 20 == 49)
				hoop_key_level1[3] = 1;

			int i = 0;
			for (i = 0; i <= 3; i++)
			{
				if (block_arr[(Y_coordinate_ball / 10) + i][X_coordinate_ball / 20] == 2)
					block_arr[(Y_coordinate_ball / 10) + i][X_coordinate_ball / 20] = 5;

				if (block_arr[(Y_coordinate_ball / 10) - i][X_coordinate_ball / 20] == 2)
					block_arr[(Y_coordinate_ball / 10) - i][X_coordinate_ball / 20] = 5;
			}
			gamepoint += hoop_gain;
			// hoop_key =1 ;
		}

		if (block_arr[Y_coordinate_ball / 10][X_coordinate_ball / 20] == coins)
		{
			int i = 0;
			for (i = 0; i <= 1; i++)
			{
				if (block_arr[(Y_coordinate_ball / 10) + i][X_coordinate_ball / 20] == coins)
					block_arr[(Y_coordinate_ball / 10) + i][X_coordinate_ball / 20] = vcoin;

				if (block_arr[(Y_coordinate_ball / 10) - i][X_coordinate_ball / 20] == coins)
					block_arr[(Y_coordinate_ball / 10) - i][X_coordinate_ball / 20] = vcoin;
			}
			gamepoint += coin_gain;
		}

		// star - 1040,270
		if (X_coordinate_ball >= 1020 && X_coordinate_ball <= 1060 && Y_coordinate_ball < 300 && Y_coordinate_ball >= 270 && game_state == 3)
		{
			// display congratulations

			// move to next

			game_state = 2;
			X_coordinate_ball = 100;
			Y_coordinate_ball = 540;
			health_bar = 3;
		}
	}

	else if (game_state == 4)
	{ // jump logic for lvl 2
		int x = X_coordinate_ball / 20;
		int y = Y_coordinate_ball / 10;

		if (block_arr1[(Y_coordinate_ball / 10) - 1][x] != brick)
		{
			jump_velocity -= downward_pull;
			Y_coordinate_ball += jump_velocity;
		}
		else if (block_arr1[(Y_coordinate_ball / 10) - 1][x] == brick && (Y_coordinate_ball % 10) != 0)
		{
			int d = Y_coordinate_ball % 10;
			Y_coordinate_ball -= d;
		}

		else if (block_arr1[Y_coordinate_ball / 10][X_coordinate_ball / 20] == brick)
		{
			jump_velocity = 0;

			if (block_arr1[Y_coordinate_ball / 10][X_coordinate_ball / 20] == brick)
			{
				Y_coordinate_ball = 10 * ((Y_coordinate_ball / 10) + 1);
			}
		}

		if (block_arr1[(Y_coordinate_ball / 10) + 3][X_coordinate_ball / 20] == brick)
			jump_velocity = -10;

		// first thorn
		if ((X_coordinate_ball > 220 && X_coordinate_ball <= 250) && (Y_coordinate_ball >= 330 && Y_coordinate_ball <= 370))
		{
			health_bar--;
			// PlaySound("C:\\Users\\tanji\\Downloads\\explosion-91872.wav", NULL, SND_FILength_of_strAME | SND_ASYNC);
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 100;
			Y_coordinate_ball = 330;
			gamepoint -= thorn_loss;
		}

		// fourth thord
		if ((X_coordinate_ball > 620 && X_coordinate_ball <= 650) && (Y_coordinate_ball >= 330 && Y_coordinate_ball <= 370))
		{
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 480;
			Y_coordinate_ball = 330;
			gamepoint -= thorn_loss2;
		}

		// fifth thorn
		if ((X_coordinate_ball > 800 && X_coordinate_ball <= 830) && (Y_coordinate_ball >= 330 && Y_coordinate_ball <= 370))
		{
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 680;
			Y_coordinate_ball = 330;
			gamepoint -= thorn_loss;
		}

		// sixth thorn
		if ((X_coordinate_ball > 980 && X_coordinate_ball <= 1010) && (Y_coordinate_ball >= 240 && Y_coordinate_ball <= 280))
		{

			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 940;
			Y_coordinate_ball = 350;
			gamepoint -= thorn_loss2;
		}

		// 7th thorn
		if ((X_coordinate_ball > 940 && X_coordinate_ball <= 970) && (Y_coordinate_ball >= 40 && Y_coordinate_ball <= 80))
		{
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 940;
			Y_coordinate_ball = 350;
			gamepoint -= thorn_loss2;
		}

		// 8th thorn

		if ((X_coordinate_ball > 860 && X_coordinate_ball <= 890) && (Y_coordinate_ball >= 140 && Y_coordinate_ball <= 180))
		{
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 940;
			Y_coordinate_ball = 350;
			gamepoint -= thorn_loss;
		}

		// 9th thorn
		if ((X_coordinate_ball > 660 && X_coordinate_ball <= 690) && (Y_coordinate_ball >= 40 && Y_coordinate_ball <= 90))
		{
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 720;
			Y_coordinate_ball = 40;
			gamepoint -= thorn_loss;
		}
		// 10th thorn

		if ((X_coordinate_ball > 520 && X_coordinate_ball <= 550) && (Y_coordinate_ball >= 170 && Y_coordinate_ball <= 220))
		{
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 600;
			Y_coordinate_ball = 40;
			gamepoint -= thorn_loss2;
		}

		// 11th thorn

		if ((X_coordinate_ball > 220 && X_coordinate_ball <= 250) && (Y_coordinate_ball >= 40 && Y_coordinate_ball <= 90))
		{
			health_bar--;
			pre_x = X_coordinate_ball;
			pre_y = Y_coordinate_ball;
			ispopped = 1;
			iPauseTimer(1);
			iSetTimer(1500, stop);

			X_coordinate_ball = 600;
			Y_coordinate_ball = 40;
			gamepoint -= thorn_loss2;
		}

		if (block_arr1[Y_coordinate_ball / 10][X_coordinate_ball / 20] == hoops)
		{

			if (X_coordinate_ball / 20 == 10)
				hoop_key_level2[0] = 1;
			if (X_coordinate_ball / 20 == 14)
				hoop_key_level2[1] = 1;
			if (X_coordinate_ball / 20 == 51)
				hoop_key_level2[2] = 1;

			int i = 0;
			for (i = 0; i <= 3; i++)
			{
				if (block_arr1[(Y_coordinate_ball / 10) + i][X_coordinate_ball / 20] == 2)
					block_arr1[(Y_coordinate_ball / 10) + i][X_coordinate_ball / 20] = 5;

				if (block_arr1[(Y_coordinate_ball / 10) - i][X_coordinate_ball / 20] == 2)
					block_arr1[(Y_coordinate_ball / 10) - i][X_coordinate_ball / 20] = 5;
			}
			gamepoint += hoop_gain;
		}

		if (block_arr1[Y_coordinate_ball / 10][X_coordinate_ball / 20] == coins)
		{
			int i = 0;
			for (i = 0; i <= 1; i++)
			{
				if (block_arr1[(Y_coordinate_ball / 10) + i][X_coordinate_ball / 20] == coins)
					block_arr1[(Y_coordinate_ball / 10) + i][X_coordinate_ball / 20] = vcoin;

				if (block_arr1[(Y_coordinate_ball / 10) - i][X_coordinate_ball / 20] == coins)
					block_arr1[(Y_coordinate_ball / 10) - i][X_coordinate_ball / 20] = vcoin;
			}
			gamepoint += coin_gain;
		}
		// star - 20, 210
		if (X_coordinate_ball >= 20 && X_coordinate_ball <= 50 && Y_coordinate_ball < 240 && Y_coordinate_ball >= 210 && game_state == 4)
		{
			// // display congratulations
			fprintf(fp, "%d %s\n", gamepoint, str2);
			fclose(fp);

			// // move to next
			game_state = 9;
		}
	}

	if (X_coordinate_ball <= 0)
		X_coordinate_ball = 0;
	if (X_coordinate_ball >= 1100)
		X_coordinate_ball = 1100 - 20;
}
// ball pop delay
void stop()
{
	ispopped = 0;
	iPauseTimer(2);
	iResumeTimer(1);
}
