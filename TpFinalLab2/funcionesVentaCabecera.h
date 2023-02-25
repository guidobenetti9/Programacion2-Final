#ifndef FUNCIONESVENTACABECERA_H_INCLUDED
#define FUNCIONESVENTACABECERA_H_INCLUDED

bool sobreEscribirRegistroVentaCabecera(VentaCabecera obj, int pos);
bool eliminarLogicoRegistroVentaCabecera();
int contarRegistrosVentaCabecera();
int contarRegistrosVentaCabeceraSinEliminar();
int buscarIDVentaCabecera(int ID);
int buscarIDVentaCabeceraEliminado(int ID);
int mostrarRegistrosBorradosVentaCabecera();
bool bajaFisicaVentaCabeceras();
bool recuperacionLogicaVentaCabecera();
bool backupVentaCabecera();
bool recuperacionFisicaVentaCabecera();
bool recuperacionLogicaVentaCabeceraCompleta();

bool recuperacionLogicaVentaCabeceraCompleta(){
    VentaCabecera obj;
    int pos=0;
    bool sob;
    while(obj.leerDeDisco(pos)==true){
        obj.setEstado(true);
        sob= sobreEscribirRegistroVentaCabecera(obj, pos);
        if(sob==true) cout<<"CABECERA DE BOLETA ["<<obj.getIDVentaCabecera()<<"] "<<"RESTAURADA EXITOSAMENTE"<<endl;
        pos++;
    }
    return sob;///por que si el ultimo no se sobreescribio entonces no es completa
}

/// hacer listados personalizados........pendiente

bool sobreEscribirRegistroVentaCabecera(VentaCabecera obj, int pos){
    FILE *p;
    p=fopen(ARCHIVO_VENTA_CABECERA, "rb+");
    if(p==NULL)return false;
    fseek(p, sizeof obj*pos, 0);
    bool escribio=fwrite(&obj, sizeof (VentaCabecera), 1, p);
    fclose(p);
    return escribio;
}

