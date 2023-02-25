#ifndef CLASEFECHA_H_INCLUDED
#define CLASEFECHA_H_INCLUDED

time_t tiempo = time(NULL);
struct tm *tmPtr = localtime(&tiempo);

int diaActual= tmPtr->tm_mday;
int mesActual= tmPtr->tm_mon + 1;
int anioActual= tmPtr->tm_year+1900;
bool fechavalida(int dia, int mes, int anio) {
    if(dia<1 || dia>31) return false;
    else if (mes<1 || mes>12) return false;
    else switch(mes) {
        case 4:
        case 6:
        case 9:
        case 11:
            if(dia>30) return false;
            break;
        case 2:
            if (dia>28)return false;
            break;
        }


    if (anio>anioActual) {
        return false;
    }
    if(anio<anioActual) {
        return true;
    }

    if(anio==anioActual&&mes==mesActual&&dia<=diaActual) {
        return true;
    }
    if(anio==anioActual&&mes<=mesActual&&dia<=diaActual) {
        return true;
    }
    if(anio==anioActual&&mes==mesActual&&dia>diaActual) {
        return false;
    }
    if((mes>mesActual)&&(anio==anioActual)) {
        return false;
    }

    if(mes<=mesActual) {

        if(mes==mesActual&&dia<=diaActual) {

            return true;
        }

        return true;

    }
    return true;
}

class Fecha {
    private:
        int dia, mes, anio;


    public:
        Fecha(int d=diaActual, int m=mesActual, int a=anioActual) {
            if(fechavalida(diaActual,mesActual,anioActual)) {
                dia=diaActual;
                mes=mesActual;
                anio=anioActual;
            } else {
                cout<<"  ERROR! Fecha invalida"<<endl;
            }

        }

        bool setDia(int d) {
            if(d>0&&d<32) {
                dia=d;
                return true;
            }
            return false;

        }
        bool setMes(int m) {
            if(m>0&&m<=12) {
                mes=m;
                return true;
            }
            return false;

        }
        bool setAnio(int a) {
            if(a>=1900&&a<=2022) {
                anio=a;
                return true;
            }
            return false;

        }
        int getDia() {
            return dia;
        }
        int getMes() {
            return mes;
        }
        int getAnio() {
            return anio;
        }
        bool Cargar() {


            int d,m,a,bd=0,bm=0,ba=0, iv=0;
            do {
                bd=0;
                bm=0;
                ba=0;
                if(iv==1) {
                    cout<<"  Fecha invalida, ingresar de nuevo\n";
                }
                do {
                    if(bd==1) {
                        cout<<"  Error! ingresar nuevamente=> ";
                    }

                    cout<<"  DIA: ";
                    cin>>d;
                    setDia(d);
                    bd=1;
                } while(!setDia(d));
                do {
                    if(bm==1) {
                        cout<<"  Error! ingresar nuevamente=> ";
                    }

                    cout<<"  MES: ";
                    cin>>m;
                    setMes(m);
                    bm=1;
                } while(!setMes(m));
                do {
                    if(ba==1) {
                        cout<<"  Error! ingresar nuevamente: ";
                    }

                    cout<<"  ANIO: ";
                    cin>>a;
                    setAnio(a);


                    ba=1;

                } while(!setAnio(a));
                iv=1;
            } while(fechavalida(getDia(),getMes(),getAnio())==false);
            return true;
        }
        void Mostrar() {
            cout<<dia<<" de ";
            MostrarNombreMeses(mes);
            cout<<" de "<<anio;
        }

};

#endif // CLASEFECHA_H_INCLUDED
