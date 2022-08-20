	CClientDC dc(this);
	dc.Ellipse(100, 100, 200, 200);
	CDC memdc, memdc1;
	memdc.CreateCompatibleDC(&dc);
	memdc1.CreateCompatibleDC(&dc);
	CRect rt;
	GetClientRect(&rt);
	int nWidth = rt.Width(), nHeight = rt.Height();
	
	CBitmap bmp, * pBmpOld;
	bmp.CreateCompatibleBitmap(&dc, nWidth, nHeight);
	pBmpOld = memdc.SelectObject(&bmp);
	memdc.BitBlt(0, 0, nWidth, nHeight, &dc, 0, 0, SRCCOPY);
	memdc.SelectObject(pBmpOld);

	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = 0x28;
	GetDIBits(dc.m_hDC, (HBITMAP)bmp, 0, 0, NULL, &bmi, DIB_RGB_COLORS);

	BYTE * pBits = (BYTE *) new BYTE[bmi.bmiHeader.biSizeImage];
	if (!pBits)
		return;
	memset(pBits, 0, bmi.bmiHeader.biSizeImage);
	GetDIBits(dc.m_hDC, (HBITMAP)bmp, 0, bmi.bmiHeader.biHeight, pBits, &bmi, 
		DIB_RGB_COLORS);
	dc.FillSolidRect(0, 0, nWidth, nHeight, RGB(125, 125, 0));
	AfxMessageBox("Ok to restore");

	for (int i = 9; i >= 0; i --)
	{
		for (DWORD l = 0; l < bmi.bmiHeader.biSizeImage; l ++)
			pBits[l] *= i / 10.0;
		SetDIBitsToDevice(dc.m_hDC, 0, 0, nWidth, nHeight, 0, 0, 0, nHeight, pBits, &bmi, 
			DIB_RGB_COLORS);
	}

	delete []pBits;
	AfxMessageBox("Ok");
