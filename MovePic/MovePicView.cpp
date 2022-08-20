// MovePicView.cpp : implementation of the CMovePicView class
//

#include "stdafx.h"
#include "MovePic.h"

#include "MovePicDoc.h"
#include "MovePicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMovePicView

IMPLEMENT_DYNCREATE(CMovePicView, CView)

BEGIN_MESSAGE_MAP(CMovePicView, CView)
	//{{AFX_MSG_MAP(CMovePicView)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovePicView construction/destruction

CMovePicView::CMovePicView()
{
	srand(GetTickCount());

	double * pData;

	for (int i = 0; i < 5; i ++)
	{
		pData = new double[8];

		for (int j = 0; j < 8; j ++)
			pData[j] = rand() % 10;

		m_arDatas.Add(pData);
	}

	for (i = 0; i < 8; i ++)
		m_arUsage.Add(rand() % 3);

	pie.SetCtrl(this);
}

CMovePicView::~CMovePicView()
{
	for (int i = 0; i < m_arDatas.GetSize(); i ++)
		delete m_arDatas[i];

	m_arDatas.RemoveAll();
}

BOOL CMovePicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMovePicView drawing

void CMovePicView::OnDraw(CDC* pDC)
{
	CMovePicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rt, rtNow;
	GetClientRect(&rt);

	pDC->FillSolidRect(&rt, RGB(200, 200, 200));
	pDC->SetBkColor(RGB(200, 200, 200));

	pie.SetDrawTitle(rand() % 2);
	pie.SetDrawLegend(rand() % 2);
	pie.SetDrawPieTitle(rand() % 2);

	pie.Draw(&rt, pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMovePicView printing

BOOL CMovePicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMovePicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMovePicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMovePicView diagnostics

#ifdef _DEBUG
void CMovePicView::AssertValid() const
{
	CView::AssertValid();
}

void CMovePicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMovePicDoc* CMovePicView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMovePicDoc)));
	return (CMovePicDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMovePicView message handlers

void CMovePicView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnRButtonDown(nFlags, point);

	CClientDC dc(this);
	
	for (int i = 0; i < 5; i ++)
		DrawCube(&dc, 100 + 20 * i, 50, 10, 10, 40);
/*	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CRect rt;
	GetClientRect(&rt);
	int nWidth = rt.Width(), nHeight = rt.Height();

	CBitmap bmp, * pBmpOld;
	bmp.CreateCompatibleBitmap(&dc, nWidth, nHeight);
	pBmpOld = memdc.SelectObject(&bmp);

	dc.FillSolidRect(&rt, RGB(255, 125, 125));
//	dc.Ellipse(&rt);
	dc.MoveTo(0, 0);
	dc.LineTo(rt.Width() - 1, rt.Height() - 1);
	dc.MoveTo(rt.Width() - 1, 0);
	dc.LineTo(0, rt.Height() - 1);
	
	memdc.BitBlt(0, 0, nWidth, nHeight, &dc, 0, 0, SRCCOPY);
	dc.FillSolidRect(&rt, RGB(255, 255, 255));
	AfxMessageBox("Ok to restore");

	EllipseEnlarge(&memdc, &dc, 0, 0, 0, 0, nWidth, nHeight, nWidth, nHeight, 1, 3);
	
	memdc.SelectObject(pBmpOld);
	bmp.DeleteObject();*/
}

