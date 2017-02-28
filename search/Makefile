WORKROOT    = ./

ULIB=$(WORKROOT)/lib2-64
PUBLIC=$(WORKROOT)/public/
VERSION = $(VERSION64_SIGN)
CC = g++ -g  $(VERSION)

BIN=$(WORKROOT)/bin

INC=-I$(PUBLIC)/odict/output/include \
	-I$(ULIB)/libcrf/include \
	-I$(ULIB)/wordseg/ \
	-I$(ULIB)/ullib/include \
	-I$(ULIB)/ccode/include/ \
	-I$(ULIB)/others-ex/include \
	-I$(ULIB)/dict/include 	\
	-I$(ULIB)/jieba/include   \
	-I$(ULIB)/leveldb/include   \
	-I$(WORKROOT)/include 

	#-I$(ULIB)/jsoncpp/ 	\
	
LIB=-L$(ULIB)/wordseg/ -lsegment \
	-L$(ULIB)/bsl/lib -lbsl \
	-L$(ULIB)/libcrf/lib -lcrf \
	-L$(PUBLIC)/odict/output/ -lodict \
	-L$(ULIB)/dict/lib/ -luldict \
	-L$(ULIB)/others-ex/lib/ -lullib_ex \
	-L$(ULIB)/ccode/lib/ -lulccode \
	-L$(ULIB)/ullib/lib/ -lullib \
	-L$(ULIB)/leveldb/lib/  -lleveldb -lsnappy \
	-lcrypto -lm -lz -lpthread -lstdc++ 

	#-L$(ULIB)/jsoncpp/  -ljson \
#	-L./lib2-64/jsoncpp/ -ljson \


#CFLAGS = -g -DLINUX -D_REENTRANT -Wall -O3 -fPIC

CFLAGS = -g -DLINUX -D_REENTRANT -Wall

all : test_seg test_odict

test_seg: src/segment.cpp test/test_seg.cpp
	$(CC) $^ -o $(BIN)/$@ $(INC) $(LIB) $(CFLAGS)

test_odict: test/test_odict.cpp
	$(CC) $^ -o $(BIN)/$@ $(INC) $(LIB) $(CFLAGS)

## test_unit:test/test_unit.cpp indexer.o word_segment.o word_dict.o segment.o

test_unit:test/test_unit.cpp  src/indexer.cpp  src/segment.cpp src/word_dict.cpp src/util.cpp  src/searcher.cpp src/rank.cpp
#test_unit:test/test_unit.cpp  src/indexer.cpp  src/segment.cpp src/word_dict.cpp src/util.cpp  
	$(CC) $^ -o $(BIN)/$@ $(INC) $(LIB) $(CFLAGS)
indexer.o : src/indexer.cpp 
	$(CC) $^ -c $(BIN)/$@ $(INC) $(LIB) $(CFLAGS)
word_segment.o: src/word_segment.cpp 
	$(CC) $^ -c $(BIN)/$@ $(INC) $(LIB) $(CFLAGS)
word_dict.o:  src/word_dict.cpp 
	$(CC) $^ -c $(BIN)/$@ $(INC) $(LIB) $(CFLAGS)
segment.o: src/segment.cpp
	$(CC) $^ -c $(BIN)/$@ $(INC) $(LIB) $(CFLAGS)
searcher.o: src/searcher.cpp
	$(CC) $^ -c $(BIN)/$@ $(INC) $(LIB) $(CFLAGS)
rank.o: src/rank.cpp
	$(CC) $^ -c $(BIN)/$@ $(INC) $(LIB) $(CFLAGS)

clean:
	rm -f $(BIN)/*
