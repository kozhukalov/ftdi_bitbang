### Prerequisites
```bash
dnf install libftdi libftdi-devel
```

### Build
```bash
mkdir build
cd build
cmake ../ -DEXAMPLES=ON
make
```

### Install
```bash
sudo make install
```
