#include <stdio.h>
#include <stdbool.h>

typedef struct {
	int power;
	int strength;
	bool asleep;
} Creature;

typedef struct {
	int p1_life;
	int p2_life;
	Creature p1_creatures[5];
	Creature p2_creatures[5];
} Game;

Creature summon(int life) {
	Creature creature;
	int input = life;
	do {
		printf("How much Life do you want to pay?\nYou currently have %d Life.\n",life);
		scanf("%d", &input);
	} while (input >= life || input == 0);
	do {
		puts("Summon a creature whose Power and Strength equal the Life you paid.");
		puts("How much Power should the creature have?");
		scanf("%d", &creature.power);
		puts("How much Strength should the creature have?");
		scanf("%d", &creature.strength);
	} while (creature.power + creature.strength != input);
	creature.asleep = true;
	return creature;
}

Game reset_game() {
	Game game;
	game.p1_life = 2000;
	game.p2_life = 2000;
	game.p1_creatures[0].power = 0;
	game.p1_creatures[1].power = 0;
	game.p1_creatures[2].power = 0;
	game.p1_creatures[3].power = 0;
	game.p1_creatures[4].power = 0;
	game.p1_creatures[0].strength = 0;
	game.p1_creatures[1].strength = 0;
	game.p1_creatures[2].strength = 0;
	game.p1_creatures[3].strength = 0;
	game.p1_creatures[4].strength = 0;
	game.p2_creatures[0].power = 0;
	game.p2_creatures[1].power = 0;
	game.p2_creatures[2].power = 0;
	game.p2_creatures[3].power = 0;
	game.p2_creatures[4].power = 0;
	game.p2_creatures[0].strength = 0;
	game.p2_creatures[1].strength = 0;
	game.p2_creatures[2].strength = 0;
	game.p2_creatures[3].strength = 0;
	game.p2_creatures[4].strength = 0;
	game.p1_creatures[0].asleep = true;
	game.p1_creatures[1].asleep = true;
	game.p1_creatures[2].asleep = true;
	game.p1_creatures[3].asleep = true;
	game.p1_creatures[4].asleep = true;
	game.p2_creatures[0].asleep = true;
	game.p2_creatures[1].asleep = true;
	game.p2_creatures[2].asleep = true;
	game.p2_creatures[3].asleep = true;
	game.p2_creatures[4].asleep = true;
	return game;
}

void print_game(Game game) {
	puts("+-----------+-----------+-----------+-----------+-----------+\n|           |           |           |           |           |");
	for (int i = 0; i < 5; ++i) {
		if (game.p2_creatures[i].power != 0 || game.p2_creatures[i].strength != 0) {
			printf("| %4d/%d",game.p2_creatures[i].power,game.p2_creatures[i].strength);
			for (int a = 9999; game.p2_creatures[i].strength < a; a /= 10)
				printf(" ");
		}
		else
			printf("|           ");
	}
	puts("|\n|           |           |           |           |           |\n+-----------+-----------+-----------+-----------+-----------+");
	puts("|           |           |           |           |           |");
	for (int i = 0; i < 5; ++i) {
		if (game.p1_creatures[i].power != 0 || game.p1_creatures[i].strength != 0) {
			printf("| %4d/%d",game.p1_creatures[i].power,game.p1_creatures[i].strength);
			for (int a = 9999; game.p1_creatures[i].strength < a; a /= 10)
				printf(" ");
		}
		else
			printf("|           ");
	}
	puts("|\n|           |           |           |           |           |");
	puts("+-----------+-----------+-----------+-----------+-----------+");
	printf("Player 1 Life: %d\nPlayer 2 Life: %d\n", game.p1_life, game.p2_life);
}

