#include <stdio.h>

int main()
{

    int contador;
    for (contador = 0; contador < 10; contador++)
    {
        printf("contador: %d\n", contador);
    }
    //inicializar a variavel
    contador = 0;

    // enquanto contador for menor do que 10, executa
    while (contador < 10)
    {
        // codigo a executar, enquanto o ciclo for verdadeiro
        printf("contador: %d\n", contador);

        //incrementar -> somar 1
        contador++;
    }
    

}