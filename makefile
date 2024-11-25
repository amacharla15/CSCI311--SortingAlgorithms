
---

### `Makefile`

```makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2

# Targets and files
TARGETS = sorting_tests plot_results
SRC1 = main.cpp
SRC2 = plot.cpp

# Default target
all: $(TARGETS)

sorting_tests: $(SRC1)
	$(CXX) $(CXXFLAGS) -o sorting_tests $(SRC1)

plot_results: $(SRC2)
	$(CXX) $(CXXFLAGS) -o plot_results $(SRC2) -I/usr/include/python3.8 -lpython3.8

clean:
	rm -f $(TARGETS) *.o *.csv *.png
