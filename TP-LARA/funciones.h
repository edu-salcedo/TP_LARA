#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


const char *PATH_PLATOS = "datos/platos.dat";

void opciones(int op)
{
    struct platos plato;
    int opciones;
    do{
    switch(op)
    {
    case 1:
        opciones=menuPlato();
        switch(opciones)
        {
           case 1: if (cargar_plato(&plato))
                       {
                       guardar_plato(plato);
                       }

              break;
           case 2:  editar_plato();
              break;
           case 3:  listar_plato_id(plato);
              break;
           case 4:  platos_restaurante(plato);
              break;
           case 5: listar_todo(plato);
              break;
              case 6: baja_plato();
              break;
          }
      break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;

        break;

    }
  } while(opciones!=0);
}

bool cargar_plato(platos *plat)
{
    int i,id,op;
    do{
    cout <<"ingrese id :";
    cin>>id;
    if (id<1)
    {    cls();
        setColor(RED);
       cout<<" \n no se puede ingresar numeros negativos"<<endl;
       setColor(LIGHTCYAN);
       cin.ignore();
       cin.get();
       cls();
    }
    }while(id<1);
    op=buscar_ID_plato(id);
    system("cls");
    if(op ==-1)
    {  plat->id=id;
    cout <<"     ID          "<<id<<endl;
    do{
    cout <<" NOMBRE            :";
    cin.ignore();
    cin.getline(plat->nombre,50,'\n');
     i=strlen(plat->nombre);                          //validando que se ingrese un nombre y no quede vacio
    if (i==0)
    {    setColor(RED);
        cout <<"no se ingresado un nombre ";
         setColor(LIGHTCYAN);
        cin.get();
        cls();
    }
    }while(i==0);
     plat->costoPre=validacion_costo();                      //  validando las condicones mediante funciones con
     plat->valor=validacion_venta(plat->costoPre);           //  retorno.
     plat->tiempo_Pre=  validacion_tiempo();
     plat->id_Restaurante=validacion_id_res();
     plat->comision_Rest= validacion_comision();
     plat->id_categoria=validacion_cat();
     plat->estado=true;
      cls();
     cout <<"\n EL PLATO SE CARGO CORRECTAMENTE "<<endl;
     return true;
    }

   cout <<"  EL PLATO NO SE PUDO CARGAR "<<endl;
   cin.ignore();
   cin.get();
   cls();
   return false;
}

