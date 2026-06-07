all: debug

debug:
	cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/debug -j

release:
	cmake -B build/release -DCMAKE_BUILD_TYPE=Release
	cmake --build build/release -j

test:
	cd build/debug && ctest --output-on-failure

clean:
	rm -rf build
