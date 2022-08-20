// MovePic.h : main header file for the MOVEPIC application
//

#if !defined(AFX_MOVEPIC_H__CDC3F504_F315_11D2_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_MOVEPIC_H__CDC3F504_F315_11D2_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMovePicApp:
// See MovePic.cpp for the implementation of this class
//

class CMovePicApp : public CWinApp
{
public:
	CMovePicApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovePicApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMovePicApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEPIC_H__CDC3F504_F315_11D2_A7FE_0080C8763FA4__INCLUDED_)
