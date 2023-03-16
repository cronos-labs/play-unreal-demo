all:format


format:
	find . -name "*.h" -o -name "*.cpp" -o -name "*.cc" -o -name "*.cs" | xargs clang-format -i -style=file
