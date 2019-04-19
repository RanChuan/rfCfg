
// NewCfgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NewCfg.h"
#include "NewCfgDlg.h"
#include "afxdialogex.h"
#include "ThisComm.h"
#include "hex2bin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNewCfgDlg 对话框



CNewCfgDlg::CNewCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEWCFG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNewCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO3, m_combo);
	DDX_Control(pDX, IDC_EDIT1, m_DeviceAddr);
	DDX_Control(pDX, IDC_COMBO1, m_DeviceType);
	DDX_Control(pDX, IDC_COMBO2, m_KTType);
	DDX_Control(pDX, IDC_COMBO4, m_StudyType);
	DDX_Control(pDX, IDC_EDIT4, m_CenterAddr);
	DDX_Control(pDX, IDC_COMBO5, m_DeviceType1);
	DDX_Control(pDX, IDC_COMBO6, m_DeviceType2);
	DDX_Control(pDX, IDC_COMBO7, m_DeviceType3);
	DDX_Control(pDX, IDC_COMBO8, m_DeviceType4);
	DDX_Control(pDX, IDC_COMBO9, m_DeviceType5);
	DDX_Control(pDX, IDC_EDIT5, m_DeviceAddr1);
	DDX_Control(pDX, IDC_EDIT6, m_DeviceAddr2);
	DDX_Control(pDX, IDC_EDIT7, m_DeviceAddr3);
	DDX_Control(pDX, IDC_EDIT8, m_DeviceAddr4);
	DDX_Control(pDX, IDC_EDIT9, m_DeviceAddr5);
	DDX_Control(pDX, IDC_EDIT10, m_MyIP);
	DDX_Control(pDX, IDC_EDIT11, m_MyCOM);
	DDX_Control(pDX, IDC_EDIT12, m_FwIP);
	DDX_Control(pDX, IDC_EDIT13, m_FwCOM);
	DDX_Control(pDX, IDC_EDIT14, m_WgIP);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_file);
	DDX_Control(pDX, IDC_EDIT2, m_RestAddr);
}

BEGIN_MESSAGE_MAP(CNewCfgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CNewCfgDlg::OnBnClickedOpenCom)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewCfgDlg::OnBnClickedFindDevice)
	ON_BN_CLICKED(IDC_BUTTON3, &CNewCfgDlg::OnBnClickedSendDeviceCfg)
	ON_BN_CLICKED(IDC_BUTTON5, &CNewCfgDlg::OnBnClickedEnterCfg)
	ON_BN_CLICKED(IDC_BUTTON7, &CNewCfgDlg::OnBnClickedEscCfg)
	ON_BN_CLICKED(IDC_BUTTON4, &CNewCfgDlg::OnBnClickedDeviceStudy)
	ON_BN_CLICKED(IDC_BUTTON6, &CNewCfgDlg::OnBnClickedCenterAddr)
	ON_BN_CLICKED(IDC_BUTTON8, &CNewCfgDlg::OnBnClickedSendAddrs)
	ON_BN_CLICKED(IDC_BUTTON9, &CNewCfgDlg::OnBnClickedCenterIP)
	ON_BN_CLICKED(IDC_BUTTON10, &CNewCfgDlg::OnBnClickedCompileTime)
	ON_BN_CLICKED(IDC_BUTTON11, &CNewCfgDlg::OnBnClickedUpdataApp)
	ON_BN_CLICKED(IDC_BUTTON12, &CNewCfgDlg::OnBnClickedRestDevice)
END_MESSAGE_MAP()


// CNewCfgDlg 消息处理程序

BOOL CNewCfgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CDC *pDC = GetDC();
	HDC hdc = pDC->m_hDC;//获得屏幕设备描述表句柄; 
	int iScrWidth = GetDeviceCaps(hdc, HORZRES);//获取屏幕水平分辨率; 
	int iScrHeight = GetDeviceCaps(hdc, VERTRES);//获取屏幕垂直分辨率; 
	ReleaseDC(pDC);//释放屏幕设备描述表 




				   //居中显示对话框
	MoveWindow(iScrWidth / 2 - 380, iScrHeight / 2 - 350, 760, 610, 0);
	ShowWindow(SW_SHOWNORMAL);


	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNewCfgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNewCfgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNewCfgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

