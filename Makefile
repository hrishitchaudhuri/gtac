TARGET_LIST := bin/fleury bin/wpc bin/tarjan bin/boruvka bin/revdel bin/fordfulk

UTILS_WO_DS := src/utils/graph.c src/utils/fileread.c
UTILS_W_DS := $(UTILS_WO_DS) src/utils/disjoint_set.c

all: $(TARGET_LIST)

bin/fleury: src/fleury.c $(UTILS_WO_DS)
	gcc -g $^ -o $@

bin/wpc: src/welsh_powell.c $(UTILS_WO_DS)
	gcc -g $^ -o $@

bin/tarjan: src/tarjan.c $(UTILS_WO_DS)
	gcc -g $^ -o $@

bin/boruvka: src/boruvka.c $(UTILS_W_DS)
	gcc -g $^ -o $@

bin/revdel: src/reverse_delete.c $(UTILS_W_DS)
	gcc -g $^ -o $@

bin/fordfulk: src/fordfulkerson.c $(UTILS_WO_DS)
	gcc -g $^ -o $@



clean:
	rm $(TARGET_LIST)