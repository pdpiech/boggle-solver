CXX=g++ -Wall
CXXFLAGS=-std=gnu++14
RM=rm -f
SRCS=boggle.cxx boggle_main.cxx

debug: CXXFLAGS += -DDEBUG -g
debug: $(OBJS)
	$(CXX) $(CXXFLAGS) -o boggle $(SRCS)

release: CXXFLAGS += -O3
release: $(OBJS)
	$(CXX) $(CXXFLAGS) -o boggle $(SRCS)

clean:
	$(RM) $(OBJS)
	$(RM) boggle
