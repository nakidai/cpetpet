include config.mk

CFLAGS += $(shell MagickWand-config --cflags)
CFLAGS += -std=c99

LDFLAGS += $(shell MagickWand-config --ldflags --libs)

RM = rm -f
SRCDIR = src
OBJDIR = obj
OBJS = cpetpet.o

all: cpetpet.a cpetpet.so

$(OBJS): config.h cpetpet.h

cpetpet.a cpetpet.so: $(OBJS)

cpetpet.so:
	cc -shared -o $@ ${LDFLAGS} ${LDLIBS} $^

cpetpet.a:
	ar rcs $@ $^

install: all
	install -d $(DESTDIR)/lib $(DESTDIR)/share/cpetpet
	install -m644 cpetpet.a $(DESTDIR)/lib
	install -m755 cpetpet.so $(DESTDIR)/lib
	install -m644 share/cpetpet/* $(DESTDIR)/share/cpetpet

clean:
	$(RM) *.a *.o *.so

cleanall: clean
	$(RM) config.* config.*

.PHONY: all clean install