ThisComm com;




			//打开串口
void CNewCfgDlg::OnBnClickedOpenCom()
{
	CString buf;
	m_combo.GetWindowText(buf);
	if (
		(buf[0] == _T('C')) && (buf[1] == _T('O')) && (buf[2] == _T('M')) && (buf[3] >= _T('0')) &&
		(buf[3] <= _T('9')) && (((buf[4] >= _T('0')) && (buf[4] <= _T('9')) && m_combo.GetWindowTextLength() == 5)
			|| m_combo.GetWindowTextLength() == 4)
		)
	{
		if (com.if_open)
		{
			com.CloseComm();
			buf.Format(_T("打开%s"), m_comid);
			if (!com.if_open) SetDlgItemText(IDC_BUTTON2, buf);

		}
		else
		{
			m_comid = buf;
			com.OpenComm(m_comid);
			buf.Format(_T("关闭%s"), m_comid);
			if (com.if_open) SetDlgItemText(IDC_BUTTON2, buf);

		}
	}
	else
	{
		MessageBox( _T("请选择一个COM口！"), _T("错误"));
	}


}


		//查找可以配置的设备
void CNewCfgDlg::OnBnClickedFindDevice()
{
	// TODO: 在此添加控件通知处理程序代码
}


			//发送设备的配置
void CNewCfgDlg::OnBnClickedSendDeviceCfg()
{
	my_config cfg;
	CString buf;
	int ret = 0;
	int addr = 0;//配置设备地址时，设备不理会
	int newaddr = 0;
	unsigned char type = 0;
	unsigned char kttype = 0;
	cfg.my_setcom(&com);

	m_DeviceAddr.GetWindowText(buf);
	newaddr = _ttoi(buf);
	if (newaddr == 0x00)
	{
		MessageBox( _T("请选择有效的设备地址！"),_T("错误"));
		return;
	}
	m_DeviceType.GetWindowText(buf);
	if (buf == _T("采集器"))
	{
		type = 0x01;
	}
	else if (buf == _T("空调控制器"))
	{
		type = 0x02;
	}
	else if (buf == _T("除湿机控制器"))
	{
		type = 0x03;
	}
	else if (buf == _T("加湿机控制器"))
	{
		type = 0x05;
	}
	else if (buf == _T("净化器控制器"))
	{
		type = 0x04;
	}
	else if (buf == _T("恒湿机"))
	{
		type = 0x06;
	}
	else
	{
		MessageBox( _T("请选择有效的设备类型！"), _T("错误"));
		return;
	}

	if (type == 0x02)
	{
		m_KTType.GetWindowText(buf);
		if (buf == _T("格力"))
		{
			kttype = 0x01;
		}
		else if (buf == _T("美的"))
		{
			kttype = 0x02;
		}
		else if (buf == _T("自定义"))
		{
			kttype = 0x03;
		}
		else
		{
			MessageBox(_T("请选择有效的空调类型！"), _T("错误"));
			return;
		}
	}


	ret = cfg.my_cfgaddr(addr, newaddr, type, kttype);
	if (ret == 0)
	{
		MessageBox( _T("设备配置成功！"), _T("提示"));
		return;
	}
	else
	{
		buf = _T("设备配置有可能失败了(~_~!)\r\n错误类型为：") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("错误"));
		return;
	}
}

				//进入配置模式
void CNewCfgDlg::OnBnClickedEnterCfg()
{
	int ret = 0;
	my_config cfg;
	CString buf;
	int addr = 0;//配置设备地址时，设备不理会
	cfg.my_setcom(&com);
	ret = cfg.my_entercfg(addr);
	if (ret == 0)
	{
		buf.Format(_T("设备进入配置模式成功！"), ret);
		MessageBox(buf, _T("提示"));
		return;
	}
	else
	{
		buf = _T("设备进入配置模式有可能失败了(~_~!)\r\n错误类型为：") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("错误"));
		return;
	}

}

			//退出配置模式