void CMovePicView::SlideShow(CDC *pDCSrc, CDC * pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nWidth, int nHeight, int nPattern, int nSpeed)
{
	int nShiftX = nWidth / 100, nStripeWidth = nWidth / 10;
	int nShiftXLeft = (nWidth - nStripeWidth * 9) / 10;
	int nShiftY = nHeight / 100, nStripeHeight = nHeight / 10;
	int nShiftYLeft = (nHeight - nStripeHeight * 9) / 10;
	
	int i, nSecX = 0, nSecY = 0, x, y;
	switch (nPattern)
	{
	case 0:
		for (i = 1; i <= 10; i ++)
		{
			for (nSecX = 0; nSecX < 9; nSecX ++)
			{
				x = nStripeWidth * nSecX;
				pDCDest->BitBlt(x + nCxDest, nCyDest, nShiftX * i, nHeight, pDCSrc, x + nCxSrc, nCySrc, SRCCOPY);
			}
			pDCDest->BitBlt(nStripeWidth * 9 + nCxDest, nCyDest, nShiftXLeft * i, nHeight, pDCSrc, nStripeWidth * 9 + nCxSrc, nCySrc, SRCCOPY);
			Sleep(20 * (nSpeed + 1));
		}
		break;

	case 1:
		for (i = 1; i <= 10; i ++)
		{
			for (nSecY = 0; nSecY < 9; nSecY ++)
			{
				y = nStripeHeight * nSecY;
				pDCDest->BitBlt(nCxDest, y + nCyDest, nWidth, nShiftY * i, pDCSrc, nCxSrc, y + nCySrc, SRCCOPY);
			}
			pDCDest->BitBlt(nCxDest, nStripeHeight * 9 + nCyDest, nWidth, nShiftYLeft * i, pDCSrc, nCxSrc, nStripeHeight * 9 + nCySrc, SRCCOPY);
			Sleep(20 * (nSpeed + 1));
		}
		break;

	case 2:
		for (i = 1; i <= 10; i ++)
		{
			for (nSecX = 0; nSecX < 10; nSecX ++)
			{
				x = nStripeWidth * nSecX;
				nSecY = nSecX % 2;
				for (; nSecY < 9; nSecY += 2)
				{
					y = nStripeHeight * nSecY;
					pDCDest->BitBlt(x + nCxDest, y + nCyDest, nShiftX * i, nStripeHeight, pDCSrc, x + nCxSrc, y + nCySrc, SRCCOPY);
				}
				if (nSecX % 2)
				{
					pDCDest->BitBlt(nStripeWidth * nSecX + nCxDest, nStripeHeight * 9 + nCyDest, nShiftX * i, nHeight - nStripeHeight * 9, pDCSrc, nStripeWidth * nSecX + nCxSrc, nStripeHeight * 9 + nCySrc, SRCCOPY);
					pDCDest->BitBlt(nStripeWidth * 9 + nCxDest, nStripeHeight * nSecX + nCyDest, nShiftX * i, nStripeHeight, pDCSrc, nStripeWidth * 9 + nCxSrc, nStripeHeight * nSecX + nCySrc, SRCCOPY);
				}
			}
			Sleep(20 * (nSpeed + 1));
		}
		for (i = 1; i < 10; i ++)
		{
			for (nSecX = 0; nSecX < 10; nSecX ++)
			{
				x = nStripeWidth * nSecX;
				nSecY = (nSecX + 1) % 2;
				for (; nSecY < 9; nSecY += 2)
				{
					y = nStripeHeight * nSecY;
					pDCDest->BitBlt(x + nCxDest, y + nCyDest, nShiftX ? nShiftX * i : nStripeWidth, nStripeHeight, pDCSrc, x + nCxSrc, y + nCySrc, SRCCOPY);
				}
				if (!(nSecX % 2))
				{
					pDCDest->BitBlt(nStripeWidth * nSecX + nCxDest, nStripeHeight * 9 + nCyDest, nShiftX * i, nHeight - nStripeHeight * 9, pDCSrc, nStripeWidth * nSecX + nCxSrc, nStripeHeight * 9 + nCySrc, SRCCOPY);
					pDCDest->BitBlt(nStripeWidth * 9 + nCxDest, nStripeHeight * nSecX + nCyDest, nShiftX * i, nStripeHeight, pDCSrc, nStripeWidth * 9 + nCxSrc, nStripeHeight * nSecX + nCySrc, SRCCOPY);
				}
			}
			Sleep(20 * (nSpeed + 1));
		}
		break;

	case 3:
		for (i = 1; i <= 10; i ++)
		{
			for (nSecX = 0; nSecX < 10; nSecX ++)
			{
				x = nStripeWidth * nSecX;
				nSecY = nSecX % 2;
				for (; nSecY < 9; nSecY += 2)
				{
					y = nStripeHeight * nSecY;
					pDCDest->BitBlt(x + nCxDest, y + nCyDest, nStripeWidth, nShiftY * i, pDCSrc, x + nCxSrc, y + nCySrc, SRCCOPY);
				}
				if (nSecX % 2)
				{
					pDCDest->BitBlt(nStripeWidth * nSecX + nCxDest, nStripeHeight * 9 + nCyDest, nWidth - nStripeWidth * 9, nShiftY * i, pDCSrc, nStripeWidth * nSecX + nCxSrc, nStripeHeight * 9 + nCySrc, SRCCOPY);
					pDCDest->BitBlt(nStripeWidth * 9 + nCxDest, nStripeHeight * nSecX + nCyDest, nStripeWidth, nShiftY * i, pDCSrc, nStripeWidth * 9 + nCxSrc, nStripeHeight * nSecX + nCySrc, SRCCOPY);
				}
			}
			Sleep(20 * (nSpeed + 1));
		}
		for (i = 1; i <= 10; i ++)
		{
			for (nSecX = 0; nSecX < 10; nSecX ++)
			{
				x = nStripeWidth * nSecX;
				nSecY = (nSecX + 1) % 2;
				for (; nSecY < 9; nSecY += 2)
				{
					y = nStripeHeight * nSecY;
					pDCDest->BitBlt(x + nCxDest, y + nCyDest, nStripeWidth, nShiftY * i, pDCSrc, x + nCxSrc, y + nCySrc, SRCCOPY);
				}
				if (!(nSecX % 2))
				{
					pDCDest->BitBlt(nStripeWidth * nSecX + nCxDest, nStripeHeight * 9 + nCyDest, nWidth - nStripeWidth * 9, nShiftY * i, pDCSrc, nStripeWidth * nSecX + nCxSrc, nStripeHeight * 9 + nCySrc, SRCCOPY);
					pDCDest->BitBlt(nStripeWidth * 9 + nCxDest, nStripeHeight * nSecX + nCyDest, nStripeWidth, nShiftY * i, pDCSrc, nStripeWidth * 9 + nCxSrc, nStripeHeight * nSecX + nCySrc, SRCCOPY);
				}
			}
			Sleep(20 * (nSpeed + 1));
		}
		break;
	}

	pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);
}

int CMovePicView::CalcShiftBits(DWORD dwMask)
{
	for (int i = 0; i < sizeof(dwMask) * 8 && !(dwMask & 1); i ++)
		dwMask = dwMask >> 1;

	return i;
}

