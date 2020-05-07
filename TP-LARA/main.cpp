#include <iostream>
#include <stdlib.h>
#include "rlutil.h"
using namespace rlutil;
#include <string.h>
# include <cstdlib>
# include  <cstdio>
using namespace std;
#include "prototipo.h"
#include  "menu_validaciones.h"
#include "funciones.h"


int main()
{ int op;
   gotoxy(1,3);
    intro();
    do{

    op=menuPrincipal();
    if (op)
    {
       opciones(op);
    }
   } while (op!=0);
    return 0;
}

