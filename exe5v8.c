/*

*/

#include <stdio.h>

int main()
{
    int contador = 0;

    while (contador < 10)
    {
        if (contador == 5)
        {
            contador++;
            continue;
        }
        printf("contador %d\n", contador);

        contador++;

    }
    return 0; 
}