void CNewCfgDlg::OnBnClickedEscCfg()
{
	int ret = 0;
	my_config cfg;
	CString buf;
	int addr = 0;//配置设备地址时，设备不理会
	cfg.my_setcom(&com);
	ret = cfg.my_esccfg(addr);
	if (ret == 0)
	{
		buf.Format(_T("设备退出配置模式成功！"), ret);
		MessageBox(buf, _T("提示"));
		return;
	}
	else
	{
		buf = _T("设备退出配置模式有可能失败了(~_~!)\r\n错误类型为：") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("错误"));
		return;
	}

}


			//红外学习
void CNewCfgDlg::OnBnClickedDeviceStudy()
{
	int ret = 0;
	my_config cfg;
	CString buf;
	int addr = 0;//配置设备地址时，设备不理会
	unsigned char studytype = 0;
	cfg.my_setcom(&com);

	m_StudyType.GetWindowText(buf);
	if (buf == _T("空调升温"))
	{
		studytype = 3;
	}
	else if (buf == _T("空调降温"))
	{
		studytype = 4;
	}
	else if (buf == _T("空调开"))
	{
		studytype = 1;
	}
	else if (buf == _T("空调关"))
	{
		studytype = 2;
	}
	else if (buf == _T("净化器开"))
	{
		studytype = 1;
	}
	else if (buf == _T("净化器关"))
	{
		studytype = 2;
	}
	else
	{
		buf.Format(_T("请选择要学习的命令！"), ret);
		MessageBox(buf, _T("提示"));
		return;
	}

	ret = cfg.my_cfgstudy(addr, studytype);
	if (ret == 0)
	{
		buf.Format(_T("设备进入学习模式成功！"), ret);
		MessageBox(buf, _T("提示"));
		return;
	}
	else
	{
		buf = _T("设备进入学习模式有可能失败了(~_~!)\r\n错误类型为：") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("错误"));
		return;
	}

	
}

			//配置集中器的地址
void CNewCfgDlg::OnBnClickedCenterAddr()
{
	my_config cfg;
	CString buf;
	int ret = 0;
	int addr = 0;//配置设备地址时，设备不理会
	int newaddr = 0;
	unsigned char type = 0;
	unsigned char kttype = 0;
	cfg.my_setcom(&com);

	m_CenterAddr.GetWindowText(buf);
	newaddr = _ttoi(buf);
	if (newaddr == 0x00)
	{
		MessageBox(_T("请选择有效的设备地址！"), _T("错误"));
		return;
	}
	ret=cfg.my_cfgaddr(addr, newaddr, type, kttype);
	if (ret == 0x00)
	{
		MessageBox(_T("集中器地址配置成功！"), _T("提示"));
		return;
	}
	else 
	{
		buf = _T("集中器地址配置有可能失败了(~_~!)\r\n错误类型为：") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("错误"));
		return;
	}
}


				//发送设备地址
