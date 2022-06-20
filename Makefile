all:
	git submodule update --init --recursive
	cp -Rf ./play-unreal-plugin/CronosPlaySdk/Plugins/CronosPlayUnreal ./CronosPlayUnrealDemo/Plugins
	cd CronosPlayUnrealDemo && ./copydll.sh
