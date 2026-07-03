@echo off

qemu-system-x86_64 -machine q35 -m 512 -drive if=pflash,format=raw,readonly=on,file="C:\Program Files\qemu\ovmf\OVMF_CODE_4M.fd" -drive if=pflash,format=raw,file="C:\Program Files\qemu\ovmf\OVMF_VARS_4M.fd" -drive format=raw,file=fat:rw:ESP -serial vc -net none