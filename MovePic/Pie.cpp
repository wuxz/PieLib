// Pie.cpp: implementation of the CPie class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MovePic.h"
#include "Pie.h"
#include "movepicview.h"
#include "math.h"
#include "chart.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define pi 3.1416
#define nPieSpace 10

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPie::CPie()
{
	m_bHasPieTitle = TRUE;
}

CPie::~CPie()
{

}

BOOL CPie::Draw(CRect * pRect, CDC *pDC)
{
	pDC->Pie(pRect, CPoint(pRect->right, pRect->CenterPoint().y - 20), CPoint(pRect->right, pRect->CenterPoint().y -21));
	return TRUE;

	m_arSum.RemoveAll();
	m_pPtArr = NULL;

	if (!CChart::Draw(pRect, pDC))
	{
		FinishDraw(pRect, pDC);
		return FALSE;
	}

	double fCurrtPieTotal = 0;
	int i, j, k, m;
	CSize szChar;
	double fRatio;
	int nRad;
	int nPieWidth;
	int nPieRealWidth;
	int nPieShiftX, nPieShiftY;
	CRect rtPie;
	CString strPie;
	POINT ptCenter;

	m_pPtArr = new POINT[m_nSeriesesIncluded + 1];

	nPieWidth = min(m_rtPic.Width(), m_rtPic.Height());
	
	i = 1;
	
	BOOL bHasPieTitle = m_bHasPieTitle;

	while (nPieWidth >= 2 + nPieSpace && (!bHasPieTitle || (bHasPieTitle && nPieWidth >= 2 + 20)) && m_rtPic.Width() / (nPieWidth + nPieSpace) * (m_rtPic.Height() / (nPieWidth + (bHasPieTitle ? 20 : 0))) < m_nRows)
	{
		i ++;
		nPieWidth = min(m_rtPic.Width(), m_rtPic.Height()) / i;
	}

	if (bHasPieTitle && nPieWidth <= 2 + 20)
	{
		bHasPieTitle = FALSE;
		i = 1;

		while (nPieWidth >= 2 + nPieSpace && m_rtPic.Width() / (nPieWidth + nPieSpace) * (m_rtPic.Height() / (nPieWidth) < m_nRows))
		{
			i ++;
			nPieWidth = min(m_rtPic.Width(), m_rtPic.Height()) / i;
		}
	}

	if (nPieWidth < 2 + nPieSpace)
	{
		FinishDraw(pRect, pDC);
		return FALSE;
	}
	
	nPieShiftX = (m_rtPic.Width() - min(m_rtPic.Width() / (nPieWidth + nPieSpace), m_nRows) * (nPieWidth + nPieSpace)) / 2;
	nPieShiftY = (m_rtPic.Height() - (int)((float)m_nRows / min(m_rtPic.Width() / (nPieWidth + nPieSpace), m_nRows) + 0.999) * (nPieWidth + (bHasPieTitle ? 20 : 0))) / 2;

	pDC->SetTextAlign(TA_CENTER);

	for (m = 0; m < m_nRows; m ++)
	{
		nPieRealWidth = (int)(m_arTotal[m] * nPieWidth / m_fMaxTotal);
		if (nPieRealWidth < 2 + nPieSpace)
			continue;

		rtPie.left = m_rtPic.left + m % (m_rtPic.Width() / (nPieWidth + nPieSpace)) * (nPieWidth + nPieSpace);
		rtPie.top = m_rtPic.top + m / (m_rtPic.Width() / (nPieWidth + nPieSpace)) * (nPieWidth + (bHasPieTitle ? 20 : 0));
		rtPie.left += nPieShiftX;
		rtPie.top += nPieShiftY;
		rtPie.right = rtPie.left + nPieWidth;
		rtPie.bottom = rtPie.top + nPieWidth + (bHasPieTitle ? 20 : 0);
		
		if (bHasPieTitle)
		{
			strPie.Format(_T("R%d"), m + 1);
			pDC->TextOut(rtPie.CenterPoint().x, rtPie.top, strPie);
		}

		rtPie.left += (nPieWidth - nPieRealWidth) / 2;
		rtPie.top += (nPieWidth - nPieRealWidth) / 2 +  + (bHasPieTitle ? 20 : 0);

		rtPie.right = rtPie.left + nPieRealWidth;
		rtPie.bottom = rtPie.top + nPieRealWidth;

		fRatio = 0;
		nRad = rtPie.Width() / 2;
		ptCenter = rtPie.CenterPoint();
		
		m_pPtArr[0].x = rtPie.right;
		m_pPtArr[0].y = ptCenter.y;
		
		for (i = 1, j = 1; i < m_nSerieses; i ++)
		{
			if (m_pCtrl->m_arUsage[i - 1] == 2)
				continue;
			
			fCurrtPieTotal += m_pCtrl->m_arDatas[m][i - 1];
			fRatio = fCurrtPieTotal / m_arTotal[m];
			
			m_pPtArr[j].x = (long)(ptCenter.x + nRad * cos(fRatio * pi * 2));
			m_pPtArr[j].y = (long)(ptCenter.y - nRad * sin(fRatio * pi * 2));
			
			j ++;
		}
		
		m_pPtArr[m_nSeriesesIncluded].x = m_pPtArr[0].x;
		m_pPtArr[m_nSeriesesIncluded].y = m_pPtArr[0].y;
		
		for(i = 0, j = 0, k = 0; i < m_nSerieses; i ++)
		{
			if (m_pCtrl->m_arUsage[i] == 2)
				continue;
			
			if (m_pCtrl->m_arUsage[i] == 0)
			{
				if (!m_bBrhDirty)
				{
					m_pBrhOld = pDC->SelectObject(&m_pBrhArr[j]);
					m_bBrhDirty = TRUE;
				}
				else
					pDC->SelectObject(&m_pBrhArr[j]);
				
				if (!(m_pPtArr[k].x == m_pPtArr[k + 1].x == ptCenter.x) && !(m_pPtArr[k].y == m_pPtArr[k + 1].y == ptCenter.y))
					pDC->Pie(rtPie, m_pPtArr[k], m_pPtArr[k + 1]);
				
				j ++;
			}
			
			k ++;
		}
	}

	FinishDraw(pRect, pDC);

	return TRUE;
}

void CPie::FinishDraw(CRect *pRect, CDC *pDC)
{
	CChart::FinishDraw(pRect, pDC);

	if (m_pPtArr)
	{
		delete[] m_pPtArr;
		m_pPtArr = NULL;
	}
}

void CPie::SetDrawPieTitle(BOOL b)
{
	m_bHasPieTitle = b;
}
