#ifndef MENUVENTA_H_INCLUDED
#define MENUVENTA_H_INCLUDED

///PROTOTIPOS
///***************************************************************
void menuListadoVenta();///                                      *
void mostrarBoletasxID();///                                     *
void menuConfiguracionesVenta();///                              *
void menuModificarVenta();///                                    *
void modificarDniCliente();///                                   *
void modificarIdVendedor();///                                   *
void modificarFechaDeCompra();///                                *
void menuVentas();///                                            *
void cargarVenta();///                                           *
void modificarVentaDetalleIDvendedor();///                       *
void modificarVentaDetalleImporte();///                          *
void modificarVentaDetalleIDProducto();///                       *
void listarBoletasxMedioDePago();///                             *
void modificarVentaPieFormaDePago();///                          *
void modificarVentaDetalleCantidad();///                         *
bool eliminarLogicoRegistroVentaDetalle();///                    *
///***************************************************************

///DESARROLLO


void menuVentas() {
    int opc;
    do {
        cout <<"            MENU VENTA"          << endl;
        cout <<" --------------------------------"<< endl;
        cout <<"  1) CARGAR VENTAS"<< endl;
        if(contarRegistrosVentaCabecera()>0) {
            cout <<"  2) LISTAR BOLETAS"<< endl;
            cout <<"  3) CONFIGURAR VENTAS"<< endl;
        }
        cout <<"  0) VOLVER"<< endl;
        cout <<" --------------------------------"<< endl;
        cout <<" SELECCIONE UNA DE LAS OPCIONES: ";

        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            cargarVenta();
            break;
        case 2:
            if(contarRegistrosVentaCabecera()>0) menuListadoVenta();
            else cout<<"  Primero debe cargar las ventas para poder listarlas"<<endl;
            break;
        case 3:
            if(contarRegistrosVentaCabecera()>0) menuConfiguracionesVenta();
            else cout<<"  Primero debe cargar las ventas para poder configurarlas"<<endl;
            break;
        case 0:
            system("cls");
            return;
            break;
        default:
            system("cls");
            cout << "OPCION INCORRECTA " <<endl;
            break;
        }


    } while(opc!=0);
    system("cls");
    system("pause");

}

void menuListadoVenta() {
    int tam= contarRegistrosVentaCabecera();
    int opc;
    do {

        cout << "           MENU LISTADO VENTA"              << endl;
        cout << " ---------------------------------------"<< endl;
        cout << "  1) MOSTRAR TODAS LAS BOLETAS"<< endl;
        cout << "  2) BUSCAR BOLETA POR ID"<< endl;
        cout << "  3) LISTAR BOLETAS POR METODO DE PAGO " << endl;
        cout << "  0) VOLVER"<< endl;;
        cout << " ---------------------------------------"<< endl;
        cout << " SELECCIONE UNA DE LAS OPCIONES: ";

        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            for(int i=0; i<tam; i++) {
                MostrarBoletas(i);
            }

            break;
        case 2:
            mostrarBoletasxID();

            break;
        case 3:
            listarBoletasxMedioDePago();
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
        system("pause");
        system("cls");
    } while(opc!=0);

}
void mostrarBoletasxID() {

    int id;

    cout<<"  Ingresar ID de la Boleta (cabecera): ";
    cin>>id;
    int pos= buscarIDVentaCabecera(id);
    if(pos!=-1) {
        MostrarBoletas(pos);
    } else {
        cout<<"  ERROR! la boleta "<<id<<" no existe"<<endl;
    }

}

