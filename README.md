## dde-dock datetime plugin (modified version)

*Please notice that this is **NOT** an official project*

### Screenshot

![Screenshot of pineappledatetime](https://github.com/BLumia/dde-dock-pineappledatetime/raw/media/screenshot.png)

### Info

Simple quick hack to make it display year/month/day on it's `Dock::Efficient` mode (`24HourFormat` only). Also some really little simple tweak to make it compilable without fetching the full dde-dock repo.

Current codebase is fork from [dde-dock#39c1a6b](https://github.com/linuxdeepin/dde-dock/commit/39c1a6b609c65026a505bd6b74a451bff26ee456). You can checkout the commit history and do a `diff` to see what I did changed.

### Usage

You need do `apt-get build-dep dde-dock` first.

To compile and run:

``` bash
# you should clone it first:
git clone https://github.com/BLumia/dde-dock-pineappledatetime.git && cd dde-dock-pineappledatetime/
# then build it
mkdir build
cd build/
cmake ../
make
# then you got `libpineappledatetime.so`
# this will copy this into `/usr/lib/dde-dock/plugins/`
# p.s. `make install` will copy the lib to `/usr/share/lib/dde-dock/plugins`
#      but it seems `dde-dock` doesn't scan that path by default...
sudo cp ../libpineappledatetime.so /usr/lib/dde-dock/plugins/
# finally, restart `dde-dock` (kill it and dde will restart it automatically)
killall dde-dock
```

Then done!

### License

GPLv3 (as required, same as original license)
