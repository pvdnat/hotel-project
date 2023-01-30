TARGET = wish
OBJS = wish.o wish_read.o

# MANY flags that cause all sorts of warnings
CFLAGS = -Wall -pedantic -Wextra -Wcast-align -Wcast-qual \
	-Wdisabled-optimization -Wformat=2 -Winit-self \
	-Wmissing-include-dirs -Wredundant-decls -Wshadow \
	-Wstrict-overflow=5 -Wundef -Werror -Wno-unused \
	-g -Wno-unused-result -O3 -Wlogical-op -Wno-strict-overflow 

all: $(TARGET)

wish: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) #-lefence

wish.o: wish.c wish.h

wish_read.o: wish_read.c wish.h

clean:
	rm -f $(OBJS) $(TARGET)