void menuConfiguracionesVenta() {
    int opc;
    bool bak, bak2, bak3, rec, rec2, rec3, borro;
    do {
        system("cls");
        cout << "          MENU CONFIGURACION VENTAS "       << endl;
        cout << " -----------------------------------------"<< endl;
        cout << "  1) MODIFICAR CAMPOS"<< endl;
        cout << "  2) HACER BACKUP"<< endl;
        cout << "  3) RESTAURAR BACKUP"<< endl;
        cout << "  4) RESTAURAR BOLETA"<< endl;
        cout << "  5) RESTAURAR TODAS LAS BOLETAS"<< endl;
        cout << "  6) DAR DE BAJA A TODA LA BOLETA"<< endl;
        cout << "  7) BORRAR DETALLE DE LA BOLETA"<< endl;
        cout << "  0) VOLVER"<< endl;;
        cout << " -----------------------------------------"<< endl;
        cout << " SELECCIONE UNA DE LAS OPCIONES: ";

        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            menuModificarVenta();
            break;
        case 2:
            bak=backupVentaCabecera();
            bak2= backupVentaDetalle();
            bak3= backupVentaPie();
            if(bak==true && bak2==true && bak3==true) {
                cout << "  COPIA DE SEGURIDAD EXITOSA!! " <<endl;
            } else {
                cout << "  ERROR EN COPIA DE SEGURIDAD!! " <<endl;
            }

            break;
        case 3:
            rec= recuperacionFisicaVentaCabecera();
            rec2 =recuperacionFisicaVentaDetalle();
            rec3= recuperacionFisicaVentaPie();
            if(rec==true && rec2==true && rec3==true) {
                cout << "  RECUPERACION EXITOSA!! " <<endl;
            } else {
                cout << "  ERROR EN RECUPERACION !! " <<endl;
            }
            break;
        case 4:
            rec= recuperacionLogicaVentaCabecera();
            rec2= recuperacionLogicaVentaDetalle();
            rec3= recuperacionLogicaVentaPie();
            cout<<endl;
            if(rec==true&&rec2==true&&rec3==true) {
                cout << "  RECUPERACION EXITOSA!! " <<endl;
            } else {
                cout << "  ERROR EN RECUPERACION!! " <<endl;
            }

            break;
        case 5:
            rec= recuperacionLogicaVentaCabeceraCompleta();
            rec2= recuperacionLogicaVentaDetalleCompleta();
            rec3= recuperacionLogicaVentaPieCompleta();
            if(rec==true && rec2==true && rec3==true) {
                cout << "  RECUPERACION EXITOSA!! " <<endl;
            } else {
                cout << "  ERROR EN RECUPERACION!! " <<endl;
            }
            break;
        case 6:
            borro= eliminarLogicoRegistroVentaCabecera();
            if(borro==true)cout<<"Baja Exitosa!"<<endl;
            else cout<<"Error en la Baja"<<endl;
            break;
        case 7:
            borro= eliminarLogicoRegistroVentaDetalle();
            if(borro==true)cout<<"Baja Exitosa!"<<endl;
            else cout<<"Error en la Baja"<<endl;
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
        system("pause");
        system("cls");
    } while(opc!=0);

}
void menuModificarVenta() {
    int opc;

    do {
        system("cls");
        cout << "                 MENU VENTAS"            << endl;
        cout << " -------------------------------------------"<< endl;
        cout << "  1) MODIFICAR ID DEL VENDEDOR"<< endl;
        cout << "  2) MODIFICAR FECHA DE COMPRA " << endl;
        cout << "  3) MODIFICAR ID DE PRODUCTO " << endl;
        cout << "  4) MODIFICAR CANTIDAD DE PRODUCTOS " << endl;
        cout << "  5) MODIFICAR FORMA DE PAGO" << endl;
        cout << "  0) VOLVER"<< endl;
        cout << " -------------------------------------------"<< endl;
        cout << " SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            modificarIdVendedor();
            break;
        case 2:
            modificarFechaDeCompra();
            break;
        case 3:
            modificarVentaDetalleIDProducto();
            break;
        case 4:
            modificarVentaDetalleCantidad();
            break;
        case 5:
            modificarVentaPieFormaDePago();
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
        system("pause");
        system("cls");
    } while(opc!=0);


}