void CMovePicView::FadeIn(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nWidth, int nHeight, int nSpeed)
{
	CDC memdc;
	memdc.CreateCompatibleDC(pDCSrc);
	
	CBitmap bmp, * pBmpOld;
	bmp.CreateCompatibleBitmap(pDCSrc, nWidth, nHeight);
	pBmpOld = memdc.SelectObject(&bmp);
	memdc.BitBlt(0, 0, nWidth, nHeight, pDCSrc, 0, 0, SRCCOPY);
	memdc.SelectObject(pBmpOld);

	BITMAPINFO bmi, * pBmi, * pBmiNew;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = 0x28;
	GetDIBits(pDCSrc->m_hDC, (HBITMAP)bmp, 0, 0, NULL, &bmi, DIB_RGB_COLORS);

	int nHeaderSize = sizeof(BITMAPINFOHEADER);
	switch (bmi.bmiHeader.biBitCount)
	{
	case 8:
		nHeaderSize += 256 * sizeof(RGBQUAD);
		break;

	case 16:
		if (bmi.bmiHeader.biCompression == BI_BITFIELDS)
			nHeaderSize += 3 * sizeof(RGBQUAD);
		break;

	case 32:
		if (bmi.bmiHeader.biCompression == BI_BITFIELDS)
			nHeaderSize += 3 * sizeof(RGBQUAD);
		break;

	default:
		{
			bmp.DeleteObject();
			return;
		}
	}

	pBmi = (BITMAPINFO *) new BYTE[nHeaderSize];
	pBmiNew = (BITMAPINFO *) new BYTE[nHeaderSize];
	if (!pBmi || !pBmiNew)
	{
		bmp.DeleteObject();
		return;
	}

	memcpy(pBmi, &bmi, sizeof(BITMAPINFOHEADER));
	BYTE * pBits = (BYTE *) new BYTE[bmi.bmiHeader.biSizeImage];
	if (!pBits)
	{
		delete[] pBmi;
		delete[] pBmiNew;
		bmp.DeleteObject();

		return;
	}

	BYTE * pBitsNew = (BYTE *) new BYTE[bmi.bmiHeader.biSizeImage];
	if (!pBitsNew)
	{
		delete[] pBmi;
		delete[] pBmiNew;
		delete[] pBits;
		bmp.DeleteObject();
		return;
	}

	memset(pBits, 0, bmi.bmiHeader.biSizeImage);
	GetDIBits(pDCSrc->m_hDC, (HBITMAP)bmp, 0, bmi.bmiHeader.biHeight, pBits, pBmi, 
		DIB_RGB_COLORS);
	memcpy(pBitsNew, pBits, bmi.bmiHeader.biSizeImage);
	memcpy(pBmiNew, pBmi, nHeaderSize);

	DWORD dwMaskRed, dwMaskGreen, dwMaskBlue, dwValue;
	DWORD dwRed, dwGreen, dwBlue;
	int nShiftRed, nShiftGreen, nShiftBlue;

	int i;
	DWORD l;
	switch (bmi.bmiHeader.biBitCount)
	{
	case 8:
		for (i = 1; i <= 10; i ++)
		{
			for (l = 0; l < 256; l ++)
			{
				pBmiNew->bmiColors[l].rgbRed = pBmi->bmiColors[l].rgbRed * i / 100;
				pBmiNew->bmiColors[l].rgbGreen = pBmi->bmiColors[l].rgbGreen * i / 100;
				pBmiNew->bmiColors[l].rgbBlue = pBmi->bmiColors[l].rgbBlue * i / 100;
			}
			SetDIBitsToDevice(pDCDest->m_hDC, nCxDest, nCyDest, nWidth, nHeight, nCxSrc, nCySrc, 0, nHeight, pBitsNew, pBmiNew, 
				DIB_RGB_COLORS);
			Sleep(20 * (nSpeed) + 1);
		}

		break;
	
	case 16:
		memcpy(&dwMaskRed, &pBmi->bmiColors[0], 4);
		memcpy(&dwMaskGreen, &pBmi->bmiColors[1], 4);
		memcpy(&dwMaskBlue, &pBmi->bmiColors[2], 4);
		nShiftRed = CalcShiftBits(dwMaskRed);
		nShiftGreen = CalcShiftBits(dwMaskGreen);
		nShiftBlue = CalcShiftBits(dwMaskBlue);
		if (bmi.bmiHeader.biCompression == BI_BITFIELDS)
		{
			for (i = 1; i <= 10; i ++)
			{
				for (l = 0; l < bmi.bmiHeader.biSizeImage - 1; l += 2)
				{
					dwValue = (pBits[l + 1] << 8) + pBits[l];
					dwRed = ((dwValue & dwMaskRed) >> nShiftRed) * i / 10;
					dwGreen = ((dwValue & dwMaskGreen) >> nShiftGreen) * i / 10;
					dwBlue = ((dwValue & dwMaskBlue) >> nShiftBlue) * i / 10;
					dwValue = (dwRed << nShiftRed)+ (dwGreen << nShiftGreen) + (dwBlue << nShiftBlue);
					
					pBitsNew[l + 1] = (BYTE)(dwValue >> 8);
					pBitsNew[l] = (BYTE)(dwValue & 0x00ff);
				}
				SetDIBitsToDevice(pDCDest->m_hDC, nCxDest, nCyDest, nWidth, nHeight, nCxSrc, nCySrc, 0, nHeight, pBitsNew, pBmiNew, 
					DIB_RGB_COLORS);
				Sleep(20 * (nSpeed) + 1);
			}
		}
		else
		{
			for (i = 1; i <= 10; i ++)
			{
				for (l = 0; l < bmi.bmiHeader.biSizeImage - 1; l += 2)
				{
					dwValue = (pBits[l + 1] << 8) + pBits[l];
					dwRed = ((dwValue & dwMaskRed) >> 10) * i / 10;
					dwGreen = ((dwValue & dwMaskGreen) >> 5) * i / 10;
					dwBlue = (dwValue & dwMaskBlue) * i / 10;
					dwValue = (dwRed << 10) + (dwGreen << 5) + (dwBlue << nShiftBlue);
					
					pBitsNew[l + 1] = (BYTE)(dwValue >> 8);
					pBitsNew[l] = (BYTE)(dwValue & 0x00ff);
				}
				SetDIBitsToDevice(pDCDest->m_hDC, nCxDest, nCyDest, nWidth, nHeight, nCxSrc, nCySrc, 0, nHeight, pBitsNew, pBmiNew, 
					DIB_RGB_COLORS);
				Sleep(20 * (nSpeed) + 1);
			}
		}
		
		break;

	case 24:
		for (i = 1; i <= 10; i ++)
		{
			for (l = 0; l < bmi.bmiHeader.biSizeImage; l ++)
				pBitsNew[l] = (pBits[l] * i) / 10;

			SetDIBitsToDevice(pDCDest->m_hDC, nCxDest, nCyDest, nWidth, nHeight, nCxSrc, nCySrc, 0, nHeight, pBitsNew, pBmiNew, 
				DIB_RGB_COLORS);
			Sleep(20 * (nSpeed) + 1);
		}

		break;

	case 32:
		if (bmi.bmiHeader.biCompression == BI_BITFIELDS)
		{
			memcpy(&dwMaskRed, &pBmi->bmiColors[0], 4);
			memcpy(&dwMaskGreen, &pBmi->bmiColors[1], 4);
			memcpy(&dwMaskBlue, &pBmi->bmiColors[2], 4);
			nShiftRed = CalcShiftBits(dwMaskRed);
			nShiftGreen = CalcShiftBits(dwMaskGreen);
			nShiftBlue = CalcShiftBits(dwMaskBlue);
			for (i = 1; i <= 10; i ++)
			{
				for (l = 0; l < bmi.bmiHeader.biSizeImage - 3; l += 4)
				{
					memcpy(&dwValue, &pBits[l], 4);
					dwRed = ((dwValue & dwMaskRed) >> nShiftRed) * i / 10;
					dwGreen = ((dwValue & dwMaskGreen) >> nShiftGreen) * i / 10;
					dwBlue = ((dwValue & dwMaskBlue) >> nShiftBlue) * i / 10;
					dwValue = (dwRed << nShiftRed)+ (dwGreen << nShiftGreen) + (dwBlue << nShiftBlue);
					
					memcpy(&pBitsNew[l], &dwValue, 4);
				}
				SetDIBitsToDevice(pDCDest->m_hDC, nCxDest, nCyDest, nWidth, nHeight, nCxSrc, nCySrc, 0, nHeight, pBitsNew, pBmiNew, 
					DIB_RGB_COLORS);
				Sleep(20 * (nSpeed) + 1);
			}
		}
		else
		{
			for (i = 1; i <= 10; i ++)
			{
				for (l = 0; l < bmi.bmiHeader.biSizeImage - 3; l += 4)
				{
					pBitsNew[l] = pBits[l] * i / 10;
					pBitsNew[l + 1] = pBits[l + 1] * i / 10;
					pBitsNew[l + 2] = pBits[l + 2] * i / 10;
				}
				SetDIBitsToDevice(pDCDest->m_hDC, nCxDest, nCyDest, nWidth, nHeight, nCxSrc, nCySrc, 0, nHeight, pBitsNew, pBmiNew, 
					DIB_RGB_COLORS);
				Sleep(20 * (nSpeed) + 1);
			}
		}
		
		break;
	}
	
	delete[] pBits;
	delete[] pBitsNew;
	delete[] pBmi;

	bmp.DeleteObject();
}

