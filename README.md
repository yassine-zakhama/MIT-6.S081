# MIT-6.S081: Operating Systems Engineering

## Environment Setup (Debian / Ubuntu)

Make sure you are running either Debian bullseye or sid.
On Ubuntu, you can check your Debian compatibility layer with:

```sh
cat /etc/debian_version
```

### Installing Dependencies via APT

Install all required tools:

```sh
sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
```

### qemu-system-misc fix

At this moment in time, it seems that the package qemu-system-misc has received an update that breaks its compatibility with our kernel. If you run make qemu and the script appears to hang after

```sh
qemu-system-riscv64 -machine virt -bios none -kernel kernel/kernel -m 128M -smp 3 -nographic -drive file=fs.img,if=none,format=raw,id=x0 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0
```

you'll need to uninstall that package and install an older version:

```sh
sudo apt-get remove qemu-system-misc
sudo apt-get install qemu-system-misc=1:4.2-3ubuntu6
```

## Debugging xv6 with QEMU + GDB

This project uses QEMU to emulate a RISC-V system and GDB for kernel debugging.

Run:

```sh
make qemu-gdb
```

Open a second terminal:

```sh
gdb-multiarch kernel/kernel
```

Inside GDB:

```sh
set architecture riscv:rv64
target remote :26000
```

### Disclaimer

- This repository is **unofficial** and is not affiliated with or endorsed by MIT or the 6.S081 teaching team.
- All course materials and content are property of MIT 6.S081 staff and are provided here for **personal learning and practice** only. Please respect academic integrity policies.
