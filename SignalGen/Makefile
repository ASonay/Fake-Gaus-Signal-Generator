NAME=SignalGen
ODIR=../WRFile
EXEC=$(NAME)

CXX=g++
CINT=rootcint
CFLAGS=-I/usr/include/root
LDFLAGS=-O -Wall `root-config --cflags --libs` -lm -lz 
SOURCE=$(NAME).cxx $(ODIR)/*.cpp

HEADER= $(ODIR)/*.hh
$(EXEC): $(SOURCE) $(HEADER)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(SOURCE) -o $(EXEC)

clean:
	@rm -fv $(EXEC)
