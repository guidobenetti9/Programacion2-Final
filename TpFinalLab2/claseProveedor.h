#ifndef CLASEPROVEEDOR_H_INCLUDED
#define CLASEPROVEEDOR_H_INCLUDED

class Proveedor {
    private:
        int IdProveedor;
        char NombreProveedor[50];
        char telefono[30];
        char direccion[30];
        int Categoria; /// de 1 a 4
        ///1. fabricantes
        ///2. Mayoristas y distribuidores
        ///3. Artesanos independientes
        ///4. Importe
        int provincia;
        bool activo;
    public:

        int getCategoria() {
            return Categoria;
        }
        int getIDProveedor() {
            return IdProveedor;
        }
        int getProvincia() {
            return provincia;
        }
        const char *getNombreProveedor() {
            return NombreProveedor;
        }
        const char *getTelefono() {
            return telefono;
        }
        const char *getDireccion() {
            return direccion;
        }
        bool getEstado() {
            return activo;
        }

        void setIdProveedor(int np) {
            IdProveedor=np;
        }
        bool setProvincia(int np) {
            if(np>0 && np<24) {
                provincia=np;
                return true;
            }
            return false;
        }

        bool setCategoria(int cat) {
            if(cat>0 && cat<5) {
                Categoria=cat;
                return true;
            }
            return false;
        }

        void setNombreProveedor(const char *n) {
            strcpy(NombreProveedor,n);
        }
        void setTelefono(const char *n) {
            strcpy(telefono,n);
        }
        void setDireccion(const char *n) {
            strcpy(direccion,n);
        }
        void setEstado(bool a) {
            activo=a;
        }


        bool leerDeDisco(int pos);
        bool grabarEnDisco();
        void Cargar();
        void Mostrar();

};

void Proveedor::Cargar() {

    char NProve[50];
    char tel[30];
    char dir[30];
    int cat; /// de 1 a 4
    const char Categorias[4][31]= {
        "1. fabricantes",
        "2. Mayoristas y distribuidores",
        "3. Artesanos independientes",
        "4. Importacion"
    };
    int prov, bd=0;

    cout<<"Nombre de Proveedor: ";
    cargarCadena(NProve,49);
    setNombreProveedor(NProve);
    cout<<"Telefono: ";
    cargarCadena(tel,29);
    setTelefono(tel);
    cout<<"Direccion: ";
    cargarCadena(dir,29);
    setDireccion(dir);
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
    } while(setCategoria(cat)==false);
    setCategoria(cat);
    bd=0;
    do {
        if(bd==1) {
            cout<<"ERROR! ingrese un numero valido\n";
        }
        cout<<"Numero de Provincia: ";
        cin>>prov;
        bd=1;
    } while(setProvincia(prov)==false);
    setProvincia(prov);
    setEstado(true);

}

void Proveedor::Mostrar() {
    const char Categorias[4][31]= {
        "fabricantes",
        "Mayoristas y distribuidores",
        "Artesanos independientes",
        "Importacion"
    };
    if(getEstado()==true) {
        for(int i=0; i<61; i++) {
            cout<<char(205);
        }
        cout<<endl;
        cout<<"  Nombre de Proveedor: "<<getNombreProveedor()<<endl;
        cout<<"  ID: "<<getIDProveedor()<<endl;
        cout<<"  Telefono: "<<getTelefono()<<endl;
        cout<<"  Direccion: "<<getDireccion()<<endl;
        cout<<"  Categoria: "<<Categorias[getCategoria()-1]<<endl;
        cout<<"  Numero de Provincia: "<<getProvincia()<<endl;
        for(int i=0; i<61; i++) {
            cout<<char(205);
        }
        cout<<endl;
        cout<<endl;

    }
}

bool Proveedor::leerDeDisco(int pos) {
    FILE *p;
    p=fopen(ARCHIVO_PROVEEDOR, "rb");
    if(p==NULL) return false;
    fseek(p, sizeof *this*pos,0);
    bool leyo=fread(this, sizeof *this,1, p);
    fclose(p);
    return leyo;
}

bool Proveedor::grabarEnDisco() {
    FILE *p;
    p=fopen(ARCHIVO_PROVEEDOR, "ab");
    if(p==NULL) return false;
    bool grabo=fwrite(this, sizeof *this,1, p);
    fclose(p);
    return grabo;
}

#endif // CLASEPROVEEDOR_H_INCLUDED
