#ifndef FUNCIONESVENTADETALLE_H_INCLUDED
#define FUNCIONESVENTADETALLE_H_INCLUDED


bool sobreEscribirRegistroVentaDetalle(VentaDetalle obj, int pos);
int contarRegistrosVentaDetalle();
int contarRegistrosVentaDetalleSinEliminar();
int buscarIDVentaDetalle(int ID);
int buscarIDVentaDetalleEliminado(int ID);
int mostrarRegistrosBorradosVentaDetalle();
bool bajaFisicaVentaDetalles();
bool recuperacionLogicaVentaDetalle();
bool backupVentaDetalle();
bool recuperacionFisicaVentaDetalle();


/// hacer listados personalizados........pendiente

bool recuperacionLogicaVentaDetalleCompleta(){
    VentaDetalle obj;
    int pos=0;
    bool sob;
    while(obj.leerDeDisco(pos)==true){
        obj.setEstado(true);
        sob= sobreEscribirRegistroVentaDetalle(obj, pos);
        if(sob==true) cout<<"DETALLE DE BOLETA ["<<obj.getIdVentaDetalle()<<"] "<<"RESTAURADO EXITOSAMENTE"<<endl;
        pos++;

    }
    return sob; ///si el ultimo no se sobreescribio correctamente entonces no es completa
}


bool sobreEscribirRegistroVentaDetalle(VentaDetalle obj, int pos){
    FILE *p;
    p=fopen(ARCHIVO_VENTA_DETALLE, "rb+");
    if(p==NULL)return false;
    fseek(p, sizeof obj*pos, 0);
    bool escribio=fwrite(&obj, sizeof (VentaDetalle), 1, p);
    fclose(p);
    return escribio;
}





int contarRegistrosVentaDetalle(){
    int cantidad;
    FILE *f;
    VentaDetalle obj;
    f=fopen(ARCHIVO_VENTA_DETALLE,"rb");
    if (f==NULL) {
        fclose(f);
        return 0;
    }
        fseek(f, 0, SEEK_END);
        cantidad= ftell(f)/sizeof obj;

    fclose(f);
    return cantidad;
}

int contarRegistrosVentaDetalleSinEliminar(){
    int cantidad=0;
    FILE *f;
    VentaDetalle obj;
    f=fopen(ARCHIVO_VENTA_DETALLE,"rb");
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

int buscarIDVentaDetalle(int ID){
    VentaDetalle obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_VENTA_DETALLE,"rb");
    if(pAlu==NULL){
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIDVentaDetalle()==ID&&obj.getEstado()==true){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int buscarIDVentaDetalleEliminado(int ID){
    VentaDetalle obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_VENTA_DETALLE,"rb");
    if(pAlu==NULL){
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIDVentaDetalle()==ID&&obj.getEstado()==false){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int mostrarRegistrosBorradosVentaDetalle(){
VentaDetalle VentaDetalle;
int  i=0,j=0;

while(VentaDetalle.leerDeDisco(i)){
    if(VentaDetalle.getEstado()==false){
        VentaDetalle.setEstado(true);
        VentaDetalle.Mostrar();
        VentaDetalle.setEstado(false);
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

bool bajaFisicaVentaDetalles(){
    VentaDetalle reg;
    int pos=0;
    FILE *p, *pNuevo;
    cout<<"LOS SIGUIENTES REGISTROS SERAN ELIMINADOS DE MANERA DEFINITIVA"<<endl;
    int ret= mostrarRegistrosBorradosVentaDetalle();
    if(ret==-1)return false;
    cout<<"DESEA CONTINUAR? (S/N): ";
    char respuesta;
    cin>>respuesta;
    if(respuesta=='N' || respuesta=='n')return false;
    p=fopen(ARCHIVO_VENTA_DETALLE_BACKUP, "wb");
    while(reg.leerDeDisco(pos++)){
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    pNuevo=fopen(ARCHIVO_VENTA_DETALLE, "wb");
    if(pNuevo==NULL)return false;

    p=fopen(ARCHIVO_VENTA_DETALLE_BACKUP, "rb");
    if(p==NULL){
        fclose(pNuevo);
        return false;
    }
    while(fread(&reg,sizeof reg,1,p)==1){
        if(reg.getEstado()==true){
            fwrite(&reg, sizeof reg,1, pNuevo);
        }
        else{
            cout<<"VentaDetalle ["<<reg.getIDVentaDetalle()<<"] "<<"BORRADO"<<endl;
        }
    }
    fclose(p);
    fclose(pNuevo);
    return true;
}

bool recuperacionLogicaVentaDetalle(){
    VentaDetalle obj;
    int ID, pos;
    int ret= mostrarRegistrosBorradosVentaDetalle();
    if(ret==-1)return false;
    cout<<endl<<"Ingresar id de VentaDetalle a recuperar: ";cin>>ID;
    pos=buscarIDVentaDetalleEliminado(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO O NO FUE ELIMINADO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(true);
    if(sobreEscribirRegistroVentaDetalle(obj, pos)){
        return true;
    }
    return false;
}

bool backupVentaDetalle(){
    VentaDetalle reg;
    int pos=0;
    FILE *p,*a;
    a=fopen(ARCHIVO_VENTA_DETALLE, "rb");
    if(a==NULL) {
        cout<<"  NO HAY VENTAS (DETALLE) CARGADAS!" <<endl;
        return false;
    }
    p=fopen(ARCHIVO_VENTA_DETALLE_BACKUP, "wb");
    if(p==NULL){return false;}
    while(reg.leerDeDisco(pos++)){
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    fclose(a);
    return true;
}

bool recuperacionFisicaVentaDetalle(){

    VentaDetalle reg;
    FILE *p, *pNuevo;
    p=fopen(ARCHIVO_VENTA_DETALLE_BACKUP, "rb");
    if(p==NULL){
        fclose(p);
        return false;
    }

    pNuevo=fopen(ARCHIVO_VENTA_DETALLE, "wb");
    if(pNuevo==NULL)return false;

    while(fread(&reg,sizeof reg,1,p)==1){

            fwrite(&reg, sizeof reg,1, pNuevo);
            cout<<"DETALLE DE BOLETA ["<<reg.getIDVentaDetalle()<<"] "<<"RECUPERADO EXITOSAMENTE"<<endl;

    }
    fclose(p);
    fclose(pNuevo);
    return true;
}



#endif // FUNCIONESVENTADETALLE_H_INCLUDED