DWORD CMovePicView::GetRandValue()
{
	int x, y;
	x = rand() % 30;
	y = rand() % 30;

	while (m_bCoordUsed[x][y] && m_nCoordUsed < 900)
	{
		x = rand() % 30;
		y = rand() % 30;
	}

	m_nCoordUsed ++;
	m_bCoordUsed[x][y] = TRUE;

	return MAKEWPARAM((WORD)x, (WORD)y);
}

void CMovePicView::RandBlock(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nWidth, int nHeight, int nPattern, int nSpeed)
{
	int x, y;
	int nBlockWidth, nBlockHeight;
	m_nCoordUsed = 0;
	srand((unsigned)time(NULL));

	if (nPattern == 2)
	{
		for (x = 0; x < 30; x ++)
			for (y = 0; y < 30; y ++)
				m_bCoordUsed[x][y] = FALSE;
			
			
		nBlockWidth = nWidth / 30;
		nBlockHeight = nHeight / 30;
		if (nWidth % 30)
			nBlockWidth ++;
		if (nHeight % 30)
			nBlockHeight ++;
			
		DWORD dwCoord;
			
		while (m_nCoordUsed < 900)
		{
			dwCoord = GetRandValue();
			x = LOWORD(dwCoord);
			y = HIWORD(dwCoord);
			pDCDest->BitBlt(nCxDest + nBlockWidth * x, nCyDest + nBlockHeight * y, 
				x == 29 ? nWidth - 29 * nBlockWidth : nBlockWidth, 
				y == 29 ? nHeight - 29 * nBlockHeight : nBlockHeight, 
				pDCSrc, nCxSrc + nBlockWidth * x, nCySrc + nBlockHeight * y, 
				SRCCOPY);
			Sleep(3 * (nSpeed + 1));
		}
	}
	else
	{
		for (x = 0; x < 2048; x ++)
			m_bXorYUsed[x] = FALSE;
			
		if (nPattern == 1)
		{
			while (m_nCoordUsed < nWidth)
			{
				x = GetRandXorY(nWidth);
				pDCDest->BitBlt(nCxDest + x, nCyDest, 1, nHeight, pDCSrc,
					nCxSrc + x, nCySrc, SRCCOPY);
				Sleep(900  / nWidth * (nSpeed + 1));
			}
		}
		else
		{
			while (m_nCoordUsed < nHeight)
			{
				y = GetRandXorY(nHeight);
				pDCDest->BitBlt(nCxDest, nCyDest + y, nWidth, 1, pDCSrc,
					nCxSrc, nCySrc + y, SRCCOPY);
				Sleep(900/nHeight * (nSpeed + 1));
			}
		}
	}
}

int CMovePicView::GetRandXorY(int nLimit)
{
	int x;
	x = rand() % nLimit;

	while (m_bXorYUsed[x] && m_nCoordUsed < nLimit)
		x = rand() % nLimit;

	m_nCoordUsed ++;
	m_bXorYUsed[x] = TRUE;

	return x;
}

