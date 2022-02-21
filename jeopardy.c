/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    //char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    printf("This is Jeopardy \n");

    // initialize each of the players in the array
    for(int i = 0; i < 4; i++) {
        players[i].score = 0;

        printf("Enter player name: ");
        scanf("%s", (char *) &players[i].name);
    }

    // Perform an infinite loop getting command input from users until game ends
    //while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    while(!answered_status())
    {
        system("clear");

        char selected_player[MAX_LEN] = "";
        char selected_category[MAX_LEN] = "";
        int selected_val = 0;

        do {
            if(strcmp(selected_player, "") != 0)
                printf("The player %s was not found", selected_player);

            printf("Enter first player's name: ");
            scanf("%s", (char *) &selected_player);
        } while(!player_exists(players, 4, selected_player));

        do {
            if(selected_val != 0)
                printf("Invalid selection");

            printf("Enter category: ");
            getchar();
            fgets((char *) selected_category, MAX_LEN, stdin);
            strtok(selected_category, "\n");

            printf("Enter: ");
            scanf("%d", (int *) &selected_val);
        } while(already_answered(selected_category, selected_val));


        system("clear");
        display_question(selected_category, selected_val);

        char *answer[MAX_LEN] = {0};
        getchar();
        fgets((char *) answer, MAX_LEN, stdin);

        char *tokenize_answer;
        tokenize((char *) answer, &tokenize_answer);

        if(tokenize_answer == NULL)
            printf("Try again");
        else if(valid_answer(selected_category, selected_val, tokenize_answer)) {
            printf("Correct Answer!");
            printf("%s gains %d points \n", selected_player, selected_val);
            update_score(players, 4, selected_player, selected_val);
        } else {
            printf("Wrong Answer!");
            int num = get_question_number(selected_category, selected_val);
            printf("Correct answer was: %s", questions[num].answer);
        }

        track_answered(selected_category, selected_val);

        // Call functansions from the questions and players source files

        // Execute the game until all questions are answered

        // Display the final results and exit
    }

    show_results(players, 4);
    getchar();

    return EXIT_SUCCESS;
}


void tokenize(char *input, char **tokens) {
    char *str;

    if((str = strtok(input, "")) != NULL)
        if(strcmp(str, "who") != 0 && strcmp(str, "what") != 0)
            return;

    if((str = strtok(NULL, "")) != NULL)
        if(strcmp(str, "is") != 0)
            return;

    *tokens = strtok(NULL, "\n");
}

void show_results(player *players, int num_players) {
    int name = 0;
    int score = 0;
    int winner = 0;

    for(int i = 0; i < num_players; i++) {
        if((int) strlen(players[i].name) > name)
            name = strlen(players[i].name);

        if(players[i].score > score) {
            score = players[i].score;
            winner = i;
        }
    }

    printf("Scores: \n");
    for(int i = 0; i < num_players; i++)
        printf("%*s: %d\n", name + 1, players[i].name, players[i].score);

    printf("Winner: %s", players[winner].name);
}
