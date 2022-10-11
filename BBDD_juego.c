//Programa en C para crear una base de datos
//Incluir esta libreriﾭa para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h> 
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	//Conector para acceder al servidor de bases de datos 
	MYSQL *conn;
	int err;
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//inicializar la conexion, indicando nuestras claves de acceso
	//al servidor de bases de datos (user,pass)
	conn = mysql_real_connect (conn, "localhost","root", "mysql", NULL, 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Indicamos la base de datos con la que queremos trabajar 
	err=mysql_query(conn, "use bd;");
	if (err!=0)
	{
		printf ("Error al crear la base de datos %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
    
    //Hacemos la consulta
    err=mysql_query(conn, 
    "SELECT DISTINCT JUGADOR.ID FROM (JUGADORS, PARTIDES)
    WHERE JUGADOR.ID IN (
        SELECT DISTINCT JUGADOR.ID FROM (JUGADORS, PARTIDES)
        WHERE JUGADOR.NUM_PARTIDES = MAX(JUGADOR.NUM_PARTIDES)
        AND   JUGADOR.DINERS = MAX(JUGADOR.DINERS) 
    )
    AND JUGADOR.ID_PARTIDA = JUGADOR.ID_PARTIDA
    AND JUGADOR.ID NOT IN JUGADOR.ID;")
    if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}

    resultado = mysql_store_result (conn);
    printf (resultado)