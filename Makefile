CC = gcc
CFLAGS = -g -Wall -I. -I./include
LDFLAGS = 
BIN = tstl2cl
LIBBIN = libtstl2cl.a
OBJS = c_algo.o c_function.o c_list.o c_memory.o c_vector.o c_pair.o c_tree.o c_set.o c_map.o test/t_main.o \
	test/t_list.o test/t_vector.o test/t_tree.o test/t_map.o test/t_set.o \
	c_queue.o c_stack.o test/t_queue.o test/t_stack.o c_iterator.o test/t_algo.o

LIBOBJS = c_algo.o c_function.o c_list.o c_memory.o c_vector.o c_pair.o c_tree.o c_set.o c_map.o \
		c_queue.o c_stack.o c_iterator.o 

all:	$(BIN)

$(BIN):	$(OBJS)
	$(CC) $^ -o $@
	
lib: $(LIBOBJS)
	$(AR) rcs $(LIBBIN) $^
	ranlib $(LIBBIN)

clean:
	$(RM) *.o ./test/*.o $(BIN)
