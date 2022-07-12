all: fetch download

fetch:
	git submodule update --init --recursive

download:
	cd Plugins/play-unreal-plugin && make
