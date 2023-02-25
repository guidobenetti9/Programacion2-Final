#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED


void menuReportes();
void mostrarBoletaMasCara();
void mostrarProductoMasCaro();
void listarxNacionalidadARG();
void MostrarBoletas(int pos);
void ordenarVendedoresxApellido();
void ordenarVendedores(Vendedor *v, int cantReg);
void mostrarVendedores(Vendedor *vec, int cantReg);
void contarCategorias();
void mostrarVectorProv(int *v, int tam);
void listarBoletaDebito(int opc);
void listarBoletaEfectivo(int opc);
void listarBoletaCredito(int opc);
void calcularVueltoNecesarioPorVendedor();
void recaudacionPorVendedor();
void cantidadDeProductosPorProveedor();

void menuReportes() {
    int opc;
    do {
        cout <<"                   MENU REPORTES"                   << endl;
        cout <<" -------------------------------------------------" << endl;
        cout <<"  1) MOSTRAR BOLETA MAS CARA " << endl;
        cout <<"  2) MOSTRAR PRODUCTO MAS CARO " << endl;
        cout <<"  3) LISTAR VENDEDORES POR NACIONALIDAD ARGENTINA " << endl;
        cout <<"  4) MOSTRAR VENDEDORES POR APELLIDO EN ORDEN ALFABETICO " << endl;
        cout <<"  5) MOSTRAR CANTIDAD DE PROVEEDORES POR CATEGORIA " << endl;
        cout <<"  6) CALCULAR VUELTO NECESARIO POR VENDEDOR (MEDIANTE EL PROMEDIO)" << endl;
        cout <<"  7) CALCULAR RECAUDACION POR VENDEDOR " << endl;
        cout <<"  8) CANTIDAD DE PRODUCTOS VARIADOS POR PROVEEDOR" << endl;
        cout <<" -------------------------------------------------" << endl;
        cout <<"  0) VOLVER AL MENU PRINCIPAL" << endl;
        cout <<"   INGRESAR OPCION: ";
        cin >> opc;
        system("cls");

        switch(opc) {
        case 1:
            mostrarBoletaMasCara();
            system("pause");
            break;
        case 2:
            mostrarProductoMasCaro();
            system("pause");
            break;
        case 3:
            listarxNacionalidadARG();
            break;
        case 4:
            ordenarVendedoresxApellido();
            system("pause");
            break;
        case 5:
            contarCategorias();
            break;
        case 6:
            calcularVueltoNecesarioPorVendedor();
            system("pause");
            break;
        case 7:
            recaudacionPorVendedor();
            system("pause");
            break;
        case 8:
            cantidadDeProductosPorProveedor();
            system("pause");
            break;
        case 0:
            system("cls");
            return;
            break;
        default:
            system("cls");
            cout << "OPCION INCORRECTA " <<endl;
            system("pause");
            system("cls");
            break;
        }
        system("cls");
    } while(opc!=0);



}

void cantidadDeProductosPorProveedor() {

    Producto _producto;
    Proveedor _proveedor;
    int pos=0, pos2=0,cantidad=0;

    while(_proveedor.leerDeDisco(pos)==true) {
        pos2=0;
        cantidad=0;
        while(_producto.leerDeDisco(pos2)==true) {
            if(_producto.getIdProveedor()==_proveedor.getIDProveedor()&&_producto.getEstado()==true&&_proveedor.getEstado()==true) {
                cantidad++;
            }
            pos2++;
        }
        cout<<"  EL PROVEEDOR ["<<_proveedor.getIDProveedor()<<"] ("<<_proveedor.getNombreProveedor()<<") Tiene "<<cantidad<<" VARIEDADES DE PRODUCTOS"<<endl;


        cout<<endl;

        pos++;
    }



}

void recaudacionPorVendedor() {
    system("cls");
    int id, pos=0;
    VentaCabecera _VentaCabecera;
    Vendedor _Vendedor;
    cout<<"  INGRESAR ID DEL VENDEDOR: ";
    cin>>id;
    int posVen= buscarIDVendedor(id);
    if(posVen==-1) {
        cout<<"  ERROR EL ID NO EXISTE!"<<endl;
        return;
    }
    _Vendedor.leerDeDisco(posVen);
    float recaudacionTotal=0.0;
    while(_VentaCabecera.leerDeDisco(pos)==true) {
        if(_VentaCabecera.getIdVendedor()==id) {
            recaudacionTotal+= _VentaCabecera.getImporteTotal();
        }
        pos++;
    }

    if(recaudacionTotal==0.0) {
        cout<<"  EL VENDEDOR TODAVIA NO VENDIO PARA CALCULAR CUANTO RECAUDO"<<endl;
        return;
    }
    cout<<"  EL VENDEDOR "<<_Vendedor.getNombreVendedor() <<" "<<_Vendedor.getApellidoVendedor()<<" RECAUDO $"<<recaudacionTotal<<endl;
}


