#include "stdafx.h"//这个头文件一定要放在第一

#include "My_Config.h"
#include "crc8_16.h"
#include "ThisComm.h"









//这个函数把用用分号分开的CString转化在数字数组中

int str_to_int(CString buf, int *ints)
{
	int offset = 0;
	CString temp;
	int trant_num = 0;//转换的数字个数
	while (!buf.IsEmpty())//如果字符串不为空
	{
		offset = buf.Find(_T(";"), 0);//找到第一个";"出现的位置
		if (offset == -1)//没有找到分号,只有一个数字了
		{
			ints[trant_num] = _ttoi(buf);
			trant_num++;
			return trant_num;
		}
		else
		{
			if (offset == 0)//分号出现在第一位
			{
				buf.Delete(0, 1);
				continue;
			}
			temp = buf.Left(offset);//提取最前面的数字
			ints[trant_num] = _ttoi(temp);
			trant_num++;
			buf.Delete(0, offset + 1);


		}
	}
	return trant_num;
}



















//进入配置模式
int my_config::my_entercfg(unsigned short addr)
{
	unsigned char data[100] = { 0 };
	unsigned char recv[100] = { 0 };
	int ret = 0;
	unsigned char crc[2];
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = addr >> 8;
	data[3] = addr;
	data[4] = 0x06;
	data[5] = 0x00;
	data[6] = 0x01;
	data[7] = 0x01;//进入配置模式
	Get_Crc16((unsigned char*)data, data[6]+7, (u8*)crc);
	data[8] = crc[0];
	data[9] = crc[1];
	if (com)
	{
		ret=com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	int i = 0;
	ret = -1;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 50))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				//if (addr == ((recv[2] << 8) | recv[3]))
				//{
					if ((data[4] | 0x80) == recv[4])
					{
						ret = (recv[7] << 8) | recv[8];//成功
						break;
					}
					else
					{
						ret = -4;
					}
				//}
				//else
				//{
				//	ret = -2;
				//}
			}
			else
			{
				ret = -3;
			}
		}
		i++;
		if (i > 5)
		{
			break;
		}
	}
	return ret;
}

//退出配置模式
int my_config::my_esccfg(unsigned short addr)
{
	unsigned char data[100];
	unsigned char recv[100];
	unsigned char crc[2];
	int ret = 0;
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = addr >> 8;
	data[3] = addr;
	data[4] = 0x06;
	data[5] = 0x00;
	data[6] = 0x01;
	data[7] = 0x00;//配置模式
	Get_Crc16((unsigned char*)data, data[6] + 7, (u8*)crc);
	data[8] = crc[0];
	data[9] = crc[1];
	if (com)
	{
		ret = com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	int i = 0;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 50))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				//if (addr == ((recv[2] << 8) | recv[3]))
				//{
					if ((data[4] | 0x80) == recv[4])
					{
						ret = (recv[7]<<8)|recv[8];//成功
						break;
					}
				//}
			}
		}
		i++;
		if (i > 5)
		{
			ret = -1;//失败
			break;
		}
	}
	return ret;
}

int my_config::my_cfgaddr(unsigned short addr, unsigned short newaddr,unsigned char type, unsigned char kttype)
{

	unsigned char data[100];
	unsigned char recv[100];
	unsigned char crc[2];
	int ret = 0;
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = addr >> 8;
	data[3] = addr;
	data[4] = 0x07;
	data[5] = 0x00;
	data[6] = 0x04;
	data[7] = newaddr>>8;
	data[8] = newaddr;
	data[9] = type;
	data[10] = kttype;
	Get_Crc16((unsigned char*)data, data[6] + 7, (u8*)crc);
	data[data[6] + 7] = crc[0];
	data[data[6] + 8] = crc[1];
	if (com)
	{
		ret = com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	int i = 0;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 50))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				//if (addr == ((recv[2] << 8) | recv[3]))
				//{
					if ((data[4] | 0x80) == recv[4])
					{
						ret = (recv[7] << 8) | recv[8];//成功
						break;
					}
				//}
			}
		}
		i++;
		if (i > 5)
		{
			ret = -1;//失败
			break;
		}
	}
	return ret;
}

int my_config::my_cfgstudy(unsigned short addr,unsigned char type)
{
	unsigned char data[100];
	unsigned char recv[100];
	unsigned char crc[2];
	int ret = 0;
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = addr >> 8;
	data[3] = addr;
	data[4] = 0x08;
	data[5] = 0x00;
	data[6] = 0x02;
	data[7] = 2;
	data[8] = type;
	Get_Crc16((unsigned char*)data, data[6] + 7, (u8*)crc);
	data[data[6] + 7] = crc[0];
	data[data[6] + 8] = crc[1];
	if (com)
	{
		ret = com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	int i = 0;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 50))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				//if (addr == ((recv[2] << 8) | recv[3]))
				//{
				if ((data[4] | 0x80) == recv[4])
				{
					ret = (recv[7] << 8) | recv[8];//成功
					break;
				}
				//}
			}
		}
		i++;
		if (i > 5)
		{
			ret = -1;//失败
			break;
		}
	}
	return ret;
}

