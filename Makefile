all:
	cmake -S . -B build-mingw -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
	cmake --build build-mingw

run: all
	cmd.exe /c start "" cmd /k ".\\bin\\analizaSortari.exe"

clean:
	-rmdir /s /q build-mingw
	-del /f /q analizaSortari.exe
