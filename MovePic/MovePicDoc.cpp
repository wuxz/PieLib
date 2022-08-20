// MovePicDoc.cpp : implementation of the CMovePicDoc class
//

#include "stdafx.h"
#include "MovePic.h"

#include "MovePicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMovePicDoc

IMPLEMENT_DYNCREATE(CMovePicDoc, CDocument)

BEGIN_MESSAGE_MAP(CMovePicDoc, CDocument)
	//{{AFX_MSG_MAP(CMovePicDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovePicDoc construction/destruction

CMovePicDoc::CMovePicDoc()
{
	// TODO: add one-time construction code here

}

CMovePicDoc::~CMovePicDoc()
{
}

BOOL CMovePicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMovePicDoc serialization

void CMovePicDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMovePicDoc diagnostics

#ifdef _DEBUG
void CMovePicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMovePicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMovePicDoc commands
