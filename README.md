## dde-dock datetime plugin (modified version)

### Info

Simple quick hack to make it display year/month/day on it's `Dock::Efficient` mode (`24HourFormat` only). Also some really little simple tweak to make it compilable without fetching the full dde-dock repo.

Current codebase is fork from [dde-dock#39c1a6b](https://github.com/linuxdeepin/dde-dock/commit/39c1a6b609c65026a505bd6b74a451bff26ee456). You can checkout the commit history and do a `diff` to see what I did changed.

### Usage

You need do `apt-get build-dep dde-dock` first.

To compile:

``` bash
# you should clone it first:
git clone https://github.com/BLumia/dde-dock-pineappledatetime.git && cd dde-dock-pineappledatetime/
# then build it
mkdir build
cd build/
cmake ../
make
# then you got `libpineappledatetime.so`
# this will copy this into `/usr/`
sudo make install
```
