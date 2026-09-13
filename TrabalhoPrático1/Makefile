CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

TARGET = tp1_osa

SRCS = main.cpp aluno.cpp gerenciadorArquivo.cpp benchmark.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)