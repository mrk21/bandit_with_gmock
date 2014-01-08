.DEFAULT: all
.PHONY: all
all: googlemock bandit

.PHONY: clean
clean:
	$(RM) -r googlemock bandit

.PHONY: rebuild
rebuild: clean all


googlemock:
	svn checkout http://googlemock.googlecode.com/svn/tags/release-1.7.0 $@
	cd $@ && cmake . && $(MAKE)

bandit:
	git clone https://github.com/joakimkarlsson/bandit.git $@
	cd $@ && git checkout v1.1.4