void CNewCfgDlg::OnBnClickedSendAddrs()
{
	my_config cfg;
	CString buf;
	int addrs[100] = { 0 };
	unsigned char dtype[100] = { 0 };
	int i = 0;
	int t = 0;
	int ret = 0;
	int addr = 0;//配置设备地址时，设备不理会
	int newaddr = 0;
	unsigned char type = 0;
	unsigned char kttype = 0;
	cfg.my_setcom(&com);

	m_DeviceAddr1.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType1.GetWindowText(buf);
		if (buf == _T("采集器")){type = 0x01;}
		else if (buf == _T("空调控制器")){type = 0x02;}
		else if (buf == _T("除湿机控制器")){type = 0x03;}
		else if (buf == _T("加湿机控制器")){type = 0x05;}
		else if (buf == _T("净化器控制器")){type = 0x04;}
		else if (buf == _T("恒湿机")){type = 0x06;}
		else{MessageBox(_T("请选择有效的设备类型！"), _T("错误"));return;}
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;

	m_DeviceAddr2.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType2.GetWindowText(buf);
		if (buf == _T("采集器")) { type = 0x01; }
		else if (buf == _T("空调控制器")) { type = 0x02; }
		else if (buf == _T("除湿机控制器")) { type = 0x03; }
		else if (buf == _T("加湿机控制器")) { type = 0x05; }
		else if (buf == _T("净化器控制器")) { type = 0x04; }
		else if (buf == _T("恒湿机")) { type = 0x06; }
		else { MessageBox(_T("请选择有效的设备类型！"), _T("错误")); return; }
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;

	m_DeviceAddr3.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType3.GetWindowText(buf);
		if (buf == _T("采集器")) { type = 0x01; }
		else if (buf == _T("空调控制器")) { type = 0x02; }
		else if (buf == _T("除湿机控制器")) { type = 0x03; }
		else if (buf == _T("加湿机控制器")) { type = 0x05; }
		else if (buf == _T("净化器控制器")) { type = 0x04; }
		else if (buf == _T("恒湿机")) { type = 0x06; }
		else { MessageBox(_T("请选择有效的设备类型！"), _T("错误")); return; }
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;

	m_DeviceAddr4.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType4.GetWindowText(buf);
		if (buf == _T("采集器")) { type = 0x01; }
		else if (buf == _T("空调控制器")) { type = 0x02; }
		else if (buf == _T("除湿机控制器")) { type = 0x03; }
		else if (buf == _T("加湿机控制器")) { type = 0x05; }
		else if (buf == _T("净化器控制器")) { type = 0x04; }
		else if (buf == _T("恒湿机")) { type = 0x06; }
		else { MessageBox(_T("请选择有效的设备类型！"), _T("错误")); return; }
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;

	m_DeviceAddr5.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType5.GetWindowText(buf);
		if (buf == _T("采集器")) { type = 0x01; }
		else if (buf == _T("空调控制器")) { type = 0x02; }
		else if (buf == _T("除湿机控制器")) { type = 0x03; }
		else if (buf == _T("加湿机控制器")) { type = 0x05; }
		else if (buf == _T("净化器控制器")) { type = 0x04; }
		else if (buf == _T("恒湿机")) { type = 0x06; }
		else { MessageBox(_T("请选择有效的设备类型！"), _T("错误")); return; }
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;
	if (i == 0)
	{
		MessageBox(_T("没有要配置的设备地址！"), _T("提示"));
		return;

	}

	ret=cfg.my_cfgcenter(addr, (unsigned short *)addrs, i, dtype);
	if (ret == 0x00)
	{
		MessageBox(_T("集中器设备地址添加成功！"), _T("提示"));
		return;
	}
	else
	{
		buf = _T("集中器设备地址添加有可能失败了(~_~!)\r\n错误类型为：") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("错误"));
		return;
	}

}

				//集中器上的IP地址
