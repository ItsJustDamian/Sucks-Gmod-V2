/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#include "DrawLib.h"

void CDrawLib::SetD3DDevice(IDirect3DDevice9 * pDevice)
{
	this->dev = pDevice;
}

void CDrawLib::SetDrawColor(int r, int g, int b, int a)
{
	this->drawColor = D3DCOLOR_ARGB(a, r, g, b);
}

void CDrawLib::SetDrawColor(int r, int g, int b)
{
	this->drawColor = D3DCOLOR_ARGB(255, r, g, b);
}

void CDrawLib::SetDrawColor(float r, float g, float b)
{
	this->drawColor = D3DCOLOR_ARGB(255, (int)r, (int)g, (int)b);
}

void CDrawLib::SetDrawColor(DWORD color)
{
	this->drawColor = color;
}

LPD3DXFONT CDrawLib::CreateSurfaceFont(int size, const char * font)
{
	if (this->dev == nullptr)
	{
		Logger->ErrorMsg("Failed to create font, device not set!");
		return nullptr;
	}

	LPD3DXFONT tmpFont;
	D3DXCreateFontA(this->dev, size, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font, &tmpFont);
	return tmpFont;
}

void CDrawLib::SetFont(LPD3DXFONT font)
{
	this->Font = font;
}

void CDrawLib::DrawFilledRect(int x, int y, int w, int h)
{
	if (this->dev == nullptr)
	{
		Logger->ErrorMsg("Failed to draw filled rect, device not set!");
		return;
	}

	D3DRECT rect = { x, y, x + w, y + h };
	this->dev->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, this->drawColor, 0, 0);
}

void CDrawLib::DrawBorderBox(int x, int y, int w, int h, int t)
{
	if (this->dev == nullptr)
	{
		Logger->ErrorMsg("Failed to draw border box, device not set!");
		return;
	}

	DrawFilledRect(x, y, w, t);
	DrawFilledRect(x, y, t, h);
	DrawFilledRect(x + w, y, t, h);
	DrawFilledRect(x, y + h, w + t, t);
}

void CDrawLib::DrawCornerdBox(int x, int y, int w, int h, int s, int t)
{
	if (this->dev == nullptr)
	{
		Logger->ErrorMsg("Failed to draw cornered box, device not set!");
		return;
	}

	DrawFilledRect(x - w, y, s, t);
	DrawFilledRect(x - w, y, t, s);
	DrawFilledRect(x + (w - s), y, s, t);
	DrawFilledRect(x + w, y, t, s);
	DrawFilledRect(x - w, y + h, s, t);
	DrawFilledRect(x - w, y + (h - s), t, s);
	DrawFilledRect(x + (w - s), y + h, s, t);
	DrawFilledRect(x + w, y + (h - s), t, s + s);
}

void CDrawLib::DrawLine(int x1, int y1, int x2, int y2, int t)
{
	if (this->dev == nullptr)
	{
		Logger->ErrorMsg("Failed to draw line, device not set!");
		return;
	}

	ID3DXLine* LineL;
	D3DXCreateLine(this->dev, &LineL);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	LineL->SetWidth(t);
	LineL->Draw(Line, 2, this->drawColor);
	LineL->Release();
}

void CDrawLib::DrawString(int x, int y, const char * str)
{
	if (this->Font == nullptr)
	{
		if (this->dev == nullptr)
		{
			Logger->ErrorMsg("Failed to draw string, font not set!");
			return;
		}
	}

	RECT rect = { x, y, x + 120, y + 15 };
	this->Font->DrawTextA(NULL, str, -1, &rect, DT_NOCLIP, this->drawColor);
}
