
// NewCfgDlg.h : 头文件
//

#pragma once
#include "My_Config.h"
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CNewCfgDlg 对话框
class CNewCfgDlg : public CDialogEx
{
// 构造
public:
	CNewCfgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWCFG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenCom();

public:
	CString m_comid = _T("COM1");

	// 串口号
	CComboBox m_combo;
	afx_msg void OnBnClickedFindDevice();
	// 采集器或控制器的地址
	CEdit m_DeviceAddr;
	// 设备类型
	CComboBox m_DeviceType;
	// 空调类型
	CComboBox m_KTType;
	// 学习的类型
	CComboBox m_StudyType;
	// 集中器地址
	CEdit m_CenterAddr;
	afx_msg void OnBnClickedSendDeviceCfg();
	afx_msg void OnBnClickedEnterCfg();
	afx_msg void OnBnClickedEscCfg();
	afx_msg void OnBnClickedDeviceStudy();
	afx_msg void OnBnClickedCenterAddr();
	// 设备类型1，用于配置集中器
	CComboBox m_DeviceType1;
	// 设备类型2
	CComboBox m_DeviceType2;
	// 设备类型3
	CComboBox m_DeviceType3;
	// 设备类型4
	CComboBox m_DeviceType4;
	// 设备类型5
	CComboBox m_DeviceType5;
	// 设备地址1
	CEdit m_DeviceAddr1;
	// 设备地址2
	CEdit m_DeviceAddr2;
	// 设备地址2
	CEdit m_DeviceAddr3;
	// 设备地址4
	CEdit m_DeviceAddr4;
	// 设备地址5
	CEdit m_DeviceAddr5;
	afx_msg void OnBnClickedSendAddrs();
	// 本机ip地址
	CEdit m_MyIP;
	// 本机端口号
	CEdit m_MyCOM;
	// 服务器ip地址
	CEdit m_FwIP;
	// 服务器端口号
	CEdit m_FwCOM;
	// 网关ip地址
	CEdit m_WgIP;
	afx_msg void OnBnClickedCenterIP();
	afx_msg void OnBnClickedCompileTime();
	afx_msg void OnBnClickedUpdataApp();
	// 打开文件，
	CMFCEditBrowseCtrl m_file;
	// 重启指定地址的设备
	CEdit m_RestAddr;
	afx_msg void OnBnClickedRestDevice();
};