int main() {
	int atk;
	int zone;
	bool skip;
	bool empty;
	char answer;
	Game game = reset_game();
	while (game.p1_life > 0 && game.p2_life > 0) {
		if (game.p1_life != 1) {
			print_game(game);
			do {
				puts("Which zone do you want to summon a creature to?");
				scanf("%d", &zone);
			} while (zone < 1 || zone > 5 || game.p1_creatures[zone-1].power != 0 || game.p1_creatures[zone-1].strength != 0);
			game.p1_creatures[zone-1] = summon(game.p1_life);
			game.p1_life -= game.p1_creatures[zone-1].power + game.p1_creatures[zone-1].strength;
			skip = false;
		} else skip = true;
		for (int i = 0; i < 5; ++i)
			if (game.p1_creatures[i].asleep == false) {
				print_game(game);
				do {
					printf("Do you want to attack with the creature in zone %d?\n",i+1);
					scanf("%c",&answer);
				} while (answer != 'Y' && answer != 'N' && answer != 'y' && answer != 'n');
				if (answer == 'Y' || answer == 'y') {
					empty = true;
					for (int a = 0; a < 5; ++a) {
						if (game.p2_creatures[a].power != 0 || game.p2_creatures[a].strength != 0)
						empty = false;
					}
					if (empty == true) {
						printf("Direct Attack! Player 2 lost %d Life.\n", game.p1_creatures[i].power);
						game.p2_life -= game.p1_creatures[i].power;
					}
					else {
						do {
							puts("Which zone with a monster to you want to attack?");
							scanf("%d", &atk);
						} while (atk < 1 || atk > 5 || (game.p2_creatures[atk-1].power == 0 && game.p2_creatures[atk-1].strength == 0));
						if (game.p1_creatures[i].power >= game.p2_creatures[atk-1].strength && game.p1_creatures[i].strength <= game.p2_creatures[atk-1].power) {
							game.p1_creatures[i].power = 0;
							game.p1_creatures[i].strength = 0;
							game.p1_creatures[i].asleep = true;
							game.p2_creatures[atk-1].power = 0;
							game.p2_creatures[atk-1].strength = 0;
							game.p2_creatures[atk-1].asleep = true;
						}
						else if (game.p1_creatures[i].power < game.p2_creatures[atk-1].strength && game.p1_creatures[i].strength <= game.p2_creatures[atk-1].power) {
							game.p1_creatures[i].power = 0;
							game.p1_creatures[i].strength = 0;
							game.p1_creatures[i].asleep = true;
						}
						else if (game.p1_creatures[i].power >= game.p2_creatures[atk-1].strength && game.p1_creatures[i].strength > game.p2_creatures[atk-1].power) {
							game.p2_creatures[atk-1].power = 0;
							game.p2_creatures[atk-1].strength = 0;
							game.p2_creatures[atk-1].asleep = true;
						}
					}
				}
			}
		game.p1_creatures[zone-1].asleep = skip;
		if (game.p2_life != 1) {
			print_game(game);
			do {
				puts("Which zone do you want to summon a creature to?");
				scanf("%d", &zone);
			} while (zone < 1 || zone > 5 || game.p2_creatures[zone-1].power != 0 || game.p2_creatures[zone-1].strength != 0);
			game.p2_creatures[zone-1] = summon(game.p2_life);
			game.p2_life -= game.p2_creatures[zone-1].power + game.p2_creatures[zone-1].strength;
			skip = false;
		} else skip = true;
		for (int i = 0; i < 5; ++i)
			if (game.p2_creatures[i].asleep == false) {
				print_game(game);
				do {
					printf("Do you want to attack with the creature in zone %d?\n",i+1);
					scanf("%c",&answer);
				} while (answer != 'Y' && answer != 'N' && answer != 'y' && answer != 'n');
				if (answer == 'Y' || answer == 'y') {
					empty = true;
					for (int a = 0; a < 5; ++a) {
						if (game.p1_creatures[a].power != 0 || game.p1_creatures[a].strength != 0)
						empty = false;
					}
					if (empty == true) {
						printf("Direct Attack! Player 1 lost %d Life.\n", game.p2_creatures[i].power);
						game.p1_life -= game.p2_creatures[i].power;
					}
					else {
						do {
							puts("Which zone with a creature to you want to attack?");
							scanf("%d", &atk);
						} while (atk < 1 || atk > 5 || (game.p1_creatures[atk-1].power == 0 && game.p1_creatures[atk-1].strength == 0));
						if (game.p1_creatures[atk-1].power >= game.p2_creatures[i].strength && game.p1_creatures[atk-1].strength <= game.p2_creatures[i].power) {
							game.p1_creatures[i].power = 0;
							game.p1_creatures[i].strength = 0;
							game.p1_creatures[i].asleep = true;
							game.p2_creatures[atk-1].power = 0;
							game.p2_creatures[atk-1].strength = 0;
							game.p2_creatures[atk-1].asleep = true;
						}
						else if (game.p1_creatures[i].power < game.p2_creatures[atk-1].strength && game.p1_creatures[atk-1].strength <= game.p2_creatures[i].power) {
							game.p1_creatures[i].power = 0;
							game.p1_creatures[i].strength = 0;
							game.p1_creatures[i].asleep = true;
						}
						else if (game.p1_creatures[i].power >= game.p2_creatures[atk-1].strength && game.p1_creatures[atk-1].strength > game.p2_creatures[i].power) {
							game.p2_creatures[atk-1].power = 0;
							game.p2_creatures[atk-1].strength = 0;
							game.p2_creatures[atk-1].asleep = true;
						}
					}
				}
			}
		game.p2_creatures[zone-1].asleep = skip;
	}
	if (game.p2_life < 1)
		puts("Player 1 Wins!");
	else if (game.p1_life < 1)
		puts("Player 2 Wins!");
	else
		puts("Draw!");
	getchar();
}
