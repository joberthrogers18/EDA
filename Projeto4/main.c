#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
     int x;
     srand(time(NULL));

    x = 20 + (rand()%44);
    printf("%d ", x);

     return 0;
}