void modificarVentaPieFormaDePago() { ///funciona bien nos hizo renegar por el buscarid
    system("cls");
    VentaPie _VentaPie;
    int id;
    cout<<"  INGRESAR ID DE LA CABECERA DE LA BOLETA: ";
    cin>>id;
    int pos= buscarIDVentaCabecera(id);///venta pie va en paralelo con venta cabecera
    if(pos==-1) {
        cout<<"  ERROR ID NO ENCONTRADO!"<<endl;
        system("pause");
        return;
    }
    _VentaPie.leerDeDisco(pos);
    int forma;
    cout<<"  INGRESAR NUEVA FORMA DE PAGO: ";
    cin>>forma;
    _VentaPie.setFormaDePago(forma);
    if(forma == 1) {
        _VentaPie.setDescuento(0.85);
    }
    if(forma == 2) {
        _VentaPie.setDescuento(0.90);
    }
    if(forma == 3) {
        _VentaPie.setDescuento(1);
    }
    VentaCabecera _VentaCabecera;
    _VentaCabecera.leerDeDisco(pos);
    _VentaCabecera.setImporteTotal(_VentaPie.getSubtotal() * _VentaPie.getDescuento() );


    float aimp;
    int bd=0;
    if(_VentaPie.setVuelto(_VentaPie.getImportePagado()-_VentaCabecera.getImporteTotal())==false) {
        cout<<"  IMPORTE A PAGAR NUEVO: $"<<_VentaCabecera.getImporteTotal()<<endl;

        do {
            if(bd==1) cout<<"  EL IMPORTE NO PUEDE SER NEGATIVO Y DEBE SER MAYOR AL IMPORTE A PAGAR!"<<endl;
            cout<<"  INGRESE CON CUANTO DINERO VA A PAGAR: $";
            cin>>aimp;
            bd=1;
        } while( aimp < _VentaCabecera.getImporteTotal() );
        _VentaPie.setImportePagado(aimp);

    }
    _VentaPie.setVuelto(_VentaPie.getImportePagado()-_VentaCabecera.getImporteTotal());


    sobreEscribirRegistroVentaPie(_VentaPie,pos);

    sobreEscribirRegistroVentaCabecera(_VentaCabecera,pos);

}

void modificarIdVendedor() {
    int pos, id;
    cout << "  INGRESE POR TECLADO EL ID DE LA CABECERA DE LA BOLETA QUE DESEA MODIFICAR: ";
    cin >> id;
    pos= buscarIDVentaCabecera(id);
    if(pos==-1) {
        cout<<"  ERROR! EL ID NO EXISTE"<<endl;
        return;
    }
    VentaCabecera obj;
    obj.leerDeDisco(pos);
    int IdVendedor;
    cout << "  INGRESE EL ID DE VENDEDOR NUEVO QUE DESEA ASIGNAR ";
    cin >> IdVendedor;
    obj.setIdVendedor(IdVendedor);
    if(obj.setIdVendedor(IdVendedor)==false) {
        cout<<"  Id de Vendedor Invalido!"<<endl;
        return;
    }
    bool sob= sobreEscribirRegistroVentaCabecera(obj,pos);
    if(sob == true) cout<<"  Modificacion Exitosa!"<<endl;
    else cout<<"  Modificacion Fallida!"<<endl;
}

void modificarFechaDeCompra() {
    int pos, id;
    cout << "  INGRESE POR TECLADO EL ID DE LA CABECERA DE LA BOLETA QUE DESEA MODIFICAR: ";
    cin >> id;
    pos= buscarIDVentaCabecera(id);
    if(pos==-1) {
        cout<<"  ERROR! EL ID NO EXISTE"<<endl;
        return;
    }
    VentaCabecera obj;
    obj.leerDeDisco(pos);
    bool sob, cargo;
    Fecha aux;

    int bd=0;
    do {
        if(bd==1)cout << "FECHA INVALIDA! "<<endl;
        cout << "INGRESE LA FECHA DE COMPRA NUEVA QUE DESEA ASIGNAR "<<endl;
        cargo= aux.Cargar();
        bd=1;
    } while(cargo==false);
    obj.setFechaDeCompra(aux);
    sob= sobreEscribirRegistroVentaCabecera(obj,pos);
    if(sob == true) cout<<"  Modificacion Exitosa!"<<endl;
    else cout<<"  Modificacion Fallida!"<<endl;
}

