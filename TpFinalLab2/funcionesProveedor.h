#ifndef FUNCIONESPROVEEDOR_H_INCLUDED
#define FUNCIONESPROVEEDOR_H_INCLUDED

bool cargarProveedor();
void ModificarProveedor();
bool sobreEscribirRegistroProveedor(Proveedor obj, int pos);
bool eliminarLogicoRegistroProveedor();
int contarRegistrosProveedor();
int contarRegistrosProveedorSinEliminar();
int buscarIDProveedor(int ID);
int buscarCategoriaProveedor(int cat);
bool mostrarProveedorPorCategoria();
bool mostrarProveedorPorID();
int buscarIDProveedorEliminado(int ID);
int mostrarRegistrosBorradosProveedor();
bool bajaFisicaProveedors();
bool recuperacionLogicaProveedor();
bool recuperacionLogicaProveedorCompleta();
bool backupProveedor();
bool recuperacionFisicaProveedor();

/// hacer listados personalizados........pendiente

void ModificarProveedor() {
    Proveedor obj;
    const char Categorias[4][31]= {
        "1. fabricantes",
        "2. Mayoristas y distribuidores",
        "3. Artesanos independientes",
        "4. Importacion"
    };
    char NProve[50];
    char tel[30];
    char dir[30];
    int cat;
    int id, pos, mod, bd=0, prov;
    bool modifico;
    cout<<"  Ingresar id del Proveedor: ";
    cin>>id;
    pos=buscarIDProveedor(id);
    if(pos==-1){
        cout<<"  NO EXISTE EL PROVEEDOR CON EL ID INGRESADO"<<endl;
        return;
    }
    obj.leerDeDisco(pos);

    cout<<" 1. Nombre: "<<obj.getNombreProveedor()<<endl;
    cout<<" 2. Telefono: "<<obj.getTelefono()<<endl;
    cout<<" 3. Direccion: "<<obj.getDireccion()<<endl;
    cout<<" 4. Categoria: "<<Categorias[obj.getCategoria()-1]<<endl;
    cout<<" 5. Provincia: "<<obj.getProvincia()<<endl;

    cout<<" Que item desea modificar?: ";
    cin>>mod;

    switch(mod) {
    case 1:
        cout<<"Nombre de Proveedor: ";
        cargarCadena(NProve,49);
        obj.setNombreProveedor(NProve);
        modifico= sobreEscribirRegistroProveedor(obj, pos);

        if(modifico==true) cout<<"Modificacion exitosa"<<endl;
        else cout<<"Modificacion fallida"<<endl;

        break;
    case 2:
        cout<<"Telefono: ";
        cargarCadena(tel,29);
        obj.setTelefono(tel);
        modifico= sobreEscribirRegistroProveedor(obj, pos);

        if(modifico==true) cout<<"Modificacion exitosa"<<endl;
        else cout<<"Modificacion fallida"<<endl;

        break;
    case 3:
        cout<<"Direccion: ";
        cargarCadena(dir,29);
        obj.setDireccion(dir);
        modifico= sobreEscribirRegistroProveedor(obj, pos);

        if(modifico==true) cout<<"Modificacion exitosa"<<endl;
        else cout<<"Modificacion fallida"<<endl;

        break;
    case 4:
        bd=0;
        cout<<"Categorias\n";
        for(int i=0; i<4; i++) {
            cout<<Categorias[i]<<endl;
        }
        do {
            if(bd==1) {
                cout<<"ERROR! no esta en la lista\n";
            }
            cout<<"Seleccione una opcion: ";
            cin>>cat;
            bd=1;
        } while(obj.setCategoria(cat)==false);
        obj.setCategoria(cat);
        modifico= sobreEscribirRegistroProveedor(obj, pos);

        if(modifico==true) cout<<"Modificacion exitosa"<<endl;
        else cout<<"Modificacion fallida"<<endl;

        break;
    case 5:
        bd=0;
        do {
            if(bd==1) {
                cout<<"ERROR! ingrese un numero valido\n";
            }
            cout<<"Numero de Provincia: ";
            cin>>prov;
            bd=1;
        } while(obj.setProvincia(prov)==false);
        obj.setProvincia(prov);
        modifico= sobreEscribirRegistroProveedor(obj, pos);

        if(modifico==true) cout<<"Modificacion exitosa"<<endl;
        else cout<<"Modificacion fallida"<<endl;

        break;


    }

}

