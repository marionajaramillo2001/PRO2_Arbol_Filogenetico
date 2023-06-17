/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"


Cluster::Cluster() {}

Cluster::Cluster(string id)
{
  this->id = id;
  pair<string,double> c (id,-1);
  b = BinTree<pair<string,double> > (c);
}

Cluster::Cluster(Cluster& clus1, Cluster& clus2, double dist)
{
  id = clus1.consultar_id() + clus2.consultar_id();
  b = BinTree<pair<string,double> > (pair<string,double> (id,dist), clus1.b, clus2.b);

}

string Cluster::consultar_id () const
{
  return id;
}

void Cluster::escribir_bintree(const BinTree<pair<string,double> >& t)
{
  if (t.value().second == -1) cout << "[" << t.value().first << "]";
  else {
    cout << "[(" << t.value().first << ", " << t.value().second << ") ";
    escribir_bintree(t.left());
    escribir_bintree(t.right());
    cout << "]";
  }
}

void Cluster::escribir_cluster() const
{
  escribir_bintree(b);
}
