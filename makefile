# makefile for 'hp' --- reverse polish notation calculator

# note that 'hp' uses 'stacc', the recursive descent parser generator

CFLAGS= -O
DESTDIR=/usr/local/bin
MANSEC=l
CP= cp

hp: st.parse.h st.parse.c hp.c
	$(CC) $(CFLAGS) hp.c -lm -o hp

st.parse.h st.parse.c: hp.stacc
	stacc < hp.stacc

install: hp hp.1
	$(CP) hp $(DESTDIR)
	$(CP) hp.1 /usr/man/man$(MANSEC)/hp.$(MANSEC)

clean:
	rm -f st.parse.c st.parse.h

clobber: clean
	rm -f hp
