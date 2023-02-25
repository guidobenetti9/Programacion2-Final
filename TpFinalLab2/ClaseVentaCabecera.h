#ifndef CLASEVENTACABECERA_H_INCLUDED
#define CLASEVENTACABECERA_H_INCLUDED

class VentaCabecera {
    private:
        int Id; ///autonumerico Consecutivo
        int IdVendedor;/// lo mismo pero para vendedor
        float ImporteTotal;
        Fecha FechaDeCompra;
        bool Estado;
    public:
        VentaCabecera(int Id=1, int IdVendedor=1,float ImporteTotal=0.0,bool Estado=true, int diaCompra=diaActual, int mesCompra=mesActual, int anioCompra=anioActual) {
            this->Id=Id;
            this->IdVendedor=IdVendedor;
            this->ImporteTotal=ImporteTotal;
            this->Estado=Estado;
            FechaDeCompra.setDia(diaCompra);
            FechaDeCompra.setMes(mesCompra);
            FechaDeCompra.setAnio(anioCompra);

        }
        ///SETS
        void setIDVentaCabecera(int id) {Id=id;};

        bool setIdVendedor(int Id) {
            if(Id > 0 && buscarIDVendedor(Id)!=-1){///se verifica que existe el vendedor
                IdVendedor=Id;
                return true;
            }
            return false;
        }

        bool setImporteTotal(float ImT) {
            if(ImT > 0 ){///se verifica que existe el vendedor
                ImporteTotal= ImT;
                return true;
            }
            return false;
        }

        void setEstado(bool e) {Estado= e;}
        void setFechaDeCompra( Fecha aux ) {FechaDeCompra=aux;}

        ///GETS

        Fecha getFechaDeCompra() {return FechaDeCompra;}
        int getIDVentaCabecera() {return Id;}
        int getIdVendedor() {return IdVendedor;}
        float getImporteTotal(){return ImporteTotal;}
        bool getEstado() {return Estado;}

        bool Cargar();
        bool Mostrar();
        ///metodos Archivo
        bool leerDeDisco(int pos);
        bool grabarEnDisco();


};

bool VentaCabecera::leerDeDisco(int pos) {
    FILE *p;
    p=fopen(ARCHIVO_VENTA_CABECERA,"rb");
    if(p==NULL) {
        return false;
    }
    fseek(p,pos*sizeof (VentaCabecera),0);
    bool leyo=fread(this, sizeof (VentaCabecera), 1,p);
    fclose(p);
    return leyo;
}


bool VentaCabecera::grabarEnDisco() {
    FILE *p;
    p=fopen(ARCHIVO_VENTA_CABECERA,"ab");
    if(p==NULL) {
        return false;
    }
    bool escribio=fwrite(this, sizeof (VentaCabecera), 1,p);
    fclose(p);
    return escribio;
}


bool VentaCabecera::Cargar() {

    int bd, idv;
    bool e=true,cargo;

    bd=0;

    do {
        if(bd==1) {
            cout<<"  ID invalido! ingresar de nuevo"<<endl;
        }
        cout<<"  ID del vendedor: ";
        cin>>idv;
        cargo=setIdVendedor(idv);
        bd=1;
    } while(cargo==false);
    bd=0;



    do {
        if(bd==1) {
            cout<<"  Fecha Invalida! ingresar de nuevo"<<endl;
        }
        cout<<"  Fecha de Compra"<<endl;
        cargo=FechaDeCompra.Cargar();
        bd=1;
    } while(cargo==false);
    bd=0;

    setEstado(e);
    return true;

}

bool VentaCabecera::Mostrar() {
    if(getEstado()==true) {
        cout<<endl;
        cout<<"  ";
        for(int i=0;i<65;i++){
            cout<<char(220);
        }

        cout<<endl;
        cout<<"  "<<char(219)<<"                      SuperMercado-PAGUI                       "<<char(219)<<endl;
        cout<<"  ";
        for(int i=0;i<65;i++){
            cout<<char(223);
        }
        cout<<endl;
        cout<<"   ID Venta: "<<getIDVentaCabecera()<<"                          ";
        FechaDeCompra.Mostrar();
        cout<<endl;
        cout<<"   ID Vendedor: ["<<getIdVendedor()<<"]                   ";
        cout<<"   Importe Total: $"<<getImporteTotal()<<endl;
        cout<<"   ";
        for(int i=0;i<63;i++){
            cout<<char(250);
        }
        cout<<endl;
        return true;
    }
    return false;


}


#endif // CLASEVENTACABECERA_H_INCLUDED
