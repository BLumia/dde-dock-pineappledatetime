## dde-dock 时间插件 (修改版)

[English](README.md) | 简体中文

*请注意此项目 **并非** 官方项目*

### Screenshot

![pineappledatetime 的截图](https://github.com/BLumia/dde-dock-pineappledatetime/raw/media/screenshot.png)

### 概述

这是一个使得 `Dock::Efficient`（高效模式） 下的时间插件可以增加 年/月/日 的格式显示日期的修改版时间插件，并使得该项目可以脱离 dde-dock 独立构建。

这份代码是由 [dde-dock#39c1a6b](https://github.com/linuxdeepin/dde-dock/commit/39c1a6b609c65026a505bd6b74a451bff26ee456) 分离修改而来的。如果感兴趣，可以进行 `diff` 对比差异来查看我修改了什么内容。

### 用法

假定您已经在您的 `/etc/apt/sources.list` 中添加了对应的 `deb-src` 源，以便你可以通过执行 `apt build-dep <软件包名>` 来安装构建某个软件包所需的依赖。接下来你需要执行 `apt build-dep dde-dock` 安装你所需的大部分构建依赖，然后再通过执行 `apt install dde-dock-dev` 来安装 dde-dock 的插件开发包 `dde-dock-dev`。当然，如果希望，你也可以自行手动安装这些依赖而不使用 `build-dep`。

编译和运行:

``` bash
# 你需要先克隆仓库源码到本地:
git clone https://github.com/BLumia/dde-dock-pineappledatetime.git && cd dde-dock-pineappledatetime/
# 创建一个用于构建源码的目录:
mkdir build
cd build/
# 然后开始构建:
cmake ../
make
# 完成后你将得到一个 `libpineappledatetime.so` 文件
# 接下来会把它安装到 `/usr/lib/dde-dock/plugins/` 目录中
sudo make install
# 最后，重启 `dde-dock` (结束 dde-dock 进程后 dde-dock 会自己重新启动)
killall dde-dock
```

> 提示: 在 dde-dock 大于 `4.10.4` (`>4.10.4`) 的版本里，你就可以直接把插件放在 `~/.local/lib/dde-dock/plugins/` 而无需放到 `/usr/lib/dde-dock/plugins/` 了。

然后就完成了！

### 许可协议

GPLv3 (由 dde-dock 原始代码直接修改衍生而来，故应和 dde-dock 的许可保持一致)
