# cainit

## What is it?

Have you ever had an assinment for your C++ class that asks you to write a bunch of classes, and give each one of its variables a Get and Set function? Well, if you hate spending most of your time doing that, you might find the project useful.

`cainit` creates both the header and source files for your classes, complete with variables (set to private by default), Get and Set methods, and include statements. It uses really simple configuration files, and it shouldn't take you more than a couple seconds to setup your assignments. 

You can find a quick guide on how to write configuration files on the examples folder

## How do I install it?

Installation is only available on linux, and it does not require any dependencies aside from make and a working C++ compiler.

### Download the latest release from the releases page

### Decompress the downloaded package
```bash
tar -xvf cainit-x.x.tar.gz
```

### Compile and install it
```bash
cd cainit-x.x/
./configure
make 
sudo make install
```

## How do I use it
```bash
cainit path/to/config
```