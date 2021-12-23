#include <iostream>

int move_p(int &dice, int& dice_count)
{
    int move = (dice++);
    if(dice == 101) dice = 1;

    move += (dice++);
    if(dice == 101) dice = 1;

    move += (dice++);
    if(dice == 101) dice = 1;

    dice_count += 3;
    return move;
}

void take_turn(int& p_X, int& die, int& dice_count, int &pX_score)
{
    int move = move_p(die, dice_count);
    if( (p_X + move)%10 == 0)
        p_X = 10;
    else
        p_X = (p_X + move)%10;

    pX_score += p_X;
}

int main(int argc, char *argv[])
{
    int p0, p1;
    if(argc != 3)
    {
        std::cout << "Need two starting inputs" << std::endl;
        return 0;
    }
    else
    {
        p0 = atoi(argv[1]);
        p1 = atoi(argv[2]);
        std::cout << "Player 1 starting position: " << p0 << std::endl;
        std::cout << "Player 2 starting position: " << p1 << std::endl;
    }

    int p0_score = 0;
    int p1_score = 0;
    int die = 1;
    int dice_count = 0;
    while( p0 < 1000 && p1 < 1000)
    {
        take_turn(p0, die, dice_count, p0_score);
        if(p0_score >= 1000) break;

        take_turn(p1, die, dice_count, p1_score);
        if(p1_score >= 1000) break;
    };

    printf("Answer: %d %d %d\n", p0_score, p1_score, dice_count);
    printf("%d\n", (p0_score < p1_score) ? p0_score * dice_count : p1_score * dice_count);

    return 0;
}
