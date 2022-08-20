// MovePicDoc.h : interface of the CMovePicDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEPICDOC_H__CDC3F50A_F315_11D2_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_MOVEPICDOC_H__CDC3F50A_F315_11D2_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMovePicDoc : public CDocument
{
protected: // create from serialization only
	CMovePicDoc();
	DECLARE_DYNCREATE(CMovePicDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovePicDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMovePicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMovePicDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEPICDOC_H__CDC3F50A_F315_11D2_A7FE_0080C8763FA4__INCLUDED_)