void CNewCfgDlg::OnBnClickedCenterIP()
{
	my_config cfg;
	CString buf;
	int my_ip[4] = { 0 };
	int fw_ip[4] = { 0 };
	int wg_ip[4] = { 0 };
	int my_com = 0;
	int fw_com = 0;
	CenterIP ip;
	int ret = 0;
	int addr = 0;//配置设备地址时，设备不理会
	cfg.my_setcom(&com);

	m_MyIP.GetWindowText(buf);
	ret = str_to_int(buf, my_ip);
	if (ret == 4)
	{
		ip.my_ip[0] = my_ip[0];
		ip.my_ip[1] = my_ip[1];
		ip.my_ip[2] = my_ip[2];
		ip.my_ip[3] = my_ip[3];
	}
	else
	{
		MessageBox(_T("集中器IP格式不正确！"), _T("提示"));
		return;
	}

	m_MyCOM.GetWindowText(buf);
	ret = str_to_int(buf, &my_com);
	if (ret)
	{
		ip.my_com = my_com;
	}
	else
	{
		MessageBox(_T("本机端口号不正确！"), _T("提示"));
		return;
	}

	m_FwIP.GetWindowText(buf);
	ret = str_to_int(buf, fw_ip);
	if (ret == 4)
	{
		ip.fw_ip[0] = fw_ip[0];
		ip.fw_ip[1] = fw_ip[1];
		ip.fw_ip[2] = fw_ip[2];
		ip.fw_ip[3] = fw_ip[3];
	}
	else
	{
		MessageBox(_T("服务器IP格式不正确！"), _T("提示"));
		return;
	}

	m_FwCOM.GetWindowText(buf);
	ret = str_to_int(buf, &fw_com);
	if (ret)
	{
		ip.fw_com = fw_com;
	}
	else
	{
		MessageBox(_T("服务器端口号不正确！"), _T("提示"));
		return;
	}

	m_WgIP.GetWindowText(buf);
	ret = str_to_int(buf, wg_ip);
	if (ret == 4)
	{
		ip.wg_ip[0] = wg_ip[0];
		ip.wg_ip[1] = fw_ip[1];
		ip.wg_ip[2] = wg_ip[2];
		ip.wg_ip[3] = wg_ip[3];
	}
	else
	{
		MessageBox(_T("网关IP格式不正确！"), _T("提示"));
		return;
	}
	ret = cfg.my_cfgcenterip(addr, ip);
	if (ret == 0x00)
	{
		MessageBox(_T("集中器IP地址配置成功！"), _T("提示"));
		return;
	}
	else
	{
		buf = _T("集中器IP地址配置有可能失败了(~_~!)\r\n错误类型为：") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("错误"));
		return;
	}
}


//查询电路板的软件编译时间
void CNewCfgDlg::OnBnClickedCompileTime()
{
	my_config cfg;
	CString buf;
	unsigned char data[100] = { 0 };
	int ret = 0;
	int addr = 0;//配置设备地址时，设备不理会
	cfg.my_setcom(&com);

	ret = cfg.my_complitetime(data);
	if (ret == 0)
	{
		buf = data;
		buf = _T("电路板软件编译时间为：\r\n ") + buf;
		//		buf.Format(_T("电路板软件编译时间为：\r\n s%"), buf);
		MessageBox(buf, _T("提示"));
		return;

	}
	else
	{
		buf = _T("查询电路板软件版本失败！\r\n错误类型为：") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("错误"));
		return;
	}
}







				//下载bin文件，输入文件名
int download_bin(CString buf, CNewCfgDlg *mywind)
{
	my_config cfg;
	HANDLE hfile;
	DWORD filesize;//文件总长度
	int ret = 0;
	unsigned char data[100] = { 0 };
	cfg.my_setcom(&com);

	hfile = CreateFile(buf, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hfile == (HANDLE)-1)
	{
		buf = _T("打开此文件失败：\r\n ") + buf + _T("\r\n请选择一个程序文件！");
		mywind->MessageBox(buf, _T("提示"));
		return 1;
	}
	filesize = GetFileSize(hfile, NULL);
	DWORD  real_read;//文件读取实际长度变量
	ret = ReadFile(hfile, data, 4, &real_read, NULL);
	DWORD truck = ((data[0]) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));
	if ((truck & 0x2FFE0000) != 0x20000000)
	{
		buf = _T("此文件不是合法的bin程序文件：\r\n ") + buf + _T("\r\n请选择一个程序文件！");
		mywind->MessageBox(buf, _T("提示"));
		CloseHandle(hfile);
		return 1;
	}
	ret = ReadFile(hfile, data + 4, 40, &real_read, NULL);
	int iap_i = 0;//尝试握手次数变量
	CString iap_txt;
	while (1)
	{
		iap_txt.Format(_T("尝试握手 %d/%d"), iap_i, 20);
		mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
		ret = cfg.my_enteriap(filesize);//参数是要写入的数据长度
		if ((ret <50) && (ret >= 0))break;
		if (ret == -1)
		{
			iap_i++;
			if (iap_i > 20) break;
		}
		else
		{
			break;
		}
	}
	int num_all = 0;
	int num_now = 1;
	num_all = filesize / 44;
	if (filesize % 44) num_all++;
	real_read = 44;
	int iaping = 0;
	while (ret == 0)
	{
		iap_txt.Format(_T("%d/%d"), num_now, num_all);
		mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
		ret = cfg.my_updataing(real_read, num_now, num_all, data);
		if (ret == -1)
		{
			iaping++;
			if (iaping > 20)//重复五次
			{
				break;
			}
			ret = 0;
		}
		else if ((ret <50) && (ret > 0))//
		{
			break;
		}
		else
		{
			iaping = 0;//复位重试次数
			if (num_all == num_now) break;
			num_now++;
			for (int a = 0; a < 100; a++) { data[a] = 0; }
			ReadFile(hfile, data, 44, &real_read, NULL);
		}

	}
	if (ret != 0)
	{
		buf = _T("下载程序失败！\r\n错误类型为：") + cfg.my_geterrtype(ret);
		mywind->MessageBox(buf, _T("错误"));
	}
	else
	{
		buf = _T("下载程序完成！");
		mywind->MessageBox(buf, _T("提示"));
	}
	CloseHandle(hfile);
	iap_txt = _T("下载程序");
	mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
	return  0;

}