void CMovePicView::MirrorBand(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nBandWidth, int nBandHeight, int nPattern)
{
	int i;
	switch (nPattern)
	{
	case 0:
		for (i = 0; i < nBandWidth; i ++)
			pDCDest->BitBlt(nCxDest + i, nCyDest, 1, nBandHeight, pDCSrc, nCxSrc + nBandWidth * 2 - i, nCySrc, SRCCOPY);

		break;

	case 1:
		for (i = 0; i < nBandWidth; i ++)
			pDCDest->BitBlt(nCxDest - i, nCyDest, 1, nBandHeight, pDCSrc, nCxSrc - nBandWidth * 2 + i, nCySrc, SRCCOPY);

		break;

	case 2:
		for (i = 0; i < nBandHeight; i ++)
			pDCDest->BitBlt(nCxDest, nCyDest + i, nBandWidth, 1, pDCSrc, nCxSrc, nCySrc + nBandHeight * 2 - i, SRCCOPY);

		break;

	case 3:
		for (i = 0; i < nBandHeight; i ++)
			pDCDest->BitBlt(nCxDest, nCyDest - i, nBandWidth, 1, pDCSrc, nCxSrc, nCySrc - nBandHeight * 2 + i, SRCCOPY);

		break;

	}
}

void CMovePicView::WindIn(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nWidth, int nHeight, int nPattern, int nSpeed)
{
	int nBandWidth, nBandHeight;
	int i;

	switch (nPattern)
	{
	case 0:
		nBandWidth = nWidth / 10;

		for (i = 0; i < nWidth - 2 * nBandWidth;)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(pDCSrc, pDCDest, i + nCxSrc, nCySrc, i + nCxDest, nCyDest, nBandWidth, nHeight, 0);
			pDCDest->BitBlt(i + nCxDest, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc, nCySrc, SRCCOPY);
			i += 3;
		}
		while(i < nWidth - 3)
		{
			Sleep(5 * (nSpeed + 1));
			nBandWidth = (nWidth - i) / 2;
			MirrorBand(pDCSrc, pDCDest, i + nCxSrc, nCySrc, i + nCxDest, nCyDest, nBandWidth, nHeight, 0);
			pDCDest->BitBlt(i + nCxDest, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc, nCySrc, SRCCOPY);
			i += 3;
		}
		Sleep(5 * (nSpeed + 1));
		pDCDest->BitBlt(i + nCxDest, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc, nCySrc, SRCCOPY);

		break;

	case 1:
		nBandWidth = nWidth / 10;

		for (i = nWidth - 1; i > 2 * nBandWidth;)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(pDCSrc, pDCDest, i + nCxSrc, nCySrc, i + nCxDest, nCyDest, nBandWidth, nHeight, 1);
			pDCDest->BitBlt(i + nCxDest - 2, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc - 2, nCySrc, SRCCOPY);
			i -= 3;
		}
		while(i >= 3)
		{
			Sleep(5 * (nSpeed + 1));
			nBandWidth = (i + 1) / 2;
			MirrorBand(pDCSrc, pDCDest, i + nCxSrc, nCySrc, i + nCxDest, nCyDest, nBandWidth, nHeight, 1);
			pDCDest->BitBlt(i + nCxDest - 2, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc - 2, nCySrc, SRCCOPY);
			i -= 3;
		}
		Sleep(5 * (nSpeed + 1));
		pDCDest->BitBlt(nCxDest, nCyDest, 3, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;

	case 2:
		nBandHeight = nHeight / 10;

		for (i = 0; i < nHeight - 2 * nBandHeight;)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(pDCSrc, pDCDest, nCxSrc, i + nCySrc, nCxDest, i + nCyDest, nWidth, nBandHeight, 2);
			pDCDest->BitBlt(nCxDest, i + nCyDest, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc, SRCCOPY);
			i += 3;
		}
		while(i < nHeight - 3)
		{
			Sleep(5 * (nSpeed + 1));
			nBandHeight = (nHeight - i) / 2;
			MirrorBand(pDCSrc, pDCDest, nCxSrc, i + nCySrc, nCxDest, i + nCyDest, nWidth, nBandHeight, 2);
			pDCDest->BitBlt(nCxDest, i + nCyDest, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc, SRCCOPY);
			i += 3;
		}
		Sleep(5 * (nSpeed + 1));
			pDCDest->BitBlt(nCxDest, i + nCyDest, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc, SRCCOPY);

		break;

	case 3:
		nBandHeight = nHeight / 10;

		for (i = nHeight - 1; i > 2 * nBandHeight;)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(pDCSrc, pDCDest, nCxSrc, i + nCySrc, nCxDest, i + nCyDest, nWidth, nBandHeight, 3);
			pDCDest->BitBlt(nCxDest, i + nCyDest - 2, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc - 2, SRCCOPY);
			i -= 3;
		}
		while(i >= 3)
		{
			Sleep(5 * (nSpeed + 1));
			nBandWidth = (i + 1) / 2;
			MirrorBand(pDCSrc, pDCDest, nCxSrc, i + nCySrc, nCxDest, i + nCyDest, nWidth, nBandHeight, 3);
			pDCDest->BitBlt(nCxDest, i + nCyDest - 2, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc - 2, SRCCOPY);
			i -= 3;
		}
		Sleep(5 * (nSpeed + 1));
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, 3, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;
	}
}

