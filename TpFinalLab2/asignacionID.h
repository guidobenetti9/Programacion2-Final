#ifndef ASIGNACIONID_H_INCLUDED
#define ASIGNACIONID_H_INCLUDED


int AsignarIDVentaCabecera(){
    int idc=contarRegistrosVentaCabecera()+1;
    return idc;
}


int AsignarIDVentaPie(){

    int idc=contarRegistrosVentaPie()+1;
    return idc;
}

int AsignarIDVendedor(){

    int idc=contarRegistrosVendedores()+1;
    return idc;
}


int AsignarIDVentaDetalle(){
    int idi=contarRegistrosVentaDetalle()+1;

    return idi;
}

int AsignarIDProveedor(){

    int id=contarRegistrosProveedor()+1;
    return id;
}


int AsignarIdProducto(){

    int id=contarRegistrosProducto()+1;
    return id;
}

#endif // ASIGNACIONID_H_INCLUDED
