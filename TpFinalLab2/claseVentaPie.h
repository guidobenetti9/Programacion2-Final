#ifndef CLASEVENTAPIE_H_INCLUDED
#define CLASEVENTAPIE_H_INCLUDED


class VentaPie {
    private:
        int Id; ///autonumerico Consecutivo
        int IdVentaCabecera;///a partir de aca accedemos tambien a venta detalle
        float Descuento;
        float Subtotal;
        float Vuelto;
        float ImportePagado;
        int FormaDePago;///de 1 a 3
        bool Estado;
    public:
        VentaPie(int Id=1, int IdVentaCabecera=1, float Descuento=1.0,float Subtotal=1.0,float Vuelto=0.0,float ImportePagado=0.0, int FormaDePago=1, bool Estado=true) {
            this->Id=Id;
            this->IdVentaCabecera=IdVentaCabecera;
            this->Descuento=Descuento;
            this->Vuelto=Vuelto;
            this->Estado=Estado;
            this->ImportePagado=ImportePagado;
            this->FormaDePago=FormaDePago;
            this->Subtotal=Subtotal;

        }
        ///SETS
        void setIDVentaPie(int id) {
            Id=id;
        };
        void setDescuento( float desc) {
            Descuento= desc;
        }

        bool setIdVentaCabecera(int Ida) {
            if(Ida > 0 && buscarIDVentaCabecera(Ida)!=-1) { ///se verifica que existe
                IdVentaCabecera=Ida;
                return true;
            }
            return false;
        }

        void setSubtotal(float ImT) {

            Subtotal= ImT;

        }

        void setEstado(bool e) {
            Estado= e;
        }
        bool setVuelto( float aux ) {
            if(aux>0.0) {
                Vuelto=aux;
                return true;
            }
            return false;
        }
        bool setImportePagado( float aux ) {
            if(aux>0.0) {
                ImportePagado=aux;
                return true;
            }
            return false;
        }
        bool setFormaDePago( int aux ) {
            if(aux>0) {
                FormaDePago=aux;
                return true;
            }
            return false;
        }

        ///GETS
        int getIDVentaPie() {
            return Id;
        };
        float getDescuento() {
            return Descuento;
        }
        int getIdVentaCabecera() {
            return IdVentaCabecera;
        }
        float getSubtotal() {
            return Subtotal;
        }
        bool getEstado() {
            return Estado;
        }
        float getVuelto() {
            return Vuelto;
        }
        float getImportePagado() {
            return ImportePagado;
        }
        int getFormaDePago() {
            return FormaDePago;
        }
        int Cargar();
        bool Mostrar();
        ///metodos Archivo
        bool leerDeDisco(int pos);
        bool grabarEnDisco();
};


bool VentaPie::leerDeDisco(int pos) {
    FILE *p;
    p=fopen(ARCHIVO_VENTA_PIE,"rb");
    if(p==NULL) {
        return false;
    }
    fseek(p,pos*sizeof (VentaPie),0);
    bool leyo=fread(this, sizeof (VentaPie), 1,p);
    fclose(p);
    return leyo;
}


bool VentaPie::grabarEnDisco() {
    FILE *p;
    p=fopen(ARCHIVO_VENTA_PIE,"ab");
    if(p==NULL) {
        return false;
    }
    bool escribio=fwrite(this, sizeof (VentaPie), 1,p);
    fclose(p);
    return escribio;
}


int VentaPie::Cargar() {
    int fPago, bd=0;
    float precioFinal=0.0, vue=0.0;
    ///PRIMERO MUESTRO EL SUBTOTAL
    do {
        if(bd==1) cout<<"  OPCION INCORRECTA!"<<endl;
        cout<<"  FORMA DE PAGO"<<endl;
        cout<<"  1. DEBITO (15% DE DESCUENTO)"<<endl;
        cout<<"  2. CREDITO (10% DE DESCUENTO)"<<endl;
        cout<<"  3. EFECTIVO (NO HAY DESCUENTO)"<<endl;
        cout<<"  INGRESAR OPCION: ";
        cin>>fPago;
        bd=1;
    } while(fPago > 3 || fPago < 1);
    setFormaDePago(fPago);
    if(fPago == 1) {
        setDescuento(0.85);
    }
    if(fPago == 2) {
        setDescuento(0.90);

    }
    if(fPago == 3) {
        setDescuento(1);
    }

    if(fPago==1 || fPago==2){
        precioFinal= getSubtotal() * getDescuento();
        cout<<"  DEBE PAGAR: $"<<precioFinal<<endl;
        setImportePagado(precioFinal);
        setVuelto(0);
        setEstado(true);
        return precioFinal;

    }

    precioFinal= getSubtotal() * getDescuento();
    bd=0;
    cout<<"  DEBE PAGAR: $"<<precioFinal<<endl;
    float ImpPagar;
    do {
        if(bd==1) cout<<"  EL IMPORTE NO PUEDE SER NEGATIVO Y DEBE SER MAYOR AL IMPORTE A PAGAR!"<<endl;
        cout<<"  INGRESE CON CUANTO DINERO VA A PAGAR: $";
        cin>>ImpPagar;
        bd=1;
    } while( ImpPagar < precioFinal );
    setImportePagado(ImpPagar);
    vue= ImpPagar - precioFinal;
    setVuelto(vue);
    cout<<"  SU VUELTO: $"<<getVuelto()<<endl;
    setEstado(true);
    return precioFinal;
}

bool VentaPie::Mostrar() {
    if(getEstado()==true) {
        cout<<endl<<"  ";
        for(int i=0; i<62; i++) {
            cout<<char(250);
        }
        ///PRIMERO MUESTRO EL SUBTOTAL
        ///despues cargo y ahi muestro el importe total de la sumatoria de venta detalle
        cout<<"\n                      SUBTOTAL SIN DESCUENTO: $"<<getSubtotal();

        cout<<endl<<"  ";
        for(int i=0; i<62; i++) {
            cout<<char(250);
        }
        cout<<"\n  FORMA DE PAGO: ";
        if(getFormaDePago()==1) {
            cout<<"DEBITO"<<endl;
            cout<<"  DESCUENTO %15  ";
        }
        if(getFormaDePago()==2) {
            cout<<"CREDITO"<<endl;
            cout<<"  DESCUENTO %10  ";
        }
        if(getFormaDePago()==3) {
            cout<<"EFECTIVO"<<endl;
            cout<<"  DESCUENTO %0  ";
        }
        float precioFinal;
        precioFinal= getSubtotal() * getDescuento();
        cout<<endl<<"  ";
        for(int i=0; i<62; i++) {
            cout<<char(205);
        }
        cout<<"\n                             TOTAL: $"<< precioFinal <<endl<<"  ";
        for(int i=0; i<62; i++) {
            cout<<char(205);
        }
        cout<<"\n  IMPORTE PAGADO: $"<<getImportePagado()<<endl;
        cout<<"  VUELTO: $"<<getVuelto()<<endl;

        return true;
    }
    return false;


}



#endif // CLASEVENTAPIE_H_INCLUDED
