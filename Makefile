TARGETFILE=libreadfile.so.1.0 libuart.so.1.0
-include test.m
FILE=$(patsubst lib%.so.1.0,%.o,$(TARGETFILE))
GCC:=gcc
FLAGS=-Wall -shared -Wl,-rpath,./ -o
FLAGS_O=-Wall -fPIC -c -o
all:$(TARGETFILE)
$(TARGETFILE):lib%.so.1.0:%.o
	$(GCC) $(FLAGS)  $@ $<
$(FILE):%.o:%.c
	$(GCC) $(FLAGS_O)  $@ $<
.PHONY:clean
clean:
	@file=`ls|grep "\.so\|\.o"`;\
	for rmfile in $$file;\
	do\
	   rm "$$rmfile";\
	done;
ifdef myname
	@echo "$(myname)"
else
	@echo "have no define"
endif
