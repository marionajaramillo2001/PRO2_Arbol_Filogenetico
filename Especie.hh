/** @file Especie.hh
    @brief Especificación de la clase Especie
*/

#ifndef _ESPECIE_
#define _ESPECIE_

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <vector>
#endif
using namespace std;


/*
 * Clase Especie
 */

/** @class Especie
    @brief Representa el conjunto de características y operaciones de las especies.

    Ofrece operaciones de consulta de identificador, gen y distancia, de lectura y de escritura.
*/
class Especie {

private:

  /** @brief Identificador de la especie */
  string id;
  /** @brief Gen de la especie */
  string gen;
  /** @brief vector de los kmer de una especie*/
  vector<string> kmer;
  /** @brief Parámetro que sirve para el cálculo de los kmer*/
  int k;

  /** @brief Crea el kmer de una especie
      \pre <em>gen</em> es una secuencias de letras A,C,T,G, k > 0 y <em>kmer</em> vacío
      \post <em>kmer</em> contiene todas las secuencias de k letras del gen <em>gen</em> en orden creciente
  */
  static void crea_kmer(string gen, int k, vector<string>& kmer);


public:

  // Constructoras

  /** @brief Creadora por defecto
      \pre cierto
      \post El resultado es una especie vacía
  */
  Especie();

  /** @brief Creadora de una especie con identificador, gen y parámetro k
      \pre <em>id</em> está formado únicamente por letras minúsculas/mayúsuculas, dígitos y por el carácter de subrayado '_'; <em>gen</em> está formado por una combinació de A,C,G,T; <em>k</em> > 0
      \post El resultado es una especie con id <em>id</em>, gen <em>gen</em> y parámetro <em>k</em>
  */
  Especie(string id, string gen, int k);

  // Consultoras

  /** @brief Consulta el identificador de una especie
      \pre La especie no es vacía
      \post El resultado es el id del parámetro implícito
  */
  string consultar_id() const;

  /** @brief Consulta el gen de una especie
      \pre La especie no es vacía
      \post El resultado es el gen del parámetro implícito
  */
  string consultar_gen() const;

  /** @brief Calcula la distancia entre dos especies
      \pre La especie no es vacía
      \post El resultado es la distancia entre la especie del p.i. y la especie <em>e</em>
  */
  double distancia(const Especie& e) const;

  // Escritura y lectura

  /** @brief Operación de lectura
      \pre Hay preparados en el canal de entrada un string formado exclusivamente por mayúsculas, minúsculas y el carácter de subrayado "_" y otro string que contiene una secuencia de A,C,G,T; k > 0
      \post El parámetro implícito pasa a tener los atributos leídos en el canal estándar de entrada
  */
  void leer(int k);

  /** @brief Operación de escritura
      \pre La especie no es vacía
      \post Se ha escrito el identificador y el gen del parámetro implícito por el canal estándar de salida
  */
  void escribir() const;

};
#endif
