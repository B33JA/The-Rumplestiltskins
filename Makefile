.DEFAULT_GOAL := all

all: ppd

clean:
	rm -rf ppd *.o *.dSYM

ppd: Coin.o Node.o LinkedList.o ReadData.o SaveData.o ppd.o
	g++ -Wall -Werror -std=c++14 -g -O Coin.o Node.o LinkedList.o ReadData.o SaveData.o ppd.o -o ppd

copyfiles:
	cp clean_files/* .

#Thoroughly test each aspect of program; each test case tests multiple aspects (saving, reading, logic)

#Purchase I0001 with $2, $3 (error), $5 (give change) then save
testpurchase: copyfiles ppd
	./ppd stock.dat coins.dat < tests/testpurchase.input > tests/testpurchase.actual_ppd_out
	 diff -w -y tests/testpurchase.expcoins coins.dat
#	 diff -w tests/testpurchase.output tests/testpurchase.actual_ppd_out
	
#Purchase I0005 with $10x 5c coins, cancel transaction then save
testcancelpurchase: copyfiles ppd
	./ppd stock.dat coins.dat < tests/testcancelpurchase.input > tests/testcancelpurchase.actual_ppd_out
	 diff -w -y tests/testcancelpurchase.expcoins coins.dat
#	 diff -w tests/testcancelpurchase.output tests/testcancelpurchase.actual_ppd_out

#Purchase I0005 4x times with $5. This cases the 20c coin in the register to run out & cancel the transaction.
testnochange: copyfiles ppd
	./ppd stock.dat coins.dat < tests/testnochange.input > tests/testnochange.actual_ppd_out
	 diff -w -y tests/testnochange.expcoins coins.dat
	 diff -w tests/testnochange.expstock stock.dat
#	 diff -w tests/testnochange.output tests/testnochange.actual_ppd_out

#Purchase 1x of each item, reset stock. Final stock should be identical to initial stock.
testresetstock: copyfiles ppd
	./ppd stock.dat coins.dat < tests/testresetstock.input > tests/testresetstock.actual_ppd_out
	 diff -w tests/testresetstock.expstock stock.dat
#	 diff -w tests/testresetstock.output tests/testresetstock.actual_ppd_out

#Remove I0002, attempt to buy (fail), then save. Expstock should be missing the I0002 entry completely.
testremoveitem: copyfiles ppd
	./ppd stock.dat coins.dat < tests/testremoveitem.input > tests/testremoveitem.actual_ppd_out
	 diff -w tests/testremoveitem.expstock stock.dat
#	 diff -w tests/testremoveitem.output tests/testremoveitem.actual_ppd_out

#mis-spell coinfile, as if it was deleted/missing
testmissingcoinfile: copyfiles ppd
	./ppd stock.dat coinz.dat < tests/testmissingcoinfile.input > tests/testmissingcoinfile.actual_ppd_out
	 diff -w tests/testmissingcoinfile.output tests/testmissingcoinfile.actual_ppd_out

#testall: testpurchase testcancelpurchase testnochange testresetstock testremoveitem testmissingcoinfile

run: copyfiles ppd
	./ppd stock.dat coins.dat