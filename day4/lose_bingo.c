#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct objBoard
{
    int* board;
    int* found;
    int* row_count;
    int* col_count;
    int board_number;

    struct objBoard * next;
} Board;

Board* new_board(Board **head)
{
    Board * last = *head;

    Board *b = malloc(sizeof(Board));
    b->board = malloc(sizeof(int) * 25);
    b->found = malloc(sizeof(int) * 25);
    b->row_count = malloc(sizeof(int) * 5);
    b->col_count = malloc(sizeof(int) * 5);
    b->next = NULL;

    if(*head == NULL)
    {
        *head = b;
        b->board_number = 0;
    }
    else{
        while(last->next != NULL)
        {
            last = last->next;
        };

        last->next = b;
        b->board_number = last->board_number+1;
    }
    return b;
}

void board_ij(Board *b, int i, int j, int val)
{
    b->board[i * 5 + j] = val;
}

void print_board( Board **HEAD, char * which)
{
    Board *curr = *HEAD;
    while(curr != NULL)
    {
        printf("%s %d:\n", which, curr->board_number);
        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 5; j++)
            {
                if(which == "board")
                    printf("%2d ", curr->board[i*5 + j]);
                else if(which == "found")
                    printf("%2d ", curr->found[i*5 + j]);
            }
            printf("\n");
        }
        printf("\n");
        curr = curr->next;
    }
}

Board* winner(Board **HEAD, int *won, int* numboards)
{
    Board *curr = *HEAD;
    while(curr != NULL)
    {
        if(!won[curr->board_number])
        {
            for(int i = 0; i < 5; i++)
            {
                if(curr->row_count[i] == 5 || curr->col_count[i] == 5)
                {
                    won[curr->board_number] = 1;
                    (*numboards)--;
                    if(*numboards == 0)
                        return curr;
                    else
                        break;
                }
            }
        }
        curr = curr->next;
    }

    return NULL;
}


int score_winner(Board *b, int val)
{
    int unmarked = 0;
    for(int i = 0; i < 25; i++)
    {
        if(b->found[i] == 0) unmarked += b->board[i];
    }
    return unmarked * val;
}

void delete_board(Board *b)
{
    free(b->board);
    free(b->found);
    free(b->row_count);
    free(b->col_count);
    free(b);
}

void Bingo(Board **head, int value)
{
    Board *temp = *head;
    while(temp != NULL)
    {
        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 5; j++)
            {
                if(temp->board[i*5 +j] == value)
                {
                    temp->found[i*5+j] = 1;
                    temp->row_count[i] += 1;
                    temp->col_count[j] += 1;
                }
            }
        }
        temp = temp->next;
    }
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];
        char rounds[512];

        fgets(rounds, sizeof(rounds), file);

        Board * HEAD = NULL;
        int numboards = 0;
        while(fgets(line, sizeof(line), file))
        {
            Board *b = new_board(&HEAD);
            numboards ++;
            for(int i=0; i < 5; i++)
            {
                fgets(line, sizeof(line), file);
                char * token = strtok(line, " ");
                int j = 0;
                while (token != NULL)
                {
                    int val = atoi(token);
                    board_ij( b, i, j, val);
                    j++;
                    token = strtok(NULL, " ");
                };
            }
        };
        print_board(&HEAD, "board");
        int * won = malloc(sizeof(int)*numboards);

        char * token = strtok(rounds, ",");
        int val = 0;
        Board *win = NULL;
        while (token != NULL )
        {
            val = atoi(token);
            Bingo(&HEAD, val);

            win = winner(&HEAD, won, &numboards);
            if(win)
            {
//                print_board(&HEAD, "found");
                printf("board %d val %d score %d\n", win->board_number, val, score_winner(win, val));
                break;
            }

            token = strtok(NULL, ",");
        }

        free(won);

        fclose(file);
    }

    return 0;
}