void modificarVentaDetalleIDProducto() {
    int pos, id;
    cout << "  INGRESE POR TECLADO EL ID DE LA CABECERA DE LA BOLETA QUE DESEA MODIFICAR: ";
    cin >> id;
    pos= buscarIDVentaCabecera(id);
    if(pos==-1) {
        cout<<"  ERROR! EL ID NO EXISTE"<<endl;
        return;
    }
    VentaCabecera vCab;
    vCab.leerDeDisco(pos);
    VentaDetalle obj;
    VentaPie _VentaPie;
    _VentaPie.leerDeDisco(pos);
    Producto aux;

    cout<<endl<<"  INGRESAR ID DEL DETALLE DE LA VENTA: ";
    int iv;
    cin>>id;
    int pos2= buscarIDVentaDetalle(id);
    if(pos2==-1) {
        cout<<endl<<"  ERROR! EL ID NO ES VALIDO"<<endl;
        return;
    }
    obj.leerDeDisco(pos2);

    if(obj.getidVenta() != vCab.getIDVentaCabecera() ) {
        cout<<"EL ID DE VENTA DETALLE NO CORRESPONDE AL ID DE LA CABECERA"<<endl;
        system("pause");
        system("cls");
        return;
    }

    cout<<"  INGRESAR EL ID DEL PRODUCTO NUEVO: ";
    cin>>iv;
    int posP= buscarIDProducto(iv);
    aux.leerDeDisco(posP);
    if(posP==-1) {
        cout<<"  ERROR! EL ID NO EXISTE"<<endl;
        return;
    }
    obj.setIdProducto(iv);
    obj.setImporte(aux.getPrecioUnitario() * float(obj.getCantidad()));
    sobreEscribirRegistroVentaDetalle(obj,pos2);

    pos2=0;
    float imp=0.0;
    while(obj.leerDeDisco(pos2)==true) {
        if(vCab.getIDVentaCabecera()==obj.getidVenta() && obj.getEstado()==true) {
            imp+= obj.getImporte();
        }
        pos2++;
    }
    _VentaPie.setSubtotal(imp);

    vCab.setImporteTotal(_VentaPie.getSubtotal() * _VentaPie.getDescuento() );


    float aimp;
    int bd=0;
    if(_VentaPie.setVuelto(_VentaPie.getImportePagado()-vCab.getImporteTotal())==false) {
        cout<<"  IMPORTE A PAGAR NUEVO: $"<<vCab.getImporteTotal()<<endl;

        do {
            if(bd==1) cout<<"  EL IMPORTE NO PUEDE SER NEGATIVO Y DEBE SER MAYOR AL IMPORTE A PAGAR!"<<endl;
            cout<<"  INGRESE CON CUANTO DINERO VA A PAGAR: $";
            cin>>aimp;
            bd=1;
        } while( aimp < vCab.getImporteTotal() );
        _VentaPie.setImportePagado(aimp);
    }



    _VentaPie.setVuelto(_VentaPie.getImportePagado()-vCab.getImporteTotal());

    sobreEscribirRegistroVentaPie(_VentaPie,pos);
    sobreEscribirRegistroVentaCabecera(vCab,pos);

    MostrarBoletas(pos);

}


void modificarVentaDetalleCantidad() {
    int pos, id;
    cout << "  INGRESE POR TECLADO EL ID DE LA CABECERA DE LA BOLETA QUE DESEA MODIFICAR: ";
    cin >> id;
    pos= buscarIDVentaCabecera(id);
    if(pos==-1) {
        cout<<"  ERROR! EL ID NO EXISTE"<<endl;
        return;
    }
    VentaCabecera vCab;
    vCab.leerDeDisco(pos);
    VentaDetalle obj;
    VentaPie _VentaPie;
    _VentaPie.leerDeDisco(pos);
    Producto aux;

    cout<<endl<<"  INGRESAR ID DEL DETALLE DE LA VENTA: ";
    int iv;
    cin>>id;
    int pos2= buscarIDVentaDetalle(id);
    if(pos2==-1) {
        cout<<endl<<"  ERROR! EL ID NO ES VALIDO"<<endl;
        return;
    }
    obj.leerDeDisco(pos2);

    if(obj.getidVenta() != vCab.getIDVentaCabecera() ) {
        cout<<"EL ID DE VENTA DETALLE NO CORRESPONDE AL ID DE LA CABECERA"<<endl;
        system("pause");
        system("cls");
        return;
    }

    cout<<"  INGRESAR LA CANTIDAD NUEVA : ";
    cin>>iv;

    int posP= buscarIDProducto(obj.getIdProducto());
    aux.leerDeDisco(posP);
    if(posP==-1) {
        cout<<"  ERROR! EL ID NO EXISTE"<<endl;
        return;
    }
    if(iv>aux.getStock()) {
        cout<<"  NO HAY STOCK SUFICIENTE!"<<endl;
        system("pause");
        return;
    }
    obj.setCantidad(iv);
    obj.setImporte(aux.getPrecioUnitario() * float(obj.getCantidad()));
    sobreEscribirRegistroVentaDetalle(obj,pos2);

    pos2=0;
    float imp=0.0;
    while(obj.leerDeDisco(pos2)==true) {
        if(vCab.getIDVentaCabecera()==obj.getidVenta() && obj.getEstado()==true) {
            imp+= obj.getImporte();
        }
        pos2++;
    }
    _VentaPie.setSubtotal(imp);

    vCab.setImporteTotal(_VentaPie.getSubtotal() * _VentaPie.getDescuento() );
    float aimp;
    int bd=0;
    if(_VentaPie.setVuelto(_VentaPie.getImportePagado()-vCab.getImporteTotal())==false) {
        cout<<"  IMPORTE A PAGAR NUEVO: $"<<vCab.getImporteTotal()<<endl;

        do {
            if(bd==1) cout<<"  EL IMPORTE NO PUEDE SER NEGATIVO Y DEBE SER MAYOR AL IMPORTE A PAGAR!"<<endl;
            cout<<"  INGRESE CON CUANTO DINERO VA A PAGAR: $";
            cin>>aimp;
            bd=1;
        } while( aimp < vCab.getImporteTotal() );
         _VentaPie.setImportePagado(aimp);


    }
    _VentaPie.setVuelto(_VentaPie.getImportePagado()-vCab.getImporteTotal());
    sobreEscribirRegistroVentaPie(_VentaPie,pos);
    sobreEscribirRegistroVentaCabecera(vCab,pos);

    MostrarBoletas(pos);

}

