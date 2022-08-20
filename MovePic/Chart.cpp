// Chart.cpp: implementation of the CChart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MovePic.h"
#include "Chart.h"
#include "movepicview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChart::CChart()
{

}

CChart::~CChart()
{

}

BOOL CChart::Draw(CRect *pRect, CDC *pDC)
{
	m_rgnOld = NULL;
	
	double fTotal = 0;
	m_fMaxTotal = 0, m_fMinTotal = 0;

	int i, j;
	m_bBrhDirty = FALSE;
	m_pBrhArr = NULL;
	m_pBrhOld = NULL;

	m_rgn.CreateRectRgnIndirect(pRect);
	GetClipRgn(pDC->m_hDC, m_rgnOld);
	pDC->SelectClipRgn(&m_rgn);

	m_rtPic.SetRect(0, 0, 0, 0);

	m_nRows = m_pCtrl->m_arDatas.GetSize();
	m_nSeriesesToDraw = 0;
	m_nSeriesesIncluded = 0;

	if (m_nRows == 0)
		return FALSE;

	m_nSerieses = m_pCtrl->m_arUsage.GetSize();

	for (j = 0; j < m_nRows; j ++)
	{
		for (i = 0, m_nSeriesesToDraw = 0, m_nSeriesesIncluded = 0; i < m_nSerieses; i ++)
		{
			if (m_pCtrl->m_arUsage[i] != 2)
			{
				m_nSeriesesIncluded ++;
		
				if (m_pCtrl->m_arUsage[i] == 0)
					m_nSeriesesToDraw ++;

				fTotal += m_pCtrl->m_arDatas[j][i];
			}
		}

		m_arTotal.Add(fTotal);
		
		if (fTotal > m_fMaxTotal)
			m_fMaxTotal = fTotal;
		else if (fTotal < m_fMinTotal)
			m_fMinTotal = fTotal;
	}

	if (m_nSeriesesToDraw == 0)
		return FALSE;

	m_pBrhArr = new CBrush[m_nSeriesesToDraw];

	for (i = 0; i < m_nSeriesesToDraw; i ++)
		m_pBrhArr[i].CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));

	CSize szChar;
	CRect rtMid, rtTitle, rtFooter;
	int nLegendHeight;
	CString strLegend;
	CRect rtPiece, rtLegendDraw, rtLegend;
	POINT ptCenter;

	rtMid.CopyRect(pRect);

	if (m_bHasTitle)
	{
		pDC->SetTextAlign(TA_CENTER);

		szChar = pDC->GetOutputTextExtent(_T("Title"));
		rtTitle.CopyRect(pRect);
		rtTitle.bottom = rtTitle.top + 40 + szChar.cy;
	
		ptCenter = rtTitle.CenterPoint();
		rtTitle.left = max(ptCenter.x - szChar.cx / 2, pRect->left);
		rtTitle.right = min(ptCenter.x + szChar.cx / 2, pRect->right);

		if (rtTitle.top < pRect->top || rtTitle.bottom > pRect->bottom)
			return FALSE;

		rtMid.top = rtTitle.bottom;

		pDC->MoveTo(rtTitle.left - 10, rtTitle.top + 15);
		pDC->LineTo(rtTitle.right + 10, rtTitle.top + 15);
		pDC->LineTo(rtTitle.right + 10, rtTitle.bottom - 15);
		pDC->LineTo(rtTitle.left - 10, rtTitle.bottom - 15);
		pDC->LineTo(rtTitle.left - 10, rtTitle.top + 15);
		pDC->TextOut(ptCenter.x, rtTitle.top + 20, _T("Title"));

		szChar = pDC->GetOutputTextExtent(_T("Footer"));
		rtFooter.CopyRect(pRect);
		rtFooter.top = rtFooter.bottom - 40 - szChar.cy;
		rtFooter.left = max(ptCenter.x - szChar.cx / 2, pRect->left);
		rtFooter.right = min(ptCenter.x + szChar.cx / 2, pRect->right);

		if (rtFooter.top < rtTitle.bottom || rtFooter.bottom > pRect->bottom)
		{
			rtFooter.left = rtFooter.right = rtFooter.top = rtFooter.bottom = 0;
			goto exitTitle;
		}

		rtMid.bottom = rtFooter.top;

		pDC->MoveTo(rtFooter.left - 10, rtFooter.top + 15);
		pDC->LineTo(rtFooter.right + 10, rtFooter.top + 15);
		pDC->LineTo(rtFooter.right + 10, rtFooter.bottom - 15);
		pDC->LineTo(rtFooter.left - 10, rtFooter.bottom - 15);
		pDC->LineTo(rtFooter.left - 10, rtFooter.top + 15);
		pDC->TextOut(ptCenter.x, rtFooter.top + 20, _T("Footer"));

		pDC->SetTextAlign(TA_LEFT);

		if (rtMid.right <= rtMid.left || rtMid.bottom <= rtMid.top)
			return FALSE;
	}

