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

android:
ifeq ($(UNAME), Darwin)
	./android_key_gen.sh && /Users/Shared/Epic\ Games/UE_4.27/Engine/Build/BatchFiles/RunUAT.sh  \
		BuildCookRun \
		-utf8output \
		-targetplatform=Android \
		-cookflavor=ASTC \
		-clientconfig=Development \
		-serverconfig=Development \
		-project=$(PWD)/CronosPlayUnrealDemo.uproject \
		-noP4 -nodebuginfo -allmaps -nocompileeditor \
		-cook -build -stage -prereqs -pak -archive \
		-archivedirectory=$(PWD)/archive
else ifeq ($(UNAME), Linux)
	./android_key_gen.sh && /home/ue4/UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh \
		BuildCookRun \
		-utf8output \
		-platform=Android \
		-cookflavor=ASTC \
		-clientconfig=Development \
		-serverconfig=Development \
		-project=$(PWD)/CronosPlayUnrealDemo.uproject \
		-noP4 -nodebuginfo -allmaps \
		-cook -build -stage -prereqs -pak -archive \
		-archivedirectory=$(PWD)/archive
endif

ios:
ifeq ($(UNAME), Darwin)
	/Users/Shared/Epic\ Games/UE_4.27/Engine/Build/BatchFiles/RunUAT.sh  \
		BuildCookRun \
		-utf8output \
		-platform=iOS \
		-clientconfig=Development \
		-serverconfig=Development \
		-project=$(PWD)/CronosPlayUnrealDemo.uproject \
		-noP4 -nodebuginfo -allmaps -nocompileeditor \
		-cook -build -stage -prereqs -pak -package -archive \
		-archivedirectory=$(PWD)/archive
endif
