CXX_VERSION = c++11

INCLUDE_PATHS += vendor/googlemock/include
INCLUDE_PATHS += vendor/googlemock/gtest/include
INCLUDE_PATHS += vendor/bandit
INCLUDE_PATHS += ..

LIBRARY_PATHS += vendor/googlemock
LIBRARY_PATHS += vendor/googlemock/gtest

LIBRARIES += gmock
LIBRARIES += gtest
LIBRARIES += pthread


CXXFLAGS += -std='$(CXX_VERSION)'
CXXFLAGS += $(addprefix -I, $(INCLUDE_PATHS))

LDFLAGS += $(addprefix -L, $(LIBRARY_PATHS))
LDFLAGS += $(addprefix -l, $(LIBRARIES))


.DEFAULT: all
.PHONY: all
all: vendor main
	./main --reporter=spec

.PHONY: vendor
vendor:
	$(MAKE) -C $@

.PHONY: clean
clean:
	$(RM) main src/main.o

.PHONY: distclean
distclean: clean
	$(MAKE) -C vendor clean

.PHONY: rebuild
rebuild: clean all


main: src/main.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<
