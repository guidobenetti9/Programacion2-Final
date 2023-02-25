#ifndef MENUPROVEEDORES_H_INCLUDED
#define MENUPROVEEDORES_H_INCLUDED

bool menuProveedores();
void menuListadoProveedores();
void menuConfiguracionProveedores();


bool menuProveedores() {
    Proveedor _Proveedor;
    bool cargo;
    int opc;
    do {
        system("cls");
        cout << endl;
        cout <<"          MENU PROVEEDORES" << endl;
        cout <<"  -------------------------------"<< endl;
        cout <<"  1) CARGAR PROVEEDORES"<< endl;
        cout <<"  2) LISTAR PROVEEDORES"<< endl;
        cout <<"  3) CONFIGURAR PROVEEDORES"<< endl;
        cout <<"  0) VOLVER"<< endl;
        cout <<"  -------------------------------"<< endl;
        cout <<"  SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");
        switch(opc) {
        case 1:
            _Proveedor.Cargar();
            _Proveedor.setIdProveedor(AsignarIDProveedor());
            cargo= _Proveedor.grabarEnDisco();
            if(cargo==true) cout << endl << "  Se guardo correctamente" <<endl;
            else cout << endl << "  ERROR! Se guardo Incorrectamente" <<endl;
            break;
        case 2:
            menuListadoProveedores();
            break;
        case 3:
            menuConfiguracionProveedores();
            break;
        case 0:
            break;
        default:
            system("cls");
            cout << "OPCION INCORRECTA " <<endl;
            system("pause");
            system("cls");
            break;
        }
    } while(opc!=0);

    return cargo;

}

void menuListadoProveedores() {
    Proveedor _Proveedor;
    int pos=0, bd=0;
    int opc;
    bool existe;
    do {
        system("cls");
        cout << endl;
        cout << "      MENU LISTADO PROVEEDORES" << endl;
        cout << "  -------------------------------"<< endl;
        cout << "  1) MOSTRAR A TODOS LOS PROVEEDORES"<< endl;
        cout << "  2) BUSCAR PROVEEDOR POR ID"<< endl;
        cout << "  3) BUSCAR PROVEEDORES POR CATEGORIA"<< endl;
        cout << "  0) VOLVER"<< endl;
        cout << "  -------------------------------"<< endl;
        cout << "  SELECCIONE UNA DE LAS OPCIONES: ";
        cin >> opc;
        system("cls");
        switch(opc) {
        case 1:

            while(_Proveedor.leerDeDisco(pos++)==true) {
                _Proveedor.Mostrar();
                bd++;
            }
            if(bd==0) cout<<"No hay registros"<<endl;
            pos=0;
            bd=0;
            break;
        case 2:
            existe= mostrarProveedorPorID();
            if(existe==false) cout<<"No existe el ID ingresado"<<endl;
            break;
        case 3:
            existe= mostrarProveedorPorCategoria();
            if(existe==false) cout<<"No existe el proveedor con esa categoria"<<endl;
            break;
        case 0:
            system("cls");
            return;
            break;
        default:
            system("cls");
            cout << "OPCION INCORRECTA " <<endl;
            system("pause");

            break;
        }

        system("pause");
        system("cls");
    } while(opc!=0);

}
void menuConfiguracionProveedores() {

    int opc;
    bool borro, bak, rec;
    do {
        system("cls");
        cout << endl;
        cout << "      MENU CONFIGURACION PROVEEDORES" << endl;
        cout << "  --------------------------------------"<< endl;
        cout << "  1) DAR DE BAJA A PROVEEDOR"<< endl;
        cout << "  2) MODIFICAR PROVEEDOR"<< endl;
        cout << "  3) REALIZAR COPIA DE SEGURIDAD DE PROVEEDORES"<< endl;
        cout << "  4) RESTAURAR PROVEEDOR"<< endl;
        cout << "  5) RESTAURAR A TODOS LOS PROVEEDORES"<< endl;
        cout << "  6) RESTAURAR COPIA DE SEGURIDAD"<< endl;
        cout << "  0) VOLVER"<< endl;
        cout << "  --------------------------------------"<< endl;
        cout << "  SELECCIONE UNA DE LAS OPCIONES: ";
        cin >> opc;
        system("cls");
        switch(opc) {
        case 1:
            borro= eliminarLogicoRegistroProveedor();
            if(borro==true)cout<<"Baja Exitosa!"<<endl;
            else cout<<"Error en la Baja"<<endl;
            break;
        case 2:
            ModificarProveedor();
            break;
        case 3:
            bak= backupProveedor();
            if(bak==true)cout<<"  Copia de seguridad Exitosa!"<<endl;
            else cout<<"  Error en la Copia de seguridad"<<endl;
            break;
        case 4:
            rec= recuperacionLogicaProveedor();
            if(rec==true)cout<<"  Recuperacion Exitosa!"<<endl;
            else cout<<"  Error en la Recuperacion"<<endl;
            break;
        case 5:
            rec= recuperacionLogicaProveedorCompleta();
            if(rec==true)cout<<"  Recuperacion Exitosa!"<<endl;
            else cout<<"  Error en la Recuperacion"<<endl;
            break;
        case 6:
            rec= recuperacionFisicaProveedor();
            if(rec==true)cout<<"  Recuperacion Exitosa!"<<endl;
            else cout<<"  Error en la Recuperacion"<<endl;
            break;
        case 0:
            system("cls");
            return;
            break;
        default:
            system("cls");
            cout << "OPCION INCORRECTA " <<endl;
            system("pause");

            break;
        }

        system("pause");
        system("cls");
    } while(opc!=0);

}

bool mostrarProveedorPorID() {
    int pos, id;
    Proveedor obj;
    cout<<"   Ingresar ID del Proveedor: ";
    cin>>id;
    pos= buscarIDProveedor(id);
    if(pos!=-1) {
        obj.leerDeDisco(pos);
        obj.Mostrar();
        return true;
    }
    return false;
}

bool mostrarProveedorPorCategoria() {
    int pos, cat, bd=0;
    Proveedor obj;

    cout<<"  1. fabricantes"<<endl;
    cout<<"  2. Mayoristas y distribuidores"<<endl;
    cout<<"  3. Artesanos independientes"<<endl;
    cout<<"  4. Importacion"<<endl;

    cout<<"   Ingresar numero de Categoria del Proveedor/es: ";
    cin>>cat;
    pos= 0;
    while(obj.leerDeDisco(pos++)==true) {
        if(obj.getCategoria() == cat) {
            obj.Mostrar();
            bd++;
            cout<<endl;
        }
    }
    if(bd>0) return true;


    return false;
}


#endif // MENUPROVEEDORES_H_INCLUDED
