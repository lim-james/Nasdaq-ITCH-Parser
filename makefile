all: debug

debug:
	cmake -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build -j

release:
	cmake -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build -j

test:
	cd build && ctest --output-on-failure

clean:
	rm -rf build