void listarBoletasxMedioDePago() {
    VentaPie obj;
    int opc;

    do {
        cout << "INGRESE QUE BOLETAS DESEA LISTAR POR METODO DE PAGO: "<< endl;
        cout << "1) DEBITO "<< endl;
        cout << "2) CREDITO "<< endl;
        cout << "3) EFECTIVO "<< endl;
        cout << "--------------------" << endl;
        cout << "0) VOLVER " << endl;
        cin >> opc;
        switch(opc) {
        case 1:
            listarBoletaDebito(opc);
            system("pause");
            break;
        case 2:
            listarBoletaCredito(opc);
            system("pause");
            break;
        case 3:
            listarBoletaEfectivo(opc);
            system("pause");
            break;


        }


    } while(opc==0);
}

void cargarVenta() {
    VentaCabecera _regVentaCabecera;
    VentaDetalle _regVentaDetalle;
    Producto _regProducto;
    int salio;
    Vendedor _vendedor;/// lo usamos para validar que la fecha de compra sea despues de su fecha de ingreso

    float ImpTotal, ImporteTotalConDescuento, Importe=0.00;
    int pos=0, stock;

    _regVentaCabecera.setIDVentaCabecera(AsignarIDVentaCabecera());

    ImpTotal=0.00;
    cout<<"  ID Cabecera: ["<<_regVentaCabecera.getIDVentaCabecera()<<"]"<<endl;
    ///cargo cabecera
    _regVentaCabecera.Cargar();

    _vendedor.leerDeDisco(buscarIDVendedor(_regVentaCabecera.getIdVendedor()));
    if(_regVentaCabecera.getFechaDeCompra().getAnio() < _vendedor.getfechaDeIngreso().getAnio() ){
        system("cls");
        cout<<"  LA FECHA DE COMPRA TIENE QUE SER DESPUES DE LA FECHA DE INGRESO DEL VENDEDOR!"<<endl;
        system("pause");
        system("cls");
        return;
    }
    if(_regVentaCabecera.getFechaDeCompra().getAnio() == _vendedor.getfechaDeIngreso().getAnio() && _regVentaCabecera.getFechaDeCompra().getMes() < _vendedor.getfechaDeIngreso().getMes() ){
        system("cls");
        cout<<"  LA FECHA DE COMPRA TIENE QUE SER DESPUES DE LA FECHA DE INGRESO DEL VENDEDOR!"<<endl;
        system("pause");
        system("cls");
        return;
    }
    if(_regVentaCabecera.getFechaDeCompra().getAnio() == _vendedor.getfechaDeIngreso().getAnio() && _regVentaCabecera.getFechaDeCompra().getMes() == _vendedor.getfechaDeIngreso().getMes() && _regVentaCabecera.getFechaDeCompra().getDia() < _vendedor.getfechaDeIngreso().getDia() ){
        system("cls");
        cout<<"  LA FECHA DE COMPRA TIENE QUE SER DESPUES DE LA FECHA DE INGRESO DEL VENDEDOR!"<<endl;
        system("pause");
        system("cls");
        return;
    }

    _regVentaDetalle.setidVenta(_regVentaCabecera.getIDVentaCabecera());

    salio= _regVentaDetalle.Cargar();
    if(salio==2){
        system("cls");
        return;
    }

    while(_regVentaDetalle.getidVenta()==_regVentaCabecera.getIDVentaCabecera()  ) {
        system("cls");
        ///Id autonumerico para detalle
        _regVentaDetalle.setIdVentaDetalle(AsignarIDVentaDetalle());

        ///buscamos producto
        pos= buscarIDProducto(_regVentaDetalle.getIdProducto());
        ///lo cargamos en memoria para acceder al precio unitario y asignar importe e ir acumulando
        if(pos==-1) {
            cout<<"  ERROR! FALLO EN LECTURA"<<endl;
            system("pause");
            system("cls");
            return;
        }
        _regProducto.leerDeDisco(pos);
        stock= _regProducto.getStock();

        if(_regProducto.getStock() < _regVentaDetalle.getCantidad() ) {
            cout<<"  NO HAY STOCK SUFICIENTE! LA BOLETA NO SERA CARGADA"<<endl;
            system("pause");
            system("cls");
            return;
        } else {
            stock=_regProducto.getStock() - _regVentaDetalle.getCantidad();
            _regProducto.setStock(stock);
            sobreEscribirRegistroProducto(_regProducto,pos);
        }
        cout<<"  (Stock restante de "<<_regProducto.getDescripcion()<<"/s: "<<stock<<")"<<endl;
        if(pos!=-1) {

            Importe= float(_regVentaDetalle.getCantidad()) * 1.00 * _regProducto.getPrecioUnitario() ;
            _regVentaDetalle.setImporte(Importe);
            ImpTotal+= Importe;
        }

        ///guardamos detalle
        _regVentaDetalle.grabarEnDisco();

            _regVentaDetalle.setidVenta(_regVentaCabecera.getIDVentaCabecera());

            salio= _regVentaDetalle.Cargar();
            if(salio==2){
                break;
            }
            system("cls");

    }
    system("cls");
    VentaPie _regVentaPie;
    _regVentaPie.setSubtotal(ImpTotal);
    _regVentaPie.setIdVentaCabecera(_regVentaCabecera.getIDVentaCabecera());
    _regVentaPie.setIDVentaPie(AsignarIDVentaPie());
    cout<<"  SUBTOTAL SIN DESCUENTO: $"<<ImpTotal<<endl;
    ImporteTotalConDescuento=_regVentaPie.Cargar();
    _regVentaPie.grabarEnDisco();

    ///guardamos cabecera
    if(pos!=-1) {
        _regVentaCabecera.setImporteTotal(ImporteTotalConDescuento);
        _regVentaCabecera.grabarEnDisco();
    }
    system("pause");
    system("cls");

}


