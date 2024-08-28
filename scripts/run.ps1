# compiles and executes for windows with MinGW
# run from project root directory
param([bool]$recompile=$true)
if ($recompile) {
    if (Test-Path -Path './build/bin/app.exe') {
        Remove-Item ./build/bin/app.exe
    }
    cmake -S . -B build -G "MinGW Makefiles"
    cmake --build build --config Release
}
if (Test-Path -Path './build/bin/app.exe') {
    cd ./build/bin
    ./app.exe
    cd ../..
}