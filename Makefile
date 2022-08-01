UNAME := $(shell uname)
PWD = $(shell pwd)
all: fetch download

fetch:
	git submodule update --init --recursive

download:
	cd Plugins/play-unreal-plugin && make

RunUAT:
ifeq ($(UNAME), Linux)
	/home/ue4/UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh \
	BuildCookRun \
	-utf8output \
	-platform=Linux \
	-clientconfig=Shipping \
	-serverconfig=Shipping \
	-project=$(PWD)/CronosPlayUnrealDemo.uproject \
	-noP4 -nodebuginfo -allmaps \
	-cook -build -stage -prereqs -pak -archive \
	-nocompileeditor \
	-archivedirectory=$(PWD)
endif

ifeq ($(UNAME), Darwin)
	/Users/Shared/Epic\ Games/UE_4.27/Engine/Build/BatchFiles/RunUAT.sh  \
		BuildCookRun \
		-utf8output \
		-platform=Mac \
		-clientconfig=Shipping \
		-serverconfig=Shipping \
		-project=$(PWD)/CronosPlayUnrealDemo.uproject \
		-noP4 -nodebuginfo -allmaps \
		-cook -build -stage -prereqs -pak -archive \
		-nocompileeditor \
		-archivedirectory=$(PWD)
endif
