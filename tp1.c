#include "src/pokedex.h"
#include "src/csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
const int MAX_COLUMNAS = 5;
const int VALOR_INICIAL = 0;
const int ERROR = -1;
#define ROJO_CHILLON "\033[1;91m"
#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
#define AMARILLO "\033[0;33m"
#define AZUL "\033[0;34m"
#define VIOLETA "\033[0;35m"
#define CYAN "\033[0;36m"
#define GRIS "\033[0;37m"
#define COLOR_RESET "\033[0m"
#define VERDE_CHILLON "\033[1;92m"
#define AMARILLO_CHILLON "\033[1;93m"
#define AZUL_CHILLON "\033[1;94m"
#define VIOLETA_CHILLON "\033[1;95m"
#define CYAN_CHILLON "\033[1;96m"
#define GRIS_CHILLON "\033[1;97m"
#define COLOR_AMARILLO "\033[33m"
#define COLOR_VERDE "\033[32m"
#define COLOR_AZUL "\033[34m"
#define COLOR_GRIS "\033[37m"
#define COLOR_PURPLE "\e[4;33m]"
int contador_fuego = 0;
int contador_planta = 0;
int contador_agua = 0;
int contador_electrico = 0;
int contador_roca = 0;
int contador_lucha = 0;
int contador_pokemones = 0;
int contador_normal = 0;

void ordenar_pokedex(struct pokedex *pokedex);

bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}
int ejecutar_comando(const char *comando)
{
	int resultado = system(comando);
	if (resultado != 0) {
	}
	return resultado;
}

bool imprimir_pokemon(struct pokemon *pokemon, void *ctx)
{
	(void)ctx;

	const char *color;
	const char *color_resto;

	switch (pokemon->tipo) {
	case TIPO_FUEGO:
		color = ROJO_CHILLON;
		color_resto = ROJO;
		contador_fuego++;
		break;
	case TIPO_ELECTRICO:
		color = AMARILLO_CHILLON;
		color_resto = AMARILLO;
		contador_electrico++;
		break;
	case TIPO_PLANTA:
		color = VERDE_CHILLON;
		color_resto = VERDE;
		contador_planta++;
		break;
	case TIPO_AGUA:
		color = AZUL_CHILLON;
		color_resto = AZUL;
		contador_agua++;
		break;
	case TIPO_LUCHA:
		color = VIOLETA_CHILLON;
		color_resto = VIOLETA;
		contador_lucha++;
		break;
	case TIPO_ROCA:
		color = CYAN_CHILLON;
		color_resto = CYAN;
		contador_roca++;
		break;
	case TIPO_NORMAL:
		color = GRIS_CHILLON;
		color_resto = GRIS;
		contador_normal++;
	default:
		color = GRIS_CHILLON;
		color_resto = GRIS;
		break;
	}
	contador_pokemones++;
	printf("\n\t\t\t\t\t%sNombre:" COLOR_RESET " %s%-20s" COLOR_RESET,
	       color_resto, color, pokemon->nombre);
	printf("\t\t%sTipo: " COLOR_RESET "%s%-2c" COLOR_RESET, color_resto,
	       color, pokemon->tipo);
	printf("%s\t\tFuerza:" COLOR_RESET " %s%2d" COLOR_RESET, color_resto,
	       color, pokemon->fuerza);
	printf("\t\t%sDestreza: " COLOR_RESET "%s%2d" COLOR_RESET, color_resto,
	       color, pokemon->destreza);
	printf("\t\t%sResistencia:" COLOR_RESET " %s%2d\n" COLOR_RESET,
	       color_resto, color, pokemon->resistencia);
	return true;
}

