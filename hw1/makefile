
all: bin/ut_all

bin/ut_all: test/ut_all.cpp test/ut_file.h test/ut_folder.h test/ut_iterator.h src/file.h src/folder.h src/node.h src/null_iterator.h src/dfs_iterator.h src/iterator.h iterator.o
	mkdir -p bin && g++ -std=c++11 -Wfatal-errors -Wall test/ut_all.cpp obj/iterator.o -o bin/ut_all -lgtest -lpthread

iterator.o: src/iterator.h src/iterator.cpp
	mkdir -p obj && g++ -std=c++11 -c src/iterator.cpp -o obj/iterator.o

clean:
	rm -rf bin obj

dirs:
	mkdir -p bin obj