#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


void establecerDatosInicio(){

    system("copy VendedoresIni.ini Vendedores.dat");
    system("copy VentaCabeceraIni.ini VentaCabecera.dat");
    system("copy VentaDetalleIni.ini VentaDetalle.dat");
    system("copy VentaPieIni.ini VentaPie.dat");
    system("copy ProductosIni.ini Productos.dat");
    system("copy proveedoresIni.ini proveedores.dat");
    system("cls");
    cout<<"  Datos establecidos"<<endl;

}

void ponerCeroVector(int *a, int x) {
    int i;
    for(i=0; i<x; i++)
        a[i]=0;
}

void sumarVectores(int *a, int *b, int *destino, int x) {
    int i;
    for(i=0; i<x; i++)
        destino[i]=a[i]+b[i];
}

enum Color
{
    cNEGRO=0,
    cAZUL=1,
    cVERDE=2,
    cCIAN=3,
    cROJO=4,
    cMAGENTA=5,
    cMARRON=6,
    cGRIS_CLARO=7,
    cGRIS=8,
    cAZUL_CLARO=9,
    cVERDE_CLARO=10,
    cCIAN_CLARO=11,
    cROJO_CLARO=12,
    cMAGENTA_CLARO=13,
    cAMARILLO=14,
    cBLANCO=15
};
void gotoxy(short x, short y)  ///UBICA EL CURSOR EN LA POSICIÓN x,y DE LA PANTALLA
{
    COORD a;
    a.X = x;
    a.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void clrscr(void) {
    system("cls");
}
void pause(void) {
    system("pause >nul");
}
void textcolor(short colorTexto=15, short colorFondo=0) {
    short color = colorTexto + colorFondo * 16;
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), color);
}
void recuadro(short iniX, short iniY, short ancho, short alto, short colorLinea=cBLANCO, short colorFondo=cNEGRO) {
    int i, j;
    for(i=iniX; i<=iniX+ancho; i++) {
        for(j=iniY; j<=iniY+alto; j++) {
            gotoxy(i, j);
            textcolor(colorLinea, colorFondo);
            //Arriba izquierda
            if(i==iniX && j==iniY) {
                cout << (char) 201;
            }
            //Arriba derecha
            else if(i==iniX+ancho && j==iniY) {
                cout << (char) 187;
            }
            //Abajo izquierda
            else if(i==iniX && j==iniY+alto) {
                cout << (char) 200;
            }
            //Abajo derecha
            else if(i==iniX+ancho && j==iniY+alto) {
                cout << (char) 188;
            }
            //Lineas arriba y abajo
            else if(j==iniY || j==iniY+alto) {
                cout << (char) 205;
            }
            //Lineas izquierda y derecha
            else if(i==iniX || i==iniX+ancho) {
                cout << (char) 186;
            }
            //Dentro del recuadro
            else {
                cout << " ";
            }
        }
    }
}

///////////////////////////////////////////////////////


