target := tcpwait
sourcedir := source
includedir := include
builddir := .build
testdir := tests

CFLAGS += -I$(includedir) -MMD -MP -O3 -g -std=gnu11 -Wall -Wextra -Wpedantic -Werror
LDFLAGS += 
MKDIR := mkdir -p

default: $(target)

sources := $(wildcard $(sourcedir)/*.c) $(tests)
dependencies := $(patsubst %.c, $(builddir)/%.d, $(sources))
objects := $(patsubst %.c, $(builddir)/%.o, $(sources))

$(target): $(objects)
	$(CC) -o $@ $(objects) $(LDFLAGS)

$(builddir)/%.o: %.c
	$(MKDIR) $(dir $@) && \
	$(CC) $(CFLAGS) -o $@ -c $<

test: $(target)
	py.test $(testdir)

-include $(dependencies)