bool cargarProveedor() {
    bool cargo;
    Proveedor _Proveedor;
    _Proveedor.Cargar();
    cargo= _Proveedor.grabarEnDisco();
    return cargo;
}


bool sobreEscribirRegistroProveedor(Proveedor obj, int pos) {
    FILE *p;
    p=fopen(ARCHIVO_PROVEEDOR, "rb+");
    if(p==NULL)return false;
    fseek(p, sizeof obj*pos, 0);
    bool escribio=fwrite(&obj, sizeof (Proveedor), 1, p);
    fclose(p);
    return escribio;
}

bool eliminarLogicoRegistroProveedor() {
    Proveedor obj;
    int ID, pos;
    cout<<"INGRESE EL ID DEL PROVEEDOR A ELIMINAR: ";
    cin>>ID;
    pos=buscarIDProveedor(ID);
    if(pos==-1) {
        cout<<"NO EXISTE EL ID EN EL ARCHIVO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(false);
    if(sobreEscribirRegistroProveedor(obj, pos)) {
        return true;
    }
    return false;

}

int contarRegistrosProveedor() {
    int cantidad;
    FILE *f;
    Proveedor obj;
    f=fopen(ARCHIVO_PROVEEDOR,"rb");
    if (f==NULL) {
        fclose(f);
        return 0;
    }
    fseek(f, 0, SEEK_END);
    cantidad= ftell(f)/sizeof obj;

    fclose(f);
    return cantidad;
}

int contarRegistrosProveedorSinEliminar() {
    int cantidad=0;
    FILE *f;
    Proveedor obj;
    f=fopen(ARCHIVO_PROVEEDOR,"rb");
    if (f==NULL) {
        fclose(f);
        return -1;
    }
    //fseek(f, 0, SEEK_END);
    //cantidad= ftell(f)/sizeof obj;
    while(fread(&obj,sizeof obj, 1, f)==1) {
        if(obj.getEstado()==true) {
            cantidad++;

        }
    }

    fclose(f);
    return cantidad;
}

int buscarIDProveedor(int ID) {
    Proveedor obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_PROVEEDOR,"rb");
    if(pAlu==NULL) {
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1) {
        if(obj.getIDProveedor()==ID&&obj.getEstado()==true) {
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}


int buscarCategoriaProveedor(int cat) {
    Proveedor obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_PROVEEDOR,"rb");
    if(pAlu==NULL) {
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1) {
        if(obj.getCategoria()== cat && obj.getEstado()==true) {
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int buscarIDProveedorEliminado(int ID) {
    Proveedor obj;
    FILE *pAlu;
    int pos=0;
    pAlu=fopen(ARCHIVO_PROVEEDOR,"rb");
    if(pAlu==NULL) {
        return -1;
    }
    while(fread(&obj,sizeof obj, 1, pAlu)==1) {
        if(obj.getIDProveedor()==ID&&obj.getEstado()==false) {
            fclose(pAlu);
            return pos;
        }
        pos++;
    }
    fclose(pAlu);
    return -1;
}

int mostrarRegistrosBorradosProveedor() {
    Proveedor Proveedor;
    int  i=0,j=0;

    while(Proveedor.leerDeDisco(i)) {
        if(Proveedor.getEstado()==false) {
            Proveedor.setEstado(true);
            Proveedor.Mostrar();
            Proveedor.setEstado(false);
            j++;
        }

        i++;
    }
    if(i==0) {
        cout<<"No hay Archivo"<<endl;
        return -1;
    }
    i=0;

    if(j==0) {
        cout<<"PAPELERA VACIA"<<endl;
        return -1;
    }
    return j;

}

bool bajaFisicaProveedors() {
    Proveedor reg;
    int pos=0;
    FILE *p, *pNuevo;
    cout<<"LOS SIGUIENTES REGISTROS SERAN ELIMINADOS DE MANERA DEFINITIVA"<<endl;
    int ret= mostrarRegistrosBorradosProveedor();
    if(ret==-1)return false;

    cout<<"DESEA CONTINUAR? (S/N): ";
    char respuesta;
    cin>>respuesta;
    if(respuesta=='N' || respuesta=='n')return false;
    p=fopen(ARCHIVO_PROVEEDOR_BACKUP, "wb");
    while(reg.leerDeDisco(pos++)) {
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    pNuevo=fopen(ARCHIVO_PROVEEDOR, "wb");
    if(pNuevo==NULL)return false;

    p=fopen(ARCHIVO_PROVEEDOR_BACKUP, "rb");
    if(p==NULL) {
        fclose(pNuevo);
        return false;
    }
    while(fread(&reg,sizeof reg,1,p)==1) {
        if(reg.getEstado()==true) {
            fwrite(&reg, sizeof reg,1, pNuevo);
        } else {
            cout<<"Proveedor ["<<reg.getIDProveedor()<<"] "<<"BORRADO"<<endl;
        }
    }
    fclose(p);
    fclose(pNuevo);
    return true;
}

bool recuperacionLogicaProveedor() {
    Proveedor obj;
    int ID, pos;
    int ret= mostrarRegistrosBorradosProveedor();
    if(ret==-1)return false;
    cout<<"Ingresar id de Proveedor a recuperar: ";
    cin>>ID;
    pos=buscarIDProveedorEliminado(ID);
    if(pos==-1) {
        cout<<"NO EXISTE EL ID EN EL ARCHIVO O NO FUE ELIMINADO"<<endl;
        return false;
    }
    obj.leerDeDisco(pos);;
    obj.setEstado(true);
    if(sobreEscribirRegistroProveedor(obj, pos)) {
        return true;
    }
    return false;
}

bool recuperacionLogicaProveedorCompleta(){
    Proveedor obj;
    int pos=0;
    bool sob;
    while(obj.leerDeDisco(pos)==true){
        obj.setEstado(true);
        sob= sobreEscribirRegistroProveedor(obj, pos);
        if(sob==true) cout<<"PROVEEDOR ["<<obj.getIDProveedor()<<"] "<<"RESTAURADO EXITOSAMENTE"<<endl;
        pos++;

    }
    return true;

}

bool backupProveedor() {
    Proveedor reg;

    int pos=0;
    FILE *p,*a;
    a=fopen(ARCHIVO_PROVEEDOR, "rb");
    if(a==NULL) {
        cout<<"  NO HAY PROVEEDORES CARGADOS!" <<endl;
        return false;
    }
    p=fopen(ARCHIVO_PROVEEDOR_BACKUP, "wb");
    if(p==NULL) {
        return false;
    }
    while(reg.leerDeDisco(pos++)) {
        fwrite(&reg, sizeof reg,1, p);
    }
    fclose(p);
    fclose(a);
    return true;
}

bool recuperacionFisicaProveedor() {

    Proveedor reg;
    FILE *p, *pNuevo;
    p=fopen(ARCHIVO_PROVEEDOR_BACKUP, "rb");
    if(p==NULL) {
        fclose(p);
        return false;
    }
    pNuevo=fopen(ARCHIVO_PROVEEDOR, "wb");
    if(pNuevo==NULL){
        fclose(pNuevo);
        return false;

    }

    while(fread(&reg,sizeof reg,1,p)==1) {

        fwrite(&reg, sizeof reg,1, pNuevo);
        cout<<"PROVEEDOR ["<<reg.getIDProveedor()<<"] "<<"RESTAURADO EXITOSAMENTE"<<endl;

    }
    fclose(p);
    fclose(pNuevo);
    return true;
}



#endif // FUNCIONESPROVEEDOR_H_INCLUDED
