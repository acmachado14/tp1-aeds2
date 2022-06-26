compile:
	gcc src/main.c src/hash/tabelaHash.c src/indice/indiceInvertido.c src/relevancia/relevancia.c src/arquivo/manipulacaoArquivo.c src/tree/patricia.c -lm -o exefile

run:
	./exefile