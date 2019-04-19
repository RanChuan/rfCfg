
// NewCfgDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CNewCfgDlg �Ի���



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


// CNewCfgDlg ��Ϣ�������

BOOL CNewCfgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CDC *pDC = GetDC();
	HDC hdc = pDC->m_hDC;//�����Ļ�豸��������; 
	int iScrWidth = GetDeviceCaps(hdc, HORZRES);//��ȡ��Ļˮƽ�ֱ���; 
	int iScrHeight = GetDeviceCaps(hdc, VERTRES);//��ȡ��Ļ��ֱ�ֱ���; 
	ReleaseDC(pDC);//�ͷ���Ļ�豸������ 




				   //������ʾ�Ի���
	MoveWindow(iScrWidth / 2 - 380, iScrHeight / 2 - 350, 760, 610, 0);
	ShowWindow(SW_SHOWNORMAL);


	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNewCfgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNewCfgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

ThisComm com;




			//�򿪴���
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
			buf.Format(_T("��%s"), m_comid);
			if (!com.if_open) SetDlgItemText(IDC_BUTTON2, buf);

		}
		else
		{
			m_comid = buf;
			com.OpenComm(m_comid);
			buf.Format(_T("�ر�%s"), m_comid);
			if (com.if_open) SetDlgItemText(IDC_BUTTON2, buf);

		}
	}
	else
	{
		MessageBox( _T("��ѡ��һ��COM�ڣ�"), _T("����"));
	}


}


		//���ҿ������õ��豸
void CNewCfgDlg::OnBnClickedFindDevice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


			//�����豸������
void CNewCfgDlg::OnBnClickedSendDeviceCfg()
{
	my_config cfg;
	CString buf;
	int ret = 0;
	int addr = 0;//�����豸��ַʱ���豸�����
	int newaddr = 0;
	unsigned char type = 0;
	unsigned char kttype = 0;
	cfg.my_setcom(&com);

	m_DeviceAddr.GetWindowText(buf);
	newaddr = _ttoi(buf);
	if (newaddr == 0x00)
	{
		MessageBox( _T("��ѡ����Ч���豸��ַ��"),_T("����"));
		return;
	}
	m_DeviceType.GetWindowText(buf);
	if (buf == _T("�ɼ���"))
	{
		type = 0x01;
	}
	else if (buf == _T("�յ�������"))
	{
		type = 0x02;
	}
	else if (buf == _T("��ʪ��������"))
	{
		type = 0x03;
	}
	else if (buf == _T("��ʪ��������"))
	{
		type = 0x05;
	}
	else if (buf == _T("������������"))
	{
		type = 0x04;
	}
	else if (buf == _T("��ʪ��"))
	{
		type = 0x06;
	}
	else
	{
		MessageBox( _T("��ѡ����Ч���豸���ͣ�"), _T("����"));
		return;
	}

	if (type == 0x02)
	{
		m_KTType.GetWindowText(buf);
		if (buf == _T("����"))
		{
			kttype = 0x01;
		}
		else if (buf == _T("����"))
		{
			kttype = 0x02;
		}
		else if (buf == _T("�Զ���"))
		{
			kttype = 0x03;
		}
		else
		{
			MessageBox(_T("��ѡ����Ч�Ŀյ����ͣ�"), _T("����"));
			return;
		}
	}


	ret = cfg.my_cfgaddr(addr, newaddr, type, kttype);
	if (ret == 0)
	{
		MessageBox( _T("�豸���óɹ���"), _T("��ʾ"));
		return;
	}
	else
	{
		buf = _T("�豸�����п���ʧ����(~_~!)\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("����"));
		return;
	}
}

				//��������ģʽ
void CNewCfgDlg::OnBnClickedEnterCfg()
{
	int ret = 0;
	my_config cfg;
	CString buf;
	int addr = 0;//�����豸��ַʱ���豸�����
	cfg.my_setcom(&com);
	ret = cfg.my_entercfg(addr);
	if (ret == 0)
	{
		buf.Format(_T("�豸��������ģʽ�ɹ���"), ret);
		MessageBox(buf, _T("��ʾ"));
		return;
	}
	else
	{
		buf = _T("�豸��������ģʽ�п���ʧ����(~_~!)\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("����"));
		return;
	}

}

			//�˳�����ģʽ
void CNewCfgDlg::OnBnClickedEscCfg()
{
	int ret = 0;
	my_config cfg;
	CString buf;
	int addr = 0;//�����豸��ַʱ���豸�����
	cfg.my_setcom(&com);
	ret = cfg.my_esccfg(addr);
	if (ret == 0)
	{
		buf.Format(_T("�豸�˳�����ģʽ�ɹ���"), ret);
		MessageBox(buf, _T("��ʾ"));
		return;
	}
	else
	{
		buf = _T("�豸�˳�����ģʽ�п���ʧ����(~_~!)\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("����"));
		return;
	}

}


			//����ѧϰ
void CNewCfgDlg::OnBnClickedDeviceStudy()
{
	int ret = 0;
	my_config cfg;
	CString buf;
	int addr = 0;//�����豸��ַʱ���豸�����
	unsigned char studytype = 0;
	cfg.my_setcom(&com);

	m_StudyType.GetWindowText(buf);
	if (buf == _T("�յ�����"))
	{
		studytype = 3;
	}
	else if (buf == _T("�յ�����"))
	{
		studytype = 4;
	}
	else if (buf == _T("�յ���"))
	{
		studytype = 1;
	}
	else if (buf == _T("�յ���"))
	{
		studytype = 2;
	}
	else if (buf == _T("��������"))
	{
		studytype = 1;
	}
	else if (buf == _T("��������"))
	{
		studytype = 2;
	}
	else
	{
		buf.Format(_T("��ѡ��Ҫѧϰ�����"), ret);
		MessageBox(buf, _T("��ʾ"));
		return;
	}

	ret = cfg.my_cfgstudy(addr, studytype);
	if (ret == 0)
	{
		buf.Format(_T("�豸����ѧϰģʽ�ɹ���"), ret);
		MessageBox(buf, _T("��ʾ"));
		return;
	}
	else
	{
		buf = _T("�豸����ѧϰģʽ�п���ʧ����(~_~!)\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("����"));
		return;
	}

	
}

			//���ü������ĵ�ַ
void CNewCfgDlg::OnBnClickedCenterAddr()
{
	my_config cfg;
	CString buf;
	int ret = 0;
	int addr = 0;//�����豸��ַʱ���豸�����
	int newaddr = 0;
	unsigned char type = 0;
	unsigned char kttype = 0;
	cfg.my_setcom(&com);

	m_CenterAddr.GetWindowText(buf);
	newaddr = _ttoi(buf);
	if (newaddr == 0x00)
	{
		MessageBox(_T("��ѡ����Ч���豸��ַ��"), _T("����"));
		return;
	}
	ret=cfg.my_cfgaddr(addr, newaddr, type, kttype);
	if (ret == 0x00)
	{
		MessageBox(_T("��������ַ���óɹ���"), _T("��ʾ"));
		return;
	}
	else 
	{
		buf = _T("��������ַ�����п���ʧ����(~_~!)\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("����"));
		return;
	}
}


				//�����豸��ַ
void CNewCfgDlg::OnBnClickedSendAddrs()
{
	my_config cfg;
	CString buf;
	int addrs[100] = { 0 };
	unsigned char dtype[100] = { 0 };
	int i = 0;
	int t = 0;
	int ret = 0;
	int addr = 0;//�����豸��ַʱ���豸�����
	int newaddr = 0;
	unsigned char type = 0;
	unsigned char kttype = 0;
	cfg.my_setcom(&com);

	m_DeviceAddr1.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType1.GetWindowText(buf);
		if (buf == _T("�ɼ���")){type = 0x01;}
		else if (buf == _T("�յ�������")){type = 0x02;}
		else if (buf == _T("��ʪ��������")){type = 0x03;}
		else if (buf == _T("��ʪ��������")){type = 0x05;}
		else if (buf == _T("������������")){type = 0x04;}
		else if (buf == _T("��ʪ��")){type = 0x06;}
		else{MessageBox(_T("��ѡ����Ч���豸���ͣ�"), _T("����"));return;}
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;

	m_DeviceAddr2.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType2.GetWindowText(buf);
		if (buf == _T("�ɼ���")) { type = 0x01; }
		else if (buf == _T("�յ�������")) { type = 0x02; }
		else if (buf == _T("��ʪ��������")) { type = 0x03; }
		else if (buf == _T("��ʪ��������")) { type = 0x05; }
		else if (buf == _T("������������")) { type = 0x04; }
		else if (buf == _T("��ʪ��")) { type = 0x06; }
		else { MessageBox(_T("��ѡ����Ч���豸���ͣ�"), _T("����")); return; }
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;

	m_DeviceAddr3.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType3.GetWindowText(buf);
		if (buf == _T("�ɼ���")) { type = 0x01; }
		else if (buf == _T("�յ�������")) { type = 0x02; }
		else if (buf == _T("��ʪ��������")) { type = 0x03; }
		else if (buf == _T("��ʪ��������")) { type = 0x05; }
		else if (buf == _T("������������")) { type = 0x04; }
		else if (buf == _T("��ʪ��")) { type = 0x06; }
		else { MessageBox(_T("��ѡ����Ч���豸���ͣ�"), _T("����")); return; }
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;

	m_DeviceAddr4.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType4.GetWindowText(buf);
		if (buf == _T("�ɼ���")) { type = 0x01; }
		else if (buf == _T("�յ�������")) { type = 0x02; }
		else if (buf == _T("��ʪ��������")) { type = 0x03; }
		else if (buf == _T("��ʪ��������")) { type = 0x05; }
		else if (buf == _T("������������")) { type = 0x04; }
		else if (buf == _T("��ʪ��")) { type = 0x06; }
		else { MessageBox(_T("��ѡ����Ч���豸���ͣ�"), _T("����")); return; }
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;

	m_DeviceAddr5.GetWindowText(buf);
	ret = str_to_int(buf, &addrs[i]);
	if (ret)
	{
		m_DeviceType5.GetWindowText(buf);
		if (buf == _T("�ɼ���")) { type = 0x01; }
		else if (buf == _T("�յ�������")) { type = 0x02; }
		else if (buf == _T("��ʪ��������")) { type = 0x03; }
		else if (buf == _T("��ʪ��������")) { type = 0x05; }
		else if (buf == _T("������������")) { type = 0x04; }
		else if (buf == _T("��ʪ��")) { type = 0x06; }
		else { MessageBox(_T("��ѡ����Ч���豸���ͣ�"), _T("����")); return; }
		for (t = i; t < i + ret; t++) { dtype[t] = type; }
	}
	i += ret;
	if (i == 0)
	{
		MessageBox(_T("û��Ҫ���õ��豸��ַ��"), _T("��ʾ"));
		return;

	}

	ret=cfg.my_cfgcenter(addr, (unsigned short *)addrs, i, dtype);
	if (ret == 0x00)
	{
		MessageBox(_T("�������豸��ַ��ӳɹ���"), _T("��ʾ"));
		return;
	}
	else
	{
		buf = _T("�������豸��ַ����п���ʧ����(~_~!)\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("����"));
		return;
	}

}

				//�������ϵ�IP��ַ
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
	int addr = 0;//�����豸��ַʱ���豸�����
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
		MessageBox(_T("������IP��ʽ����ȷ��"), _T("��ʾ"));
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
		MessageBox(_T("�����˿ںŲ���ȷ��"), _T("��ʾ"));
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
		MessageBox(_T("������IP��ʽ����ȷ��"), _T("��ʾ"));
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
		MessageBox(_T("�������˿ںŲ���ȷ��"), _T("��ʾ"));
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
		MessageBox(_T("����IP��ʽ����ȷ��"), _T("��ʾ"));
		return;
	}
	ret = cfg.my_cfgcenterip(addr, ip);
	if (ret == 0x00)
	{
		MessageBox(_T("������IP��ַ���óɹ���"), _T("��ʾ"));
		return;
	}
	else
	{
		buf = _T("������IP��ַ�����п���ʧ����(~_~!)\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("����"));
		return;
	}
}


//��ѯ��·����������ʱ��
void CNewCfgDlg::OnBnClickedCompileTime()
{
	my_config cfg;
	CString buf;
	unsigned char data[100] = { 0 };
	int ret = 0;
	int addr = 0;//�����豸��ַʱ���豸�����
	cfg.my_setcom(&com);

	ret = cfg.my_complitetime(data);
	if (ret == 0)
	{
		buf = data;
		buf = _T("��·���������ʱ��Ϊ��\r\n ") + buf;
		//		buf.Format(_T("��·���������ʱ��Ϊ��\r\n s%"), buf);
		MessageBox(buf, _T("��ʾ"));
		return;

	}
	else
	{
		buf = _T("��ѯ��·������汾ʧ�ܣ�\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		MessageBox(buf, _T("����"));
		return;
	}
}







				//����bin�ļ��������ļ���
int download_bin(CString buf, CNewCfgDlg *mywind)
{
	my_config cfg;
	HANDLE hfile;
	DWORD filesize;//�ļ��ܳ���
	int ret = 0;
	unsigned char data[100] = { 0 };
	cfg.my_setcom(&com);

	hfile = CreateFile(buf, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hfile == (HANDLE)-1)
	{
		buf = _T("�򿪴��ļ�ʧ�ܣ�\r\n ") + buf + _T("\r\n��ѡ��һ�������ļ���");
		mywind->MessageBox(buf, _T("��ʾ"));
		return 1;
	}
	filesize = GetFileSize(hfile, NULL);
	DWORD  real_read;//�ļ���ȡʵ�ʳ��ȱ���
	ret = ReadFile(hfile, data, 4, &real_read, NULL);
	DWORD truck = ((data[0]) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));
	if ((truck & 0x2FFE0000) != 0x20000000)
	{
		buf = _T("���ļ����ǺϷ���bin�����ļ���\r\n ") + buf + _T("\r\n��ѡ��һ�������ļ���");
		mywind->MessageBox(buf, _T("��ʾ"));
		CloseHandle(hfile);
		return 1;
	}
	ret = ReadFile(hfile, data + 4, 40, &real_read, NULL);
	int iap_i = 0;//�������ִ�������
	CString iap_txt;
	while (1)
	{
		iap_txt.Format(_T("�������� %d/%d"), iap_i, 20);
		mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
		ret = cfg.my_enteriap(filesize);//������Ҫд������ݳ���
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
			if (iaping > 20)//�ظ����
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
			iaping = 0;//��λ���Դ���
			if (num_all == num_now) break;
			num_now++;
			for (int a = 0; a < 100; a++) { data[a] = 0; }
			ReadFile(hfile, data, 44, &real_read, NULL);
		}

	}
	if (ret != 0)
	{
		buf = _T("���س���ʧ�ܣ�\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		mywind->MessageBox(buf, _T("����"));
	}
	else
	{
		buf = _T("���س�����ɣ�");
		mywind->MessageBox(buf, _T("��ʾ"));
	}
	CloseHandle(hfile);
	iap_txt = _T("���س���");
	mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
	return  0;

}


//����ֵ��ʵ�ʶ�ȡ���ֽ���
DWORD GetData(unsigned char *datain, unsigned char *dataout, DWORD getlength,DWORD datain_length)
{
	static DWORD i = 0;
	DWORD a = 0;

	if (datain_length == 0) {
		i = 0;//�޸���һ�γ��������Ժ�ÿ�ζ�ʧ�ܵ�bug
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



					//����hex�ļ��������ļ���
int download_hex(CString buf, CNewCfgDlg *mywind)
{
	my_config cfg;
	Hex2Bin hex2bin;
	HANDLE hfile;
	DWORD filesize;//�ļ��ܳ���
	int ret = 0;
	unsigned char data[100] = { 0 };
	cfg.my_setcom(&com);

	hfile = CreateFile(buf, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hfile == (HANDLE)-1)
	{
		buf = _T("�򿪴��ļ�ʧ�ܣ�\r\n ") + buf + _T("\r\n��ѡ��һ�������ļ���");
		mywind->MessageBox(buf, _T("��ʾ"));
		return 1;
	}
	filesize = GetFileSize(hfile, NULL);
	char *hexdata = new char[filesize];
	unsigned char *bindata = new unsigned char[filesize];
	DWORD  real_read;//�ļ���ȡʵ�ʳ��ȱ���
	DWORD  hexaddr = 0;
	ret = ReadFile(hfile, hexdata, filesize, &real_read, NULL);
	CloseHandle(hfile);
	buf = hexdata;
	delete hexdata;
	ret = hex2bin.hex2bin(bindata, buf, &hexaddr,&filesize);
//	hfile = CreateFile(_T("F:\\��~\\VS2015\\2018.9.11 ��������\\NewCfg\\Debug\\my.bin"), GENERIC_ALL, NULL, NULL, CREATE_NEW, NULL, NULL);
	if (ret != 0)
	{
		delete bindata;
		buf = _T("hexתbinʧ�ܣ�");
		mywind->MessageBox(buf, _T("��ʾ"));
		return ret;
	}
//	ret=WriteFile(hfile, bindata, filesize, &real_read, NULL);
//	CloseHandle(hfile);
	if (hexaddr != 0x08002800)//�����ַ����
	{
		buf = _T("�����ַ������");
		mywind->MessageBox(buf, _T("��ʾ"));
		return 3;
	}
	
	DWORD truck = ((bindata[0]) | (bindata[1] << 8) | (bindata[2] << 16) | (bindata[3] << 24));
	if ((truck & 0x2FFE0000) != 0x20000000)
	{
		buf = _T("���ļ����ǺϷ���hex�����ļ���\r\n ") + buf + _T("\r\n��ѡ��һ�������ļ���");
		mywind->MessageBox(buf, _T("��ʾ"));
		return 1;
	}
	int iap_i = 0;//�������ִ�������
	CString iap_txt;
	while (1)
	{
		iap_txt.Format(_T("�������� %d/%d"), iap_i, 20);
		mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
		ret = cfg.my_enteriap(filesize);//������Ҫд������ݳ���
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
	
	GetData(bindata, data, 44, 0);//���þ�̬����
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
			if (iaping > 20)//�ظ����
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
			iaping = 0;//����ʱ��λ���Դ���
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
		buf = _T("���س���ʧ�ܣ�\r\n��������Ϊ��") + cfg.my_geterrtype(ret);
		mywind->MessageBox(buf, _T("����"));
	}
	else
	{
		buf = _T("���س�����ɣ�");
		mywind->MessageBox(buf, _T("��ʾ"));
	}
	iap_txt = _T("���س���");
	mywind->SetDlgItemText(IDC_BUTTON11, iap_txt);
	return  0;

}













				//���ص�Ƭ��������߳�
DWORD WINAPI ThreadUpdataApp(LPVOID param)
{
	CString buf;
	CNewCfgDlg *mywind;
	int ret = 0;
	int addr = 0;//�����豸��ַʱ���豸�����
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
		buf = _T("û��ѡ���ļ����ǳ����ļ���");
		mywind->MessageBox(buf, _T("��ʾ"));
		return 1;
	}
	return ret;
}




//���س���
void CNewCfgDlg::OnBnClickedUpdataApp()
{
	static DWORD dwThreadID = 0;
	HANDLE handleFirst;
	if (dwThreadID!=0)
	{
		CString buf;
		GetDlgItemText(IDC_BUTTON11,buf);
		if (buf != _T("���س���"))
		{
			MessageBox(_T("����������������ִ�У�"), _T("��ʾ"));
		}
		else
		{
			dwThreadID = 0;
		}
	}
	if (dwThreadID == 0)
	{
		handleFirst = CreateThread(NULL, 0, ThreadUpdataApp, 
			AfxGetApp()->m_pMainWnd,//ר�������ڵ�ָ��
			0, &dwThreadID);
	}

}




			//�����豸
void CNewCfgDlg::OnBnClickedRestDevice()
{
	my_config cfg;
	CString buf;
	int ret = 0;
	int addr = 0;//�����豸��ַʱ���豸�����
	cfg.my_setcom(&com);

	m_RestAddr.GetWindowText(buf);
	if (buf.IsEmpty())
	{
		buf = _T("��������Ҫ�����豸�ĵ�ַ��");
		MessageBox(buf, _T("��ʾ"));
		return;
	}
	else
	{
		ret = cfg.my_reset(_ttoi(buf));
	}
	if (ret == 0)
	{
		buf = _T("�����ɹ���") ;
		MessageBox(buf, _T("��ʾ"));
		return;

	}
	else
	{
		buf=_T("�����п���ʧ����(~_~!)\r\n��������Ϊ��")+cfg.my_geterrtype(ret);
		MessageBox(buf, _T("����"));
		return;
	}

}
