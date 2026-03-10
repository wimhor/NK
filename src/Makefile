#
# Makefile: Makefile for the NK-landscape implementations.
#
# Wim Hordijk   Last modified: 10 March 2026
#

CC     = g++

nk: nk_walk.cpp Random.cpp NK.cpp Random.h NK.h
	$(CC) -o ../nk_walk nk_walk.cpp Random.cpp NK.cpp

nkc: nkc_walk.cpp Random.cpp NKC.cpp Random.h NKC.h
	$(CC) -o ../nkc_walk nkc_walk.cpp Random.cpp NKC.cpp

clean:
	rm -f *~ *.o

#
# EOF: Makefile
#
