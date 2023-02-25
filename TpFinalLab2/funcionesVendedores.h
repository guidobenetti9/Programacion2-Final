#ifndef FUNCIONESVENDEDORES_H_INCLUDED
#define FUNCIONESVENDEDORES_H_INCLUDED

bool sobreEscribirRegistroVendedor(Vendedor obj, int pos);
bool eliminarLogicoRegistroVendedor();
int contarRegistrosVendedores();
int contarRegistrosVendedoresSinEliminar();
int buscarIDVendedor(int ID);
int buscarIDVendedorEliminado(int ID);
int mostrarRegistrosBorradosVendedores();
bool bajaFisicaVendedors();
bool recuperacionLogicaVendedor();
bool backupVendedores();
bool recuperacionFisicaVendedores();
bool recuperacionLogicaVendedorCompleta();

/// hacer listados personalizados........pendiente

bool recuperacionLogicaVendedorCompleta(){
    Vendedor obj;
    int pos=0;
    bool sob;
    while(obj.leerDeDisco(pos)==true){
        obj.setEstado(true);
        sob= sobreEscribirRegistroVendedor(obj, pos);
        if(sob==true) cout<<"VENDEDOR ["<<obj.getIDVendedor()<<"] "<<"RESTAURADO EXITOSAMENTE"<<endl;
        pos++;

    }
    return sob;
}

bool sobreEscribirRegistroVendedor(Vendedor obj, int pos){
    FILE *p;
    p=fopen(ARCHIVO_VENDEDORES, "rb+");
    if(p==NULL)return false;
    fseek(p, sizeof obj*pos, 0);
    bool escribio=fwrite(&obj, sizeof (Vendedor), 1, p);
    fclose(p);
    return escribio;
}

bool eliminarLogicoRegistroVendedor(){
    Vendedor obj;
    int ID, pos;
    cout<<"INGRESE EL ID DEL Vendedor A ELIMINAR: ";
    cin>>ID;
    pos=buscarIDVendedor(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(false);
    if(sobreEscribirRegistroVendedor(obj, pos)){
        return true;
    }
    return false;

}

int contarRegistrosVendedores(){
    int cantidad;
    FILE *f;
    Vendedor obj;
    f=fopen(ARCHIVO_VENDEDORES,"rb");
    if (f==NULL) {
        fclose(f);
        return 0;
    }
        fseek(f, 0, SEEK_END);
        cantidad= ftell(f)/sizeof obj;

    fclose(f);
    return cantidad;
}

int contarRegistrosVendedoresSinEliminar(){
    int cantidad=0;
    FILE *f;
    Vendedor obj;
    f=fopen(ARCHIVO_VENDEDORES,"rb");
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

int buscarIDVendedor(int ID){
    Vendedor obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_VENDEDORES,"rb");
    if(pAlu==NULL){
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIDVendedor()==ID&&obj.getEstado()==true){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int buscarIDVendedorEliminado(int ID){
    Vendedor obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_VENDEDORES,"rb");
    if(pAlu==NULL){
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIDVendedor()==ID&&obj.getEstado()==false){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int mostrarRegistrosBorradosVendedores(){
Vendedor Vendedor;
int  i=0,j=0;

while(Vendedor.leerDeDisco(i)){
    if(Vendedor.getEstado()==false){
        Vendedor.setEstado(true);
        Vendedor.Mostrar();
        Vendedor.setEstado(false);
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

bool bajaFisicaVendedors(){
    Vendedor reg;
    int pos=0;
    FILE *p, *pNuevo;
    cout<<"LOS SIGUIENTES REGISTROS SERAN ELIMINADOS DE MANERA DEFINITIVA"<<endl;
    int ret= mostrarRegistrosBorradosVendedores();
    if(ret==-1)return false;
    cout<<"DESEA CONTINUAR? (S/N): ";
    char respuesta;
    cin>>respuesta;
    if(respuesta=='N' || respuesta=='n')return false;
    p=fopen(ARCHIVO_VENDEDORES_BACKUP, "wb");
    while(reg.leerDeDisco(pos++)){
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    pNuevo=fopen(ARCHIVO_VENDEDORES, "wb");
    if(pNuevo==NULL)return false;

    p=fopen(ARCHIVO_VENDEDORES_BACKUP, "rb");
    if(p==NULL){
        fclose(pNuevo);
        return false;
    }
    while(fread(&reg,sizeof reg,1,p)==1){
        if(reg.getEstado()==true){
            fwrite(&reg, sizeof reg,1, pNuevo);
        }
        else{
            cout<<"Vendedor "<<reg.getIDVendedor()<<" "<<reg.getNombreVendedor()<<" "<<"BORRADO"<<endl;
        }
    }
    fclose(p);
    fclose(pNuevo);
    return true;
}

bool recuperacionLogicaVendedor(){
    Vendedor obj;
    int ID, pos;
    int ret= mostrarRegistrosBorradosVendedores();
    if(ret==-1)return false;
    cout<<"Ingresar id de Vendedor a recuperar: ";cin>>ID;
    pos=buscarIDVendedorEliminado(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO O NO FUE ELIMINADO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(true);
    if(sobreEscribirRegistroVendedor(obj, pos)){
        return true;
    }
    return false;
}

bool backupVendedores(){
    Vendedor reg;
    int pos=0;
    FILE *p,*a;
    a=fopen(ARCHIVO_VENDEDORES, "rb");
    if(a==NULL) {
        cout<<"  NO HAY VENDEDORES CARGADOS!" <<endl;
        return false;
    }
    p=fopen(ARCHIVO_VENDEDORES_BACKUP, "wb");
    if(p==NULL){return false;}
    while(reg.leerDeDisco(pos++)){
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    fclose(a);
    return true;
}

bool recuperacionFisicaVendedores(){

    Vendedor reg;
    FILE *p, *pNuevo;
    p=fopen(ARCHIVO_VENDEDORES_BACKUP, "rb");
    if(p==NULL){
        fclose(p);
        return false;
    }

    pNuevo=fopen(ARCHIVO_VENDEDORES, "wb");
    if(pNuevo==NULL)return false;

    while(fread(&reg,sizeof reg,1,p)==1){

            fwrite(&reg, sizeof reg,1, pNuevo);
            cout<<"VENDEDOR ["<<reg.getIDVendedor()<<"] "<<"RESTAURADO EXITOSAMENTE"<<endl;

    }
    fclose(p);
    fclose(pNuevo);
    return true;
}


#endif // FUNCIONESVENDEDORES_H_INCLUDED
