#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
	





int main(int argc, char *argv[]) {
	
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	
	MYSQL *conn;
	conn = mysql_init(NULL);
	if(conn == NULL){
		printf("Error al crear la conexion con la base de datos:%u%s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	conn = mysql_real_connect (conn, "localhost", "root", "mysql", "UNO", 0, NULL, 0);
	if(conn == NULL)
	{
		printf("Error al inicializar la conexion con la base de datos: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	char consulta[400];
	strcpy(consulta,"\0");
	printf("consulta: %s\n", consulta);
	
	
	strcat (consulta,  "SELECT Jugador.Nombre FROM Jugador JOIN Ranking ON Jugador.Identificador = Ranking.Nombre WHERE Ranking.ELO = (SELECT MAX(ELO) FROM Ranking);");
	
	printf("consulta: %s\n", consulta);
	
	err = mysql_query(conn, consulta);
	
	if(err!=0){
		return -1;
		exit(1);
	}
	
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	printf("%s\n", row[0]);
}
