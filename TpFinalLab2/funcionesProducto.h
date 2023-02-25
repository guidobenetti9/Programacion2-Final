#ifndef FUNCIONESPRODUCTO_H_INCLUDED
#define FUNCIONESPRODUCTO_H_INCLUDED

bool sobreEscribirRegistroProducto(Producto obj, int pos);
bool eliminarLogicoRegistroProducto();
int contarRegistrosProducto();
int contarRegistrosProductoSinEliminar();
int buscarIDProducto(int ID);
int buscarIDProductoEliminado(int ID);
int mostrarRegistrosBorradosProducto();
bool bajaFisicaProductos();
bool recuperacionLogicaProducto();
bool recuperacionLogicaProductoCompleta();
bool backupProducto();
bool recuperacionFisicaProducto();

/// hacer listados personalizados........pendiente

bool sobreEscribirRegistroProducto(Producto obj, int pos){
    FILE *p;
    p=fopen(ARCHIVO_PRODUCTOS, "rb+");
    if(p==NULL)return false;
    fseek(p, sizeof obj*pos, 0);
    bool escribio=fwrite(&obj, sizeof (Producto), 1, p);
    fclose(p);
    return escribio;
}

bool eliminarLogicoRegistroProducto(){
    Producto obj;
    int ID, pos;
    cout<<"INGRESE EL ID DEL Producto A ELIMINAR: ";
    cin>>ID;
    pos=buscarIDProducto(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(false);
    if(sobreEscribirRegistroProducto(obj, pos)){
        return true;
    }
    return false;

}

int contarRegistrosProducto(){
    int cantidad;
    FILE *f;
    Producto obj;
    f=fopen(ARCHIVO_PRODUCTOS,"rb");
    if (f==NULL) {
        fclose(f);
        return 0;
    }
        fseek(f, 0, SEEK_END);
        cantidad= ftell(f)/sizeof obj;

    fclose(f);
    return cantidad;
}

int contarRegistrosProductoSinEliminar(){
    int cantidad=0;
    FILE *f;
    Producto obj;
    f=fopen(ARCHIVO_PRODUCTOS,"rb");
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

int buscarIDProducto(int ID){
    Producto obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_PRODUCTOS,"rb");
    if(pAlu==NULL){
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIDProducto()==ID&&obj.getEstado()==true){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int buscarIDProductoEliminado(int ID){
    Producto obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_PRODUCTOS,"rb");
    if(pAlu==NULL){
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1){
        if(obj.getIDProducto()==ID&&obj.getEstado()==false){
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int mostrarRegistrosBorradosProducto(){
Producto Producto;
int  i=0,j=0;

while(Producto.leerDeDisco(i)){
    if(Producto.getEstado()==false){
        Producto.setEstado(true);
        Producto.Mostrar();
        Producto.setEstado(false);
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

bool bajaFisicaProductos(){
    Producto reg;
    int pos=0;
    FILE *p, *pNuevo;
    cout<<"LOS SIGUIENTES REGISTROS SERAN ELIMINADOS DE MANERA DEFINITIVA"<<endl;
    int ret= mostrarRegistrosBorradosProducto();
    if(ret==-1)return false;
    cout<<"DESEA CONTINUAR? (S/N): ";
    char respuesta;
    cin>>respuesta;
    if(respuesta=='N' || respuesta=='n')return false;
    p=fopen(ARCHIVO_PRODUCTOS_BACKUP, "wb");
    while(reg.leerDeDisco(pos++)){
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    pNuevo=fopen(ARCHIVO_PRODUCTOS, "wb");
    if(pNuevo==NULL)return false;

    p=fopen(ARCHIVO_PRODUCTOS_BACKUP, "rb");
    if(p==NULL){
        fclose(pNuevo);
        return false;
    }
    while(fread(&reg,sizeof reg,1,p)==1){
        if(reg.getEstado()==true){
            fwrite(&reg, sizeof reg,1, pNuevo);
        }
        else{
            cout<<"Producto ["<<reg.getIDProducto()<<"] "<<"BORRADO"<<endl;
        }
    }
    fclose(p);
    fclose(pNuevo);
    return true;
}

bool recuperacionLogicaProducto(){
    Producto obj;
    int ID, pos;

    int ret= mostrarRegistrosBorradosProducto();
    if(ret==-1)return false;
    cout<<"Ingresar id de Producto a recuperar: ";cin>>ID;
    pos=buscarIDProductoEliminado(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO O NO FUE ELIMINADO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(true);
    if(sobreEscribirRegistroProducto(obj, pos)){
        return true;
    }
    return false;
}

bool recuperacionLogicaProductoCompleta(){
    Producto obj;
    int pos=0;
    bool sob;
    while(obj.leerDeDisco(pos)==true){
        obj.setEstado(true);
        sob= sobreEscribirRegistroProducto(obj, pos);
        cout<<"PRODUCTO ["<<obj.getIDProducto()<<"] "<<"RESTAURADO EXITOSAMENTE"<<endl;
        pos++;

    }
    return sob;
}

bool backupProducto(){
    Producto reg;
    int pos=0;
    FILE *p,*a;
    a=fopen(ARCHIVO_PRODUCTOS, "rb");
    if(a==NULL) {
        cout<<"  NO HAY PRODUCTOS CARGADOS!" <<endl;
        return false;
    }
    p=fopen(ARCHIVO_PRODUCTOS_BACKUP, "wb");
    if(p==NULL){return false;}
    while(reg.leerDeDisco(pos++)){
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    fclose(a);
    return true;
}

bool recuperacionFisicaProducto(){
    Producto reg;
    FILE *p, *pNuevo;

    p=fopen(ARCHIVO_PRODUCTOS_BACKUP, "rb");
    if(p==NULL){
        fclose(p);
        return false;
    }
    pNuevo=fopen(ARCHIVO_PRODUCTOS, "wb");
    if(pNuevo==NULL)return false;

    while(fread(&reg,sizeof reg,1,p)==1){

            fwrite(&reg, sizeof reg,1, pNuevo);
            cout<<"Producto ["<<reg.getIDProducto()<<"] "<<"RECUPERADO EXITOSAMENTE"<<endl;

    }
    fclose(p);
    fclose(pNuevo);
    return true;
}

#endif // FUNCIONESPRODUCTO_H_INCLUDED