//返回值是实际读取的字节数
DWORD GetData(unsigned char *datain, unsigned char *dataout, DWORD getlength,DWORD datain_length)
{
	static DWORD i = 0;
	DWORD a = 0;

	if (datain_length == 0) {
		i = 0;//修复有一次程序下载以后每次都失败的bug
		return 0;
	}
	for (a = 0; a< getlength; a++)
	{
		if (a + i == datain_length) break;
		dataout[a] = datain[a + i];
	}
	i += a;
	return a;
}



					//下载hex文件，输入文件名
int download_hex(CString buf, CNewCfgDlg *mywind)
{
	my_config cfg;
	Hex2Bin hex2bin;
	HANDLE hfile;
	DWORD filesize;//文件总长度
	int ret = 0;
	unsigned char data[100] = { 0 };
	cfg.my_setcom(&com);

	hfile = CreateFile(buf, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hfile == (HANDLE)-1)
	{
		buf = _T("打开此文件失败：\r\n ") + buf + _T("\r\n请选择一个程序文件！");
		mywind->MessageBox(buf, _T("提示"));
		return 1;
	}
	filesize = GetFileSize(hfile, NULL);
	char *hexdata = new char[filesize];
	unsigned char *bindata = new unsigned char[filesize];
	DWORD  real_read;//文件读取实际长度变量
	DWORD  hexaddr = 0;
	ret = ReadFile(hfile, hexdata, filesize, &real_read, NULL);
	CloseHandle(hfile);
	buf = hexdata;
	delete hexdata;
	ret = hex2bin.hex2bin(bindata, buf, &hexaddr,&filesize);
//	hfile = CreateFile(_T("F:\\川~\\VS2015\\2018.9.11 程序下载\\NewCfg\\Debug\\my.bin"), GENERIC_ALL, NULL, NULL, CREATE_NEW, NULL, NULL);
	if (ret != 0)
	{
		delete bindata;
		buf = _T("hex转bin失败！");
		mywind->MessageBox(buf, _T("提示"));
		return ret;
	}
//	ret=WriteFile(hfile, bindata, filesize, &real_read, NULL);
//	CloseHandle(hfile);
	if (hexaddr != 0x08002800)//程序地址不对
	{
		buf = _T("程序地址不符！");
		mywind->MessageBox(buf, _T("提示"));
		return 3;
	}
	
	DWORD truck = ((bindata[0]) | (bindata[1] << 8) | (bindata[2] << 16) | (bindata[3] << 24));
	if ((truck & 0x2FFE0000) != 0x20000000)
	{
		buf = _T("此文件不是合法的hex程序文件：\r\n ") + buf + _T("\r\n请选择一个程序文件！");
		mywind->MessageBox(buf, _T("提示"));
		return 1;
	}
	int iap_i = 0;//尝试握手次数变量
	CString iap_txt;
	while (1)
	{
		iap_txt.Format(_T("尝试握手 %d/%d"), iap_i, 20);
		mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
		ret = cfg.my_enteriap(filesize);//参数是要写入的数据长度
		if ((ret <50) && (ret >= 0))break;
		if (ret <= -1)
		{
			iap_i++;
			if (iap_i > 20) break;
		}
		else
		{
			break;
		}
	}
	
	GetData(bindata, data, 44, 0);//重置静态变量
	int num_all = 0;
	int num_now = 1;
	num_all = filesize / 44;
	if (filesize % 44) num_all++;
	real_read = GetData(bindata, data, 44, filesize);
	int iaping = 0;
	while (ret == 0)
	{
		iap_txt.Format(_T("%d/%d"), num_now, num_all);
		mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
		ret = cfg.my_updataing(real_read, num_now, num_all, data);
		if (ret <= -1)
		{
			iaping++;
			if (iaping > 20)//重复五次
			{
				break;
			}
			ret = 0;
		}
		else if ((ret <50) && (ret > 0))//
		{
			break;
		}
		else if (ret==0)
		{
			iaping = 0;//正常时复位重试次数
			if (num_all == num_now) break;
			num_now++;
			for (int a = 0; a < 100; a++) { data[a] = 0; }
			real_read=GetData(bindata, data, 44, filesize);
		}
		else
		{
			break;
		}

	}
	delete bindata;
	if (ret != 0)
	{
		buf = _T("下载程序失败！\r\n错误类型为：") + cfg.my_geterrtype(ret);
		mywind->MessageBox(buf, _T("错误"));
	}
	else
	{
		buf = _T("下载程序完成！");
		mywind->MessageBox(buf, _T("提示"));
	}
	iap_txt = _T("下载程序");
	mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
	return  0;

}













				//下载单片机程序的线程