int buscar_ID_plato(int id)
{   platos plat;
    int i=0;
    FILE *p;
    p=fopen(PATH_PLATOS,"rb");
        if (p==NULL)
         {
        cout <<"no se encontro archivo";
         return -1;
         }
while (fread(&plat, sizeof(platos),1,p))
{

    if (id==plat.id)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

void guardar_plato(platos plat)
{
  FILE *p;
  p=fopen(PATH_PLATOS,"ab");
  if (p==NULL)
  {
      cout <<" no se pudo abrir archivo";
  }
  fwrite(&plat,sizeof(platos),1,p);
  fclose(p);
}

int listar(platos plat)
{
     setColor(LIGHTMAGENTA);
    cout <<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    setColor(WHITE);
    cout <<"    ID               :"<<plat.id<<endl;
    cout <<"    NOMBRE           :"<<plat.nombre<<endl;
    cout <<" COSTO PREPARACION   :"<<plat.costoPre<<" pesos"<<endl;
    cout <<" VALOR VENTA         :"<<plat.valor<<endl;
    cout <<" TIEMPO PREPARACION  :"<<plat.tiempo_Pre<<" minutos"<<endl;
    cout <<" ID RESTAURANTE      :"<<plat.id_Restaurante<<endl;
    cout <<" COMICION RESTAURANTE:"<<plat.comision_Rest<<" pesos"<<endl;
    cout <<" ID CATEGORIA        :"<<plat.id_categoria<<endl;
    setColor(LIGHTMAGENTA);
    cout <<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    cout <<endl;
    cout <<"------------------------------"<<endl;
    cout <<endl;


}

void listar_plato_id(platos plat)
{  int id,pos;
   cout <<" ingrese id "<<endl;
   cin >>id;
   pos= buscar_ID_plato(id);
  if (pos>=0)
  {
      platos plat =leer_platos(pos);
      if (plat.estado==true)
      {
         listar(plat);
      }
      else{
        setColor(GREEN);
        cout <<" \n =============================="<<endl;
        setColor(RED);
        cout <<"  no se encontro id del plato "<<endl;
        setColor(GREEN);
        cout <<" =============================="<<endl;
      }
  }
  else{
        setColor(GREEN);
        cout <<" \n =============================="<<endl;
        setColor(RED);
        cout <<"  no se encontro id del plato "<<endl;
        setColor(GREEN);
        cout <<" =============================="<<endl;
      }

  cin.ignore();
  cin.get();
  cls();
}

void listar_todo(platos plat)
{
    FILE *p;
    p=fopen(PATH_PLATOS,"rb");
    if (p==NULL)
    {
        cout <<"no se pudo abrir archvo";
      return;
    }
   while(fread(&plat,sizeof(platos),1,p))
   {
       if (plat.estado==true)
       {
           listar(plat);
       }
   }
   fclose(p);
   cin.ignore();
   cin.get();
   cls();
}


struct platos leer_platos(int pos)
{   platos plat;
    FILE *p;
    p=fopen(PATH_PLATOS,"rb");
    if (p==NULL)
    {
        cout<<"no se encontro archivo\n";
        plat.id= -1;
        return plat;
    }
    fseek(p,pos*sizeof(platos),SEEK_SET);
    fread(&plat,sizeof(platos),1,p);
    fclose(p);
    return plat;
}


void editar_plato()
{   int id,pos,op;
   platos plato;
    cout<< "ingrese plato a aditar "<<endl;
    cin>>id;
    cls();
   pos= buscar_ID_plato(id);
   plato=leer_platos(pos);
   if (pos>=0&&plato.estado==true)
   {

       do{
       op= menu_editar(id);
        switch(op)
       {
       case 1:cin.ignore();
            cout<<" NUEVO NOMBRE  :";cin.getline(plato.nombre,50,'\n');
           sobreescribir(plato,pos);
         break;
       case 2:
            cout<<" NUEVO COSTO PREPARACION :";cin>>plato.costoPre;
           sobreescribir(plato,pos);
         break;
       case 3:cout<<" NUEVO VALOR VENTA   : ";cin>>plato.valor;
            sobreescribir(plato,pos);
         break;
       case 4: cout<<" NUEVO TIEMPO PREPARACION: ";cin>>plato.tiempo_Pre;
        sobreescribir(plato,pos);
         break;
       case 5: cout<<" NUEVO ID RESTAURANTE    :";cin>>plato.id_Restaurante;
        sobreescribir(plato,pos);
         break;
       case 6: cout<<" NUEVO COMICION RESTAURANTE:";cin>>plato.comision_Rest;
        sobreescribir(plato,pos);
         break;
       case 7: cout<<" NUEVO  ID CATEGORIA     : ";cin>>plato.id_categoria;
        sobreescribir(plato,pos);
         break;
         case 0:
             break;
         }
       }while (op!=0);
    }
    else{
        setColor(GREEN);
        cout <<" \n =============================="<<endl;
        setColor(RED);
        cout <<"  no se encontro id del plato "<<endl;
        setColor(GREEN);
        cout <<" =============================="<<endl;
    }
    cin.ignore();
    cin.get();
    cls();
}

bool sobreescribir(platos plat,int pos)
{   bool escribio;
    FILE * p;
    p=fopen(PATH_PLATOS,"rb+");
    if(p==NULL)
    {
        cout <<"no se pudo abrir archivo\n";
        return false;
    }
    fseek(p,pos*sizeof(platos),SEEK_SET);
    escribio=fwrite(&plat,sizeof(platos),1,p);
    fclose(p);
    return escribio;

}


void platos_restaurante(platos plat)     // lista platos por  id de restaurante
{  int id_resta,i=0,cont=0;
   bool res =true;
    cout <<"ingrese ID del restaurante "<<endl;
    cin>>id_resta;
    FILE *p;
    p=fopen(PATH_PLATOS,"rb");
    if (p==NULL)
    {
        cout <<"no se encontro archivo" <<endl;
        return ;
    }

       do{
        fseek(p,i*sizeof(platos),SEEK_SET);
       res=fread(&plat,sizeof(platos),1,p);
        if (plat.id_Restaurante==id_resta)
        {
        platos plato =leer_platos(i);
        listar(plato);
        cont++;
        }
        i++;
       }while (res);

        fclose(p);
        if (cont==0){
                setColor(RED);
            cout <<" el id de restaurante no exixte";
        }

        cin.ignore();
        cin.get();

}


 void baja_plato()
 {   int id,pos;
     cout <<" ingrese id del plato ";
     cin>>id;
    pos= buscar_ID_plato(id);
     if (pos>=0)
     {
    platos plato=leer_platos(pos);
    plato.estado=false;
    sobreescribir(plato,pos);
     }
     else{
        setColor(GREEN);
        cout <<" \n =============================="<<endl;
        setColor(RED);
        cout <<"  no se encontro id del plato "<<endl;
        setColor(GREEN);
        cout <<" =============================="<<endl;
     }
 }

#endif // FUNCIONES_H_INCLUDED
