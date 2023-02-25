#ifndef MENUVENDEDOR_H_INCLUDED
#define MENUVENDEDOR_H_INCLUDED

///PROTOTIPOS
///***************************************************************
void modificarFechaInicio(int pos);///                           *
void modificarFechaNacimiento(int pos);///                       *
void modificarCategoriaVendedor(int pos);///                     *
void modificarNacionalidad(int pos);///                          *
void modificarApellido(int pos);///                              *
void modificarNombre(int pos);///                                *
void menuModificarVendedores();///                               *
void menuConfiguracionesVendedor();///                           *
void listarxCat();///                                            *
void mostrarVendedores();///                                     *
void listarxID();///                                             *
void menuListadoVendedores();///                                 *
bool CargarVendedor();///                                        *
bool menuVendedores();///                                        *
///***************************************************************


bool menuVendedores() {

    int opc;
    bool cargo;
    do {
        cout <<"      MENU VENDEDORES" << endl;
        cout <<" -------------------------"<< endl;

        cout <<"  1) CARGAR VENDEDORES"<< endl;
        if(contarRegistrosVendedores()>0){
            cout <<"  2) LISTAR VENDEDORES"<< endl;
            cout <<"  3) CONFIGURAR VENDEDORES"<< endl;
        }
        cout <<" -------------------------"<< endl;
        cout <<"  0) VOLVER"<< endl;

        cout <<"  SELECCIONE UNA DE LAS OPCIONES: ";

        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            cargo=CargarVendedor();
            break;
        case 2:
            menuListadoVendedores();
            break;
        case 3:
            menuConfiguracionesVendedor();
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

bool CargarVendedor() {
    Vendedor _Vendedores;
    bool cargo;
    _Vendedores.Cargar();
    _Vendedores.setIDVendedor(AsignarIDVendedor());
    cargo=_Vendedores.grabarEnDisco();
    if(cargo==true) {
        cout << "Cargado con exito!!" << endl;
    } else {
        cout << "Fallo al cargar!!" << endl;
    }
    return cargo;
}

void menuListadoVendedores() {
    int opc;
    do {
        system("cls");
        cout <<"         MENU LISTADO VENDEDORES"       << endl;
        cout <<" ------------------------------------"<< endl;
        cout <<"  1) LISTAR TODOS"<< endl;
        cout <<"  2) LISTAR POR ID DE VENDEDOR"<< endl;
        cout <<"  3) LISTAR VENDEDORES POR CATEGORIA"<< endl;
        cout <<" ------------------------------------"<< endl;
        cout <<"  0) CERRAR PROGRAMA"<< endl;

        cout <<"  SELECCIONE UNA DE LAS OPCIONES: ";

        cin>>opc;
        switch(opc) {
        case 1:
            mostrarVendedores();
            break;
        case 2:
            listarxID();
            system("cls");
            break;
        case 3:
            listarxCat();
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
    } while(opc!=0);

}
void mostrarVendedores() {
    system("cls");
    Vendedor obj;
    int pos=0, bd=0;
    while(obj.leerDeDisco(pos)==true) {
        obj.Mostrar();
        pos++;
        bd++;
    }
    if(bd==0) cout<<"  No hay registros"<<endl;
    system("pause");
}

void listarxID() {
    system("cls");
    Vendedor obj;
    int pos,id;
    cout << "INGRESE ID DEL VENDEDOR QUE DESEA BUSCAR: ";
    cin >> id;
    pos=buscarIDVendedor(id);
    obj.leerDeDisco(pos);
    if(pos!=-1) {
        obj.Mostrar();
    } else {
        cout << " DATOS INGRESADOS ERRONEOS "<<endl;
    }

    system("pause");
}

void listarxCat() {
    system("cls");
    Vendedor obj;
    int pos=0, cat, d=0;
    cout << "INGRESE CATEGORIA DE LOS VENDEDORES QUE DESEA BUSCAR: ";
    cin >> cat;
    while(obj.leerDeDisco(pos)) {
        if(obj.getCategoria()==cat) {
            obj.Mostrar();
            cout << endl;
            d++;

        }
        pos++;
    }
    if(d==0)cout << " DATOS INGRESADOS ERRONEOS "<<endl;
    system("pause");

    return;
}

void menuConfiguracionesVendedor() {
    int opc;
    bool bak, rec, borro;
    do {
        system("cls");
        cout << "        MENU CONFIGURACION VENDEDOR" << endl;
        cout << " ----------------------------------------"<< endl;
        cout << "  1) MODIFICAR CAMPOS"<< endl;
        cout << "  2) HACER BACKUP"<< endl;
        cout << "  3) RESTAURAR BACKUP FISICO"<< endl;
        cout << "  4) RESTAURAR VENDEDOR"<< endl;
        cout << "  5) RESTAURAR A TODOS LOS VENDEDORES"<< endl;
        cout << "  6) DAR DE BAJA"<< endl;
        cout << "  0) VOLVER"<< endl;;
        cout << " ----------------------------------------"<< endl;
        cout << " SELECCIONE UNA DE LAS OPCIONES: ";

        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            menuModificarVendedores();
            break;
        case 2:
            bak=backupVendedores();
            if(bak==true) {
                cout << "COPIA DE SEGURIDAD EXITOSA!! " <<endl;
            } else {
                cout << "ERROR EN COPIA DE SEGURIDAD!! " <<endl;
            }

            break;
        case 3:
            rec= recuperacionFisicaVendedores();
            if(rec==true)cout<<"  Recuperacion Exitosa!"<<endl;
            else cout<<"  Error en la Recuperacion"<<endl;
            break;
            break;
        case 4:
            rec= recuperacionLogicaVendedor();
            if(rec==true)cout<<"  Recuperacion Exitosa!"<<endl;
            else cout<<"  Error en la Recuperacion"<<endl;
            break;
        case 5:
            rec= recuperacionLogicaVendedorCompleta();
            if(rec==true)cout<<"  Recuperacion Exitosa!"<<endl;
            else cout<<"  Error en la Recuperacion"<<endl;
            break;
        case 6:
            borro= eliminarLogicoRegistroVendedor();
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

void menuModificarVendedores() {
    int pos, opc, id;
    cout << "INGRESE POR TECLADO EL ID DEL VENDEDOR QUE DESEA MODIFICAR ";
    cin >> id;
    pos= buscarIDVendedor(id);
    if(pos==-1) {
        cout<<"  ERROR! EL ID NO EXISTE"<<endl;
        system("pause");
        return;
    }

    do {
        system("cls");
        cout <<" ----------------------------------"<< endl;
        cout << "  1) MODIFICAR NOMBRE"<< endl;
        cout << "  2) MODIFICAR APELLIDO"<< endl;
        cout << "  3) MODIFICAR NACIONALIDAD"<< endl;
        cout << "  4) MODIFICAR CATEGORIA " << endl;
        cout << "  5) MODIFICAR FECHA DE NACIMIENTO " << endl;
        cout << "  6) MODIFICAR FECHA DE INGRESO " << endl;
        cout <<" ----------------------------------"<< endl;
        cout << "  0) VOLVER"<< endl<<endl;
        cout <<"SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            modificarNombre(pos);
            break;
        case 2:
            modificarApellido(pos);
            break;
        case 3:
            modificarNacionalidad(pos);
            break;
        case 4:
            modificarCategoriaVendedor(pos);
            break;
        case 5:
            modificarFechaNacimiento(pos);
            break;
        case 6:
            modificarFechaInicio(pos);
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

void modificarNombre(int pos) {
    Vendedor obj;
    char nombre[40];
    obj.leerDeDisco(pos);
    cout << "INGRESE EL NUEVO NOMBRE QUE DESEA ASIGNAR ";
    cargarCadena(nombre,39);
    obj.setNombreVendedor(nombre);
    sobreEscribirRegistroVendedor(obj,pos);
}

void modificarApellido(int pos) {
    Vendedor obj;
    char apellido[40];
    obj.leerDeDisco(pos);
    cout << "INGRESE EL NUEVO APELLIDO QUE DESEA ASIGNAR ";
    cargarCadena(apellido,39);
    obj.setApellidoVendedor(apellido);
    sobreEscribirRegistroVendedor(obj,pos);
}

void modificarNacionalidad(int pos) {
    Vendedor obj;
    char nacionalidad[10];
    obj.leerDeDisco(pos);
    cout << "INGRESE LA NUEVA NACIONALIDAD QUE DESEA ASIGNAR ";
    cargarCadena(nacionalidad,9);
    obj.setNacionalidad(nacionalidad);
    sobreEscribirRegistroVendedor(obj,pos);
}

void modificarCategoriaVendedor(int pos) {
    Vendedor obj;
    int cat;
    obj.leerDeDisco(pos);
    cout << "INGRESE LA CATEGORIA NUEVA QUE DESEA ASIGNAR ";
    cin >> cat;
    obj.setCategoria(cat);
    sobreEscribirRegistroVendedor(obj,pos);
}

void modificarFechaNacimiento(int pos) {
    Vendedor obj;
    bool sob,cargo;
    Fecha aux;
    obj.leerDeDisco(pos);
    int bd=0;
    do {
        if(bd==1) {
            cout << "FECHA INVALIDA"<< endl;
        }
        cout << "INGRESE LA FECHA DE NACIMIENTO NUEVA QUE DESEA ASIGNAR ";
        cargo= aux.Cargar();
        bd=1;
    } while(cargo==false);
    obj.setfechaDeNacimiento(aux);
    sob=sobreEscribirRegistroVendedor(obj,pos);
    if(sob==true) {
        cout << "MODIFICACION EXITOSA"<< endl;
    } else {
        cout << "MODIFICACION FALLIDA!"<< endl;
    }
}

void modificarFechaInicio(int pos) {
    Vendedor obj;
    obj.leerDeDisco(pos);
    cout << "INGRESE LA FECHA DE INGRESO NUEVA QUE DESEA ASIGNAR ";
    obj.getfechaDeIngreso().Cargar();
    sobreEscribirRegistroVendedor(obj,pos);
}

#endif // MENUVENDEDOR_H_INCLUDED
