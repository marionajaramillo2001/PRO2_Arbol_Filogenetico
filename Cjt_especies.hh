/** @file Cjt_especies.hh
    @brief Especificación de la clase Cjt_especies
*/

#ifndef _CJT_ESPECIES_
#define _CJT_ESPECIES_

#include "Especie.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <list>
#include <string>
#endif

/*
 * Clase Cjt_especies
 */

/** @class Cjt_especies
    @brief Guarda la información de un conjunto de especies y permite operar con dicho conjunto.

    Sus operaciones son las modificadoras del conjunto, añadiendo o eliminando especies de él, las consultoras de la existencia de una especie, de su información y del número total de especies que hay en el conjunto, la de lectura y las de escritura, ya sea de las especies del conjunto, o de la distancia presente entre ellas.
*/

class Cjt_especies {

private:

  /** @brief Lista de todas las especies que constituyen el conjunto de especies ordenada crecientemente por los identificadores de las especies. No contiene especies con el mismo identificador. */
  list<Especie> l_esp;
  /** @brief Número de especies que hay en el conjunto de especies */
  int nesp;
  /** @brief Mapa de un mapa que permite asociar a dos especies un double, el cual será la distancia entre estas dos especies*/
  map<string, map<string,double> > dist_e;
  /** @brief Parámetro que sirve para el cálculo de todas las distancias entre pares de especies*/
  int k;

  /** @brief Ordena un conjunto de especies
      \pre cierto
      \post El conjunto de especies del p.i. está ordenado crecientemente por identificador
  */
  void ordena_cjt_especies();

public:

  // Constructora

  /** @brief Creadora por defecto
      \pre cierto
      \post El resultado es un conjunto de especies vacío con parámetro <em>k</em>
  */
  Cjt_especies(int k);

  // Modificadoras

  /** @brief Añade una especie al parámetro implícito
      \pre El parámetro implícito no contiene ninguna especie con el identificador de <em>e</em>
      \post Añade la especie <em>e</em> al parámetro implícito; las especies siguen ordenadas crecientmente por el identificador de cada especie
  */
  void anadir_especie(const Especie& e);

  /** @brief Elimina la especie con el identificador dado
      \pre El parámetro implícito contiene una especie con el identificador <em>id</em>
      \post Elimina la especie con el identificador <em>id</em> del parámetro implícito
  */
  void elimina_especie(string id);

  // Consultoras

  /** @brief Consulta si una especie está en el parámetro implícito
      \pre cierto
      \post El resultado indica si existe la especie con el identificador <em>id</em> en el parámetro implícito
  */
  bool existe_especie(string id) const;

  /** @brief Proporciona el gen de la especie con un cierto identificador del parámetro implícito
      \pre existe una especie en el parámetro implícito con identificador <em>id</em>
      \post El resultado es el gen de la especie con identificador <em>id</em> que contiene el parámetro implícito
  */
  string consultar_gen_especie(string id) const;

  /** @brief Proporciona el identificador de la especie que se encuentra en posición <em>i</em>-ésima en el conjunto de especies
      \pre 0 < <em>i</em> < tamaño del conjunto de especies del parámetro implícito
      \post El resultado es el identificador de la especie que se encuentra en posición <em>i</em>-ésima en el conjunto de especies
  */
  string consultar_iesimo(int i) const;

  /** @brief Consultora del número de especies
      \pre cierto
      \post El resultado es el número de especies que hay en el parámetro implícito
  */
  int num_especies() const;

  /** @brief Consultora de la distancia entre dos especies
      \pre <em>id1</em> < <em>id2</em>; las especies con identificadores <em>id1</em> e <em>id2</em> existen en el p.i.
      \post El resultado es la distancia entre las especies con identificadores <em>id1</em> e <em>id2</em>
  */
  double consultar_distancia(string id1, string id2) const;

  // Lectura/ Escritura

  /** @brief Operación de lectura
      \pre en el canal estándar de entrada hay preparados un entero n que representa el número de especies que leeremos, y los datos de estas especies
      \post El parámetro implícito contiene el conjunto de especies leídas en el canal estándar de entrada, elimnando las especies anteriores que pudiera haber en el parámetro implícito, ordenadas crecientemente por el identificador de cada especie
  */
  void leer();

  /** @brief Operación de escritura de especies
      \pre cierto
      \post Se han escrito por el canal de salida las especies del parámetro implícito por orden creciente de identificador de especie
  */
  void escribir() const;

  /** @brief Operación de escritura de la tabla de distancias entre especies
      \pre cierto
      \post Se imprime la tabla de distancias entre cada par de especies del parámetro implícito en el canal estándar de salida
  */
  void imprimir_tabla_distancias() const;

};
#endif