bool eliminarLogicoRegistroVentaCabecera(){
    VentaCabecera obj;
    int ID, pos;
    cout<<"INGRESE EL ID DEL VentaCabecera A ELIMINAR: ";
    cin>>ID;
    pos=buscarIDVentaCabecera(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(false);
    if(sobreEscribirRegistroVentaCabecera(obj, pos)){
        return true;
    }
    return false;

}

int contarRegistrosVentaCabecera(){
    int cantidad;
    FILE *f;
    VentaCabecera obj;
    f=fopen(ARCHIVO_VENTA_CABECERA,"rb");
    if (f==NULL) {
        fclose(f);
        return 0;
    }
        fseek(f, 0, SEEK_END);
        cantidad= ftell(f)/sizeof obj;

    fclose(f);
    return cantidad;
}

int contarRegistrosVentaCabeceraSinEliminar(){
    int cantidad=0;
    FILE *f;
    VentaCabecera obj;
    f=fopen(ARCHIVO_VENTA_CABECERA,"rb");
    if (f==NULL) {
        fclose(f);
        return -1;
    }
        //fseek(f, 0, SEEK_END);
        //cantidad= ftell(f)/sizeof obj;
        while(fread(&obj,sizeof obj, 1, f)==1){
            if(obj.getEstado()==true){
                cantidad++;
            }
        }

    fclose(f);
    return cantidad;
}

int buscarIDVentaCabecera(int ID){
    VentaCabecera obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_VENTA_CABECERA,"rb");
    if(pAlu==NULL){
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIDVentaCabecera()==ID&&obj.getEstado()==true){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int buscarIDVentaCabeceraEliminado(int ID){
    VentaCabecera obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_VENTA_CABECERA,"rb");
    if(pAlu==NULL){
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIDVentaCabecera()==ID&&obj.getEstado()==false){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int mostrarRegistrosBorradosVentaCabecera(){
VentaCabecera VentaCabecera;
int  i=0,j=0;
cout<<"  Boletas Eliminadas (cabecera)" <<endl;
while(VentaCabecera.leerDeDisco(i)){
    if(VentaCabecera.getEstado()==false){
        VentaCabecera.setEstado(true);
        VentaCabecera.Mostrar();
        VentaCabecera.setEstado(false);
        j++;
    }

    i++;
    }
    if(i==0){
        cout<<"No hay Archivo"<<endl;
        return -1;
    }
    i=0;

    if(j==0){
        cout<<"PAPELERA VACIA"<<endl;
        return -1;
    }
    return j;

}

bool bajaFisicaVentaCabeceras(){
    VentaCabecera reg;
    int pos=0;
    FILE *p, *pNuevo;
    cout<<"LOS SIGUIENTES REGISTROS SERAN ELIMINADOS DE MANERA DEFINITIVA"<<endl;
    int ret= mostrarRegistrosBorradosVentaCabecera();
    if(ret==-1)return false;
    cout<<"DESEA CONTINUAR? (S/N): ";
    char respuesta;
    cin>>respuesta;
    if(respuesta=='N' || respuesta=='n')return false;

    if(respuesta=='S' || respuesta=='s'){

        p=fopen(ARCHIVO_VENTA_CABECERA_BACKUP, "wb");
        while(reg.leerDeDisco(pos++)){
            fwrite(&reg, sizeof reg,1, p);
        }
        fclose(p);
        pNuevo=fopen(ARCHIVO_VENTA_CABECERA, "wb");
        if(pNuevo==NULL)return false;

        p=fopen(ARCHIVO_VENTA_CABECERA_BACKUP, "rb");
        if(p==NULL){
            fclose(pNuevo);
            return false;
        }
        while(fread(&reg,sizeof reg,1,p)==1){
            if(reg.getEstado()==true){
                fwrite(&reg, sizeof reg,1, pNuevo);
            }
            else{
                cout<<"VentaCabecera ["<<reg.getIDVentaCabecera()<<"] "<<"BORRADO"<<endl;
            }
        }
        fclose(p);
        fclose(pNuevo);
        return true;
    }
    return false;
}

bool recuperacionLogicaVentaCabecera(){
    VentaCabecera obj;
    int ID, pos;
    mostrarRegistrosBorradosVentaCabecera();
    cout<<"Ingresar id de VentaCabecera a recuperar: ";cin>>ID;
    pos=buscarIDVentaCabeceraEliminado(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO O NO FUE ELIMINADO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(true);
    if(sobreEscribirRegistroVentaCabecera(obj, pos)){
        return true;
    }
    return false;
}

bool backupVentaCabecera(){
    VentaCabecera reg;
    int pos=0;
    FILE *p,*a;
    a=fopen(ARCHIVO_VENTA_CABECERA, "rb");
    if(a==NULL) {
        cout<<"  NO HAY VENTAS (CABECERA) CARGADAS!" <<endl;
        return false;
    }
    p=fopen(ARCHIVO_VENTA_CABECERA_BACKUP, "wb");
    if(p==NULL){return false;}
    while(reg.leerDeDisco(pos++)){
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    fclose(a);
    return true;
}

bool recuperacionFisicaVentaCabecera(){

    VentaCabecera reg;
    FILE *p, *pNuevo;


    p=fopen(ARCHIVO_VENTA_CABECERA_BACKUP, "rb");
    if(p==NULL){
        fclose(p);
        return false;
    }

    pNuevo=fopen(ARCHIVO_VENTA_CABECERA, "wb");
    if(pNuevo==NULL)return false;

    while(fread(&reg,sizeof reg,1,p)==1){

            fwrite(&reg, sizeof reg,1, pNuevo);
            cout<<"CABECERA DE BOLETA ["<<reg.getIDVentaCabecera()<<"] "<<"RESTAURADA EXITOSAMENTE"<<endl;
    }
    fclose(p);
    fclose(pNuevo);
    return true;
}

#endif // FUNCIONESVENTACABECERA_H_INCLUDED
