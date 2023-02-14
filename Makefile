# Makefile Generique

CC = g++
EXEC = Chess

CXXFLAGS = -Wall -Wextra -Werror
LDFLAGS =

OBJDIR = Obj
SRCDIR = Src
EXEDIR = bin
EXEC = Chess

INCDIR = -I Include/

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


$(EXEC): $(OBJS)
	$(CC) -o $(EXEDIR)/$(EXEC) $^ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(INCDIR) -o $@ -c $< $(CXXFLAGS)

clean:
	@rm -rf ./Obj/*.o
	@rm -rf ./bin/*

install:
	@mkdir -p Obj
	@mkdir -p bin
