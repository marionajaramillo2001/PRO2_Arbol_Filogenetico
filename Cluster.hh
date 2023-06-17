/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef _CLUSTER_
#define _CLUSTER_

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include "BinTree.hh"
#endif

/*
 * Clase Cluster
 */

/** @class Cluster
    @brief Representa el conjunto de características y operaciones de los clústers.

    Ofrece operaciones de consulta de identificador, de fusión de clústers y de escritura.

*/
class Cluster {

private:

  /** @brief Identificador del clúster */
  string id;
  /** @brief Estructura del clúster. Los elementos del árbolo binario tienen asociados un string, que será el identificador de un clúster, y un double, que será la distancia entre los hijos izquierdo y derecho de dicho elemento o -1 en caso que no tenga hijos */
  BinTree<pair<string, double> > b;

  /** @brief
      \pre El bintree <em>t</em> no está vacío
      \post Se ha escrito por el canal de salida el árbol filogenético asociado al clúster con bintree <em>t</em>, escribiendo también la distancia entre los hijos izquierdo y derecho de cada nodo
  */
  static void escribir_bintree(const BinTree<pair<string,double> >& t);

public:

  // Constructoras

  /** @brief Creadora por defecto
      \pre cierto
      \post El resultado es un clúster vacío, con id vacío y árbol binario vacío
  */
  Cluster();

  /** @brief Creadora de un clúster con una especie
      \pre <em>id</em> está formado únicamente por letras minúsculas/mayúsuculas, dígitos y por el carácter de subrayado '_'
      \post El resultado es un clúster con el identificador <em>id</em>
  */
  Cluster(string id);

  /** @brief Une dos clústers
      \pre El identificador de <em>clus1</em> es más pequeño que el de <em>clus2</em>; los clústers no son vacíos
      \post El resultado es un clúster formado por la unión de <em>clus1</em> y de <em>clus2</em>
  */
  Cluster(Cluster& clus1, Cluster& clus2, double dist);

  // Consultoras

  /** @brief Consulta el identificador del clúster
      \pre El clúster del p.i. no es vacío
      \post El resultado es el identificador del parámetro implícito
  */
  string consultar_id() const;

  // Escritura

  /** @brief Operación de escritura
      \pre El clúster del p.i. no es vacío
      \post Se ha escrito por el canal de salida el árbol filogenético del clúster del p.i., escribiendo también la distancia entre los hijos izquierdo y derecho de cada nodo
  */
  void escribir_cluster() const;
};
#endif
