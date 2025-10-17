CXX = g++
CXXFLAGS = -Wall -I./src
OBJDIR = build
BINDIR = bin

LIB = $(OBJDIR)/libcalc.a
APP = $(BINDIR)/app

OBJS = $(OBJDIR)/calculator.o $(OBJDIR)/main.o

all: $(APP)

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR)

$(BINDIR):
	if not exist $(BINDIR) mkdir $(BINDIR)

$(OBJDIR)/calculator.o: src/calculator.cpp src/calculator.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: src/main.cpp src/calculator.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB): $(OBJDIR)/calculator.o
	ar rcs $@ $^

$(APP): $(LIB) $(OBJDIR)/main.o | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJDIR)/main.o -L$(OBJDIR) -lcalc

clean:
	if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	if exist $(BINDIR) rmdir /s /q $(BINDIR)

.PHONY: all clean
