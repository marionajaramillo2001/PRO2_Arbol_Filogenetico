/** @mainpage

    El programa principal se encuentra en el módulo main.cc.
    Atendiendo a los tipos de datos sugeridos en el enunciado, necesitaremos un módulo para representar las especies y otro para los clústers. Además, también serán necesarios los módulos Cjt_especies y Cjt_clusters para guardar especies y clústers y poder trabajar con ellos.

*/

/** @file main.cc

    @brief Programa principal

    Estamos suponiendo que los datos leídos siempre son correctos, ya que
    no incluímos comprobaciones al respecto.
*/

#include "Especie.hh"
#include "Cjt_especies.hh"
#include "Cjt_clusters.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#endif

int main()
{
  int k;
  cin >> k;
  Cjt_especies c_e(k);
  Cjt_clusters c_c;

  string op; // Código de operación
  bool fin = false;

  while(not fin and cin >> op) {
    if (op == "crea_especie") { //crea_especie
      Especie e;
      e.leer(k);
      cout << "# " << op << " " << e.consultar_id() << " " << e.consultar_gen() << endl;
      if (c_e.existe_especie(e.consultar_id())) {
        cout << "ERROR: La especie " << e.consultar_id() << " ya existe." << endl;
      }
      else {
        c_e.anadir_especie(e);
      }
      cout << endl;
    }

    else if (op == "obtener_gen") { //obtener_gen
      string id;
      cin >> id;
      cout << "# " << op << " " << id << endl;
      if (c_e.existe_especie(id)) {
        cout << c_e.consultar_gen_especie(id) << endl;
      }
      else {
        cout << "ERROR: La especie " << id << " no existe." << endl;
      }
      cout << endl;
    }

    else if (op == "distancia") { //distancia
      string id1, id2;
      cin >> id1 >> id2;
      cout << "# " << op << " " << id1 << " " << id2 << endl;
      bool existe_id1 = c_e.existe_especie(id1);
      bool existe_id2 = c_e.existe_especie(id2);
      if (existe_id1 and existe_id2) {
        if (id1 < id2) cout << c_e.consultar_distancia(id1, id2) << endl;
        else cout << c_e.consultar_distancia(id2, id1) << endl;
      }
      else if ((not existe_id1) and (not existe_id2)) cout << "ERROR: La especie " << id1 << " y la especie " << id2 << " no existen." << endl;
      else if (not existe_id1) cout << "ERROR: La especie " << id1 << " no existe." << endl;
      else cout << "ERROR: La especie " << id2 << " no existe." << endl;
      cout << endl;
    }

    else if (op == "elimina_especie") { //elimina_especie
      string id;
      cin >> id;
      cout << "# " << op << " " << id << endl;
      if (c_e.existe_especie(id)) {
        c_e.elimina_especie(id);
      }
      else {
        cout << "ERROR: La especie " << id << " no existe." << endl;
      }
      cout << endl;
    }

    else if (op == "existe_especie") { //existe_especie
      string id;
      cin >> id;
      cout << "# " << op << " " << id << endl;
      if (c_e.existe_especie(id)) cout << "SI" << endl;
      else cout << "NO" << endl;
      cout << endl;
    }

    else if (op == "lee_cjt_especies") { //lee_cjt_especies
      cout << "# " << op << endl;
      c_e.leer();
      cout << endl;
    }

    else if (op == "imprime_cjt_especies") { //imprime_cjt_especies
      cout << "# " << op << endl;
      c_e.escribir();
      cout << endl;
    }

    else if (op == "tabla_distancias") { //tabla_distancias
      cout << "# " << op << endl;
      c_e.imprimir_tabla_distancias();
      cout << endl;
    }

    else if (op == "inicializa_clusters") { //inicializa_clústers
      cout << "# " << op << endl;
      c_c.inicializa_clusters(c_e);
      c_c.imprimir_tabla_distancias();
      cout << endl;
    }

    else if (op == "ejecuta_paso_wpgma") { //ejecuta_paso_wpgma
      cout << "# " << op << endl;
      if (c_c.num_clusters() <= 1) {
        cout << "ERROR: num_clusters <= 1" << endl;
      }
      else {
        c_c.ejecuta_paso_wpgma();
        c_c.imprimir_tabla_distancias();
      }
      cout << endl;
    }

    else if (op == "imprime_cluster") { //imprime_clúster
      string id;
      cin >> id;
      cout << "# " << op << " " << id << endl;
      if (c_c.existe_cluster(id)) {
        c_c.escribir_cluster(id);
      }
      else cout << "ERROR: El cluster " << id << " no existe." << endl;
      cout << endl;
    }

    else if (op == "imprime_arbol_filogenetico") { //imprime_árbol_filogenético
      cout << "# " << op << endl;
      c_c.inicializa_clusters(c_e);
      if (c_e.num_especies() == 0) {
        cout << "ERROR: El conjunto de clusters es vacio." << endl;
      }
      else {
        c_c.aplicar_wpgma();
      }
      cout << endl;
    }

    else if (op == "fin"){ //fin
      fin = true;
    }

  }
}
