# Makefile Generique

CC = g++
EXEC = ChessTu

CXXFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lcppunit

OBJTUDIR = Obj
EXETUDIR = bin

SRCTUDIR = Src
INCTUDIR = -I Include/

SRCDIR = ../Src
INCDIR = -I ../Include

SRCSTU = $(wildcard $(SRCTUDIR)/*.cpp)
OBJSTU = $(SRCSTU:$(SRCTUDIR)/%.cpp=$(OBJTUDIR)/%.o)

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJTUDIR)/%.o)


$(EXEC): $(OBJSTU) $(OBJS)
	$(CC) -o $(EXETUDIR)/$(EXEC) $^ $(LDFLAGS)

$(OBJTUDIR)/%.o : $(SRCTUDIR)/%.cpp
	$(CC) $(INCTUDIR) -o $@ -c $< $(CXXFLAGS)

$(OBJTUDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(INCDIR) -o $@ -c $< $(CXXFLAGS)

clean:
	@rm -rf ./Obj/*.o
	@rm -rf ./bin/*

install:
	@mkdir -p Obj
	@mkdir -p bin
