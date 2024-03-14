## ChangeLog ISVP-3.9.0-2016.12.9
----------

* [Toolchain] update r2.3.3: optimize SIMD128 compilation; add nostripped uclibc library; fix uclibc busybox nslookup bug; add uclibc program compilation with mips-linux-uclibc-gnu-XXX.
* [rootfs]update busybox,lib, add logcat to reference rootfs
* [u-boot] optimize DDR parameters to improve efficiency (important); add Lite Version chip compilation configuration (T10L and T20L please use Lite configuration); add SPI Nor Flash FM25Q64A support; add CRC checksum for SD card auto update.
* [kernel] optimize the default configuration of ISVP to optimize the stability and efficiency of the system; add ethtool interface to gmac driver.
* [Sensor] add ov2710,ov4689,gc2023,imx322,sc2135,jxf22,bg0806 support and effect files.
* [ISP]T20 add MIPI-CSI support, fix the bug of driver customization function.
* [Encoder] Repair some problems of stream control algorithm.
* [Audio] Optimize AEC, add ADPCM codec support.
* [Carrier] add JPEG capture function.
* [Doc] Add T20 development board Medlar and Bull description document, update FAQ, update three-way library compilation document and so on.

Notes:

* This update is compatible with the previous version of the kernel (Ver.3.8.0), it is recommended to update the configuration (defconfig).
* It is recommended to update Toolchain and rootfs (uclibc) to fix uclibc bugs and support uclibc gdbserver. the new version of Toolchain and rootfs is compatible with the old version, i.e. the old version can be used normally.
