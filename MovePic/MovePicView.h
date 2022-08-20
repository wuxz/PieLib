// MovePicView.h : interface of the CMovePicView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEPICVIEW_H__CDC3F50C_F315_11D2_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_MOVEPICVIEW_H__CDC3F50C_F315_11D2_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "pie.h"
class CMovePicDoc;

class CMovePicView : public CView
{
protected: // create from serialization only
	CMovePicView();
	DECLARE_DYNCREATE(CMovePicView);

// Attributes
public:
	CMovePicDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovePicView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nCoordUsed;
	BOOL m_bCoordUsed[30][30];
	CArray<double * , double * > m_arDatas;
	CArray<int, int> m_arUsage;

	CPie pie;

	virtual ~CMovePicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void DrawCube(CDC * pDC, int cx, int cy, int x, int y, int z);
	void EllipseEnlarge(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nTotalWidth, int nTotalHeight, int nWidth, int nHeight, int nPattern, int nSpeed);
	void FourPieces(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nTotalWidth, int nTotalHeight, int nWidth, int nHeight, int nPattern, int nSpeed);
	void PullIn(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nTotalWidth, int nTotalHeight, int nWidth, int nHeight, int nPattern, int nSpeed);
	void WindOut(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nTotalWidth, int nTotalHeight, int nWidth, int nHeight, int nPattern, int nSpeed);
	void WindIn(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nWidth, int nHeight, int nPattern, int nSpeed);
	void MirrorBand(CDC * pDCSrc, CDC * pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nBandWidth, int nBandHeight, int nPattern);
	BOOL m_bXorYUsed[2048];
	int GetRandXorY(int nLimit);
	void RandBlock(CDC *pDCSrc, CDC * pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nWidth, int nHeight, int nPattern, int nSpeed);
	DWORD GetRandValue();
	void FadeIn(CDC *pDCSrc, CDC * pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nWidth, int nHeight, int nSpeed);
	int CalcShiftBits(DWORD dwMask);
	void SlideShow(CDC * pDCSrc, CDC * pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nWidth, int nHeight, int nPattern, int nSpeed = 0);
	//{{AFX_MSG(CMovePicView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MovePicView.cpp
inline CMovePicDoc* CMovePicView::GetDocument()
   { return (CMovePicDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEPICVIEW_H__CDC3F50C_F315_11D2_A7FE_0080C8763FA4__INCLUDED_)
