

dirs := ./
includes := ./
outputExecutable := ./toy

lexerGrammar := c99.l
parserGrammar := c99.y


define getTargets
	$(foreach 				\
		cdir, \
		$(dirs), \
		$(patsubst                      \
			%$(1), \
			%$(1).o, \
			$(wildcard $(cdir)/*$(1))\
			) 			\
		)
endef


c_gen := $(patsubst %.l,%.l.gen.c,$(lexerGrammar)) $(patsubst %.l,%.l.gen.h,$(lexerGrammar)) $(patsubst %.y,%.y.gen.c,$(parserGrammar)) $(patsubst %.y,%.y.gen.h,$(parserGrammar))
c_objs := $(patsubst %.l,%.l.gen.c.o,$(lexerGrammar)) $(patsubst %.y,%.y.gen.c.o,$(parserGrammar)) $(call getTargets,.c) 

# EXTRA_OPTIONS := -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=leak -fsanitize=undefined -fsanitize-address-use-after-scope


.PHONY: all clean rebuild

.PRECIOUS: %.l.gen.c %.l.gen.h %.y.gen.c %.y.gen.h

%.l.gen.c %.l.gen.h: %.l %.y.gen.h
	flex --header-file=$(patsubst %.l,%.l.gen.h,$<) -o $(patsubst %.l,%.l.gen.c,$<) $<

%.y.gen.c %.y.gen.h: %.y
	bison --defines=$(patsubst %.y,%.y.gen.h,$<) -Wcounterexamples -o $(patsubst %.y,%.y.gen.c,$<) $<

%.c.o: %.c
	gcc $(EXTRA_OPTIONS) -DYYDEBUG -Werror -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wno-unused-function -Wno-unused-but-set-variable -c -g3 -O0 -o $@ $(patsubst %.c.o,%.c,$@) -I$(includes)

all: $(c_objs)
	gcc $(EXTRA_OPTIONS) -o $(outputExecutable) $^
	chmod +x ./test.sh


clean:
	rm -f $(c_gen)
	rm -f $(c_objs)
	rm -f $(outputExecutable)

rebuild: clean all
