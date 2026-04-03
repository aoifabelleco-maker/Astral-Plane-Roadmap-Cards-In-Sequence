$ErrorActionPreference = 'Stop'
cmake -S . -B build
cmake --build build
Write-Host 'Native build complete.'