void snorlax()
{
	printf("\t\t%s⠀⠀⠀⠀⠀⠀⠀⢠⣤⣀⠀⠀⠀⠀⢀⣀⣤⣤⠀⠀⠀⠀⠀⠀⠀\n", AZUL_CHILLON);
	printf("\t\t⠀⠀⢀⢀⠀⠀⠀⢸⡿⠛⠛⠛⠛⠛⠉⠛⢿⣿⠀⠀⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠠⣿⣿⣿⣄⠀⣼⠀⠀⠀⢂⣀⣀⡀⠀⠀⢹⡀⠀⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⢸⣿⣿⣿⣿⡷⠋⠈⠀⠀⠀⠀⠀⠀⠀⠈⠘⠣⡀⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠈⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣷⣦⡀⠀⠀\n");
	printf("\t\t⠀⠀⢹⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣦⠀\n");
	printf("\t\t⠀⠀⣸⣿⣿⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇\n");
	printf("\t\t⠀⣤⡟⠛⠋⠉⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠉⠈⠋⠈⢿⣿⡿\n");
	printf("\t\t⢀⡉⠀⠀⣀⣤⣄⢈⣿⣿⣿⣿⣿⣿⣿⣿⣿⢀⣤⣤⣄⠀⠀⣴⡄\n");
	printf("\t\t⠘⢇⠀⠰⣿⣿⢟⢼⣿⣿⣿⣿⣿⣿⣿⣿⡿⢜⠿⠿⠿⠀⡀⠀⠀\n");
	printf("\t\t⠀⠀⠁⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠈⠀⠀⠀\n" COLOR_RESET);
}
void volteon()
{
	printf("\t\t%s⠀⠀⠀⠀⠠⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n", AMARILLO_CHILLON);
	printf("\t\t⠀⡀⠀⠀⢀⣳⣄⠀⡀⣿⣰⠀⠠⠀⠀⠀⢠⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠘⢷⣤⣀⠹⣿⣧⣿⣿⣿⢦⣈⠀⠀⡆⠀⢁⢀⠀⢠⡴⡇⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⠀⠻⣿⣷⣿⣿⣿⣿⣿⣆⠈⠳⣄⠀⢰⡀⠀⠂⡞⢠⠇⠀⠀⠀⠀\n");
	printf("\t\t⠀⠲⠶⣴⣾⣿⣿⣿⣿⣿⣿⡛⠦⡀⠘⣶⣬⣿⣴⣼⢀⢎⠀⠄⠀⠀⠀\n");
	printf("\t\t⠀⠀⠤⢴⣿⣿⣿⣿⣿⣿⣍⡉⠀⢼⣾⣿⣿⣿⣿⣿⣿⠠⠊⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⣶⣿⣿⣿⡿⠋⣿⣿⡷⠆⠀⢺⣿⣇⣈⣻⣿⣏⣼⠁⡀⠀⠀⠀⠀\n");
	printf("\t\t⠀⢸⣿⡟⠛⠉⠀⢰⣿⣿⣿⠋⢀⠈⠻⠿⢿⣿⣿⡿⠋⡠⡈⠐⠀⠀⠀\n");
	printf("\t\t⠀⣿⣿⠀⠀⠀⠀⠀⢻⣿⣷⡎⠙⠃⠀⢄⠀⡩⢩⣠⣄⡡⡀⠀⠀⠀⠀\n");
	printf("\t\t⠈⠿⠿⠇⠀⠀⠀⠀⠈⣿⣿⡇⠐⠂⠀⠁⠖⠀⠉⠉⠻⢿⣿⣦⣄⠀⠀\n");
	printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⢿⣿⡷\n" COLOR_RESET);
}

void bulbassaur()
{
	printf("\n\t\t%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⣀⡀⠈⡖⡤⠄⠀\n", VERDE_CHILLON);
	printf("\t\t⠀⠀⢀⡀⠀⠀⠀⡐⠁⠀⠀⠠⠐⠂⠀⠁⠀⠀⠀⠀\n");
	printf("\t\t⠀⠰⡁⠐⢉⣉⣭⡍⠁⠂⠉⠘⡀⠀⠀⠀⠀⠂⠡⠀\n");
	printf("\t\t⢀⣊⠀⡄⠻⠿⠋⠀⠀⠀⠀⠀⢃⠀⠀⠀⠀⠀⠀⢀\n");
	printf("\t\t⡎⣾⠀⠁⣴⡆⠀⠡⢺⣿⣆⠀⢠⢱⣄⠀⠀⠀⠀⠈\n");
	printf("\t\t⡑⠟⠀⠀⠀⠀⠀⢀⣸⡿⠟⠀⠀⠈⢿⣿⡦⡀⠀⡰\n");
	printf("\t\t⠙⠔⠦⣤⣥⣤⣤⣤⡤⠆⠀⠀⠀⠀⢀⢀⠀⠈⠎⠀\n");
	printf("\t\t⠀⠀⠈⣰⡋⢉⠉⠁⠒⠂⢇⢠⡆⠀⠸⢴⣿⠀⠘⠀\n");
	printf("\t\t⠀⠀⠘⡿⠃⠀⠨⠒⢆⣸⣿⠁⠀⡠⡇⠈⠋⠀⠰⠀\n");
	printf("\t\t⠀⠀⠀⠛⠒⠒⠁⠀⠈⠷⡤⠤⠐⠀⠘⠒⠒⠖⠁⠀\n" COLOR_RESET);
}

