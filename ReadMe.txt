

		温控配置软件
	温控硬件部分今后分为有屏和无屏两个方向，以及集中器、控制器、采集器等都需要参数配置。
	
	为了提高温控软件的兼容性，使用上位机的配置软件来完成温控软件的参数配置，由于使用无线的方式，

	配置时即使电路板处于设备内部也可以完成配置

	实现了无线更新程序的功能

2018.9.14
	程序下载功能可以下载hex文件和bin文件，
		其中hex文件的Flash地址是0x8002800
		
	提高命令发送与接收的准确性
2018.9.17
	提高程序下载稳定性
	增加重启命令
	优化错误提示逻辑，显示错误类型
	可以下载经过融合的hex文件
2018.9.19
	修复有一次程序下载以后每次都失败的bug
	提高用串口时的程序下载速率，同时增加稳定性
	记录发送和接收历史到“My_History.txt”文件
2018.9.30
	加入恒湿机类型
2018.10.11
	修正下载程序重试次数不清零的bug
2018.10.23
	调整下载时尝试重试次数，解决下载速度过慢问题
2019.2.1
	解决程序大于64K时不能下载程序的问题