void CMovePicView::WindOut(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nTotalWidth, int nTotalHeight, int nWidth, int nHeight, int nPattern, int nSpeed)
{
	CDC memdc;
	memdc.CreateCompatibleDC(pDCDest);
	CBitmap bmp, * pBmpOld;
	bmp.CreateCompatibleBitmap(pDCDest, nTotalWidth, nTotalHeight);

	pBmpOld = memdc.SelectObject(&bmp);
	memdc.BitBlt(0, 0, nTotalWidth, nTotalHeight, pDCDest, 0, 0, SRCCOPY);
	int nBandWidth, nBandHeight;
	int i;

	switch (nPattern)
	{
	case 0:
		nBandWidth = nWidth / 10;

		for (i = 0; i < nBandWidth;)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, i * 2 + nCxSrc, nCySrc, i * 2 + nCxDest, nCyDest, i, nHeight, 1);
			pDCDest->BitBlt(i + nCxDest, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc, nCySrc, SRCCOPY);
			i += 3;
		}
		while(i < nWidth - nBandWidth)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, i + nBandWidth + nCxSrc, nCySrc, i + nBandWidth + nCxDest, nCyDest, nBandWidth, nHeight, 1);
			pDCDest->BitBlt(i + nCxDest, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc, nCySrc, SRCCOPY);
			i += 3;
		}
		while(i < nWidth)
		{
			nBandWidth = (nWidth - i - 1);
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, nWidth - 1 + nCxSrc, nCySrc, nWidth - 1 + nCxDest, nCyDest, nBandWidth, nHeight, 1);
			pDCDest->BitBlt(i + nCxDest, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc, nCySrc, SRCCOPY);
			i += 3;
		}

		break;

	case 1:
		for (i = nWidth - 1; i > nWidth - 1 - nWidth / 10;)
		{
			nBandWidth = nWidth - i;
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, i - nBandWidth + nCxSrc, nCySrc, i - nBandWidth + nCxDest, nCyDest, nBandWidth, nHeight, 0);
			pDCDest->BitBlt(i + nCxDest, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc, nCySrc, SRCCOPY);
			i -= 3;
		}
		nBandWidth = nWidth / 10;
		while(i >= nBandWidth)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, i - nBandWidth + nCxSrc, nCySrc, i - nBandWidth + nCxDest, nCyDest, nBandWidth, nHeight, 0);
			pDCDest->BitBlt(i + nCxDest, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc, nCySrc, SRCCOPY);
			i -= 3;
		}
		while(i >= 0)
		{
			nBandWidth = i;
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, i - nBandWidth + nCxSrc, nCySrc, i - nBandWidth + nCxDest, nCyDest, nBandWidth, nHeight, 0);
			pDCDest->BitBlt(i + nCxDest, nCyDest, 3, nHeight, pDCSrc, i + nCxSrc, nCySrc, SRCCOPY);
			i -= 3;
		}
		pDCDest->BitBlt(nCxDest, nCyDest, 3, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;

	case 2:
		nBandHeight = nHeight / 10;

		for (i = 0; i < nBandHeight;)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, nCxSrc, i * 2 + nCySrc, nCxDest, i * 2 + nCyDest, nWidth, i, 3);
			pDCDest->BitBlt(nCxDest, i + nCyDest, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc, SRCCOPY);
			i += 3;
		}
		while(i < nHeight - nBandHeight)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, nCxSrc, i + nBandHeight + nCySrc, nCxDest, i + nBandHeight + nCyDest, nWidth, nBandHeight, 3);
			pDCDest->BitBlt(nCxDest, i + nCyDest, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc, SRCCOPY);
			i += 3;
		}
		while(i < nHeight)
		{
			nBandHeight = (nHeight - i - 1);
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, nCxSrc, nHeight - 1 + nCySrc, nCxDest, nHeight - 1 + nCyDest, nWidth, nBandHeight, 3);
			pDCDest->BitBlt(nCxDest, i + nCyDest, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc, SRCCOPY);
			i += 3;
		}

		break;

	case 3:
		for (i = nHeight - 1; i > nHeight - 1 - nHeight / 10;)
		{
			nBandHeight = nHeight - i;
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, nCxSrc, i - nBandHeight + nCySrc, nCxDest, i - nBandHeight + nCyDest, nWidth, nBandHeight, 2);
			pDCDest->BitBlt(nCxDest, i + nCyDest, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc, SRCCOPY);
			i -= 3;
		}
		nBandHeight = nHeight / 10;
		while(i >= nBandHeight)
		{
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, nCxSrc, i - nBandHeight + nCySrc, nCxDest, i - nBandHeight + nCyDest, nWidth, nBandHeight, 2);
			pDCDest->BitBlt(nCxDest, i + nCyDest, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc, SRCCOPY);
			i -= 3;
		}
		while(i >= 0)
		{
			nBandHeight = i;
			Sleep(5 * (nSpeed + 1));
			MirrorBand(&memdc, pDCDest, nCxSrc, i - nBandHeight + nCySrc, nCxDest, i - nBandHeight + nCyDest, nWidth, nBandHeight, 2);
			pDCDest->BitBlt(nCxDest, i + nCyDest, nWidth, 3, pDCSrc, nCxSrc, i + nCySrc, SRCCOPY);
			i -= 3;
		}
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, 3, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;
	}

	memdc.SelectObject(pBmpOld);
	bmp.DeleteObject();
}

