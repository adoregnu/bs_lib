
.SUFFIXES :  .c .o

CC = gcc
VPATH = avl_tree pal test
CFLAGS = -I./avl_tree -I./pal
COMPILE.c = $(CC) $(CFLAGS) -c

TARGET = bs_lib.a

#SRCS = bs_lib_pal.c bs_lib_avl.c
OBJS = bs_lib_pal.o bs_lib_avl.o
TEST_OBJS= main.o menu.o

%.o: %.c
	$(COMPILE.c) $<

all: $(TARGET)

libtest: $(TEST_OBJS) $(TARGET)
	$(CC) $(CFLAGS) $^ -o $@

bs_lib.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^


include $(subst .c,.d,$(SRCS))

%.d: %.c
	$(CC) -M $(CFLAGS) $< > $@.$$$$;					 \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -f *.d *.o *.a libtest
