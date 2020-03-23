###############################################################################
#             _____ ______   ________  ___  __    _______                     #
#            |\   _ \  _   \|\   __  \|\  \|\  \ |\  ___ \                    #
#            \ \  \\\__\ \  \ \  \|\  \ \  \/  /|\ \   __/|                   #
#             \ \  \\|__| \  \ \   __  \ \   ___  \ \  \_|/__                 #
#              \ \  \    \ \  \ \  \ \  \ \  \\ \  \ \  \_|\ \                #
#               \ \__\    \ \__\ \__\ \__\ \__\\ \__\ \_______\               #
#                \|__|     \|__|\|__|\|__|\|__| \|__|\|_______|               #
#                       ________ ___  ___       _______                       #
#                      |\  _____\\  \|\  \     |\  ___ \                      #
#                      \ \  \__/\ \  \ \  \    \ \   __/|                     #
#                       \ \   __\\ \  \ \  \    \ \  \_|/__                   #
#                        \ \  \_| \ \  \ \  \____\ \  \_|\ \                  #
#                         \ \__\   \ \__\ \_______\ \_______\                 #
#                          \|__|    \|__|\|_______|\|_______|                 #
#                                                                             #
#                                                                             #
###############################################################################
#                                                                             #
# Author: Dimitri Thomopulos                 2018-07-30                       #
#                                                                             #
###############################################################################
#    You can modify this example makefile to fit for your own program.        #
#    Usually, you only need to change the five CHANGEME entries below.        #
###############################################################################
	
# CHANGEME: This should be the name of your executable
EXE = HIG

# CHANGEME: Here is the name of all object files corresponding to the source
#           code that you wrote in order to define the problem statement
OBJS = Main.o \
       read.o \
       write_instance.o

# CHANGEME: Additional libraries
ADDLIBS = 

# CHANGEME: Additional flags for compilation (e.g., include flags)
ADDINCFLAGS = 

# CHANGEME: Directory to the sources for the (example) problem definition
# files
SRCDIR = src
VPATH = src
OBJDIR = obj

###############################################################################
#  Usually, you don't have to change anything below.                          #
###############################################################################

# C++ Compiler command
CXX = g++

# C++ Compiler options
CXXFLAGS = -O3 -pipe -DIL_STD -DNDEBUG

# additional C++ Compiler options for linking
CXXLINKFLAGS =  
#-Wl,--rpath -Wl

INCL += $(ADDINCFLAGS)

# The following is necessary under cygwin, if native compilers are used
CYGPATH_W = echo

all: $(EXE)

.SUFFIXES: .cpp .c .o .obj

$(EXE): $(OBJS)
	bla=;\
	for file in $(OBJS); do bla="$$bla `$(CYGPATH_W) $(OBJDIR)/$$file`"; done; \
	$(CXX) $(CXXLINKFLAGS) $(CXXFLAGS) $(INCL) -o $@ $$bla $(LIBS) $(ADDLIBS)
	
clean:
	rm -rf $(EXE) $(OBJDIR)

remake:
	make clean;
	make;

whoo:
	@echo "Whoo!!!";
	@echo "         __              __";
	@echo '         \ `-._......_.-` /';
	@echo "          \`.  '.    .'  .' ";
	@echo "           //  _\`\/\`_  \\ ";
	@echo "          ||  /\O||O/\  || ";
	@echo "          |\  \_/||\_/  /| ";
	@echo "          \ '.   \/   .' /   WHOO!!!!";
	@echo "          / ^ \`'~  ~'\`   \ ";
	@echo "         /  _-^_~ -^_ ~-  | ";
	@echo "         | / ^_ -^_- ~_^\ | ";
	@echo "         | |~_ ^- _-^_ -| | ";
	@echo "         | \  ^-~_ ~-_^ / | ";
	@echo "         \_/;-.,____,.-;\_/ ";
	@echo "  ==D.T.====(_(_(==)_)_)========= ";
	@echo " ";
	@echo " ==================================";
	
.cpp.o:
	@mkdir -p $(OBJDIR);\
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $(OBJDIR)/$@ `test -f '$<' || echo '$(SRCDIR)/'`$<

.cpp.obj:
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $(OBJDIR)/$@ `if test -f '$<'; \
	then $(CYGPATH_W) '$<'; else $(CYGPATH_W) '$(SRCDIR)/$<'; fi`
