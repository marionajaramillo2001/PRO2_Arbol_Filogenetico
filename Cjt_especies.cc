/** @file Cjt_especies.cc
    @brief Código de la clase Cjt_especies
*/

#include "Cjt_especies.hh"
#include <algorithm>


Cjt_especies::Cjt_especies(int k)
{
  nesp = 0;
  this->k = k;
}

void Cjt_especies::anadir_especie(const Especie& e)
{
  string id_e = e.consultar_id();
  //añadimos la especie e a la lista de especies
  list<Especie>::iterator it1 = l_esp.begin();
  while (it1 != l_esp.end() and (*it1).consultar_id() < id_e) ++it1;
  l_esp.insert(it1,e);

  //calculamos las distancias entre la especie e y el resto de especies y las
  //insertamos en el mapa dist_e
  list<Especie>::const_iterator it2 = l_esp.begin();
  while ((*it2).consultar_id() != id_e) {
    dist_e[(*it2).consultar_id()][id_e] = e.distancia(*it2);
    ++it2;
  }
  ++it2; //no hace falta calcular la distancia entre la misma especie; ya
  // sabemos que es 0
  while(it2 != l_esp.end()) {
    dist_e[id_e][(*it2).consultar_id()] = e.distancia(*it2);
    ++it2;
  }

  ++nesp;
}

void Cjt_especies::elimina_especie(string id)
{
  list<Especie>::iterator it1 = l_esp.begin();
  while ((*it1).consultar_id() != id) ++it1; //nunca podrá llegar al final de la
  // lista porque sabemos que la especie con el identificador dado existe en el
  // parámetro implícito
  l_esp.erase(it1); //borramos la especie con identificador id de la lista de
  // especies

  --nesp;
}

bool Cjt_especies::existe_especie(string id) const
{
  list<Especie>::const_iterator it = l_esp.begin();
  while (it != l_esp.end() and (*it).consultar_id() != id) ++it;
  return it != l_esp.end();
}

string Cjt_especies::consultar_gen_especie(string id) const
{
  list<Especie>::const_iterator it = l_esp.begin();
  while ((*it).consultar_id() < id) ++it;
  return (*it).consultar_gen(); //se tiene en cuenta que la lista de especies no
  // contiene especies repetidas
}

string Cjt_especies::consultar_iesimo(int i) const
{
  list<Especie>::const_iterator it = l_esp.begin();
  for (int j = 0; j < i; ++j) ++it;
  return (*it).consultar_id();
}

int Cjt_especies::num_especies() const
{
  return nesp;
}

double Cjt_especies::consultar_distancia(const string id1, const string id2) const
{
  return dist_e.at(id1).at(id2); //con el uso de "at" puedo garantizar que el
  // p.i. seguirá constante. No dará nunca error porque el pre de la operación
  // exige que las especies con identificadores <em>id1</em> e <em>id2</em>
  // existan en el p.i
}

bool comp(const Especie& a, const Especie& b) {
    return a.consultar_id() < b.consultar_id();
}

void Cjt_especies::ordena_cjt_especies() {
  l_esp.sort(comp);
}

void Cjt_especies::leer()
{
  cin >> nesp;
  //se insertan las especies en la lista de especies
  Especie aux;
  l_esp.clear();

  for (int i = 0; i < nesp; ++i) {
    aux.leer(k);
    l_esp.insert(l_esp.end(), aux);
  }

  ordena_cjt_especies(); //se ordena la lista de especies por orden creciente de
  // identificador

  //calculamos las distancias entre todas las especies
  dist_e.clear();
  //Las distancias entre especies se pueden calcular dist(especie_i, especie_j)
  // o dist(especie_j, especie_i) por todo i y j donde i != j (cuando i = j la
  // distancia ya sabemos que es cero). Para ahorrarnos cálculos, calcularemos y
  // guardaremos dist(especie_i, especie_j), donde el identificador de la
  // primera especie (i) siempre será más pequeño que el identificador de la 
  // segunda especie (j)
  list<Especie>::const_iterator it1 = l_esp.begin();
  for(int i = 0; i < nesp; ++i) {
    list<Especie>::const_iterator it2 = l_esp.begin();
    for (int h = 0; h <= i; ++h) ++it2;
    for (int j = i + 1; j < nesp; ++j) {
      dist_e[(*it1).consultar_id()][(*it2).consultar_id()] = (*it1).distancia(*it2);
      ++it2;
    }
    ++it1;
  }
}

void Cjt_especies::escribir() const
{
  list<Especie>::const_iterator it = l_esp.begin();
  for (int i = 0; i < nesp; ++i) {
    cout << (*it).consultar_id() << " " << (*it).consultar_gen() << endl;
    ++it;
  }
}

void Cjt_especies::imprimir_tabla_distancias() const
{
  list<Especie>::const_iterator it1 = l_esp.begin();
  for(int i = 0; i < nesp; ++i) {
    cout << (*it1).consultar_id() << ":";
    list<Especie>::const_iterator it2 = l_esp.begin();
    for (int h = 0; h <= i; ++h) ++it2;
    for (int j = i + 1; j < nesp; ++j) {
      cout << " " << (*it2).consultar_id() << " (" << dist_e.at((*it1).consultar_id()).at((*it2).consultar_id()) << ")";
      ++it2;
    }
    cout << endl;
    ++it1;
  }
}
