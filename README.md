# What is Naivix

Naivix is a too simple, and sometimes naive, UNIX-like experimental kernel.
It hasn't been fully designed. Any architecture other than x86-64 architecture isn't supported.
They may be supported in the future.

# How to compile it

- Just "make" it. (2333333333333

# How to install it

- Install grub2 to a disk (or a  disk image).
- Copy the kernel file (`./naivix`) to a partition on the disk.
- Add a boot item for Naivix in the GRUB configuration file. Such as: 

```
# /boot/grub/custom.cfg

menuentry "Naivix" {
    set root=(hd0,gpt1)
    echo 'Loading Naivix ...'
    multiboot2 /naivix
    boot
}
```

