#pragma once
#include "IVDebugOverlay.h"

#ifdef CreateFont
#undef CreateFont
#endif
#include "memory.h"

class CEngineVGui;

enum PaintMode_t
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
};

typedef unsigned int VPANEL;

// handles
typedef unsigned long HCursor;
typedef unsigned long HTexture;
typedef unsigned long HFont;

struct IntRect
{
	int x0;
	int y0;
	int w;
	int h;
};

enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

struct Vertex_t
{
	Vertex_t() {}

	void* m_Position;
	void* m_TexCoord;
};

struct CharRenderInfo
{
	// Text pos
	int				x, y;
	// Top left and bottom right
	// This is now a pointer to an array maintained by the surface, to avoid copying the data on the 360
	Vertex_t* verts;
	int				textureId;
	int				abcA;
	int				abcB;
	int				abcC;
	int				fontTall;
	HFont			currentFont;
	// In:
	FontDrawType_t	drawType;
	wchar_t			ch;

	// Out
	bool			valid;
	// In/Out (true by default)
	bool			shouldclip;
};

class ISurface
{
public:
	constexpr void DrawSetColor(int r, int g, int b, int a = 255) noexcept
	{
		memory::Call<void>(this, 14, r, g, b, a);
	}

	constexpr void DrawFilledRect(int x, int y, int xx, int yy) noexcept
	{
		memory::Call<void>(this, 15, x, y, xx, yy);
	}

	constexpr void DrawOutlinedRect(int x, int y, int xx, int yy) noexcept
	{
		memory::Call<void>(this, 17, x, y, xx, yy);
	}
	constexpr void DrawLine(int x, int y, int xx, int yy) noexcept
	{
		memory::Call<void>(this, 18, x, y, xx, yy);
	}
	constexpr void DrawOutlinedCircle(int x, int y, int radius, int segments) noexcept
	{
		memory::Call<void>(this, 107, x, y, radius, segments);
	}

	constexpr void DrawColoredCircle(int centerx, int centery, float radius, int r, int g, int b, int a) noexcept
	{
		memory::Call<void>(this, 162, centerx, centery, radius, r, g, b, a);
	}

	void DrawSetTextFont(HFont font)
	{
		memory::Call<void>(this, 22, font);
	}

	void DrawSetTextColor(int r, int g, int b, int a)
	{
		memory::Call<void>(this, 24, r, g, b, a);
	}

	void DrawSetTextPos(int x, int y)
	{
		memory::Call<void>(this, 25, x, y);
	}
	void DrawPrintText(const wchar_t* text, int textLen, int unknown)
	{
		memory::Call<void>(this, 27, text, textLen, unknown);
	}
	HFont CreateFont()
	{
		return memory::Call<HFont>(this, 70);
	}
	bool SetFontGlyphSet(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		return memory::Call<bool>(this, 71, font, windowsFontName, tall, weight, blur, scanlines, flags,0,0);
	}
};