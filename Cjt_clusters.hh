/** @file Cjt_clusters.hh
    @brief Especificación de la clase Cjt_clusters
*/

#ifndef _CJT_CLUSTERS_
#define _CJT_CLUSTERS_

#include "Cluster.hh"
#include "Cjt_especies.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <list>
#include <string>
#endif

/*
 * Clase Cjt_clusters
 */

/** @class Cjt_clusters
    @brief Guarda la información de un conjunto de clústers y permite operar con dicho conjunto.

    Sus operaciones son las modificadoras del conjunto, inicializando un conjunto de clústers, ejecutando un paso del algoritmo WPGMA o aplicando WPGMA, las consultoras de la existencia de un clúster y del número total de clústers que hay en el conjunto y las de escritura, ya sea de los clústers del conjunto (y en particular, del árbol filogenético), o de la distancia presente entre ellos. */

class Cjt_clusters {

private:

  /** @brief Lista de todos los clústers que constituyen el conjunto de clústers ordenada crecientemente por los identificadores de los clústers. No contiene clústers con el mismo identificador. */
  list<Cluster> l_clus;
  /** @brief Número de clústers que hay en el conjunto de clústers */
  int nclus;
  /** @brief Mapa de un mapa que permite asociar a dos clústers un entero, el cual será la distancia entre estos dos clústers */
  map<string, map<string,double> > dist_clus;

public:

  // Constructoras

  /** @brief Creadora por defecto
      \pre cierto
      \post El resultado es un conjunto de clústers vacío
  */
  Cjt_clusters();

  // Modificadoras

  /** @brief Inicializa los clústers
      \pre cierto
      \post Borra los clústers del conjunto de clústers del parámetro implícito para inicializarlo con clústers que contendrán cada uno una especie del conjunto de especies <em>c_e</em>; los clústers están ordenados crecientmente por el identificador de cada clúster
  */
  void inicializa_clusters(const Cjt_especies& c_e);


  /** @brief Ejecuta un paso del algoritmo WPGMA
      \pre (número de clústers del p.i.) > 1
      \post Fusiona los dos clústers a menos distancia en uno nuevo y los elimina; los clústers siguen ordenados crecientmente por el identificador de cada clúster
  */
  void ejecuta_paso_wpgma();

  /** @brief Ejecuta el algoritmo WPGMA
      \pre cierto
      \post Fusiona los dos clústers a menos distancia en uno nuevo y los elimina. Hace este proceso repetidamente hasta que el
      conjunto de clústers tiene solamente un clúster, el cual será el árbol filogenético. Retorna el id del clúster resultante
  */
  void aplicar_wpgma();


  // Consultoras

  /** @brief Consulta si un clúster está en el parámetro implícito
      \pre cierto
      \post El resultado indica si existe el clúster con el identificador <em>id</em> en el parámetro implícito
  */
  bool existe_cluster(string id) const;

  /** @brief Consultora del número de clústers
      \pre cierto
      \post El resultado es el número de clústers que hay en el parámetro implícito
  */
  int num_clusters() const;

  // Escritura

  /** @brief Operación de escritura
      \pre El clúster con identificador <em>id</em> existe en el conjunto de clústers
      \post Se imprime el clúster que tiene identificador <em>id</em> del parámetro implícito
  */
  void escribir_cluster(string id) const;

  /** @brief Operación de escritura de la tabla de distancias entre clústers
      \pre cierto
      \post Se imprime la tabla de distancias entre cada par de clústers del parámetro implícito en el canal estándar de salida
  */
  void imprimir_tabla_distancias() const;

};
#endif