void sableye()
{
	printf("\t%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠀⢰⣰⠀⢀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢴⠃\n", VIOLETA_CHILLON);
	printf("\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⡠⠔⠋⢩⠖⠁⠀⠉⠢⢄⠀⠀⠀⢀⠔⠁⡌⠀\n");
	printf("\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⡚⢢⠀⡰⠁⠀⠀⢀⡀⠀⠀⠙⢠⠔⠁⠀⡜⠀⠀\n");
	printf("\t⠀⢀⣤⠒⠂⠉⠉⠁⠀⢀⠁⡹⠂⡷⠀⠀⡴⡘⠹⡈⢢⡀⠀⠁⠀⠀⣰⠄⡖⠀\n");
	printf("\t⣜⢴⡡⠴⠂⡀⠤⠒⠒⠚⣖⣙⠞⠀⠀⠠⡡⡇⠀⢸⠁⠇⠀⠀⠀⠀⢀⠎⠀⠀\n");
	printf("\t⠀⠀⠈⠉⠀⠀⠀⠀⠀⠀⠘⢄⠀⡇⠀⠀⠑⢌⡉⠤⠋⠀⡰⠠⢀⢔⡁⠀⠀⠀\n");
	printf("\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢴⣄⢀⣀⡀⡤⢤⡒⠈⠲⡤⣀⠀⠈⠒⠄⣀\n");
	printf("\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡱⡿⠌⡆⠀⣣⠔⠃⠀⠀⢀⣣\n");
	printf("\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠔⠊⠀⠈⠒⡡⠊⠀⠀⢠⠞⠁⠉⠀\n");
	printf("\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⡅⠀⠠⠐⠒⠒⣧⣳⢠⠆⡇⠀⠀⠀⠀\n");
	printf("\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢨⡶⠀⢱⠄⠀⠀⠹⠃⠈⢃⠀⠀⠀⠀\n" COLOR_RESET);
}
void imprimir_animacion()
{
	snorlax();
	fflush(stdout);
	sleep(1);
	ejecutar_comando("clear");
	volteon();
	fflush(stdout);
	sleep(1);
	ejecutar_comando("clear");
	bulbassaur();
	fflush(stdout);
	sleep(1);
	ejecutar_comando("clear");
	sableye();
	fflush(stdout);
	sleep(1);
	ejecutar_comando("clear");
}

int main(int argc, char const *argv[])
{
	ejecutar_comando("clear");

	struct pokedex *mi_pokedex = pokedex_crear();
	if (mi_pokedex == NULL) {
		fprintf(stderr, "error al crear pokedex.\n");
		return ERROR;
	}
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/pokedex.csv", ';');
	if (archivo == NULL) {
		pokedex_destruir(mi_pokedex);
		return ERROR;
	}

	bool (*funciones[5])(const char *,
			     void *) = { crear_string_nuevo, crear_string_nuevo,
					 leer_int, leer_int, leer_int };

	char *nombre = NULL;
	char *tipo_str = NULL;
	int fuerza = VALOR_INICIAL;
	int destreza = VALOR_INICIAL;
	int resistencia = VALOR_INICIAL;

	void *punteros[5] = { &nombre, &tipo_str, &fuerza, &destreza,
			      &resistencia };
	struct pokemon pokemon_actual;
	while (leer_linea_csv(archivo, MAX_COLUMNAS, funciones, punteros) ==
	       5) {
		pokemon_actual.nombre = nombre;
		if (tipo_str != NULL) {
			pokemon_actual.tipo = tipo_str[VALOR_INICIAL];
		} else {
			pokemon_actual.tipo = '\0';
		}
		pokemon_actual.fuerza = fuerza;
		pokemon_actual.destreza = destreza;
		pokemon_actual.resistencia = resistencia;
		if (!pokedex_agregar_pokemon(mi_pokedex, pokemon_actual)) {
			fprintf(stderr,
				"error al agregar el pokemon a la pokedex.\n");
		}
		free(nombre);
		free(tipo_str);
		nombre = NULL;
		tipo_str = NULL;
		fuerza = VALOR_INICIAL;
		destreza = VALOR_INICIAL;
		resistencia = VALOR_INICIAL;
	}
	ordenar_pokedex(mi_pokedex);
	imprimir_animacion();
	pokedex_iterar_pokemones(mi_pokedex, imprimir_pokemon, NULL);

	cerrar_archivo_csv(archivo);
	printf(ROJO
	       "\n\n\n\n\t\t\t\tPokemones tipo fuego:" COLOR_RESET ROJO_CHILLON
	       " %i\n\n" COLOR_RESET,
	       contador_fuego);
	printf(AZUL "\t\t\t\tPokemones tipo agua: " COLOR_RESET AZUL_CHILLON
		    "%i\n\n" COLOR_RESET,
	       contador_agua);
	printf(AMARILLO
	       "\t\t\t\tPokemones tipo electrico:" COLOR_RESET AMARILLO_CHILLON
	       " %i\n\n" COLOR_RESET,
	       contador_electrico);
	printf(VERDE "\t\t\t\tPokemones tipo planta:" COLOR_RESET VERDE_CHILLON
		     " %i\n\n" COLOR_RESET,
	       contador_planta);
	printf(CYAN "\t\t\t\tPokemones tipo roca:" COLOR_RESET CYAN_CHILLON
		    " %i\n\n" COLOR_RESET,
	       contador_roca);
	printf(VIOLETA
	       "\t\t\t\tPokemones tipo lucha:" COLOR_RESET VIOLETA_CHILLON
	       " %i\n\n" COLOR_RESET,
	       contador_lucha);
	printf(GRIS "\t\t\t\tPokemones tipo normal:" COLOR_RESET GRIS_CHILLON
		    " %i\n\n" COLOR_RESET,
	       contador_normal);
	printf(VIOLETA_CHILLON "\t\t\t\tPokemones totales: %i\n\n" COLOR_RESET,
	       contador_pokemones);

	pokedex_destruir(mi_pokedex);

	return 0;
}