void CMovePicView::PullIn(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nTotalWidth, int nTotalHeight, int nWidth, int nHeight, int nPattern, int nSpeed)
{
	CDC memdc;
	memdc.CreateCompatibleDC(pDCDest);
	CBitmap bmp, * pBmpOld;
	bmp.CreateCompatibleBitmap(pDCDest, nTotalWidth, nTotalHeight);

	pBmpOld = memdc.SelectObject(&bmp);
	memdc.BitBlt(0, 0, nTotalWidth, nTotalHeight, pDCDest, 0, 0, SRCCOPY);
	int nBandWidth, nBandHeight;
	int i;

	switch (nPattern)
	{
	case 0:
		nBandWidth = nWidth / 100;
		if (nBandWidth == 0)
			nBandWidth = 1;
		else if (nWidth % 100)
			nBandWidth ++;

		for (i = 0; i <= 100;)
		{
			pDCDest->BitBlt(nCxDest, nCyDest, i * nBandWidth, nHeight, pDCSrc, nWidth - i * 
				nBandWidth - 1 + nCxSrc, nCySrc, SRCCOPY);
			
			i ++;
			Sleep(3 * (nSpeed + 1));
			if (i * nBandWidth >= nWidth)
				break;

			pDCDest->BitBlt(i * nBandWidth + nCxDest, nCyDest, nWidth - i * nBandWidth, nHeight, 
				&memdc, nCxSrc, nCySrc, SRCCOPY);
		}
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;

	case 1:
		nBandWidth = nWidth / 100;
		if (nBandWidth == 0)
			nBandWidth = 1;
		else if (nWidth % 100)
			nBandWidth ++;

		for (i = 0; i <= 100;)
		{
			pDCDest->BitBlt(nCxDest + nWidth - i * nBandWidth, nCyDest, i * nBandWidth, nHeight,
				pDCSrc, nCxSrc, nCySrc, SRCCOPY);
			
			i ++;
			Sleep(3 * (nSpeed + 1));
			if (i * nBandWidth >= nWidth)
				break;

			pDCDest->BitBlt(nCxDest, nCyDest, nWidth - i * nBandWidth, nHeight, &memdc, i * 
				nBandWidth + nCxSrc, nCySrc, SRCCOPY);
		}
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;

	case 2:
		nBandHeight = nHeight / 100;
		if (nBandHeight == 0)
			nBandHeight = 1;
		else if (nHeight % 100)
			nBandHeight ++;

		for (i = 0; i <= 100;)
		{
			pDCDest->BitBlt(nCxDest, nCyDest, nWidth, i * nBandHeight, pDCSrc, nCxSrc, nHeight 
				- i * nBandHeight - 1 + nCySrc, SRCCOPY);
			
			i ++;
			Sleep(3 * (nSpeed + 1));
			if (i * nBandHeight >= nHeight)
				break;

			pDCDest->BitBlt(nCxDest, i * nBandHeight + nCyDest, nWidth, nHeight - i * nBandHeight, 
				&memdc, nCxSrc, nCySrc, SRCCOPY);
		}
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;

	case 3:
		nBandHeight = nHeight / 100;
		if (nBandHeight == 0)
			nBandHeight = 1;
		else if (nHeight % 100)
			nBandHeight ++;

		for (i = 0; i <= 100;)
		{
			pDCDest->BitBlt(nCxDest, nCyDest + nHeight - i * nBandHeight, nWidth, i * nBandHeight, 
				pDCSrc, nCxSrc, nCySrc, SRCCOPY);
			
			i ++;
			Sleep(3 * (nSpeed + 1));
			if (i * nBandHeight >= nHeight)
				break;

			pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight - i * nBandHeight, &memdc, nCxSrc, 
				i * nBandHeight + nCySrc, SRCCOPY);
		}
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;
	}

	memdc.SelectObject(pBmpOld);
	bmp.DeleteObject();
}

void CMovePicView::FourPieces(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nTotalWidth, int nTotalHeight, int nWidth, int nHeight, int nPattern, int nSpeed)
{
	CDC memdc, memdc1;
	memdc.CreateCompatibleDC(pDCDest);
	memdc1.CreateCompatibleDC(pDCDest);
	CBitmap bmp, bmp1, * pBmpOld, * pBmpOld1;
	bmp.CreateCompatibleBitmap(pDCDest, nTotalWidth, nTotalHeight);
	bmp1.CreateCompatibleBitmap(pDCDest, nTotalWidth, nTotalHeight);

	pBmpOld = memdc.SelectObject(&bmp);
	pBmpOld1 = memdc1.SelectObject(&bmp1);

	int nBandWidth, nBandHeight;
	int i;

	switch (nPattern)
	{
	case 0:
		for (i = 0; i <= 50; i ++)
		{
			nBandWidth = nWidth * i / 100;
			nBandHeight = nHeight * i / 100;
			pDCDest->BitBlt(
				nCxDest, 
				nCyDest, 
				nBandWidth, 
				nBandHeight, 
				pDCSrc, 
				nWidth / 2 - nBandWidth - 1 + nCxSrc, 
				nHeight / 2	- nBandHeight - 1 + nCySrc, 
				SRCCOPY);

			pDCDest->BitBlt(
				nWidth - 1 - nBandWidth + nCxDest, 
				nCyDest, 
				nBandWidth, 
				nBandHeight,
				pDCSrc, 
				nWidth / 2 - 1 + nCxSrc, 
				nHeight / 2 - nBandHeight - 1 + nCySrc, 
				SRCCOPY);

			pDCDest->BitBlt(
				nCxDest, 
				nHeight - nBandHeight - 1 + nCyDest, 
				nBandWidth, 
				nBandHeight, 
				pDCSrc, 
				nWidth / 2 - nBandWidth - 1 + nCxSrc, 
				nHeight / 2	- 1 + nCySrc, 
				SRCCOPY);

			pDCDest->BitBlt(
				nWidth - 1 - nBandWidth + nCxDest, 
				nHeight - nBandHeight - 1 + nCyDest, 
				nBandWidth, 
				nBandHeight,
				pDCSrc, 
				nWidth / 2 - 1 + nCxSrc, 
				nHeight / 2	- 1 + nCySrc, 
				SRCCOPY);

			Sleep(5 * (nSpeed + 1));

		}
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;

	case 1:
		memdc.BitBlt(0, 0, nTotalWidth, nTotalHeight, pDCDest, 0, 0, SRCCOPY);
		for (i = 0; i <= 50; i ++)
		{
			memdc1.BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

			nBandWidth = nWidth / 2 - nWidth * i / 100 + 1;
			nBandHeight = nHeight / 2 - nHeight * i / 100 + 1;
			memdc1.BitBlt(
				nCxDest, 
				nCyDest, 
				nBandWidth, 
				nBandHeight, 
				&memdc, 
				nWidth / 2 - nBandWidth - 1 + nCxSrc, 
				nHeight / 2	- nBandHeight - 1 + nCySrc, 
				SRCCOPY);

			memdc1.BitBlt(
				nWidth - 1 - nBandWidth + nCxDest, 
				nCyDest, 
				nBandWidth, 
				nBandHeight,
				&memdc, 
				nWidth / 2 - 1 + nCxSrc, 
				nHeight / 2 - nBandHeight - 1 + nCySrc, 
				SRCCOPY);

			memdc1.BitBlt(
				nCxDest, 
				nHeight - nBandHeight - 1 + nCyDest, 
				nBandWidth, 
				nBandHeight, 
				&memdc, 
				nWidth / 2 - nBandWidth - 1 + nCxSrc, 
				nHeight / 2	- 1 + nCySrc, 
				SRCCOPY);

			memdc1.BitBlt(
				nWidth - 1 - nBandWidth + nCxDest, 
				nHeight - nBandHeight - 1 + nCyDest, 
				nBandWidth, 
				nBandHeight,
				&memdc, 
				nWidth / 2 - 1 + nCxSrc, 
				nHeight / 2	- 1 + nCySrc, 
				SRCCOPY);

			Sleep(5 * (nSpeed + 1));
			pDCDest->BitBlt(0, 0, nWidth, nHeight, &memdc1, 0, 0, SRCCOPY);

		}
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);

		break;
	}

	memdc.SelectObject(pBmpOld);
	memdc1.SelectObject(pBmpOld1);
	bmp.DeleteObject();
	bmp1.DeleteObject();
}

