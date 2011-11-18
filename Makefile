
.SUFFIXES :  .c .o

CC = gcc
VPATH = pal sort data_structure test
CFLAGS = -I./data_structure -I./pal
COMPILE.c = $(CC) $(CFLAGS) -c

TARGET = bs_lib.a

LIB_OBJS = bs_lib_pal.o bs_lib_avl.o bs_lib_stack.o
TEST_OBJS= main.o menu.o

%.o: %.c
	$(COMPILE.c) $<

all: $(TARGET)

libtest: $(TEST_OBJS) $(TARGET)
	$(CC) $(CFLAGS) $^ -o $@

bs_lib.a: $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^


include $(subst .c,.d,$(SRCS))

%.d: %.c
	$(CC) -M $(CFLAGS) $< > $@.$$$$;					 \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -f *.d *.o *.a libtest
