#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define FILE_PATH "highscores.txt"

typedef struct {
    const char *q, *opt[4];
    char ans;
} Question;

const Question bank[] = {
    {"Capital of India?", {"A. Mumbai", "B. Delhi", "C. Kolkata", "D. Chennai"}, 'B'},
    {"Author of Ramayana?", {"A. Kalidasa", "B. Tulsidas", "C. Valmiki", "D. Ved Vyas"}, 'C'},
    {"Formula of H2O?", {"A. Oxygen", "B. Hydrogen", "C. Water", "D. Salt"}, 'C'},
    {"Red Planet?", {"A. Venus", "B. Earth", "C. Jupiter", "D. Mars"}, 'D'},
    {"Boiling Point of Water?", {"A. 90°C", "B. 100°C", "C. 120°C", "D. 80°C"}, 'B'},
    {"First Indian in space?", {"A. Kalpana", "B. Rakesh Sharma", "C. Vikram Sarabhai", "D. Nehru"}, 'B'},
    {"Java is?", {"A. OS", "B. Language", "C. Browser", "D. CPU"}, 'B'},
    {"Light year measures?", {"A. Speed", "B. Time", "C. Distance", "D. Light"}, 'C'},
    {"RAM is?", {"A. Storage", "B. Memory", "C. Disk", "D. Power"}, 'B'},
    {"Sun is?", {"A. Planet", "B. Star", "C. Satellite", "D. Meteor"}, 'B'}
};

void menu();
void startQuiz();
void showScores();
void instructions();
void saveScore(const char*, int);
char getOption();
void shuffle(int*, int);
void flush();

int main() {
    int c;
    while (1) {
        menu();
        printf("Choose: ");
        if (scanf("%d", &c) != 1) { flush(); continue; }
        switch (c) {
            case 1: startQuiz(); break;
            case 2: instructions(); break;
            case 3: showScores(); break;
            case 4: printf("Exiting.\n"); exit(0);
            default: printf("Invalid.\n");
        }
    }
}

void menu() {
    printf("\n===== QUIZMASTER =====\n");
    printf("1. Start\n2. Instructions\n3. High Scores\n4. Exit\n");
}

void instructions() {
    printf("\nRULES:\n- Choose the correct option (A/B/C/D).\n- Each correct = 1 point.\n- Final score saved.\n");
}

void startQuiz() {
    int idx[10], score = 0;
    char name[50], userAns;

    printf("\nEnter Name: ");
    scanf(" %[^\n]", name);

    srand(time(0));
    shuffle(idx, 10);

    for (int i = 0; i < 10; i++) {
        const Question *q = &bank[idx[i]];
        printf("\nQ%d. %s\n", i + 1, q->q);
        for (int j = 0; j < 4; j++) printf("%s\n", q->opt[j]);
        userAns = getOption();

        if (userAns == q->ans) {
            printf("✔ Correct\n");
            score++;
        } else {
            printf("✘ Wrong | Correct: %c\n", q->ans);
        }
    }

    printf("\n%s, your score: %d/%d\n", name, score, 10);
    if (score == 10) printf("Outstanding!\n");
    else if (score >= 8) printf("Brilliant Work!\n");
    else if (score >= 5) printf("Good Attempt.\n");
    else printf("You need to focus more.\n");

    saveScore(name, score);
}

void saveScore(const char* name, int score) {
    FILE *fp = fopen(FILE_PATH, "a");
    if (!fp) return;
    fprintf(fp, "%s - %d\n", name, score);
    fclose(fp);
}

void showScores() {
    FILE *fp = fopen(FILE_PATH, "r");
    if (!fp) {
        printf("No scores yet.\n");
        return;
    }
    printf("\n=== LEADERBOARD ===\n");
    char line[100];
    while (fgets(line, sizeof(line), fp)) printf("%s", line);
    fclose(fp);
}

char getOption() {
    char opt;
    printf("Answer (A/B/C/D): ");
    scanf(" %c", &opt);
    return toupper(opt);
}

void shuffle(int *a, int size) {
    for (int i = 0; i < size; i++) a[i] = i;
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

void flush() {
    while (getchar() != '\n');
}