int my_config::my_cfgcenter(unsigned short addr, unsigned short *daddrs, unsigned short nom,unsigned char *dtype)
{
	unsigned char data[100] = { 0 };
	unsigned char recv[100] = { 0 };
	unsigned char crc[2];
	unsigned short data_len = 0;
	int ret = 0;
	unsigned short i = 0;
	data_len = nom * 3 + 2;
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = addr >> 8;
	data[3] = addr;
	data[4] = 0x08;
	data[5] = data_len>>8;
	data[6] = data_len;
	data[7] = 1;//类型1，配置集中器中的设备地址
	for (i = 0; i < nom; i++)
	{
		data[i*3+8] = *daddrs>>8;
		data[i*3+9] = *daddrs;
		data[i * 3 + 10] = *dtype;
		daddrs+=2;//由于是int类型强行转化为short，所以地址加2
		dtype++;
	}
	Get_Crc16((unsigned char*)data, ((data[5]<<8)|data[6]) + 7, (u8*)crc);
	data[((data[5] << 8) | data[6]) + 7] = crc[0];
	data[((data[5] << 8) | data[6]) + 8] = crc[1];
	if (com)
	{
		ret = com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	i = 0;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 11))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				//if (addr == ((recv[2] << 8) | recv[3]))
				//{
					if ((data[4] | 0x80) == recv[4])
					{
						ret = (recv[7] << 8) | recv[8];//成功
						break;
					}
				//}
			}
		}
		i++;
		if (i > 5)
		{
			ret = -1;//失败
			break;
		}
	}
	return ret;
}

int my_config::my_cfgcenterip(unsigned short addr, CenterIP ip)
{
	unsigned char data[100];
	unsigned char recv[100];
	unsigned char crc[2];
	unsigned short data_len = 0;
	int ret = 0;
	unsigned short i = 0;
	data_len = 16+1;
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = addr >> 8;
	data[3] = addr;
	data[4] = 0x08;
	data[5] = data_len >> 8;
	data[6] = data_len;
	data[7] = 3;//类型3，配置集中器中的IP地址
	data[8] = ip.my_ip[0];
	data[9] = ip.my_ip[1];
	data[10] = ip.my_ip[2];
	data[11] = ip.my_ip[3];
	data[12] = ip.my_com >> 8;
	data[13] = ip.my_com;
	data[14] = ip.fw_ip[0];
	data[15] = ip.fw_ip[1];
	data[16] = ip.fw_ip[2];
	data[17] = ip.fw_ip[3];
	data[18] = ip.fw_com >> 8;
	data[19] = ip.fw_com;
	data[20] = ip.wg_ip[0];
	data[21] = ip.wg_ip[1];
	data[22] = ip.wg_ip[2];
	data[23] = ip.wg_ip[3];

	Get_Crc16((unsigned char*)data, ((data[5] << 8) | data[6]) + 7, (u8*)crc);
	data[((data[5] << 8) | data[6]) + 7] = crc[0];
	data[((data[5] << 8) | data[6]) + 8] = crc[1];
	if (com)
	{
		ret = com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	i = 0;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 11))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				//if (addr == ((recv[2] << 8) | recv[3]))
				//{
					if ((data[4] | 0x80) == recv[4])
					{
						ret = (recv[7] << 8) | recv[8];//成功
						break;
					}
				//}
			}
		}
		i++;
		if (i > 5)
		{
			ret = -1;//失败
			break;
		}
	}
	return ret;
}

int my_config::my_complitetime(unsigned char *tt)
{
	unsigned char data[100];
	unsigned char recv[100];
	unsigned char crc[2];
	int addr = 0;
	int ret = 0;
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = addr >> 8;
	data[3] = addr;
	data[4] = 0x01;
	data[5] = 0x00;
	data[6] = 0x02;
	data[7] = 0x00;
	data[8] = 0x32;
	Get_Crc16((unsigned char*)data, data[6] + 7, (u8*)crc);
	data[((data[5] << 8) | data[6]) + 7] = crc[0];
	data[((data[5] << 8) | data[6]) + 8] = crc[1];
	if (com)
	{
		ret = com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	int i = 0;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 50))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				//if (addr == ((recv[2] << 8) | recv[3]))
				//{
				if ((data[4] | 0x80) == recv[4])
				{
					ret = (recv[7] << 8) | recv[8];//成功
					unsigned char *temp = &recv[9];
					recv[6] -= 2;
					while (recv[6]--) { *tt++ = *temp++; }
					*tt = 0;
					break;
				}
				//}
			}
		}
		i++;
		if (i > 5)
		{
			ret = -1;//失败
			break;
		}
	}
	return ret;
}
		
						//参数是数据长度
