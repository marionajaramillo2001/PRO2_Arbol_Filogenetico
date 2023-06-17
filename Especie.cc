/** @file Especie.cc
    @brief Código de la clase Especie
*/

#include "Especie.hh"
#include <algorithm>


void Especie::crea_kmer(string gen, int k, vector<string>& kmer)
{
  kmer = vector<string> (gen.length()-k+1, string (k,0));
  for (int i = 0; i < kmer.size(); ++i) {
    for (int j = 0; j < k; ++j) {
      kmer[i][j] = gen[i + j];
    }
  }
  sort(kmer.begin(), kmer.end());
}

Especie::Especie() {}

Especie::Especie(string id, string gen, int k)
{
  this->id = id;
  this->gen = gen;
  this->k = k;
  crea_kmer(gen,k,kmer);
}

string Especie::consultar_id() const
{
  return id;
}

string Especie::consultar_gen() const
{
  return gen;
}

double Especie::distancia(const Especie& e) const
{
  vector<string> kmer_p_i = this->kmer;
  vector<string> kmer_e = e.kmer;
  int s1 = kmer_p_i.size();
  int s2 = kmer_e.size();
  int interseccion = 0; //variable que cuenta el cardinal de la intersección de
  // kmer_p_i y kmer_e
  int i = 0;
  int j = 0;
  while (i < s1 and j < s2) {
    if (kmer_p_i[i] == kmer_e[j]) {
      ++interseccion;
      ++i;
      ++j;
    }
    else if (kmer_p_i[i] < kmer_e[j]) ++i;
    else ++j;
  }
  // por el principio de inclusión exclusión, el cardinal de la unión de kmer_p_i
  // y kmer_e es el cardinal de kmer_p_i más el cardinal de kmer_e menos el
  // cardinal de la intersección de ambos. Aunque los kmer pueden contener
  // elementos repetidos, cuando aplicamos el PIE se considera como si fueran
  // distintos, ya que en la práctica, la unión coge el máximo de apariciones de
  // cada elemento entre los dos kmer y la intersección, el mínimo
  double card_union = s1 + s2 - interseccion;
  return (1 - (interseccion/card_union))*100; //retorna la distancia
}

void Especie::leer(int k)
{
  cin >> id >> gen;
  this->k = k;
  crea_kmer(gen,k,kmer);
}

void Especie::escribir() const
{
  cout << id << " " << gen << endl;
}
