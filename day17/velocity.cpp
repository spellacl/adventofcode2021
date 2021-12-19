#include <iostream>

void update(int vx_0, int vy_0, int &answer, int &count, int x0, int xx, int y0, int yy)
{
    int pos_x = 0, pos_y = 0;
    int vx = vx_0, vy = vy_0;
    int max_y = answer;
    bool hit = false;
    int steps = 0;
    do
    {
        steps += 1;
        pos_x += vx;
        pos_y += vy;
        if(max_y < pos_y)
            max_y = pos_y;

        if(vx < 0) vx += 1;  
        else if (vx > 0) vx -= 1;

        vy -= 1;

        if(pos_x >= x0 && pos_x <= xx && pos_y >= y0 && pos_y <= yy)
        {
            hit = true;
            answer = max_y;
            count += 1;
            printf("(%d, %d) found %d\n", vx_0, vy_0, hit);
            break;
        }
    }
    while(pos_x <= xx && steps != 1000);
}

int main(int argc, char *argv[])
{
    if( argc != 5)
    {
        return 0;
    }

    int x0 = atoi(argv[1]);
    int xx = atoi(argv[2]);
    int y0 = atoi(argv[3]);
    int yy = atoi(argv[4]);

    printf("target area: x=%d..%d, y=%d..%d\n", x0, xx, y0, yy);

    int max_y = INT_MIN;
    int count = 0;
    for(int vx_0 = 1; vx_0 <= xx; vx_0 ++)
    {
        for(int vy_0 = -10000; vy_0 <= 10000; vy_0 ++)
        {
            update(vx_0, vy_0, max_y, count, x0, xx, y0, yy);
        }
    }
    printf("max_y: %d count = %d \n", max_y, count);

    return 0;
}
