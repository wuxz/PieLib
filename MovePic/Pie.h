// Pie.h: interface for the CPie class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIE_H__0A526E20_4C08_11D3_A7FE_0080C8763FA4__INCLUDED_)
#define AFX_PIE_H__0A526E20_4C08_11D3_A7FE_0080C8763FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "chart.h"

class CPie : public CChart
{
public:
	void SetDrawPieTitle(BOOL b);
	virtual BOOL Draw(CRect * pRect, CDC * pDC);
	CPie();
	virtual ~CPie();

protected:
	CArray<double, double> m_arSum;
	POINT * m_pPtArr;
	BOOL m_bHasPieTitle;

protected:
	virtual void FinishDraw(CRect * pRect, CDC * pDC);
};

#endif // !defined(AFX_PIE_H__0A526E20_4C08_11D3_A7FE_0080C8763FA4__INCLUDED_)
