#ifndef CLASEVENTADETALLE_H_INCLUDED
#define CLASEVENTADETALLE_H_INCLUDED


class VentaDetalle {
    private:
        int id;///autonumerico
        int idVenta;/// para asociar con la cabecera lo ingresa el usuario
        int IdProducto;/// lo mismo pero para producto para acceder al precio
        float Importe;
        int Cantidad;
        bool Estado;

    public:
        VentaDetalle( int idVenta=1,int id=1,int IdProducto=1,int Cantidad=1, bool Estado=true) {
            this->id=id;
            this->idVenta=idVenta;
            this->IdProducto=IdProducto;
            this->Cantidad=Cantidad;
            this->Estado=Estado;
        }
        ///SETS
        void setIdVentaDetalle(int i){id=i;}
        int getIdVentaDetalle(){return id;}
        bool setImporte(float imp){
            if(imp>=
               0.0){
                Importe=imp;
                return true;
            }
            return false;
        }
        float getImporte(){return Importe;}
        void setidVenta(int id) { idVenta=id; }

        bool setIdProducto(int Id) {
            if( buscarIDProducto(Id)!=-1 ){
                IdProducto=Id;
                return true;
            }
            return false;
        }

        bool setCantidad(int ca) {
            if(ca > 0 ){
                Cantidad= ca;
                return true;
            }
            return false;
        }

        void setEstado(bool e) {Estado= e;}

        ///GETS

        int getIDVentaDetalle() {return id;}
        int getIdProducto() {return IdProducto;}
        int getidVenta() {return idVenta;}
        int getCantidad(){return Cantidad;}
        bool getEstado() {return Estado;}

        int Cargar();
        bool Mostrar();
        ///metodos Archivo
        bool leerDeDisco(int pos);
        bool grabarEnDisco();


};


bool VentaDetalle::leerDeDisco(int pos) {
    FILE *p;
    p=fopen(ARCHIVO_VENTA_DETALLE,"rb");
    if(p==NULL) {
        return false;
    }
    fseek(p,pos*sizeof (VentaDetalle),0);
    bool leyo=fread(this, sizeof (VentaDetalle), 1,p);
    fclose(p);
    return leyo;
}


bool VentaDetalle::grabarEnDisco() {
    FILE *p;
    p=fopen(ARCHIVO_VENTA_DETALLE,"ab");
    if(p==NULL) {
        return false;
    }
    bool escribio=fwrite(this, sizeof (VentaDetalle), 1,p);
    fclose(p);
    return escribio;
}


int VentaDetalle::Cargar() {


    int bd, idv, ca;
    bool e=true,cargo;

    bd=0;

    do {
        if(bd==1) {
            cout<<"  ID invalido! ingresar de nuevo"<<endl;
        }
        cout<<"  ID del Producto (debe ser mayor a 0): "<<endl;;
        cout<<"  0. para finalizar compra "<<endl;
        cout<<"  ";cin>>idv;


        if(idv==0) return 2;

        cargo=setIdProducto(idv);
        bd=1;
    } while(cargo==false);
    bd=0;

    do {
        if(bd==1) {
            cout<<"  cantidad Invalida! ingresar de nuevo"<<endl;
        }

        cout<<"  Cantidad: ";
        cin>>ca;
        cargo=setCantidad(ca);
        bd=1;
    } while(cargo==false);
    bd=0;

    setEstado(e);
    return 1;

}

bool VentaDetalle::Mostrar() {
    if(getEstado()==true){
        cout<<endl;
        cout<<"   ID Compra: ["<<getIdVentaDetalle()<<"]"<<endl;
        cout<<"   ID Producto: ["<<getIdProducto()<<"]"<<endl;
        cout<<"   $"<<getImporte()<<" ......................................... "<<getCantidad()<<"u x $";

        return true;
    }
    return false;


}

#endif // CLASEVENTADETALLE_H_INCLUDED
