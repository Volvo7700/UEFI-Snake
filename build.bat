@echo off
cd C:\EDK\EDK2
call edksetup.bat
build -p UEFI-Snake/UEFI-Snake.dsc -a X64 -t CLANGPDB

pause