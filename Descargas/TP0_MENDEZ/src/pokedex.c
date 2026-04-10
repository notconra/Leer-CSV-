#include "pokedex.h"
#include <string.h>
#define MAX_POKEMONES 100
const int MISMO_NOMBRE = 0;
const int MISMO_TIPO = 0;
const int SIGUIENTE = 1;
int comparar_pokemones(const struct pokemon *pokemon_1,
		       const struct pokemon *pokemon_2);

struct pokedex {
	struct pokemon *pokemones;
	size_t cantidad_pokemones;
};

struct pokedex *pokedex_crear()
{
	struct pokedex *pokedex = malloc(sizeof(struct pokedex));

	pokedex->pokemones = malloc(sizeof(struct pokemon) * MAX_POKEMONES);
	if (!pokedex->pokemones || !pokedex) {
		free(pokedex);
		return NULL;
	}
	pokedex->cantidad_pokemones = 0;
	return pokedex;
}

void ordenar_pokedex(struct pokedex *pokedex)
{
	for (size_t i = 0; i < pokedex->cantidad_pokemones - 1; i++) {
		for (size_t j = 0; j < pokedex->cantidad_pokemones - 1 - i;
		     j++) {
			if (comparar_pokemones(&pokedex->pokemones[j],
					       &pokedex->pokemones[j + 1]) >
			    0) {
				struct pokemon temp = pokedex->pokemones[j];
				pokedex->pokemones[j] =
					pokedex->pokemones[j + 1];
				pokedex->pokemones[j + 1] = temp;
			}
		}
	}
}

int comparar_pokemones(const struct pokemon *pokemon_1,
		       const struct pokemon *pokemon_2)
{
	if (!pokemon_1 || !pokemon_2 || !pokemon_1->nombre ||
	    !pokemon_2->nombre) {
		return 0;
	}

	int comparacion = strcmp(pokemon_1->nombre, pokemon_2->nombre);
	if (comparacion == MISMO_NOMBRE) {
		if (pokemon_1->tipo != pokemon_2->tipo) {
			comparacion = pokemon_1->tipo - pokemon_2->tipo;
		} else {
			if (pokemon_1->fuerza != pokemon_2->fuerza) {
				comparacion =
					pokemon_1->fuerza - pokemon_2->fuerza;
			} else {
				if (pokemon_1->destreza !=
				    pokemon_2->destreza) {
					comparacion = pokemon_1->destreza -
						      pokemon_2->destreza;
				} else {
					comparacion = pokemon_1->resistencia -
						      pokemon_2->resistencia;
				}
			}
		}
	}
	return comparacion;
}

bool pokedex_agregar_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	if (!pokedex || !pokemon.nombre ||
	    (pokedex->cantidad_pokemones >= MAX_POKEMONES)) {
		return false;
	}
	char *nombre = malloc(strlen(pokemon.nombre) + 1);
	if (!nombre) {
		return false;
	}
	strcpy(nombre, pokemon.nombre);
	struct pokemon nuevo_pokemon = pokemon;
	nuevo_pokemon.nombre = nombre;
	pokedex->pokemones[pokedex->cantidad_pokemones] = nuevo_pokemon;
	pokedex->cantidad_pokemones++;
	ordenar_pokedex(pokedex);

	return true;
}

size_t pokedex_cantidad_pokemones(struct pokedex *pokedex)
{
	if (!pokedex) {
		return 0;
	}
	size_t cantidad = pokedex->cantidad_pokemones;
	return cantidad;
}

const struct pokemon *pokedex_buscar_pokemon(struct pokedex *pokedex,
					     const char *nombre)
{
	if (!pokedex || !nombre) {
		return NULL;
	}
	for (size_t i = 0; i < pokedex->cantidad_pokemones; i++) {
		if (strcmp(pokedex->pokemones[i].nombre, nombre) ==
		    MISMO_NOMBRE) {
			return &pokedex->pokemones[i];
		}
	}
	return NULL;
}

size_t pokedex_iterar_pokemones(struct pokedex *pokedex,
				bool (*funcion)(struct pokemon *, void *),
				void *ctx)
{
	if (!pokedex || !funcion) {
		return 0;
	}

	size_t pokemones_iterados = 0;
	bool es_posible_continuar = true;

	for (size_t i = 0;
	     i < pokedex->cantidad_pokemones && es_posible_continuar; i++) {
		es_posible_continuar = funcion(&pokedex->pokemones[i], ctx);

		if (es_posible_continuar) {
			pokemones_iterados++;
		} else {
			return pokemones_iterados + 1;
		}
	}

	return pokemones_iterados;
}

void pokedex_destruir(struct pokedex *pokedex)
{
	if (!pokedex) {
		return;
	}
	for (size_t i = 0; i < pokedex->cantidad_pokemones; i++) {
		free(pokedex->pokemones[i].nombre);
	}
	free(pokedex->pokemones);
	free(pokedex);
}