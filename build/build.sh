rm ../bin/*.o ../bin/*.out

gcc -Wall -o ../bin/basic.o -c ../src/basic.c

gcc -Wall -o ../bin/string.o -c ../src/string.c

gcc -Wall -o ../bin/data.o -c ../src/data.c

gcc -Wall -o ../bin/list.o -c ../src/list.c

gcc -Wall -o ../bin/node.o -c ../src/node.c

gcc -Wall -o ../bin/linked_list.o -c ../src/linked_list.c

gcc -Wall -o ../bin/stack.o -c ../src/stack.c

gcc -Wall -o ../bin/queue.o -c ../src/queue.c

gcc -Wall -o ../bin/tree.o -c ../src/tree.c

gcc -Wall -o ../bin/parse.o -c ../src/parse.c