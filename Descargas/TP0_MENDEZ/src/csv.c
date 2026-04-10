#include "csv.h"
#include <stdio.h>
#include <string.h>
#define SIGUIENTE 1
#define FIN_LINEA '\n'
#define ERROR_CSV 0
#define FIN_STRING '\0'
const int MAX_CARACTERES = 300;

struct archivo_csv {
	FILE *archivo;
	char separador;
};

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo,
				      char separador)
{
	struct archivo_csv *archivo = malloc(sizeof(struct archivo_csv));
	if (archivo == NULL)
		return NULL;
	archivo->archivo = fopen(nombre_archivo, "r");
	if (archivo->archivo == NULL) {
		free(archivo);
		return NULL;
	}
	archivo->separador = separador;
	return archivo;
}

char *parsear_columna(const char *linea, size_t inicio, size_t fin)
{
	if (linea == NULL || inicio > fin) {
		return NULL;
	}
	size_t longitud = fin - inicio;
	char *columna = malloc(longitud + SIGUIENTE);
	if (columna == NULL) {
		return NULL;
	}
	strncpy(columna, &linea[inicio], longitud);
	columna[longitud] = FIN_STRING;

	return columna;
}

size_t verificar_linea(struct archivo_csv *archivo,
		       bool (*funciones[])(const char *, void *), void *ctx[],
		       size_t columnas)
{
	if (archivo == NULL || archivo->archivo == NULL || funciones == NULL ||
	    ctx == NULL) {
		return ERROR_CSV;
	}
	char linea[MAX_CARACTERES];

	if (!fgets(linea, sizeof(linea), archivo->archivo)) {
		return ERROR_CSV;
	}
	size_t columnas_leidas = 0;
	size_t inicio = 0;
	size_t i = 0;

	while (linea[i] != FIN_STRING && columnas_leidas < columnas) {
		if (linea[i] == archivo->separador || linea[i] == FIN_LINEA ||
		    linea[i + SIGUIENTE] == FIN_STRING) {
			size_t fin;
			if (linea[i + SIGUIENTE] == FIN_STRING) {
				fin = i + SIGUIENTE;
			} else {
				fin = i;
			}
			char *columna = parsear_columna(linea, inicio, fin);
			if (columna) {
				if (funciones[columnas_leidas] != NULL &&
				    funciones[columnas_leidas](
					    columna, ctx[columnas_leidas])) {
					columnas_leidas++;
				}
				free(columna);
			}
			inicio = i + SIGUIENTE;
		}
		i++;
	}
	if (inicio < i) {
		char *columna = parsear_columna(linea, inicio, i);
		if (columna) {
			if (funciones[columnas_leidas] != NULL &&
			    funciones[columnas_leidas](columna,
						       ctx[columnas_leidas])) {
				columnas_leidas++;
			}
			free(columna);
		}
	}
	return columnas_leidas;
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	size_t columnas_leidas =
		verificar_linea(archivo, funciones, ctx, columnas);
	return columnas_leidas;
}
void cerrar_archivo_csv(struct archivo_csv *archivo)
{
	if (archivo) {
		if (archivo->archivo) {
			fclose(archivo->archivo);
		}
		free(archivo);
	}
}
