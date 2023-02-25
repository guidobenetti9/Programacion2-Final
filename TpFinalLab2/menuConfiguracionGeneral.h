#ifndef MENUCONFIGURACIONGENERAL_H_INCLUDED
#define MENUCONFIGURACIONGENERAL_H_INCLUDED

void restaurarBackupCompleto();
void restaurarLogicoCompleto();
void backupCompleto();

void menuConfiguracionGeneral(){
    int opc;
    do {
        system("cls");
        cout << endl;
        cout << "          MENU CONFIGURACION GENERAL" << endl;
        cout << "  ---------------------------------------------"<< endl;
        cout << "  1) ESTABLECER DATOS DE INICIO"<< endl;
        cout << "  2) COPIA DE SEGURIDAD COMPLETA"<< endl;
        cout << "  3) RESTAURACION LOGICA COMPLETA"<< endl;
        cout << "  4) RESTAURAR BACKUP"<< endl;
        cout << "  0) VOLVER"<< endl;
        cout << "  ---------------------------------------------"<< endl;
        cout << "  SELECCIONE UNA DE LAS OPCIONES: ";
        cin >> opc;
        system("cls");
        switch(opc) {
        case 1:
            establecerDatosInicio();
            break;
        case 2:
            backupCompleto();
            break;
        case 3:
            restaurarLogicoCompleto();
            break;
        case 4:
            restaurarBackupCompleto();
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

void restaurarBackupCompleto(){
    bool b1=recuperacionFisicaProveedor();
    bool b2=recuperacionFisicaProducto();
    bool b3=recuperacionFisicaVendedores();
    bool b4=recuperacionFisicaVentaCabecera();
    bool b5=recuperacionFisicaVentaDetalle();
    bool b6=recuperacionFisicaVentaPie();
    if(b1==true && b2==true && b3==true && b4==true && b5==true && b6==true) cout<<"  RESTAURACION DE BACKUP COMPLETA"<<endl;


}
void restaurarLogicoCompleto(){
    bool b1=recuperacionLogicaProveedorCompleta();
    bool b2=recuperacionLogicaProductoCompleta();
    bool b3=recuperacionLogicaVendedorCompleta();
    bool b4=recuperacionLogicaVentaCabeceraCompleta();
    bool b5=recuperacionLogicaVentaDetalleCompleta();
    bool b6=recuperacionLogicaVentaPieCompleta();
    if(b1==true && b2==true && b3==true && b4==true && b5==true && b6==true) cout<<"  RESTAURACION LOGICA COMPLETA"<<endl;

}
void backupCompleto(){
    bool b1= backupProveedor();
    bool b2= backupProducto();
    bool b3= backupVendedores();
    bool b4= backupVentaCabecera();
    bool b5= backupVentaDetalle();
    bool b6= backupVentaPie();
    if(b1==true && b2==true && b3==true && b4==true && b5==true && b6==true) cout<<"  BACKUP COMPLETO"<<endl;

}

#endif // MENUCONFIGURACIONGENERAL_H_INCLUDED