int my_config::my_enteriap(unsigned short datasize)
{

	unsigned char data[100] = { 0 };
	unsigned char recv[100] = { 0 };
	int ret = 0;
	unsigned char crc[2];
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = 0x00;
	data[3] = 0x00;
	data[4] = 0x05;
	data[5] = 0;
	data[6] = 7;
	data[7] = 0x01;//更新程序
	data[8] = datasize >> 8;
	data[9] = datasize;
	data[10] = 0x08;
	data[11] = 0x00;
	data[12] = 0x28;
	data[13] = 0x00;
	Get_Crc16((unsigned char*)data, data[6] + 7, (u8*)crc);
	data[data[6] +7] = crc[0];
	data[data[6] +7+1] = crc[1];
	if (com)
	{
		ret = com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	int i = 0;
	ret = -1;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 11))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				if ((data[4] | 0x80) == recv[4])
				{
					ret = (recv[7] << 8) | recv[8];//成功
					break;
				}
				else //收到了干扰数据
				{
					ret = -4;
				}
			}
			else
			{
				ret = -3;
			}
		}
		i++;
		if (i > 5)
		{
			break;
		}
	}
	return ret;
}

int my_config::my_updataing(unsigned short length, unsigned short num_now, unsigned short num_all, unsigned char *buff)
{
	unsigned char data[100] = { 0 };
	unsigned char recv[100] = { 0 };
	int ret = 0;
	unsigned char crc[2];
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = 0x00;
	data[3] = 0x00;
	data[4] = 0x05;
	data[5] = 0;
	data[6] = length+5;
	data[7] = 0x03;//更新程序
	data[8] = num_now >> 8;
	data[9] = num_now;
	data[10] = num_all >> 8;
	data[11] = num_all;
	int t = 0;
	for (t = 0; t < length; t++)
	{
		data[12 + t] = buff[t];
	}
	Get_Crc16((unsigned char*)data, data[6] + 7, (u8*)crc);
	data[data[6] + 7] = crc[0];
	data[data[6] + 7 + 1] = crc[1];
	if (com)
	{
		ret = com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	int i = 0;
	ret = -1;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 11))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				if ((data[4] | 0x80) == recv[4])
				{
					ret = (recv[7] << 8) | recv[8];//成功
					break;
				}
				else
				{
					ret = -4;
				}
			}
			else
			{
				ret = -3;
			}
		}
		i++;
		if (i > 5)
		{
			break;
		}
	}
	return ret;
}


			//重启指定地址的设备
int my_config::my_reset(unsigned short addr)
{
	unsigned char data[100] = { 0 };
	unsigned char recv[100] = { 0 };
	int ret = 0;
	unsigned char crc[2];
	data[0] = 0xff;
	data[1] = 0xff;
	data[2] = addr>>8;
	data[3] = addr;
	data[4] = 0x09;
	data[5] = 0;
	data[6] = 1;
	data[7] = 0x02;//更新程序
	Get_Crc16((unsigned char*)data, data[6] + 7, (u8*)crc);
	data[data[6] + 7] = crc[0];
	data[data[6] + 7 + 1] = crc[1];
	if (com)
	{
		ret = com->SendComm(data, data[6] + 9);
	}
	else
	{
		return -6;//没有定义端口号
	}
	if (ret == 1)
	{
		return -5;//没有打开串口
	}
	int i = 0;
	ret = -1;
	while (1)
	{
		Sleep(200);
		if (com->RecvComm(recv, 11))
		{
			Get_Crc16((unsigned char*)recv, recv[6] + 7, (u8*)crc);
			if (crc[0] == recv[recv[6] + 7] && crc[1] == recv[recv[6] + 8])
			{
				if ((data[4] | 0x80) == recv[4])
				{
					ret = (recv[7] << 8) | recv[8];//成功
					break;
				}
				else //收到了干扰数据
				{
					ret = -4;
				}
			}
			else
			{
				ret = -3;
			}
		}
		i++;
		if (i > 5)
		{
			break;
		}
	}
	return ret;
}


					//获取错误类型
CString my_config::my_geterrtype(short errtype)
{
	CString err;
	switch (errtype)
	{
	case 0:
		err = _T("成功");
		break;
	case 1:
		err = _T("未知错误");
		break;
	case 2:
		err = _T("数据错误");
		break;
	case 3:
		err = _T("数据长度错误");
		break;
	case 4:
		err = _T("想要读取的数据长度错误");
		break;
	case 5:
		err = _T("不支持的命令类型");
		break;
	case 6:
		err = _T("没有连接");
		break;
	case 7:
		err = _T("采集器的地址不对");
		break;
	case 8:
		err = _T("不是可配置状态");
		break;
	case 9:
		err = _T("所要控制的设备与本机不符");
		break;
	case 10:
		err = _T("下位机操作超时");
		break;
	case -1:
		err = _T("没有收到下位机的返回");
		break;
	case -2:
		err = _T("失败");
		break;
	case -3:
		err = _T("CRC校验没通过");
		break;
	case -4:
		err = _T("收到了干扰");
		break;
	case -5:
		err = _T("没有打开串口");
		break;
	case -6:
		err = _T("没有指定端口号");
		break;
	default:
		err = _T("未定义的错误");
		break;
	}
	return err;
}