DWORD WINAPI ThreadUpdataApp(LPVOID param)
{
	CString buf;
	CNewCfgDlg *mywind;
	int ret = 0;
	int addr = 0;//配置设备地址时，设备不理会
	mywind = (CNewCfgDlg*)param;

	mywind->m_file.GetWindowText(buf);

	if (buf.Right(4) == _T(".bin"))
	{
		ret = download_bin(buf, mywind);
	}
	else if (buf.Right(4) == _T(".hex"))
	{
		ret = download_hex(buf, mywind);
	}
	else
	{
		buf = _T("没有选择文件或不是程序文件！");
		mywind->MessageBox(buf, _T("提示"));
		return 1;
	}
	return ret;
}




//下载程序
void CNewCfgDlg::OnBnClickedUpdataApp()
{
	static DWORD dwThreadID = 0;
	HANDLE handleFirst;
	if (dwThreadID!=0)
	{
		CString buf;
		GetDlgItemText(IDC_BUTTON11,buf);
		if (buf != _T("下载程序"))
		{
			MessageBox(_T("程序下载任务正在执行！"), _T("提示"));
		}
		else
		{
			dwThreadID = 0;
		}
	}
	if (dwThreadID == 0)
	{
		handleFirst = CreateThread(NULL, 0, ThreadUpdataApp, 
			AfxGetApp()->m_pMainWnd,//专递主窗口的指针
			0, &dwThreadID);
	}

}




			//重启设备
void CNewCfgDlg::OnBnClickedRestDevice()
{
	my_config cfg;
	CString buf;
	int ret = 0;
	int addr = 0;//配置设备地址时，设备不理会
	cfg.my_setcom(&com);

	m_RestAddr.GetWindowText(buf);
	if (buf.IsEmpty())
	{
		buf = _T("请输入想要重启设备的地址！");
		MessageBox(buf, _T("提示"));
		return;
	}
	else
	{
		ret = cfg.my_reset(_ttoi(buf));
	}
	if (ret == 0)
	{
		buf = _T("操作成功！") ;
		MessageBox(buf, _T("提示"));
		return;

	}
	else
	{
		buf=_T("操作有可能失败了(~_~!)\r\n错误类型为：")+cfg.my_geterrtype(ret);
		MessageBox(buf, _T("错误"));
		return;
	}

}