void calcularVueltoNecesarioPorVendedor() {
    system("cls");
    int id, pos=0;
    VentaCabecera _VentaCabecera;
    VentaPie _VentaPie;
    Vendedor _Vendedor;
    cout<<"  INGRESAR ID DEL VENDEDOR: ";
    cin>>id;
    int posVen= buscarIDVendedor(id);
    if(posVen==-1) {
        cout<<"  ERROR EL ID NO EXISTE!"<<endl;
        return;
    }
    _Vendedor.leerDeDisco(posVen);
    float vueltoTotal=0.0, cantidad= 0.0;
    while(_VentaCabecera.leerDeDisco(pos)==true) {
        if(_VentaCabecera.getIdVendedor()==id) {
            _VentaPie.leerDeDisco(pos);
            vueltoTotal+= _VentaPie.getVuelto();
            cantidad+= 1;
        }
        pos++;
    }

    if(cantidad==0.0) {
        cout<<"  EL VENDEDOR TODAVIA NO VENDIO PARA CALCULAR CUANTO VUELTO NECESITA"<<endl;
        return;
    }
    float vueltoNecesario= vueltoTotal/cantidad;
    cout<<"  EL VENDEDOR "<<_Vendedor.getNombreVendedor() <<" "<<_Vendedor.getApellidoVendedor()<<" NECESITA $"<<vueltoNecesario<<" DE VUELTO"<<endl;

}

void MostrarBoletas(int pos) {
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

    VentaCabecera _VentaCabecera;
    VentaDetalle _VentaDetalle;
    VentaPie _VentaPie;
    Producto _Producto;
    int pos2=0, pos3=0;
    bool leyo=_VentaCabecera.leerDeDisco(pos);
    bool leyoPie= _VentaPie.leerDeDisco(pos);///buscarIDVentaPie(_VentaCabecera.getIDVentaCabecera())
    if(leyo==false||leyoPie==false) {
        cout<<endl<<"  Fallo de lectura"<<endl;
        return;
    }
    if(_VentaCabecera.getEstado()==false) {
        cout<<"  La boleta ["<<_VentaCabecera.getIDVentaCabecera()<<"] Fue dada de Baja"<<endl;
        return;
    }
    ///El metodo mostrar ya tiene la validacion
    _VentaCabecera.Mostrar();
    if(_VentaCabecera.getEstado()==true ) {
        while(_VentaDetalle.leerDeDisco(pos2++)==true) {
            if(_VentaDetalle.getidVenta() == _VentaCabecera.getIDVentaCabecera() && _VentaDetalle.getEstado()==true) {
                _VentaDetalle.Mostrar();
                pos3= buscarIDProducto(_VentaDetalle.getIdProducto());
                _Producto.leerDeDisco(pos3);
                cout<<_Producto.getPrecioUnitario()<<endl;
                cout<<"   "<<_Producto.getDescripcion();
                cout<<" ("<<categorias[_Producto.getCategoria()-1]<<")"<<endl;
            }
        }
        _VentaPie.Mostrar();
    }
    cout<<"  ";
    for(int i=0; i<62; i++) {
        cout<<char(205);
    }
    cout<<endl<<"                ";
}

