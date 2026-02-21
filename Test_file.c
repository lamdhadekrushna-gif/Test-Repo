/*
 * ============================================================
 *   QUIZ GAME — Console Multiple Choice Quiz in C
 *   Concepts: switch, loops, strings
 * ============================================================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NAME_MAX    50
#define MAX_OPTIONS  4

/* ── Data Structure ─────────────────────────────────────────── */
typedef struct {
    char question[256];
    char options[MAX_OPTIONS][100];  /* 0=A, 1=B, 2=C, 3=D */
    char correct;                    /* 'A', 'B', 'C', or 'D' */
} Question;

/* ── Question Bank (add/edit questions here) ─────────────────── */
Question questions[] = {
    {
        "What does CPU stand for?",
        {"Control Processing Unit", "Central Processing Unit",
         "Central Program Unit", "Core Processing Utility"},
        'B'
    },
    {
        "Which data type stores a single character in C?",
        {"int", "float", "char", "string"},
        'C'
    },
    {
        "What symbol is used for single-line comments in C?",
        {"##", "//", "**", "%%"},
        'B'
    },
    {
        "Which loop always executes its body at least once?",
        {"for", "while", "do-while", "foreach"},
        'C'
    },
    {
        "What is the output of:  printf(\"%d\", 10 % 3);",
        {"3", "0", "1", "2"},
        'C'
    },
    {
        "Which function reads a string with spaces in C?",
        {"scanf(\"%s\")", "getchar()", "fgets()", "gets_string()"},
        'C'
    },
    {
        "What value does an uninitialized global int have in C?",
        {"Garbage value", "1", "0", "-1"},
        'C'
    },
    {
        "Which header file is needed to use strlen()?",
        {"stdlib.h", "math.h", "string.h", "ctype.h"},
        'C'
    },
    {
        "How do you declare a pointer to an int in C?",
        {"int p;", "int &p;", "pointer int p;", "int *p;"},
        'D'
    },
    {
        "What does the return statement in main() return to?",
        {"The compiler", "The linker", "The operating system", "The CPU"},
        'C'
    }
};

/* ── Helper: print a styled banner line ─────────────────────── */
void printLine(char ch, int len) {
    for (int i = 0; i < len; i++) putchar(ch);
    putchar('\n');
}

/* ── Helper: clear leftover input from stdin ─────────────────── */
void flushInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ── Helper: compute grade from percentage ───────────────────── */
char getGrade(int pct) {
    switch (pct / 10) {
        case 10:
        case  9: return 'A';
        case  8: return 'B';
        case  7: return 'C';
        case  6: return 'D';
        default: return 'F';
    }
}

/* ── Helper: motivational message based on grade ────────────── */
const char *getMessage(char grade) {
    switch (grade) {
        case 'A': return "Outstanding! You're a quiz master!";
        case 'B': return "Great job! Just a little more polish!";
        case 'C': return "Good effort! Keep practising!";
        case 'D': return "You passed, but there's room to grow.";
        default:  return "Don't give up — every expert was once a beginner!";
    }
}

/* ── Main ────────────────────────────────────────────────────── */
int main(void) {

    char playerName[NAME_MAX];
    int  score  = 0;
    int  total  = (int)(sizeof(questions) / sizeof(questions[0]));
    char answer;
    char labels[] = {'A', 'B', 'C', 'D'};

    /* ── Welcome Screen ───────────────────────────────────────── */
    printLine('=', 50);
    printf("          WELCOME TO THE C QUIZ GAME\n");
    printLine('=', 50);
    printf("  %d questions | Topics: C Programming Basics\n", total);
    printLine('-', 50);
    printf("\n  Enter your name: ");
    fgets(playerName, NAME_MAX, stdin);
    playerName[strcspn(playerName, "\n")] = '\0';   /* strip trailing newline */

    printf("\n  Good luck, %s! Let's begin.\n", playerName);
    printLine('=', 50);

    /* ── Question Loop ────────────────────────────────────────── */
    for (int i = 0; i < total; i++) {

        /* Print question */
        printf("\nQuestion %d of %d\n", i + 1, total);
        printLine('-', 40);
        printf("  %s\n\n", questions[i].question);

        /* Print options */
        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("    %c)  %s\n", labels[j], questions[i].options[j]);
        }

        /* Input validation loop */
        do {
            printf("\n  Your answer (A / B / C / D): ");
            scanf(" %c", &answer);
            answer = (char)toupper((unsigned char)answer);

            switch (answer) {
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                    break;   /* valid — exit the switch */
                default:
                    printf("  [!] Invalid input. Please enter A, B, C, or D.\n");
                    answer = 0;   /* reset so the loop continues */
            }
        } while (answer == 0);

        /* Evaluate answer */
        if (answer == questions[i].correct) {
            printf("  ✓  Correct!\n");
            score++;
        } else {
            printf("  ✗  Wrong!  The correct answer was: %c) %s\n",
                   questions[i].correct,
                   questions[i].options[questions[i].correct - 'A']);
        }

        /* Running score */
        printf("  Score so far: %d / %d\n", score, i + 1);
        printLine('-', 40);

        flushInput();   /* discard rest of input line */
    }

    /* ── Final Results Screen ─────────────────────────────────── */
    int  pct   = (score * 100) / total;
    char grade = getGrade(pct);

    printf("\n");
    printLine('=', 50);
    printf("               QUIZ COMPLETE!\n");
    printLine('=', 50);
    printf("  Player  : %s\n",       playerName);
    printf("  Score   : %d / %d\n",  score, total);
    printf("  Result  : %d%%\n",     pct);
    printf("  Grade   : %c\n",       grade);
    printLine('-', 50);
    printf("  %s\n", getMessage(grade));
    printLine('=', 50);
    printf("\n");

    return 0;
}