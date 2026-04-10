#include "pa2m.h"
#include <stdbool.h>
#include <string.h>
#include "src/csv.h"
#include "src/pokedex.h"

// Declarar la función de verificación fuera de otras funciones
bool verificar_columna(const char *columna, void *ctx)
{
	return true;
}

void abrirUnArchivoInexistenteDebeRetornarNull()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("noexiste/noexiste/noexiste/no", ';');
	pa2m_afirmar(archivo == NULL, "El archivo no existe y se retorna NULL");
}

void leer_archivo_vacio_retorna_cero()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/vacio.csv", ';');
	pa2m_afirmar(archivo != NULL, "se abre un archivo vacio");
	size_t leidos = leer_linea_csv(archivo, 0, NULL, NULL);
	pa2m_afirmar(leidos == 0, "se lee y se retornan 0 columnas");
	cerrar_archivo_csv(archivo);
}

void abrir_archivo_existente()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/pokedex.csv", ';');
	pa2m_afirmar(archivo != NULL, "se abre un archivo existente");
	cerrar_archivo_csv(archivo);
}

void leer_caracter_especial()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("ejemplos/especiales.csv", ',');
	pa2m_afirmar(archivo != NULL,
		     "se abre el archivo con caracteres especiales");
	bool (*funciones[3])(const char *, void *) = { verificar_columna,
						       verificar_columna,
						       verificar_columna };
	void *ctx[3] = { NULL, NULL, NULL };
	size_t columnas;
	columnas = leer_linea_csv(archivo, 3, funciones, ctx);
	pa2m_afirmar(columnas == 3, "tiene 5 columnas");
	cerrar_archivo_csv(archivo);
}

void crear_pokedex()
{
	struct pokedex *pokedex = pokedex_crear();
	pa2m_afirmar(pokedex != NULL, "se crea pokedex");
	pokedex_destruir(pokedex);
}

void agregar_pokemon_duplicado()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon = { "Emolga", TIPO_ELECTRICO, 35, 55, 40 };
	bool agregado1 = pokedex_agregar_pokemon(pokedex, pokemon);
	pa2m_afirmar(agregado1, "se agrega el primer Emolga");
	bool agregado2 = pokedex_agregar_pokemon(pokedex, pokemon);
	pa2m_afirmar(agregado2, "no se debe agregar el segundo Emolga");
	pokedex_destruir(pokedex);
}

void busqueda_pokemon_inexistente()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon = { "Ditto", TIPO_NORMAL, 35, 55, 40 };
	pokedex_agregar_pokemon(pokedex, pokemon);

	const struct pokemon *pokemon_encontrado =
		pokedex_buscar_pokemon(pokedex, "Skityy");
	pa2m_afirmar(pokemon_encontrado == NULL,
		     "no se encuentra un pokemon que no existe");

	pokedex_destruir(pokedex);
}
void busqueda_pokedex_vacia()
{
	struct pokedex *pokedex = pokedex_crear();
	const struct pokemon *pokemon_encontrado =
		pokedex_buscar_pokemon(pokedex, "Cacuna");
	pa2m_afirmar(pokemon_encontrado == NULL,
		     "no se encuentra un pokemon en una pokedex vacia");

	pokedex_destruir(pokedex);
}

void destruir_pokedex_pokemones()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemons[] = { { "Emolga", TIPO_NORMAL, 45, 49, 49 },
				      { "Chikorita", TIPO_ELECTRICO, 39, 52,
					43 } };

	for (size_t i = 0; i < sizeof(pokemons) / sizeof(pokemons[0]); i++) {
		pokedex_agregar_pokemon(pokedex, pokemons[i]);
	}

	pokedex_destruir(pokedex);

	pa2m_afirmar(true,
		     "se destruye pokedex con pokemones sin memory leaks");
}

void destruir_pokedex()
{
	struct pokedex *pokedex = pokedex_crear();

	struct pokedex *pokedex_destruido = pokedex;

	pokedex_destruir(pokedex);

	pokedex = NULL;

	pa2m_afirmar(pokedex == NULL, "se destruye una pokedex");

	pa2m_afirmar(pokedex_destruido != NULL,
		     "el puntero original no debe ser NULL");
}
void agregar_pokemon_cantidad()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemons[] = { { "Mewtwo", TIPO_NORMAL, 45, 49, 49 },
				      { "Magikarp", TIPO_AGUA, 39, 52, 43 },
				      { "Psyduck", TIPO_AGUA, 44, 48, 65 } };

	for (size_t i = 0; i < sizeof(pokemons) / sizeof(pokemons[0]); i++) {
		pokedex_agregar_pokemon(pokedex, pokemons[i]);
	}

	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 3,
		     "la cantidad de pokemoens en la pokedex es correcta");

	pokedex_destruir(pokedex);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de archivos CSV");
	abrirUnArchivoInexistenteDebeRetornarNull();
	leer_archivo_vacio_retorna_cero();
	abrir_archivo_existente();
	leer_caracter_especial();

	pa2m_nuevo_grupo("Pruebas de pokedex");
	crear_pokedex();
	agregar_pokemon_duplicado();
	agregar_pokemon_cantidad();
	busqueda_pokemon_inexistente();
	busqueda_pokedex_vacia();
	destruir_pokedex_pokemones();
	destruir_pokedex();
	return pa2m_mostrar_reporte();
}
