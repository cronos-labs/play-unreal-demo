UNAME := $(shell uname)
PLAYUNREALPLUGIN=v0.0.7-ue4-alpha
PLUGIN_FILE=CronosPlayForUnrealEngine.zip
PLUGIN_CHECKSUM_FILE=checksums.txt

PLUGIN_SRC=https://github.com/cronos-labs/play-unreal-plugin/releases/download/$(PLAYUNREALPLUGIN)/$(PLUGIN_FILE)
PLUGIN_CHEKSUM_SRC=https://github.com/cronos-labs/play-unreal-plugin/releases/download/$(PLAYUNREALPLUGIN)/$(PLUGIN_CHECKSUM_FILE)


all: android_key_gen download

android_key_gen:
ifeq ($(UNAME), Darwin)
	./android_key_gen.sh
endif

download:
	mkdir -p ./Plugins/play-unreal-plugin
	cd ./Plugins/play-unreal-plugin && curl -s -O -L $(PLUGIN_SRC)
	cd ./Plugins/play-unreal-plugin && curl -s -L $(PLUGIN_CHEKSUM_SRC) | shasum -a 256 -c -
	cd ./Plugins/play-unreal-plugin && unzip -o $(PLUGIN_FILE)
