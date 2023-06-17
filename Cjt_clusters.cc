/** @file Cjt_clusters.cc
    @brief Código de la clase Cjt_clusters
*/

#include "Cjt_clusters.hh"

Cjt_clusters::Cjt_clusters()
{
  nclus = 0;
}

void Cjt_clusters::inicializa_clusters(const Cjt_especies& c_e)
{
  l_clus.clear();
  dist_clus.clear();
  nclus = 0;

  for (int i = 0; i < c_e.num_especies(); ++i) {
    Cluster c(c_e.consultar_iesimo(i));
    l_clus.insert(l_clus.end(),c);
    ++nclus;
  }

  list<Cluster>::const_iterator it1 = l_clus.begin();

  for(int i = 0; i < nclus; ++i) {
    list<Cluster>::const_iterator it2 = l_clus.begin();
    for (int h = 0; h <= i; ++h) ++it2;
    for (int j = i + 1; j < nclus; ++j) {
      dist_clus[(*it1).consultar_id()][(*it2).consultar_id()] = c_e.consultar_distancia((*it1).consultar_id(),(*it2).consultar_id());
      ++it2;
    }
    ++it1;
  }
}

void Cjt_clusters::ejecuta_paso_wpgma()
{
  //se mira cuáles son los clústers que están a menor distancia
  double dist_min = 101; //el intervalo en el cual está definida la distancia es
  // [0,100]. Si inicializamos dist_min = 101, la primera pareja de clústers
  // consultada se convertirá en la que está a distancia mínima, haciendo que
  // dist_min tome valores dentro del intervalo en el cual está definidio
  string id1_min;
  string id2_min;

  list<Cluster>::const_iterator it1 = l_clus.begin();
  for (int i = 0; i < nclus; ++i) {
    list<Cluster>::const_iterator it2 = l_clus.begin();
    for (int h = 0; h <= i; ++h) ++it2;
    for (int j = i + 1; j < nclus; ++j) {
      if (dist_clus.at((*it1).consultar_id()).at((*it2).consultar_id()) < dist_min) {
        //no se mira qué combinación de identificadores da un identificador más
        // pequeño cuando las distancias entre dos clústers coincidan porque de
        // la manera como se recorre la lista, nunca una combinación de
        // identificadores será más pequeña que una combinación considerada anteriormente
        id1_min = (*it1).consultar_id();
        id2_min = (*it2).consultar_id();
        dist_min = dist_clus.at(id1_min).at(id2_min);
      }
      ++it2;
    }
    ++it1;
  }

  list<Cluster>::iterator it3 = l_clus.begin();
  list<Cluster>::iterator it4 = l_clus.begin();
  //it3 e it4 referencian los clústers con identificadores id1_min e id2_min respectivamente
  while (it3 != l_clus.end() and (*it3).consultar_id() < id1_min) ++it3;
  while (it4 != l_clus.end() and (*it4).consultar_id() < id2_min) ++it4;

  Cluster c(*it3,*it4,(dist_clus[(*it3).consultar_id()][(*it4).consultar_id()])/2);
  // se cumple la precondición de esta operación porque el identificador de
  // id1_min siempre será menor al de id2_min tal como se han consultado los datos

  // se añade el nuevo clúster a la lista de clústers. El identificador del nuevo clúster empezará por el identificador del clúster más pequeño, que, en este caso, será id1_min por la manera como se han consultado las distancias. Entonces, se deberá añadir a la posición que ocupaba el clúster con identificador id1_min, esto es, delante de la posición que señala it3

  string id_c = c.consultar_id();

  l_clus.insert(it3, c); //it3 sigue referenciando id1_min

  // se eliminan los clústers que tenían id1_min e id2_min de la lista de clústers
  l_clus.erase(it3);
  l_clus.erase(it4);

  --nclus;

  list<Cluster>::const_iterator it5 = l_clus.begin();
  while (it5 != l_clus.end()) {
    string id_it5 = (*it5).consultar_id();
    if (id_it5 < id_c) {
      dist_clus[id_it5][id_c] = (dist_clus.at(id_it5).at(id1_min) + dist_clus.at(id_it5).at(id2_min))/2;
    }
    else if (id_c < id_it5){
      if (id_it5 < id2_min) dist_clus[id_c][id_it5] = (dist_clus.at(id1_min).at(id_it5) + dist_clus.at(id_it5).at(id2_min))/2;
      else dist_clus[id_c][id_it5] = (dist_clus.at(id1_min).at(id_it5) + dist_clus.at(id2_min).at(id_it5))/2;
    }
    ++it5;
  }
}


void Cjt_clusters::aplicar_wpgma()
{
  while (nclus > 1) ejecuta_paso_wpgma();
  (*l_clus.begin()).escribir_cluster();
  cout << endl;
}

bool Cjt_clusters::existe_cluster(string id) const
{
  list<Cluster>::const_iterator it = l_clus.begin();
  while (it != l_clus.end() and (*it).consultar_id() != id) ++it;
  return it != l_clus.end();
}

int Cjt_clusters::num_clusters() const
{
  return nclus;
}

void Cjt_clusters::escribir_cluster(string id) const
{
  list<Cluster>::const_iterator it = l_clus.begin();
  while (it != l_clus.end() and (*it).consultar_id() != id) ++it;
  (*it).escribir_cluster();
  cout << endl;
}

void Cjt_clusters::imprimir_tabla_distancias() const
{
  list<Cluster>::const_iterator it1 = l_clus.begin();
  for(int i = 0; i < nclus; ++i) {
    cout << (*it1).consultar_id() << ":";
    list<Cluster>::const_iterator it2 = l_clus.begin();
    for (int h = 0; h <= i; ++h) ++it2;
    for (int j = i + 1; j < nclus; ++j) {
      cout << " " << (*it2).consultar_id() << " (" << dist_clus.at((*it1).consultar_id()).at((*it2).consultar_id()) << ")";
      ++it2;
    }
    cout << endl;
    ++it1;
  }
}
