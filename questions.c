/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    for(int i = 0; i < 12; i++) {
    	strcpy(questions[i].category, categories[i % 3]);
    	questions[i].answered = false;
    	strcpy(questions[i].question, "Question");
    	strcpy(questions[i].answer, "Answer");
}
    questions[0].value = 200;
    strcpy(questions[0].question, "Common gas represented by the formula CO2");
    strcpy(questions[0].answer, "Carbon Dioxide");

    questions[1].value = 200;
    strcpy(questions[1].question, "In magnetism, like poles do this");
    strcpy(questions[1].answer, "repel");

    questions[2].value = 200;
    strcpy(questions[2].question, "Measuring system established in France in 1790, called originally Systeme Internationale");
    strcpy(questions[2].answer, "metric system");

    questions[3].value = 200;
    strcpy(questions[3].question, "Members of all nationalities except French can join this fighting force");
    strcpy(questions[3].answer, "Foreign LEgion");

    questions[4].value = 200;
    strcpy(questions[4].question, "Name of the air arm of the German military");
    strcpy(questions[4].answer, "luftwaffe");

    questions[5].value = 200;
    strcpy(questions[5].question, "The U.S. Air Force was part of the Army until ... It was called the Army Air Corp");
    strcpy(questions[5].answer, "1946");

    questions[6].value = 200;
    strcpy(questions[6].question, "Mt. Logan was thought the highest on this continent till someone measured Mt. McKinley");
    strcpy(questions[6].answer, "North America");

    questions[7].value = 200;
    strcpy(questions[7].question, "Different surveys have reported its height as 29,002, 29,141 and 29,028 feet");
    strcpy(questions[7].answer, "Mount Everest");

    questions[8].value = 200;
    strcpy(questions[8].question, "A mountain chain in the Sahara bears the name of this mythical man who bears the world");
    strcpy(questions[8].answer, "Atlas");

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    
    // print categories and dollar values for each unanswered question in questions array
    int width = 20;

    for (int i = 0; i < 3; ++i) {
		putchar('+');
		for (int j = 0; j < width; ++j)
			putchar('-');
	}
	printf("+\n");

	for(int i = 0; i < 3; i++) 
		printf("| %-*s", width - 1, categories[i]);
	printf("|\n");

	for (int i = 0; i < 3; ++i) {
		putchar('+');
		for (int j = 0; j < width; ++j)
			putchar('-');
	}

	for(int i = 0; i < 12; i++) {
		if(questions[i].answered == false) {
			printf("| $&-*d", width - 2, questions[i].value);
		} else {
			printf("| %-*s", width - 2, " - ");
		}

		if(i % 3 == 2)
			printf("|\n");
	}

	for (int i = 0; i < 3; ++i) {
		putchar('+');
		for (int j = 0; j < width; ++j)
			putchar('-');
	}
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    printf("Question (%s for $%d):\n", category, value);

	int num = get_question_number(category, value);
	if(num == -1)
		printf("question %s not found, %d\n", category, value);

	printf("\t%s\n", questions[num].question);

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    int num = get_question_number(category, value);
	if(num == -1)
		printf("question %s not found, %d\n", category, value);
    
    // Look into string comparison functions
    
    return (strcasecmp(answer, questions[num].answer) == 0);
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    for(int i = 0; i < 12; i++)
		if (questions[i].value == value && strcmp(questions[i].category, category) == 0)
			return questions[i].answered;
    // lookup the question and see if it's already been marked as answered
   return true;
}

void track_answered(char *category, int value) {
	for(int i = 0; i < 12; i++) 
		if(questions[i].value == value && strcmp(questions[i].category, category) == 0)
			questions[i].answered = true;
}

bool answered_status() {
	for(int i = 0; i < 12; i++)
		if(questions[i].answered == false)
			return false;

	return true;
}

int get_question_number(char *category, int value) {
	for(int i = 0; i < 12; i++)
		if(strcmp(questions[i].category, category) == 0 && questions[i].value == value)
			return i;


	return -1;
}
