compile:
	gcc src/main.c src/hash/tabelaHash.c src/hash/indiceInvertido.c src/hash/relevancia.c src/arquivo/manipulacaoArquivo.c src/tree/patricia.c -o exefile

run:
	./exefile