/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "MainHeader.h"

class CDrawLib
{
private:
	IDirect3DDevice9 * dev;
	DWORD drawColor;
	LPD3DXFONT Font = NULL;
public:
	void SetD3DDevice(IDirect3DDevice9 * pDevice);
	void SetDrawColor(int r, int g, int b, int a);
	void SetDrawColor(int r, int g, int b);
	void SetDrawColor(float r, float g, float b);
	void SetDrawColor(DWORD color);
	LPD3DXFONT CreateSurfaceFont(int size, const char* font);
	void SetFont(LPD3DXFONT font);

	void DrawFilledRect(int x, int y, int w, int h);
	void DrawBorderBox(int x, int y, int w, int h, int t);
	void DrawCornerdBox(int x, int y, int w, int h, int s, int t);
	void DrawLine(int x1, int y1, int x2, int y2, int t);
	void DrawString(int x, int y, const char* str);
};

inline CDrawLib * DrawLib;