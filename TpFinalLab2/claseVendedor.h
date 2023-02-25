#ifndef CLASEVENDEDOR_H_INCLUDED
#define CLASEVENDEDOR_H_INCLUDED


class Vendedor {
    private:
        int IDVendedor;///autonumerico consecutivo
        char NombreVendedor[40];
        char ApellidoVendedor[40];
        char Nacionalidad[10];
        int Categoria;
        Fecha fechaDeNacimiento;
        Fecha fechaDeIngreso;
        bool estado;
    public:
        Vendedor(int idi=1, const char* ni="sin definir", const char* ai="sin definir",bool e=true,const char* na="Argentina", int ti=1, int diaNacimiento=1, int mesNacimiento=1, int anioNacimiento=2000, int diaIngreso=diaActual, int mesIngreso=mesActual, int anioIngreso=anioActual) {

            IDVendedor=idi;
            strcpy(NombreVendedor, ni);
            strcpy(ApellidoVendedor, ai);
            estado= e;
            strcpy(Nacionalidad, na);
            Categoria=ti;

            fechaDeIngreso.setDia(diaIngreso);
            fechaDeIngreso.setMes(mesIngreso);
            fechaDeIngreso.setAnio(anioIngreso);
            fechaDeNacimiento.setDia(diaNacimiento);
            fechaDeNacimiento.setMes(mesNacimiento);
            fechaDeNacimiento.setAnio(anioNacimiento);

        }

        void setIDVendedor(int id) {
            IDVendedor=id;
        };

        void setNombreVendedor(const char* ni) {
            strcpy(NombreVendedor,ni);
        }
        void setApellidoVendedor(const char* na) {
            strcpy(ApellidoVendedor,na);
        }

        bool setEstado(bool e) {
            if(e==true) {
                estado=true;
                return true;
            }
            estado=false;
            return false;
        }
        bool setNacionalidad(const char* na) {
            const char paises[6][10]= {
                "Argentina",
                "Bolivia",
                "Brasil",
                "Paraguay",
                "Uruguay",
                "Venezuela"
            };

            for(int i=0; i<10; i++) {
                if(strcmp(na, paises[i])==0) {
                    strcpy(Nacionalidad, na);
                    return true;
                }
            }
            return false;
        }

        bool setCategoria(int ti) {
            if(ti<0||ti>5) {
                return false;
            } else {
                Categoria=ti;
                return true;
            }
        }

        void setfechaDeIngreso( Fecha aux ) {
            fechaDeIngreso=aux;
        }
        void setfechaDeNacimiento( Fecha aux ) {
            fechaDeNacimiento=aux;
        }

        Fecha getfechaDeIngreso() {
            return fechaDeIngreso;   ///a traves de este get accedemos a los metodos del objeto fechaDeIngreso
        }
        Fecha getfechaDeNacimiento() {
            return fechaDeNacimiento;
        }
        int getIDVendedor() {
            return IDVendedor;
        }
        const char* getNombreVendedor() {
            return NombreVendedor;
        }
        const char* getApellidoVendedor() {
            return ApellidoVendedor;
        }
        bool getEstado() {
            return estado;
        }
        const char* getNacionalidad() {
            return Nacionalidad;
        }

        int getCategoria() {
            return Categoria;
        }

        bool Cargar();
        bool Mostrar();
        ///metodos Archivo
        bool leerDeDisco(int pos);
        bool grabarEnDisco();

        Vendedor& operator=(Vendedor &);


};

Vendedor &Vendedor::operator=(Vendedor &Ven) {
    if(this != &Ven) {
        IDVendedor=Ven.getIDVendedor();
        strcpy(NombreVendedor, Ven.getNombreVendedor());
        strcpy(ApellidoVendedor, Ven.getApellidoVendedor());
        estado= Ven.getEstado();
        strcpy(Nacionalidad, Ven.getNacionalidad());
        Categoria=Ven.getCategoria();

        fechaDeIngreso.setDia(Ven.getfechaDeIngreso().getDia());
        fechaDeIngreso.setMes(Ven.getfechaDeIngreso().getMes());
        fechaDeIngreso.setAnio(Ven.getfechaDeIngreso().getAnio());
        fechaDeNacimiento.setDia(Ven.getfechaDeNacimiento().getDia());
        fechaDeNacimiento.setMes(Ven.getfechaDeNacimiento().getMes());
        fechaDeNacimiento.setAnio(Ven.getfechaDeNacimiento().getAnio());
    }

    return *this;
}