bool eliminarLogicoRegistroVentaDetalle(){
    VentaDetalle detalle;
    int ID, pos;
    cout<<"INGRESE EL ID DEL VentaDetalle A ELIMINAR: ";
    cin>>ID;
    pos=buscarIDVentaDetalle(ID);
    if(pos==-1){
        cout<<"NO EXISTE EL ID EN EL ARCHIVO"<<endl;
        return false;
    }
    detalle.leerDeDisco(pos);
    detalle.setEstado(false);
    sobreEscribirRegistroVentaDetalle(detalle, pos);
    VentaCabecera cabecera;
    VentaPie pie;
    int posC=buscarIDVentaCabecera(detalle.getidVenta());
    cabecera.leerDeDisco(posC);///si o si esto es diferente a -1
    pie.leerDeDisco(posC);

    pos=0;
    float importeTotal=0.0;

    while(detalle.leerDeDisco(pos)==true){
        if(detalle.getEstado()==true && detalle.getidVenta()==cabecera.getIDVentaCabecera()){
            importeTotal+=detalle.getImporte();
        }
        pos++;
    }
    pie.setSubtotal(importeTotal);
    cabecera.setImporteTotal(pie.getSubtotal() * pie.getDescuento());
    pie.setVuelto(pie.getImportePagado()-cabecera.getImporteTotal());



    sobreEscribirRegistroVentaCabecera(cabecera,posC);
    sobreEscribirRegistroVentaPie(pie,posC);


    return true;
}

#endif // MENUVENTA_H_INCLUDED
