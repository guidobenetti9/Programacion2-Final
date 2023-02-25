#ifndef DECLARACIONES_H_INCLUDED
#define DECLARACIONES_H_INCLUDED

#include <windows.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
///
const char* ARCHIVO_VENDEDORES= "Vendedores.dat";
const char* ARCHIVO_VENDEDORES_BACKUP= "VendedoresBackup.bkp";
const char* ARCHIVO_VENTA_CABECERA= "VentaCabecera.dat";
const char* ARCHIVO_VENTA_CABECERA_BACKUP= "VentaCabeceraBackup.bkp";
const char* ARCHIVO_VENTA_DETALLE= "VentaDetalle.dat";
const char* ARCHIVO_VENTA_DETALLE_BACKUP= "VentaDetalleBackup.bkp";
const char* ARCHIVO_VENTA_PIE= "VentaPie.dat";
const char* ARCHIVO_VENTA_PIE_BACKUP= "VentaPieBackup.bkp";
const char* ARCHIVO_PRODUCTOS= "Productos.dat";
const char* ARCHIVO_PRODUCTOS_BACKUP= "ProductosBackup.bkp";
const char* ARCHIVO_PROVEEDOR= "proveedores.dat";
const char* ARCHIVO_PROVEEDOR_BACKUP= "ProveedoresBackup.bkp";

///
#include "funciones.h"
#include "claseFecha.h"
///
#include "claseVendedor.h"
#include "funcionesVendedores.h"
///
#include "claseProveedor.h"
#include "funcionesProveedor.h"
///
#include "claseProducto.h"
#include "funcionesProducto.h"
///
#include "ClaseVentaCabecera.h"
#include "funcionesVentaCabecera.h"
#include "ClaseVentaDetalle.h"
#include "funcionesVentaDetalle.h"
#include "claseVentaPie.h"
#include "funcionesVentaPie.h"
///
#include "asignacionID.h"
///
#include "reportes.h"
#include "menuProveedores.h"
#include "MenuProducto.h"
#include "menuVenta.h"
#include "menuVendedor.h"
#include "menuConfiguracionGeneral.h"
#include "MenuPrincipal.h"

void menuPrincipal();
void menuVentaCabecera();

#endif // DECLARACIONES_H_INCLUDED