void mostrarBoletaMasCara() {
    system("cls");
    VentaCabecera obj;
    int pos=0, tam;
    tam= contarRegistrosVentaCabecera();
    int hay= contarRegistrosVentaCabeceraSinEliminar();
    if (hay==0) {
        cout<<endl<<"  No hay boletas para hacer el reporte"<<endl;
        return;
    }
    float *vecPrecio;
    vecPrecio= new float [tam];
    if(vecPrecio==NULL) {
        cout<<"  \nFallo al asignar memoria"<<endl;

        return;
    }

    inicializarVector(vecPrecio,tam,0);

    while(obj.leerDeDisco(pos)==true) {
        if(obj.getEstado()==true) {
            vecPrecio[pos]= obj.getImporteTotal();
        }
        pos++;
    }
    pos=0;

    int mayor;
    mayor= buscarMaximo(vecPrecio,tam);

    cout<< "  LA BOLETA MAS CARA ES: " << endl;
    int posi;
    while(obj.leerDeDisco(pos)==true) {

        if(obj.getImporteTotal() == vecPrecio[mayor] ) {
            posi=pos;
        }
        pos++;
    }

    MostrarBoletas(posi);

    delete []vecPrecio;
}
void mostrarProductoMasCaro() {
    system("cls");
    if(contarRegistrosProductoSinEliminar()==0 || contarRegistrosProducto()==0 ) {
        cout<<"  NO HAY REGISTROS"<<endl;
        return;
    }
    Producto obj;
    int pos=0, tam;

    tam= contarRegistrosProducto();

    char (*matNombre)[25];

    matNombre=new char [tam] [25];
    if(matNombre==NULL) {
        cout<<"\n  Fallo al asignar memoria"<<endl;
        return;
    }

    float *vecPrecio;
    vecPrecio= new float [tam];
    if(vecPrecio==NULL) {
        cout<<"\n  Fallo al asignar memoria"<<endl;
        return;
    }
    inicializarVector(vecPrecio,tam,0);
    while(obj.leerDeDisco(pos)==true) {
        if(obj.getEstado()==true) {
            vecPrecio[pos]=obj.getPrecioUnitario();
            strcpy(matNombre[pos],obj.getDescripcion());
        }
        pos++;
    }

    int mayor;
    mayor= buscarMaximo(vecPrecio,tam);

    cout<< "EL PRODUCTO MAS CARO ES: " << matNombre[mayor] <<" $ " << vecPrecio[mayor] <<endl;

    delete []matNombre;
    delete []vecPrecio;
}

void listarxNacionalidadARG() {
    Vendedor obj;
    int pos=0;
    while(obj.leerDeDisco(pos)) {
        if(strcmp(obj.getNacionalidad(),"Argentina")==0) {
            obj.Mostrar();
        }
        pos++;
    }
    system("pause");
}
void ordenarVendedoresxApellido() {
    system("cls");
    Vendedor obj;
    int pos=0, tam;
    tam=contarRegistrosVendedores();
    if(tam==0) {
        cout<<"  \nNO HAY REGISTRO DE VENDEDORES"<<endl;
        return;
    }
    Vendedor *vecVendedor;
    vecVendedor=new Vendedor [tam];
    if(vecVendedor==NULL) {
        cout<<"  \nFallo al asignar memoria"<<endl;
        return;
    }
    while(obj.leerDeDisco(pos)) {
        vecVendedor[pos]=obj;
        pos++;
    }
    ordenarVendedores(vecVendedor,tam);

    mostrarVendedores(vecVendedor,tam);
    delete vecVendedor;

}

void ordenarVendedores(Vendedor *vec, int cantReg) {
    int i, j, posMin=0;
    Vendedor aux;
    for(i=0; i<cantReg-1; i++) {
        posMin=i;
        for(j=i+1; j<cantReg; j++) {
            if(strcmp(vec[j].getApellidoVendedor(),vec[posMin].getApellidoVendedor())<0) {
                posMin=j;
            }
        }
        aux=vec[i];
        vec[i]=vec[posMin];
        vec[posMin]=aux;
    }
}


void mostrarVendedores(Vendedor *vec, int cantReg) {
    int i;
    Vendedor aux;
    for(i=0; i<cantReg; i++) {
        vec[i].Mostrar();
    }


}

void contarCategorias() {
    Proveedor obj;

    int vecCatProveedores[4];
    inicializarVector(vecCatProveedores,4,0);
    int pos=0;
    while(obj.leerDeDisco(pos)) {
        vecCatProveedores[obj.getCategoria()-1]++;
        pos++;
    }
    mostrarVectorProv(vecCatProveedores,4);
    system("pause");
}
void mostrarVectorProv(int *v, int tam) {
    int i;
    for(i=0; i<tam; i++) {
        cout << "LA CATEGORIA: [" << i+1 << "] TIENE " << v[i] << " PROVEEDORES"<< endl;

    }
}


void listarBoletaDebito(int opc) {
    VentaPie obj;
    int pos=0;
    while(obj.leerDeDisco(pos)) {
        if(opc==obj.getFormaDePago()) {
            MostrarBoletas(pos);
        }
        pos++;
    }

}

void listarBoletaCredito(int opc) {
    VentaPie obj;
    int pos=0;
    while(obj.leerDeDisco(pos)) {
        if(opc==obj.getFormaDePago()) {
            MostrarBoletas(pos);
        }
        pos++;
    }

}
void listarBoletaEfectivo(int opc) {
    VentaPie obj;
    int pos=0;
    while(obj.leerDeDisco(pos)) {
        if(opc==obj.getFormaDePago()) {
            MostrarBoletas(pos);
        }
        pos++;
    }

}

#endif // REPORTES_H_INCLUDED
