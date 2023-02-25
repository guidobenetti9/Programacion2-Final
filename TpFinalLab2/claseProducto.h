#ifndef CLASEPRODUCTO_H_INCLUDED
#define CLASEPRODUCTO_H_INCLUDED

class Producto {
    private:
        int IdProducto; ///autonumerico
        int IdProveedor;
        float PrecioUnitario;
        int Stock;
        char Descripcion[25]; ///queso, yogurt, leche, etc
        int Categoria;///Lacteos
        bool Estado;
    public:
        Producto(int IdProducto=1, int IdProveedor=1, float PrecioUnitario=1, int Stock=1, const char* Descripcion="-", int Categoria=1, bool Estado=true) {
            this->IdProducto=IdProducto;
            this->IdProveedor=IdProveedor;
            this->PrecioUnitario=PrecioUnitario;
            this->Stock=Stock;
            strcpy(this->Descripcion,Descripcion);
            this->Categoria=Categoria;
            this->Estado=Estado;
        }
        bool setIdProveedor(int ip) {
            if(buscarIDProveedor(ip)!=-1) {
                IdProveedor=ip;
                return true;
            }
            return false;
        }
        int getIdProveedor() {
            return IdProveedor;
        }
        void setEstado(bool id) {
            Estado=id;
        }
        bool getEstado() {
            return Estado;
        }
        void setIdProducto(int id) {
            IdProducto=id;
        }
        void setDescripcion(const char* d) {
            strcpy(Descripcion,d);
        }
        bool setCategoria(int c) {
            if(c>=1 && c<=10) {
                Categoria=c;
                return true;
            }
            return false;
        }
        bool setPrecioUnitario(float PU) {
            if(PU>0) {
                PrecioUnitario= PU;
                return true;
            }
            return false;
        }
        bool setStock(int st) {
            if(st>0) {
                Stock= st;
                return true;
            }
            return false;
        }

        int getIDProducto() {
            return IdProducto;
        }
        float getPrecioUnitario() {
            return PrecioUnitario;
        }
        int getStock() {
            return Stock;
        }
        const char* getDescripcion() {
            return Descripcion;
        }
        int getCategoria() {
            return Categoria;
        }

        bool grabarEnDisco();
        bool leerDeDisco(int pos);
        void Cargar();
        void Mostrar();

};

void Producto::Cargar() {
    int bd=0;
    float PUnit;
    int St;
    char Desc[25];
    int Cat;
    int IdProv;
    const char categorias[10][16]= {
        "Lacteos",
        "Bebibas",
        "Galletitas",
        "Limpieza",
        "Cereales",
        "Enlatados",
        "Pastas",
        "Postres",
        "Carnes",
        "Verduras/Frutas"
    };

    cout<<"--Categorias--"<<endl;
    for(int i=0; i<10; i++) {
        if(i==9)cout<<"  "<<i+1<<". "<<categorias[i]<<endl;
        else cout<<"  "<<i+1<<".  "<<categorias[i]<<endl;
    }
    do {
        if(bd==1) {
            cout<<"  Debe ser una Categoria de la lista!\n";
        }
        cout<<"  Categoria: ";
        cin>>Cat;
        bd=1;
    } while(setCategoria(Cat)==false);
    setCategoria(Cat);
    bd=0;

    cout<<"  Descripcion: ";
    cargarCadena(Desc, 24);
    setDescripcion(Desc);

    do {
        if(bd==1) {
            cout<<"  Debe ser un id que exista!\n";
        }
        cout<<"  Id Proveedor: ";
        cin>>IdProv;
        bd=1;
    } while(setIdProveedor(IdProv)==false);
    setIdProveedor(IdProv);
    bd=0;

    do {
        if(bd==1) {
            cout<<"  Debe ser un Stock positivo!\n";
        }
        cout<<"  Stock: ";
        cin>>St;
        bd=1;
    } while(setStock(St)==false);
    setStock(St);
    bd=0;

    do {
        if(bd==1) {
            cout<<"  Debe ser un precio positivo!\n";
        }
        cout<<"  Precio Unitario: $";
        cin>>PUnit;
        bd=1;
    } while(setPrecioUnitario(PUnit)==false);
    setPrecioUnitario(PUnit);
    bd=0;



}
void Producto::Mostrar() {
    if(getEstado()==true) {
        for(int i=0; i<61; i++) {
            cout<<char(205);
        }
        const char categorias[10][17]= {
            "Lacteos",
            "Bebibas",
            "Galletitas",
            "Limpieza",
            "Cereales",
            "Enlatados",
            "Pastas",
            "Postres",
            "Carnes",
            "Verduras/Frutas"
        };

        cout<<endl;
        cout<<"  ID Producto: ["<<getIDProducto()<<"]"<<endl;
        cout<<"  ID Proveedor: ["<<getIdProveedor()<<"]"<<endl;
        cout<<"  Descripcion: "<<getDescripcion()<<endl;
        cout<<"  Categoria: "<<categorias[getCategoria()-1]<<endl;
        cout<<"  Stock: "<<getStock()<<endl;
        cout<<"  Precio Unitario: $"<<getPrecioUnitario()<<endl;
        cout<<endl;
        for(int i=0; i<61; i++) {
            cout<<char(205);
        }
        cout<<endl;
        cout<<endl;
    }


}

bool Producto::leerDeDisco(int pos) {
    FILE *p;
    p=fopen(ARCHIVO_PRODUCTOS, "rb");
    if(p==NULL) return false;
    fseek(p, sizeof *this*pos,0);
    bool leyo=fread(this, sizeof *this,1, p);
    fclose(p);
    return leyo;
}


bool Producto::grabarEnDisco() {
    FILE *p;
    p=fopen(ARCHIVO_PRODUCTOS,"ab");
    if(p==NULL) {
        return false;
    }
    bool grabo=fwrite(this, sizeof *this,1, p);
    fclose(p);
    return grabo;
}


#endif // CLASEPRODUCTO_H_INCLUDED
