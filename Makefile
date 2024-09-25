include config.mk

CFLAGS += $(shell MagickWand-config --cflags)
CFLAGS += -std=c99

LDFLAGS += $(shell MagickWand-config --ldflags --libs)

RM = rm -f
SRCDIR = src
OBJDIR = obj
OBJS = cpetpet.o

all: libcpetpet.a libcpetpet.so

$(OBJS): config.h cpetpet.h

libcpetpet.a libcpetpet.so: $(OBJS)

libcpetpet.so:
	cc -shared -o $@ ${LDFLAGS} ${LDLIBS} $^

libcpetpet.a:
	ar rcs $@ $^

install: all
	install -d $(DESTDIR)/lib $(DESTDIR)/share/cpetpet
	install -m644 libcpetpet.a $(DESTDIR)/lib
	install -m755 libcpetpet.so $(DESTDIR)/lib
	install -m644 share/cpetpet/* $(DESTDIR)/share/cpetpet
	install -m644 cpetpet.h $(DESTDIR)/include

uninstall:
	$(RM) -r $(DESTDIR)/share/cpetpet
	$(RM) $(DESTDIR)/lib/libcpetpet.{a,so}
	$(RM) $(DESTDIR)/include/cpetpet.h

clean:
	$(RM) *.a *.o *.so

cleanall: clean
	$(RM) config.* config.*

.PHONY: all clean cleanall install uninstall
