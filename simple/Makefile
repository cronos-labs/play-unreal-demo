UNAME := $(shell uname)
PWD := $(shell pwd)

.PHONY: build

all: build

build:
ifeq ($(UNAME), Darwin)
	/Users/Shared/Epic\ Games/UE_4.27/Engine/Build/BatchFiles/RunUAT.sh  \
		BuildCookRun \
		-utf8output \
		-platform=Mac \
		-clientconfig=Development \
		-serverconfig=Development \
		-project=$(PWD)/CronosPlayUnrealDemo.uproject \
		-noP4 -nodebuginfo -allmaps -nocompileeditor \
		-cook -build -stage -prereqs -pak -archive \
		-archivedirectory=$(PWD)/archive
else ifeq ($(UNAME), Linux)
	/home/ue4/UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh \
	BuildCookRun \
	-utf8output \
	-platform=Linux \
	-clientconfig=Development \
	-serverconfig=Development \
	-project=$(PWD)/CronosPlayUnrealDemo.uproject \
	-noP4 -nodebuginfo -allmaps \
	-cook -build -stage -prereqs -pak -archive \
	-archivedirectory=$(PWD)/archive
endif
