# user-definable settings
TRIVIAL =      # 1=YES, [empty] = no
DEBUG =        # 1=YES, [empty] = no
SETUP = macosx # possibilities: macosx, ubuntu, sallesinfo

# defines and compiler
DEFINES =
CXX = c++

ifdef TRIVIAL
  DEFINES += -DTRIVIAL
endif

# flags
FLAGS = $(DEFINES)
ifdef DEBUG
  FLAGS += -g
else
  FLAGS += 
endif

ifeq "$(SETUP)" "sallesinfo "
  ## salles informatiques @X
  $(info building for $(SETUP))
  INCLUDE = -I/usr/local/boost-1.58.0/include/ -I/usr/local/CImg-1.6.2/
  LIBS = -lpthread -lX11 -L/usr/local/boost-1.58.0/lib/
  LDPATH = LD_LIBRARY_PATH=/usr/local/boost-1.58.0/lib:/usr/lib/alliance/lib
endif

ifeq "$(SETUP)" "ubuntu "
  # ubuntu linux
  $(info building for $(SETUP))
  INCLUDE =
  LIBS = -lpthread -lX11
  LDPATH =
endif

ifeq "$(SETUP)" "macosx "
  # macosx
  # Loading libraries from X11
  # For CImg uses
  $(info building for $(SETUP))
  INCLUDE = -I/usr/local/include -I/opt/X11/include
  LIBS = -lpthread -L/usr/local/lib -L/opt/X11/lib -lX11
  DEFINES += -std=c++0x
  LDPATH = DYLD_LIBRARY_PATH=/usr/local/lib
endif

# name of executable
BIN = main

# object files it depends on
OBJS = ImageIntegrale.o

# remove command
RM = rm -f

# default rule - typing "make" will start this rule
#   the dependency is on Makefile itself (so if the Makefile was changed
#   the whole project is rebuilt) and on the executable
all:	$(BIN) Makefile

# rule to build the executable
$(BIN): $(OBJS) $(BIN).cpp Makefile
	$(CXX) $(FLAGS) $(INCLUDE) -o $(BIN) $(BIN).cpp $(OBJS) $(LIBS)

# rule to run test Q1.1
test_q_1_1: ImageIntegrale.* test_q_1_1.cpp Makefile
		$(CXX) $(FLAGS) $(INCLUDE) -o $@ ImageIntegrale.cpp test_q_1_1.cpp $(LIBS)

# rule to run test eps (Tests of epsilon and K)
testEps: ImageIntegrale.* testEps.cpp Makefile
		$(CXX) $(FLAGS) $(INCLUDE) -o $@ ImageIntegrale.cpp testEps.cpp $(LIBS)

# rule to run main
main: ImageIntegrale.* main.cpp Makefile
		$(CXX) $(FLAGS) $(INCLUDE) -o $@ ImageIntegrale.cpp main.cpp $(LIBS)

# rule to clean objects and executable
clean:
	$(RM) $(OBJS) $(BIN) test_q_1_1 testEps main

# rule to restore directory to pristine state
distclean: clean
	$(RM) core *~

# catch-all rule to compile object files
#   $@ refers to the rule name (.o) and %< to the first item in rule (.cpp)
%.o:	%.cpp %.h Makefile
	$(CXX) $(FLAGS) $(INCLUDE) -c -o $@ $<
