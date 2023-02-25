#ifndef FUNCIONESVENTAPIE_H_INCLUDED
#define FUNCIONESVENTAPIE_H_INCLUDED

bool sobreEscribirRegistroVentaPie(VentaPie obj, int pos);
bool eliminarLogicoRegistroVentaPie();
int contarRegistrosVentaPie();
int contarRegistrosVentaPieSinEliminar();
int buscarIDVentaPie(int ID);
int buscarIDVentaPieEliminado(int ID);
int mostrarRegistrosBorradosVentaPie();
bool bajaFisicaVentaPie();
bool recuperacionLogicaVentaPie();
bool backupVentaPie();
bool recuperacionFisicaVentaPie();
bool recuperacionLogicaVentaPieCompleta();

bool recuperacionLogicaVentaPieCompleta(){
    VentaPie obj;
    int pos=0;
    bool sob;
    while(obj.leerDeDisco(pos)==true){
        obj.setEstado(true);
        sob= sobreEscribirRegistroVentaPie(obj, pos);
        if(sob==true) cout<<"PIE DE BOLETA ["<<obj.getIDVentaPie()<<"] "<<"RESTAURADO EXITOSAMENTE"<<endl;
        pos++;
    }
    return sob;///por que si el ultimo no se sobreescribio entonces no es completa
}

/// hacer listados personalizados........pendiente

bool sobreEscribirRegistroVentaPie(VentaPie obj, int pos){
    FILE *p;
    p=fopen(ARCHIVO_VENTA_PIE, "rb+");
    if(p==NULL)return false;
    fseek(p, sizeof obj*pos, 0);
    bool escribio=fwrite(&obj, sizeof (VentaPie), 1, p);
    fclose(p);
    return escribio;
}

bool eliminarLogicoRegistroVentaPie(){
    VentaPie obj;
    int ID, pos;
    cout<<"INGRESE EL ID DEL VentaPie A ELIMINAR: ";
    cin>>ID;
    pos=buscarIDVentaPie(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(false);
    if(sobreEscribirRegistroVentaPie(obj, pos)){
        return true;
    }
    return false;

}

int contarRegistrosVentaPie(){
    int cantidad;
    FILE *f;
    VentaPie obj;
    f=fopen(ARCHIVO_VENTA_PIE,"rb");
    if (f==NULL) {
        fclose(f);
        return 0;
    }
        fseek(f, 0, SEEK_END);
        cantidad= ftell(f)/sizeof obj;

    fclose(f);
    return cantidad;
}

int contarRegistrosVentaPieSinEliminar(){
    int cantidad=0;
    FILE *f;
    VentaPie obj;
    f=fopen(ARCHIVO_VENTA_PIE,"rb");
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

int buscarIDVentaPie(int ID){
    VentaPie obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_VENTA_PIE,"rb");
    if(pAlu==NULL){
        cout<<"  ERROR DE LECTURA"<<endl;
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIdVentaCabecera()==ID && obj.getEstado()==true){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int buscarIDVentaPieEliminado(int ID){
    VentaPie obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_VENTA_PIE,"rb");
    if(pAlu==NULL){
        cout<<"  ERROR DE LECTURA"<<endl;
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIdVentaCabecera()==ID&&obj.getEstado()==false){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int mostrarRegistrosBorradosVentaPie(){
VentaPie VentaPie;
int  i=0,j=0;
cout<<"  Boletas Eliminadas (cabecera)" <<endl;
while(VentaPie.leerDeDisco(i)){
    if(VentaPie.getEstado()==false){
        VentaPie.setEstado(true);
        VentaPie.Mostrar();
        VentaPie.setEstado(false);
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

bool bajaFisicaVentaPie(){
    VentaPie reg;
    int pos=0;
    FILE *p, *pNuevo;
    cout<<"LOS SIGUIENTES REGISTROS SERAN ELIMINADOS DE MANERA DEFINITIVA"<<endl;
    int ret= mostrarRegistrosBorradosVentaPie();
    if(ret==-1)return false;
    cout<<"DESEA CONTINUAR? (S/N): ";
    char respuesta;
    cin>>respuesta;
    if(respuesta=='N' || respuesta=='n')return false;

    if(respuesta=='S' || respuesta=='s'){

        p=fopen(ARCHIVO_VENTA_PIE_BACKUP, "wb");
        while(reg.leerDeDisco(pos++)){
            fwrite(&reg, sizeof reg,1, p);
        }
        fclose(p);
        pNuevo=fopen(ARCHIVO_VENTA_PIE, "wb");
        if(pNuevo==NULL)return false;

        p=fopen(ARCHIVO_VENTA_PIE_BACKUP, "rb");
        if(p==NULL){
            fclose(pNuevo);
            return false;
        }
        while(fread(&reg,sizeof reg,1,p)==1){
            if(reg.getEstado()==true){
                fwrite(&reg, sizeof reg,1, pNuevo);
            }
            else{
                cout<<"VentaPie ["<<reg.getIDVentaPie()<<"] "<<"BORRADO"<<endl;
            }
        }
        fclose(p);
        fclose(pNuevo);
        return true;
    }
    return false;
}

bool recuperacionLogicaVentaPie(){
    VentaPie obj;
    int ID, pos;
    mostrarRegistrosBorradosVentaPie();
    cout<<"Ingresar id de VentaPie a recuperar: ";cin>>ID;
    pos=buscarIDVentaPieEliminado(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO O NO FUE ELIMINADO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(true);
    if(sobreEscribirRegistroVentaPie(obj, pos)){
        return true;
    }
    return false;
}

bool backupVentaPie(){
    VentaPie reg;
    int pos=0;
    FILE *p,*a;
    a=fopen(ARCHIVO_VENTA_PIE, "rb");
    if(a==NULL) {
        cout<<"  NO HAY VENTAS (CABECERA) CARGADAS!" <<endl;
        return false;
    }
    p=fopen(ARCHIVO_VENTA_PIE_BACKUP, "wb");
    if(p==NULL){return false;}
    while(reg.leerDeDisco(pos++)){
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    fclose(a);
    return true;
}

bool recuperacionFisicaVentaPie(){

    VentaPie reg;
    FILE *p, *pNuevo;


    p=fopen(ARCHIVO_VENTA_PIE_BACKUP, "rb");
    if(p==NULL){
        fclose(p);
        return false;
    }

    pNuevo=fopen(ARCHIVO_VENTA_PIE, "wb");
    if(pNuevo==NULL)return false;

    while(fread(&reg,sizeof reg,1,p)==1){

            fwrite(&reg, sizeof reg,1, pNuevo);
            cout<<"PIE DE BOLETA ["<<reg.getIDVentaPie()<<"] "<<"RECUPERADO EXITOSAMENTE"<<endl;

    }
    fclose(p);
    fclose(pNuevo);
    return true;
}

#endif // FUNCIONESVENTAPIE_H_INCLUDED