exitTitle:
	
	m_rtPic.CopyRect(&rtMid);

	if (m_bHasLegend)
	{
		szChar = pDC->GetOutputTextExtent(_T("C"));

		rtLegend.CopyRect(&rtMid);
		rtLegend.left = rtLegend.right - szChar.cx * 7;
		rtLegend.right -= szChar.cx;
		m_rtPic.right = rtLegend.left - szChar.cx * 2;

		nLegendHeight = szChar.cy * m_nSeriesesToDraw;
		if (m_nSeriesesIncluded > 1)
			nLegendHeight += (m_nSeriesesToDraw - 1) * 5;

		rtPiece.left = rtLegend.left + szChar.cx;
		rtPiece.right = rtPiece.left + szChar.cx;
		rtLegendDraw.left = rtPiece.left;
		rtLegendDraw.right = rtPiece.right;
		rtLegendDraw.top = rtMid.top + (rtMid.Height() - nLegendHeight) / 2;
		rtLegendDraw.bottom = rtLegendDraw.top + nLegendHeight; 

		if (rtLegendDraw.right <= rtLegendDraw.left)
			return FALSE;

		if (m_bHasTitle && (rtLegendDraw.left < rtTitle.right + 10 || rtLegendDraw.left < rtFooter.right + 10))
			return FALSE;

		for (i = 0, j = 0; i < m_nSerieses; i ++)
		{
			if (m_pCtrl->m_arUsage[i] == 0)
			{
				rtPiece.top = rtLegendDraw.top + (szChar.cy + 5) * j;
				rtPiece.bottom = rtPiece.top + szChar.cy;

				strLegend.Format(_T("C%d"), i + 1);

				if (!m_bBrhDirty)
				{
					m_pBrhOld = pDC->SelectObject(&m_pBrhArr[j]);
					m_bBrhDirty = TRUE;
				}
				else
					pDC->SelectObject(&m_pBrhArr[j]);

				pDC->Rectangle(&rtPiece);
				pDC->TextOut(rtPiece.right + szChar.cx, rtPiece.top, strLegend);

				j ++;
			}
		}
		
		if (m_bBrhDirty)
		{
			pDC->SelectObject(m_pBrhOld);
			m_bBrhDirty = FALSE;
		}
	}

	return TRUE;
}

void CChart::SetCtrl(CMovePicView *pCtrl)
{
	m_pCtrl = pCtrl;
}

void CChart::FinishDraw(CRect *pRect, CDC *pDC)
{
	if (m_bBrhDirty)
	{
		pDC->SelectObject(m_pBrhOld);
		m_bBrhDirty = FALSE;
	}

	if (m_pBrhArr)
	{
		delete[] m_pBrhArr;
		m_pBrhArr = NULL;
	}

	pDC->SetTextAlign(TA_LEFT);
	SelectClipRgn(pDC->m_hDC, m_rgnOld);

	m_rgn.DeleteObject();
}

void CChart::SetDrawLegend(BOOL bDraw)
{
	m_bHasLegend = bDraw;
}

void CChart::SetDrawTitle(BOOL bDraw)
{
	m_bHasTitle = bDraw;
}
