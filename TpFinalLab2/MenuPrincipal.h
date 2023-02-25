#ifndef MENUPRINCIPAL_H_INCLUDED
#define MENUPRINCIPAL_H_INCLUDED


void menuPrincipal() {
    int opc;

    Producto _Producto;
    Vendedor _Vendedor;
    do {
        system("cls");

        cout<<endl;
        cout<<"      ";
        for(int i=0; i<24; i++) {
            cout<<char(220);
        }

        cout<<endl;
        cout<<"      "<<char(219)<<"  SuperMercado-PAGUI  "<<char(219)<<endl;
        cout<<"      ";
        for(int i=0; i<24; i++) {
            cout<<char(223);
        }

        cout << endl;
        cout << "          MENU PRINCIPAL" << endl;
        cout << "  -------------------------------"<< endl;
        cout << "  1) PRESENTACION"<< endl;
        cout << "  2) MENU PROVEEDOR"<< endl;
        cout << "  3) MENU PRODUCTO"<< endl;
        cout << "  4) MENU VENDEDOR"<< endl;
        cout << "  5) MENU VENTA"<< endl;
        cout << "  6) MENU REPORTES"<< endl;
        cout<<"  7) MENU CONFIGURACION GENERAL"<<endl;
        cout << "  0) CERRAR PROGRAMA"<< endl;
        cout << "  -------------------------------"<< endl;
        cout << "  SELECCIONE UNA DE LAS OPCIONES: ";
        cin >> opc;
        system("cls");
        switch(opc) {
        case 1:
            system("start chrome https://docs.google.com/document/d/1KZ0qomkZtGxqKp-azAU8FmdRsBcI6nzUqDB9IYjs8jQ/edit");
            break;
        case 2:
            menuProveedores();
            break;
        case 3:
            if(contarRegistrosProveedorSinEliminar()>0) menuProducto();
            else {
                cout<<"\n  PRIMERO DEBE CARGAR A LOS VENDEDORES"<<endl;
                system("pause"); system("cls");
            }
            break;
        case 4:
            menuVendedores();
            break;
        case 5:
            if( contarRegistrosProductoSinEliminar()>0 && contarRegistrosVendedoresSinEliminar()>0 )
                menuVentas();
            else {
                cout<<"\n  PRIMERO DEBE CARGAR A LOS PRODUCTOS Y VENDEDORES"<<endl;
                system("pause"); system("cls");
            }
            break;
        case 6:
            if(contarRegistrosVentaCabeceraSinEliminar()>0 && contarRegistrosProductoSinEliminar()&&contarRegistrosVendedoresSinEliminar()>0 && contarRegistrosProveedorSinEliminar()>0 )
                menuReportes();
            else {
                cout<<"\n  PRIMERO DEBE CARGAR A LAS BOLETAS"<<endl;
                system("pause"); system("cls");
            }

            break;
        case 7:
           menuConfiguracionGeneral();
            break;
        case 0:
            break;
        default:
            system("cls");
            cout << "OPCION INCORRECTA " <<endl;
            system("pause");

            break;
        }
        system("cls");

    } while(opc!=0);

}

#endif // MENUPRINCIPAL_H_INCLUDED