///PROTOTIPOS
bool alta();
void copiarChar(const char*, char);
void ponerCeroMatriz(int mat[20][31], int fila, int col);
void mostrarMatriz(int mat[][31], int fila, int col);
bool ingresarDatosAccesos(int vMat[], int m[20][31]);
void puntoA(int vMat[], char mat[][30],int mAccesos[][31]);
void puntoB(int vMat[], char mat[][30]);
int buscarMaximo(float v[], int tam);
int buscarMaximo(int *v, int tam);
void buscarTresMayores(int *v, int tam);
void MostrarNombreMeses(int pos);
void MostrarNombreMeses(int pos) {
    const char Meses[12][40]= {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    cout<<Meses[pos-1];
}
///Ordenamiento por filas:
void ordenar_m_fila(int (*m)[5], int fila, int col) {
    int i,j,k,nc,aux;
    for(k=0; k<fila; k++)
        for(i=0; i<col-1; i++) {
            nc=i;
            for(j=i+1; j<col; j++)
                if(m[k][j]>m[k][nc])
                    nc=j;
            aux=m[k][i];
            m[k][i]=m[k][nc];
            m[k][nc]=aux;
        }
}
///Ordenamiento por columnas:
void ordenar_m_col(int (*m)[5], int fila, int col) {
    int i,j,k,nf,aux;
    for(k=0; k<col; k++)
        for(i=0; i<fila-1; i++) {
            nf=i;
            for(j=i+1; j<fila; j++)
                if(m[j][k]>m[nf][k])
                    nf=j;
            aux=m[i][k];
            m[i][k]=m[nf][k];
            m[nf][k]=aux;
        }
}


void ordenarVector(int *v, int tam);

void ordenarVector(int *v, int tam) {
    int i, j, posmin, aux;
    for(i=0; i<tam-1; i++) {
        posmin=i;
        for(j=i+1; j<tam; j++)
            if(v[j]<v[posmin])
                posmin=j;
        aux=v[i];
        v[i]=v[posmin];
        v[posmin]=aux;
    }
}

void puntoC(int m[20][31], char mat[][30]);

void cargarMaterias(char nombres[][30]);
void cargarCadena(char *pal, int tam);
void mostrarCadena(const char *pal);
void mostrarCadena(char *pal);
void mostrarMatrizCaracteres(char m[][30], int cant);

void inicializarVector(float *v,int tam,int valor);

void inicializarVector(int *v,int tam,int valor);

void mostrarVector(float *v, int tam);
void mostrarVector(int *v, int tam);

const char * mostrarMateria(char nombres[][30],int numero);
bool estaEnCero(int m[][31],int fila);
void menuConsultas(int *horas, char materias[][30], int matDia[][31]);
///FIN PROTOTIPOS

bool estaEnCero(int m[][31],int fila) {
    int suma=0, i;
    for(i=0; i<31; i++) {
        suma+=m[fila][i];
    }
    if(suma==0)return true;
    else return false;
}

const char *mostrarMateria(char nombres[][30],int numero) {
    return nombres[numero-1];
}
///SOBRECARGA DE FUNCIONES: ME PERMITE HACER FUNCIONES CON EL MISMO NOMBRE.
///SE ELIGE CUÁL USAR DE ACUERDO AL TIPO DE DATO DEL PARÁMETRO CUANDO SE LLAMA A LA FUNCIÓN
///
void inicializarVector(float *v,int tam,int valor=0) {
    int i;
    for(i=0; i<tam; i++) {
        v[i]=valor;
    }
}

void inicializarVector(int *v,int tam,int valor=0) {
    int i;
    for(i=0; i<tam; i++) {
        v[i]=valor;
    }
}
void mostrarVector(float *v, int tam) {
    int i;
    for(i=0; i<tam; i++) {
        cout<<v[i]<<endl;
    }
}

void mostrarVector(int *v, int tam) {
    int i;
    for(i=0; i<tam; i++) {
        cout<<v[i]<<endl;
    }
}
void cargarCadena(char *pal, int tam) {
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++) {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}

void mostrarCadena(const char *pal) {
    int i=0;
    while(pal[i]!='\0') {
        cout<<pal[i];
        i++;
    }

}

void mostrarCadena(char *pal) {
     int i=0;
    while(pal[i]!='\0') {
        cout<<pal[i];
        i++;
    }

}


void ponerCeroMatriz(int mat[20][31], int fila, int col) {
    int i,j;
    for(i=0; i<fila; i++) {
        for(j=0; j<col; j++) {
            mat[i][j]=0;
        }
    }

}

void mostrarMatriz(int mat[20][31], int fila, int col) {
    int i,j;
    for(i=0; i<fila; i++) {
        for(j=0; j<col; j++) {
            cout<<mat[i][j]<<"\t";
        }
        cout<<endl;
    }
}

bool ingresarDatosAccesos(int *vMat, int m[][31]) {
    int legajo,dia,nroMat;
    cout<<"LEGAJO: ";
    cin>>legajo;
    while(legajo!=0) {
        cout<<"MATERIA: ";
        cin>>nroMat;
        cout<<"DIA: ";
        cin>>dia;
        ///punto a y b
        vMat[nroMat-1]++;
        ///punto c
        m[nroMat-1][dia-1]++;
        cout<<"LEGAJO: ";
        cin>>legajo;
    }
    return true;
}

void puntoA(int vMat[], char mat[][30], int mAccesos[][31]) {
    int i;
    cout<<"MATERIAS SIN ACCESO"<<endl;
    for(i=0; i<20; i++) {
        ///if(vMat[i]==0){
        if(estaEnCero(mAccesos,i)) {
            cout<<i+1<<"\t"<<mat[i]<<endl;
        }
    }
}


void puntoB(int vMat[], char mat[][30]) {
    int matMax;
    matMax=buscarMaximo(vMat,20);
    cout<<"LA MATERIA CON MAS ACCESOS FUE: "<<matMax+1<<"\t"<<mat[matMax]<<endl;
}

int buscarMaximo(float *v, int tam) {
    int i, posMax=0;

    for(i=1; i<tam; i++) {
        if(v[i]>v[posMax]) {
            posMax=i;
        }
    }
    return posMax;
}

int buscarMaximo(int *v, int tam) {
    int i, posMax=0;

    for(i=1; i<tam; i++) {
        if(v[i]>v[posMax]) {
            posMax=i;
        }
    }
    return posMax;
}
void puntoC(int m[20][31], char mat[][30]) {
    int i, j;
    for(i=0; i<10; i++) {
        cout<<"MATERIA "<<i+1<<" "<<mat[i]<<endl;
        for(j=0; j<31; j++) {
            if(m[i][j]!=0) {
                cout<<"DIA "<<j+1<<" "<<"ACCESOS "<<m[i][j]<<endl;
            }
        }
        system("pause");
    }


}///

void cargarMaterias(char nombres[][30]) {
    int i, numeroMateria;
    for(i=0; i<10; i++) {
        cout<<"NUMERO DE MATERIA: ";
        cin>>numeroMateria;
        cout<<"NOMBRE DE MATERIA: ";
        cargarCadena(nombres[numeroMateria-1],29);
    }
}

void mostrarMatrizCaracteres(char m[][30], int cant) {
    int i;
    for(i=0; i<cant; i++) {
        cout<<"NUMERO DE MATERIA: "<<i+1<<"\t";
        cout<<m[i]<<endl;
    }

}

void menuConsultas(int *horas, char materias[][30], int matDia[][31]) {
    int opc;
    while(true) {
        system("cls");
        cout<<"MENU CONSULTAS"<<endl;
        cout<<"1. MATERIAS SIN ACCESOS"<<endl;
        cout<<"2. MATERIA CON MAS ACCESOS"<<endl;
        cout<<"3. ESTADISTICAS AGOSTO"<<endl;
        cout<<"0. VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<"------------------------"<<endl;
        cout<<"OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            puntoA(horas, materias, matDia);
            break;
        case 2:
            puntoB(horas, materias);
            break;
        case 3:
            puntoC(matDia, materias);
            break;
        case 0:
            return;
            break;
        default:
            cout<<"OPCION INCORRECTA"<<endl;
        }
        system("pause");
    }

}

void buscarTresMayores(int *v, int tam) {
    int pos=0, segPos=0, terPos;

    for (int i=0; i<tam; i++) {
        if(v[i]>v[pos]) {
            pos=i;
        }
    }
    for(int i=0; i<tam; i++) {
        if(pos!=i) {
            if(v[i]>v[segPos]) {
                segPos=i;
            }
        }
    }
    for(int i=0; i<tam; i++) {
        if(pos!=i&&segPos!=i) {
            if(v[i]>v[terPos]) {
                terPos=i;
            }
        }
    }
    cout<<endl;
    cout<<endl;
    cout<<v[pos];
    cout<<endl;
    cout<<v[segPos];
    cout<<endl;
    cout<<v[terPos];
    cout<<endl;
    system("pause");

}


#endif // FUNCIONES_H_INCLUDED
