CC = mpiicc 
LD = $(CC) 
OPTS = -D__UNIX__ -O3 
STDH = gendef.h
OBJS = genreg.o main.o optmid.o
genreg : $(OBJS)
	  $(LD) $(OPTS) -o $@ $(OBJS) $(LIBS)

genreg.o : genreg.c $(STDH)
	    $(CC) -c $(OPTS) genreg.c

main.o : main.c $(STDH)
	  $(CC) -c $(OPTS) main.c

optmid.o : optmid.c $(STDH)
	    $(CC) -c $(OPTS) optmid.c

clean : 
	rm *.o
	rm genreg