bool Vendedor::leerDeDisco(int pos) {
    FILE *p;
    p=fopen(ARCHIVO_VENDEDORES,"rb");
    if(p==NULL) {
        return false;
    }
    fseek(p,pos*sizeof (Vendedor),0);
    bool leyo=fread(this, sizeof (Vendedor), 1,p);
    fclose(p);
    return leyo;
}


bool Vendedor::grabarEnDisco() {
    FILE *p;
    p=fopen(ARCHIVO_VENDEDORES,"ab");
    if(p==NULL) {
        return false;
    }
    bool escribio=fwrite(this, sizeof (Vendedor), 1,p);
    fclose(p);
    return escribio;
}


bool Vendedor::Cargar() {

    char NVendedor[40];
    char AVendedor[40], nacion[10];
    int  tii;

    int bd;
    bool e=true, cargo;

    cout<<endl;
    cout<<"  Nombre de Vendedor => ";
    cargarCadena(NVendedor,39);
    setNombreVendedor(NVendedor);
    cout<<"  Apellido de Vendedor => ";
    cargarCadena(AVendedor,39);
    setApellidoVendedor(AVendedor);
    bd=0;
    do {
        if(bd==1) {
            cout<<"  El pais debe ser del MERCOSUR, ingresar de nuevo"<<endl;

        }
        cout<<"  Pais de Origen => ";
        cargarCadena(nacion, 9);
        setNacionalidad(nacion);
        bd=1;
    } while(setNacionalidad(nacion)==false);
    setNacionalidad(nacion);
    bd=0;

    do {
        if(bd==1) {
            cout<<"  Categoria incorrecta! ingresar de nuevo"<<endl;
        }
        cout<<"  Categoria (de 1 a 5)=> ";
        cin>>tii;
        bd=1;
    } while(setCategoria(tii)==false);
    setCategoria(tii);
    bd=0;

    do {
        if(bd==1) {
            cout<<"  Fecha Invalida! ingresar de nuevo"<<endl;
        }
        cout<<"  Fecha de ingreso"<<endl;
        cargo=fechaDeIngreso.Cargar();
        bd=1;
    } while(cargo==false);
    bd=0;

    do {
        if(bd==1) {
            cout<<"  Fecha Invalida! ingresar de nuevo"<<endl;
        }
        cout<<"  Fecha de Nacimiento"<<endl;
        cargo=fechaDeNacimiento.Cargar();
        if(fechaDeNacimiento.getAnio() > fechaDeIngreso.getAnio()){
            cargo= false;

        }
        if(fechaDeNacimiento.getAnio() > (anioActual-18) ) {
            cargo= false;
        }
        if(fechaDeNacimiento.getAnio() > (fechaDeIngreso.getAnio()-18) ) {
            cargo= false;
        }
        bd=1;
    } while(cargo==false);
    bd=0;
    setEstado(e);
    return true;

}

bool Vendedor::Mostrar() {
    if(getEstado()==true) {
        for(int i=0; i<61; i++) {
            cout<<char(205);
        }
        cout<<endl;
        cout<<"   ID de Vendedor................. "<<getIDVendedor();
        cout<<endl;
        cout<<"   Nombre Completo de Vendedor.... ";
        mostrarCadena(getNombreVendedor());
        cout<<" ";
        mostrarCadena(getApellidoVendedor());
        cout<<endl;
        cout<<"   Nacionalidad................... ";
        cout<<getNacionalidad();
        cout<<endl;
        cout<<"   Tipo de Vendedor............... ";
        cout<<getCategoria();
        cout<<endl;
        cout<<"   Fecha de nacimiento............ ";
        fechaDeNacimiento.Mostrar();
        cout<<endl;
        cout<<"   Fecha de ingreso............... ";
        fechaDeIngreso.Mostrar();
        cout<<endl;
        for(int i=0; i<61; i++) {
            cout<<char(205);
        }

        cout<<endl;
        cout<<endl;
        return true;
    }
    return false;


}

#endif // CLASEVENDEDOR_H_INCLUDED
