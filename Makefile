OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Especie.o Cjt_especies.o Cluster.o Cjt_clusters.o
	g++ -o program.exe program.o Especie.o Cjt_especies.o Cluster.o Cjt_clusters.o 

Especie.o: Especie.cc Especie.hh
	g++ -c Especie.cc $(OPCIONS)

Cjt_especies.o: Cjt_especies.cc Especie.hh Cjt_especies.hh
	g++ -c Cjt_especies.cc $(OPCIONS)

Cluster.o: Cluster.cc Cluster.hh 
	g++ -c Cluster.cc $(OPCIONS)

Cjt_clusters.o: Cjt_clusters.cc Cjt_clusters.hh Cluster.hh Cjt_especies.hh
	g++ -c Cjt_clusters.cc $(OPCIONS)

program.o: program.cc Especie.hh Cjt_especies.hh Cjt_clusters.hh
	g++ -c program.cc $(OPCIONS)

clean:
	rm -f *.o
	rm -f *.exe
tar:
	tar -cvf program.tar program.cc Especie.hh Especie.cc Cjt_especies.hh Cjt_especies.cc Cluster.hh Cluster.cc Cjt_clusters.hh Cjt_clusters.cc html.zip Makefile 