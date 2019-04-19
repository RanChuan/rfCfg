
// NewCfgDlg.h : ͷ�ļ�
//

#pragma once
#include "My_Config.h"
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CNewCfgDlg �Ի���
class CNewCfgDlg : public CDialogEx
{
// ����
public:
	CNewCfgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWCFG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenCom();

public:
	CString m_comid = _T("COM1");

	// ���ں�
	CComboBox m_combo;
	afx_msg void OnBnClickedFindDevice();
	// �ɼ�����������ĵ�ַ
	CEdit m_DeviceAddr;
	// �豸����
	CComboBox m_DeviceType;
	// �յ�����
	CComboBox m_KTType;
	// ѧϰ������
	CComboBox m_StudyType;
	// ��������ַ
	CEdit m_CenterAddr;
	afx_msg void OnBnClickedSendDeviceCfg();
	afx_msg void OnBnClickedEnterCfg();
	afx_msg void OnBnClickedEscCfg();
	afx_msg void OnBnClickedDeviceStudy();
	afx_msg void OnBnClickedCenterAddr();
	// �豸����1���������ü�����
	CComboBox m_DeviceType1;
	// �豸����2
	CComboBox m_DeviceType2;
	// �豸����3
	CComboBox m_DeviceType3;
	// �豸����4
	CComboBox m_DeviceType4;
	// �豸����5
	CComboBox m_DeviceType5;
	// �豸��ַ1
	CEdit m_DeviceAddr1;
	// �豸��ַ2
	CEdit m_DeviceAddr2;
	// �豸��ַ2
	CEdit m_DeviceAddr3;
	// �豸��ַ4
	CEdit m_DeviceAddr4;
	// �豸��ַ5
	CEdit m_DeviceAddr5;
	afx_msg void OnBnClickedSendAddrs();
	// ����ip��ַ
	CEdit m_MyIP;
	// �����˿ں�
	CEdit m_MyCOM;
	// ������ip��ַ
	CEdit m_FwIP;
	// �������˿ں�
	CEdit m_FwCOM;
	// ����ip��ַ
	CEdit m_WgIP;
	afx_msg void OnBnClickedCenterIP();
	afx_msg void OnBnClickedCompileTime();
	afx_msg void OnBnClickedUpdataApp();
	// ���ļ���
	CMFCEditBrowseCtrl m_file;
	// ����ָ����ַ���豸
	CEdit m_RestAddr;
	afx_msg void OnBnClickedRestDevice();
};
