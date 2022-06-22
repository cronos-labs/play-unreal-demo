all: download update

download:
	git submodule update --init --recursive
update:
	cp -Rf ./play-unreal-plugin/CronosPlaySdk/Plugins/CronosPlayUnreal ./CronosPlayUnrealDemo/Plugins
	cd CronosPlayUnrealDemo && ./copydll.sh
	
