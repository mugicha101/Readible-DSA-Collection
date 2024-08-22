param([bool]$recompile=$true)
if ($recompile) {
    if (Test-Path -Path './a.exe') {
        Remove-Item ./a.exe
    }
    g++ -std=c++17 -O3 -fpermissive -fassociative-math -ffast-math -ffloat-store ./main.cpp
}
if (Test-Path -Path './output.txt') {
    Remove-Item ./output.txt
}
if (Test-Path -Path './a.exe') {
    ./a.exe | Tee-Object ./output.txt
}