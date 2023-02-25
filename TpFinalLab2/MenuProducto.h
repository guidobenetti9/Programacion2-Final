#ifndef MENUPRODUCTO_H_INCLUDED
#define MENUPRODUCTO_H_INCLUDED
///PROTOTIPOS
///***************************************************************
bool menuProducto();///                                          *
void menuListadoProducto();///                                   *
bool cargarProductos();///                                       *
void MostrarProductos();///                                      *
void mostrarProductosxID();///                                   *
void mostrarProductosxCategoria();///                            *
void menuConfiguracionesProd();///                               *
bool ProductosRestaurar();///                                    *
void menuModificarProd();///                                     *
void modificarPrecioUnitario(int pos);///                        *
void modificarStock(int pos);///                                 *
void modificarDescripcion(int pos);///                           *
void modificarCategoria(int pos);///                             *
///***************************************************************

///DESARROLLO

bool menuProducto() {
    int opc;
    bool cargo;
    do {
        cout <<"          MENU PRODUCTOS"         << endl;
        cout <<" --------------------------------"<< endl;
        cout <<"  1) CARGAR PRODUCTOS"<< endl;
        if(contarRegistrosProducto()>0) {
            cout <<"  2) LISTAR PRODUCTOS"<< endl;
            cout <<"  3) CONFIGURAR PRODUCTOS"<< endl;
        }
        cout <<" --------------------------------"<< endl;
        cout <<"  0) VOLVER"<< endl;

        cout <<"  SELECCIONE UNA DE LAS OPCIONES: ";

        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            cargo= cargarProductos();
            break;
        case 2:

            if(contarRegistrosProducto()>0) menuListadoProducto();
            else cout<<"  Primero hay que cargar los productos antes de listar"<<endl;
            break;
        case 3:
            if(contarRegistrosProducto()>0) menuConfiguracionesProd();
            else cout<<"  Primero hay que cargar los productos antes de configurar"<<endl;
            break;
        case 0:
            system("cls");
            return cargo;
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
    return cargo;

}

void menuListadoProducto() {

    int opc;
    do {
        system("cls");
        cout <<"         MENU LISTADO PRODUCTOS " << endl;
        cout <<" --------------------------------------- "<< endl;

        cout << "  1) MOSTRAR TODOS LOS PRODUCTOS"<< endl;
        cout << "  2) BUSCAR PRODUCTO POR ID"<< endl;
        cout << "  3) MOSTRAR PRODUCTOS POR CATEGORIA"<< endl;
        cout << "  0) VOLVER"<< endl;;
        cout << " ---------------------------------------"<< endl;
        cout<<endl;
        cout <<"  SELECCIONE UNA DE LAS OPCIONES: ";

        cin>>opc;
        switch(opc) {
        case 1:
            MostrarProductos();
            break;
        case 2:
            mostrarProductosxID();
            break;
        case 3:
            mostrarProductosxCategoria();
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

bool cargarProductos() {
    bool cargo;
    Producto _Productos;
    _Productos.Cargar();
    _Productos.setIdProducto(AsignarIdProducto());
    cargo= _Productos.grabarEnDisco();
    if(cargo==true) cout << endl << "  Se guardo correctamente" <<endl;
    else cout << endl << "  ERROR! Se guardo Incorrectamente" <<endl;
    return cargo;
}

void MostrarProductos() {
    system("cls");
    Producto obj;
    int pos=0, bd=0;
    while(obj.leerDeDisco(pos)==true) {
        obj.Mostrar();
        pos++;
        bd++;
    }
    if(bd==0) cout<<"  No hay registros"<<endl;
}

void mostrarProductosxID() {
    system("cls");
    Producto obj;
    int id, pos=0;
    cout << " INGRESE EL ID DEL PRODUCTO QUE DESEA BUSCAR: ";
    cin>> id;
    while(obj.leerDeDisco(pos++)==true) {
        if(obj.getIDProducto()==id) {
            obj.Mostrar();
            return;
        }
    }
    cout<<"  EL ID INGRESADO NO EXISTE"<<endl;

}

void mostrarProductosxCategoria() {
    system("cls");
    Producto obj;
    int cat,pos=0, bd=0;
    cout << " INGRESE LA CATEGORIA DE LOS PRODUCTOS QUE DESEA BUSCAR: ";
    cin>> cat;
    while(obj.leerDeDisco(pos++)==true) {
        if(obj.getCategoria()==cat) {
            obj.Mostrar();
            bd++;
        }
    }
    if(bd==0) cout<<"  NO HAY PRODUCTOS CON ESA CATEGORIA"<<endl;
    return;
}

void menuConfiguracionesProd() {
    int opc;
    bool bak, rec, borro;
    do {
        system("cls");
        cout << "      MENU CONFIGURACIONES PRODUCTOS"              << endl;
        cout << " ----------------------------------------"<< endl;
        cout << "  1) MODIFICAR CAMPOS"<< endl;
        cout << "  2) HACER BACKUP"<< endl;
        cout << "  3) RESTAURAR BACKUP FISICO"<< endl;
        cout << "  4) RESTAURAR PRODUCTO"<< endl;
        cout << "  5) RESTAURAR A TODOS LOS PRODUCTOS"<< endl;
        cout << "  6) DAR DE BAJA"<< endl;
        cout << "  0) VOLVER"<< endl;;
        cout << " ----------------------------------------"<< endl;
        cout<<endl;
        cout <<"  SELECCIONE UNA DE LAS OPCIONES: ";

        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            menuModificarProd();
            break;
        case 2:
            bak=backupProducto();
            if(bak==true) {
                cout << "COPIA DE SEGURIDAD EXITOSA!! " <<endl;
            } else {
                cout << "ERROR EN COPIA DE SEGURIDAD!! " <<endl;
            }

            break;
        case 3:
            rec= recuperacionFisicaProducto();
            if(rec==true)cout<<"  Recuperacion Exitosa!"<<endl;
            else cout<<"  Error en la Recuperacion"<<endl;
            break;
        case 4:
            rec= recuperacionLogicaProducto();
            if(rec==true)cout<<"  Recuperacion Exitosa!"<<endl;
            else cout<<"  Error en la Recuperacion"<<endl;
            break;
        case 5:
            rec= recuperacionLogicaProductoCompleta();
            if(rec==true)cout<<"  Recuperacion Exitosa!"<<endl;
            else cout<<"  Error en la Recuperacion"<<endl;
            break;
        case 6:
            borro= eliminarLogicoRegistroProducto();
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
void menuModificarProd() {
    int pos, opc, id;
    cout << "INGRESE POR TECLADO EL ID DEL PRODUCTO QUE DESEA MODIFICAR ";
    cin >> id;
    pos= buscarIDProducto(id);
    if(pos==-1) {
        cout<<"  ERROR! EL ID NO EXISTE"<<endl;
        return;
    }

    do {
        system("cls");
        cout <<" ----------------------------------"<< endl;
        cout << "  1) MODIFICAR PRECIO UNITARIO"<< endl;
        cout << "  2) MODIFICAR STOCK"<< endl;
        cout << "  3) MODIFICAR DESCRIPCION"<< endl;
        cout << "  4) MODIFICAR CATEGORIA " << endl;
        cout <<" ----------------------------------"<< endl;
        cout << "  0) VOLVER"<< endl<<endl;
        cout <<"SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            modificarPrecioUnitario(pos);
            break;
        case 2:
            modificarStock(pos);
            break;
        case 3:
            modificarDescripcion(pos);
            break;
        case 4:
            modificarCategoria(pos);
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

void modificarPrecioUnitario(int pos) {
    Producto obj;
    int precio;
    obj.leerDeDisco(pos);
    cout << "INGRESE EL PRECIO NUEVO QUE DESEA ASIGNAR ";
    cin >> precio;
    obj.setPrecioUnitario(precio);

    bool sob= sobreEscribirRegistroProducto(obj,pos);
    if(sob == true) cout<<"  Modificacion Exitosa!"<<endl;
    else cout<<"  Modificacion Fallida!"<<endl;
}
void modificarStock(int pos) {
    Producto obj;
    int stock;
    obj.leerDeDisco(pos);
    cout << "INGRESE EL STOCK NUEVO QUE DESEA ASIGNAR ";
    cin >> stock;
    obj.setStock(stock);

    bool sob=  sobreEscribirRegistroProducto(obj,pos);
    if(sob == true) cout<<"  Modificacion Exitosa!"<<endl;
    else cout<<"  Modificacion Fallida!"<<endl;
}

void modificarDescripcion(int pos) {
    Producto obj;
    char descripcion[25];
    obj.leerDeDisco(pos);
    cout << "INGRESE LA DESCRIPCION NUEVA QUE DESEA ASIGNAR ";
    cargarCadena(descripcion,24);
    obj.setDescripcion(descripcion);

    bool sob= sobreEscribirRegistroProducto(obj,pos);
    if(sob == true) cout<<"  Modificacion Exitosa!"<<endl;
    else cout<<"  Modificacion Fallida!"<<endl;
}

void modificarCategoria(int pos) {
    Producto obj;
    int cat;
    obj.leerDeDisco(pos);
    cout << "INGRESE LA CATEGORIA NUEVA QUE DESEA ASIGNAR ";
    cin >> cat;
    obj.setCategoria(cat);

    bool sob= sobreEscribirRegistroProducto(obj,pos);
    if(sob == true) cout<<"  Modificacion Exitosa!"<<endl;
    else cout<<"  Modificacion Fallida!"<<endl;
}

bool ProductosRestaurar() {
    Producto reg;
    FILE *p, *pNuevo;
    pNuevo=fopen(ARCHIVO_PRODUCTOS,"wb");
    if(pNuevo==NULL) {
        return false;
    }
    p=fopen(ARCHIVO_PRODUCTOS_BACKUP,"rb");
    if(p==NULL) {
        fclose(pNuevo);
        return false;
    }
    while(fread(&reg,sizeof reg,1,p)==1) {
        fwrite(&reg,sizeof reg,1,pNuevo);
    }
    fclose(p);
    fclose(pNuevo);
    return true;
}

#endif // MENUPRODUCTO_H_INCLUDED
