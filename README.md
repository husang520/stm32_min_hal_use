# 日期：20260623
# 名称：STM32H743ZIT6_EmbeddedFramework_FW_V190(移植的最小系统)

## 修改人：husang

### 注意事项：

1、此项目是通过 cubemx 中的库，v190 ，来进行移植的，参考正点原子官方例程，编写的最小例程代码。配合 stm32h743zit6 开发板使用。
2、此项目是一个 makefile + gnu +openodc 项目，与 keil 项目不同。需要 .s .ld makefile 三个文件。.s 和 .ld 文件可以通过 cubemx 先生成。再拷贝进来。
3、此项目是一个 vscode 项目。需要在 vscode 中下载相应的 插件：包括但不限于：makefile tools、stm32-for-vscode (最重要)以及其他基础的插件等。

