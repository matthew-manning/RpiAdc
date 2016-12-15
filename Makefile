BUILDTARGET = adcTest
BUILDOBJECTS = adcTest.o i2c.o adclib.o

CFLAGS += -Wall -Werror

all: $(BUILDTARGET)


$(BUILDTARGET) : $(BUILDOBJECTS)
	gcc -o $@ $^ $(LFLAGS)