void CMovePicView::EllipseEnlarge(CDC *pDCSrc, CDC *pDCDest, int nCxSrc, int nCySrc, int nCxDest, int nCyDest, int nTotalWidth, int nTotalHeight, int nWidth, int nHeight, int nPattern, int nSpeed)
{
/*	CRgn rgn;

	float cx, cy, width, height;
	cx = nCxDest -  (nWidth * 0.207);
	cy = nCyDest -  (nHeight * 0.207);
	width = nWidth * 1.414;
	height = nHeight * 1.414;
	int i;

	if (nPattern == 0)
	{
		for (i = 1; i < 100; i ++)
		{
			rgn.CreateEllipticRgn(cx + (width * (100 - i) / 200), cy + (height * (100 - i) / 200), 
				cx + width - (width * (100 - i) / 200), cy + height - (height * (100 - i) / 200));
			
			pDCDest->SelectClipRgn(&rgn);
			pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);
			pDCDest->SelectClipRgn(NULL);
			rgn.DeleteObject();
			
//			Sleep(300);
		}
		
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);
		
		pDCDest->SelectClipRgn(NULL);
	}
	else
	{
		CDC memdc;
		CBitmap bmp, * pBmpOld;

		memdc.CreateCompatibleDC(pDCDest);
		bmp.CreateCompatibleBitmap(pDCDest, nTotalWidth, nTotalHeight);
		
		pBmpOld = memdc.SelectObject(&bmp);
		memdc.BitBlt(0, 0, nTotalWidth, nTotalHeight, pDCDest, 0, 0, SRCCOPY);

		for (i = 99; i > 0; i --)
		{
			rgn.CreateEllipticRgn(cx + (width * (100 - i) / 200), cy + (height * (100 - i) / 200), 
				cx + width - (width * (100 - i) / 200), cy + height - (height * (100 - i) / 200));
			
			pDCDest->SelectClipRgn(&rgn, RGN_DIFF);
			pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);
			pDCDest->SelectClipRgn(NULL);
			pDCDest->SelectClipRgn(&rgn);
			pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, &memdc, nCxSrc, nCySrc, SRCCOPY);
			pDCDest->SelectClipRgn(NULL);
			rgn.DeleteObject();
			
			Sleep(20);
		}
		
		pDCDest->BitBlt(nCxDest, nCyDest, nWidth, nHeight, pDCSrc, nCxSrc, nCySrc, SRCCOPY);
		
		pDCDest->SelectClipRgn(NULL);
		
		memdc.SelectObject(pBmpOld);
	}*/
}

void CMovePicView::DrawCube(CDC *pDC, int cx, int cy, int x, int y, int z)
{
	POINT ptarr[4];
	CBrush br, * pBrhOld;

	ptarr[0].x = cx;
	ptarr[0].y = cy;
	ptarr[1].x = cx + x;
	ptarr[1].y = cy;
	ptarr[2].x = cx + x;
	ptarr[2].y = cy + z;
	ptarr[3].x = cx;
	ptarr[3].y = cy + z;

	br.CreateSolidBrush(RGB(255, 0, 0));
	pBrhOld = (CBrush *)pDC->SelectObject(&br);
	pDC->Polygon(ptarr, 4);
	pDC->SelectObject(pBrhOld);
	br.DeleteObject();


	ptarr[0].x = cx + (int)(y * 0.35);
	ptarr[0].y = cy - (int)(y * 0.35);
	ptarr[1].x = cx + x + (int)(y * 0.35);
	ptarr[1].y = cy - (int)(y * 0.35);
	ptarr[2].x = cx + x;
	ptarr[2].y = cy;
	ptarr[3].x = cx;
	ptarr[3].y = cy;

	br.CreateSolidBrush(RGB(192, 0, 0));
	pBrhOld = (CBrush *)pDC->SelectObject(&br);
	pDC->Polygon(ptarr, 4);
	pDC->SelectObject(pBrhOld);
	br.DeleteObject();

	ptarr[0].x = cx + x;
	ptarr[0].y = cy;
	ptarr[1].x = cx + x + (int)(y * 0.35);
	ptarr[1].y = cy - (int)(y * 0.35);
	ptarr[2].x = cx + x + (int)(y * 0.35);
	ptarr[2].y = cy + z - (int)(y * 0.35);
	ptarr[3].x = cx + x;
	ptarr[3].y = cy + z;

	br.CreateSolidBrush(RGB(128, 0, 0));
	pBrhOld = (CBrush *)pDC->SelectObject(&br);
	pDC->Polygon(ptarr, 4);
	pDC->SelectObject(pBrhOld);
	br.DeleteObject();
}

