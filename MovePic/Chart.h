// Chart.h: interface for the CChart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHART_H__394B3BA0_4FD0_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_CHART_H__394B3BA0_4FD0_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMovePicView;

class CChart
{
public:
	void SetDrawTitle(BOOL bDraw);
	void SetDrawLegend(BOOL bDraw);
	void SetCtrl(CMovePicView * pCtrl);
	virtual ~CChart();

protected:
	CChart();
	virtual BOOL Draw(CRect * pRect, CDC * pDC);
	virtual void FinishDraw(CRect * pRect, CDC * pDC);
	CMovePicView * m_pCtrl;

protected:
	HRGN m_rgnOld;
	CRgn m_rgn;
	
	int m_nPieces, m_nSeriesesIncluded, m_nSeriesesToDraw;
	double m_fMaxTotal, m_fMinTotal;
	CArray<double, double> m_arTotal;
	int m_nRows, m_nSerieses;

	BOOL m_bBrhDirty;
	CBrush * m_pBrhArr, * m_pBrhOld;
	BOOL m_bHasTitle, m_bHasLegend;
	CRect m_rtPic;
};

#endif // !defined(AFX_CHART_H__394B3BA0_4FD0_11D3_A7FE_0080C8763FA4__INCLUDED_)
