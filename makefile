all: build run

.workdir := workdir
.builddir := build

.PHONY: run build clear doc

run: .workdir
	cd $(.workdir) ; ../$(.builddir)/listdos

build: .listdos

.listdos: .builddir
	cmake -B $(.builddir) -S .
	cmake --build $(.builddir)

clear:
	rm -rf $(.builddir)/*

.builddir:
	mkdir -p $(.builddir)

.workdir:
	mkdir -p $(.workdir)

doc:
	doxygen Doxyfile
