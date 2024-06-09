## gr-acars

A "simple" demonstration software for decoding ACARS, a low-bandwidth 
communication protocol used by airplanes to communicate with airports. 
Detailed description of the operating principles is available at 
http://jmfriedt.free.fr/lm_sdr.pdf (French) and 
http://jmfriedt.free.fr/en_sdr.pdf (English). See https://www.youtube.com/watch?v=54URhrJkk28
(SDRA 2020) for a discussion on the clock synchronization scheme.

The latest 2022 release for GNU Radio 3.9 and 3.10, following 3.8, named ng for 
New Generation, aims at adding bitrate clock tracking + removes the external 
dependence with libfftw by using the GNU Radio FFT wrapper. Doing so, multiple 
ACARS decoding blocks can run in parallel.

### Compile for x86 PC with:

```
cd 3.10ng
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
make -j4
sudo make install
```

(developed and tested on Debian GNU/Linux)

Compile for RaspberryPi4/Buildroot (located in ``BR_PATH``):
```
cmake -DCMAKE_INSTALL_PREFIX:PATH=$BR_PATH/output/target/usr -DCMAKE_TOOLCHAIN_FILE=$BR_PATH/output/host/share/buildroot/toolchainfile.cmake ../
make -j4
make install
```

### Features

* RTL2832U based receivers, tuned to 131.725 MHz in western Europe (main ACARS channel)
* GNU Radio Companion compatible block

<img src="3.7.5/examples/DSC01883_small.png">

<img src="3.7.5/examples/acars_sendai2.png>
