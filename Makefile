.DEFAULT_GOAL := all

all: ppd

clean:
	rm -rf ppd *.o *.dSYM

ppd: Coin.o Node.o LinkedList.o ReadData.o SaveData.o ppd.o
	g++ -Wall -Werror -std=c++14 -g -O Coin.o Node.o LinkedList.o ReadData.o SaveData.o ppd.o -o ppd

copyfiles:
	cp clean_files/* .

run: copyfiles ppd
	./ppd stock.dat coins.dat