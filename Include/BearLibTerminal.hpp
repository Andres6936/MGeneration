/*
* BearLibTerminal
* Copyright (C) 2013-2017 Cfyz
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
* of the Software, and to permit persons to whom the Software is furnished to do
* so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef BEARLIBTERMINAL_H
#define BEARLIBTERMINAL_H

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdarg>
#include <cstdlib>
#include <cwchar>
#include <sstream>

/*
 * Keyboard scancodes for events/states
 */
#define TK_A                0x04
#define TK_B                0x05
#define TK_C                0x06
#define TK_D                0x07
#define TK_E                0x08
#define TK_F                0x09
#define TK_G                0x0A
#define TK_H                0x0B
#define TK_I                0x0C
#define TK_J                0x0D
#define TK_K                0x0E
#define TK_L                0x0F
#define TK_M                0x10
#define TK_N                0x11
#define TK_O                0x12
#define TK_P                0x13
#define TK_Q                0x14
#define TK_R                0x15
#define TK_S                0x16
#define TK_T                0x17
#define TK_U                0x18
#define TK_V                0x19
#define TK_W                0x1A
#define TK_X                0x1B
#define TK_Y                0x1C
#define TK_Z                0x1D
#define TK_1                0x1E
#define TK_2                0x1F
#define TK_3                0x20
#define TK_4                0x21
#define TK_5                0x22
#define TK_6                0x23
#define TK_7                0x24
#define TK_8                0x25
#define TK_9                0x26
#define TK_0                0x27
#define TK_RETURN           0x28
#define TK_ENTER            0x28
#define TK_ESCAPE           0x29
#define TK_BACKSPACE        0x2A
#define TK_TAB              0x2B
#define TK_SPACE            0x2C
#define TK_MINUS            0x2D /*  -  */
#define TK_EQUALS           0x2E /*  =  */
#define TK_LBRACKET         0x2F /*  [  */
#define TK_RBRACKET         0x30 /*  ]  */
#define TK_BACKSLASH        0x31 /*  \  */
#define TK_SEMICOLON        0x33 /*  ;  */
#define TK_APOSTROPHE       0x34 /*  '  */
#define TK_GRAVE            0x35 /*  `  */
#define TK_COMMA            0x36 /*  ,  */
#define TK_PERIOD           0x37 /*  .  */
#define TK_SLASH            0x38 /*  /  */
#define TK_F1               0x3A
#define TK_F2               0x3B
#define TK_F3               0x3C
#define TK_F4               0x3D
#define TK_F5               0x3E
#define TK_F6               0x3F
#define TK_F7               0x40
#define TK_F8               0x41
#define TK_F9               0x42
#define TK_F10              0x43
#define TK_F11              0x44
#define TK_F12              0x45
#define TK_PAUSE            0x48 /* Pause/Break */
#define TK_INSERT           0x49
#define TK_HOME             0x4A
#define TK_PAGEUP           0x4B
#define TK_DELETE           0x4C
#define TK_END              0x4D
#define TK_PAGEDOWN         0x4E
#define TK_RIGHT            0x4F /* Right arrow */
#define TK_LEFT             0x50 /* Left arrow */
#define TK_DOWN             0x51 /* Down arrow */
#define TK_UP               0x52 /* Up arrow */
#define TK_KP_DIVIDE        0x54 /* '/' on numpad */
#define TK_KP_MULTIPLY      0x55 /* '*' on numpad */
#define TK_KP_MINUS         0x56 /* '-' on numpad */
#define TK_KP_PLUS          0x57 /* '+' on numpad */
#define TK_KP_ENTER         0x58
#define TK_KP_1             0x59
#define TK_KP_2             0x5A
#define TK_KP_3             0x5B
#define TK_KP_4             0x5C
#define TK_KP_5             0x5D
#define TK_KP_6             0x5E
#define TK_KP_7             0x5F
#define TK_KP_8             0x60
#define TK_KP_9             0x61
#define TK_KP_0             0x62
#define TK_KP_PERIOD        0x63 /* '.' on numpad */
#define TK_SHIFT            0x70
#define TK_CONTROL          0x71
#define TK_ALT              0x72

/*
 * Mouse events/states
 */
#define TK_MOUSE_LEFT       0x80 /* Buttons */
#define TK_MOUSE_RIGHT      0x81
#define TK_MOUSE_MIDDLE     0x82
#define TK_MOUSE_X1         0x83
#define TK_MOUSE_X2         0x84
#define TK_MOUSE_MOVE       0x85 /* Movement event */
#define TK_MOUSE_SCROLL     0x86 /* Mouse scroll event */
#define TK_MOUSE_X          0x87 /* Cusor position in cells */
#define TK_MOUSE_Y          0x88
#define TK_MOUSE_PIXEL_X    0x89 /* Cursor position in pixels */
#define TK_MOUSE_PIXEL_Y    0x8A
#define TK_MOUSE_WHEEL      0x8B /* Scroll direction and amount */
#define TK_MOUSE_CLICKS     0x8C /* Number of consecutive clicks */

/*
 * If key was released instead of pressed, it's code will be OR'ed with TK_KEY_RELEASED:
 * a) pressed 'A': 0x04
 * b) released 'A': 0x04|VK_KEY_RELEASED = 0x104
 */
#define TK_KEY_RELEASED     0x100

/*
 * Virtual key-codes for internal terminal states/variables.
 * These can be accessed via TerminalState function.
 */
#define TK_WIDTH            0xC0 /* Terminal window size in cells */
#define TK_HEIGHT           0xC1
#define TK_CELL_WIDTH       0xC2 /* Character cell size in pixels */
#define TK_CELL_HEIGHT      0xC3
#define TK_COLOR            0xC4 /* Current foregroung color */
#define TK_BKCOLOR          0xC5 /* Current background color */
#define TK_LAYER            0xC6 /* Current layer */
#define TK_COMPOSITION      0xC7 /* Current composition state */
#define TK_CHAR             0xC8 /* Translated ANSI code of last produced character */
#define TK_WCHAR            0xC9 /* Unicode codepoint of last produced character */
#define TK_EVENT            0xCA /* Last dequeued event */
#define TK_FULLSCREEN       0xCB /* Fullscreen state */

/*
 * Other events
 */
#define TK_CLOSE            0xE0
#define TK_RESIZED          0xE1

/*
 * Generic mode enum.
 * Right now it is used for composition option only.
 */
#define TK_OFF                 0
#define TK_ON                  1

/*
 * Input result codes for TerminalRead function.
 */
#define TK_INPUT_NONE          0
#define TK_INPUT_CANCELLED    -1

/*
 * Text printing alignment.
 */
#define TK_ALIGN_DEFAULT       0
#define TK_ALIGN_LEFT          1
#define TK_ALIGN_RIGHT         2
#define TK_ALIGN_CENTER        3
#define TK_ALIGN_TOP           4
#define TK_ALIGN_BOTTOM        8
#define TK_ALIGN_MIDDLE       12

/*
 * Terminal uses unsigned 32-bit value for color representation in ARGB order (0xAARRGGBB), e. g.
 * a) solid red is 0xFFFF0000
 * b) half-transparent green is 0x8000FF00
 */
typedef uint32_t color_t;

typedef struct dimensions_t_
{
	int width;
	int height;
}
		dimensions_t;

int TerminalOpen();

void TerminalClose();

int TerminalSet8(const int8_t* value);

int TerminalSet16(const int16_t* value);

int TerminalSet32(const int32_t* value);

void TerminalRefresh();

void TerminalClear();

void TerminalClearArea(int x, int y, int w, int h);

void TerminalCrop(int x, int y, int w, int h);

void TerminalLayer(int index);

void TerminalColor(color_t color);

void TerminalBackColor(color_t color);

void TerminalComposition(int mode);

void TerminalFont8(const int8_t* name);

void TerminalFont16(const int16_t* name);

void TerminalFont32(const int32_t* name);

void TerminalPut(int x, int y, int code);

void TerminalPutExt(int x, int y, int dx, int dy, int code, color_t* corners);

int TerminalPick(int x, int y, int index);

color_t TerminalPickColor(int x, int y, int index);

color_t TerminalPickBackColor(int x, int y);

void TerminalPrintExt8(int x, int y, int w, int h, int align, const int8_t* s, int* out_w, int* out_h);

void TerminalPrintExt16(int x, int y, int w, int h, int align, const int16_t* s, int* out_w, int* out_h);

void TerminalPrintExt32(int x, int y, int w, int h, int align, const int32_t* s, int* out_w, int* out_h);

void TerminalMeasureExt8(int w, int h, const int8_t* s, int* out_w, int* out_h);

void TerminalMeasureExt16(int w, int h, const int16_t* s, int* out_w, int* out_h);

void TerminalMeasureExt32(int w, int h, const int32_t* s, int* out_w, int* out_h);

int TerminalHasInput();

int TerminalState(int code);

int TerminalRead();

int TerminalReadStr8(int x, int y, int8_t* buffer, int max);

int TerminalReadStr16(int x, int y, int16_t* buffer, int max);

int TerminalReadStr32(int x, int y, int32_t* buffer, int max);

int TerminalPeek();

void TerminalDelay(int period);

const int8_t* TerminalGet8(const int8_t* key, const int8_t* default_);

const int16_t* TerminalGet16(const int16_t* key, const int16_t* default_);

const int32_t* TerminalGet32(const int32_t* key, const int32_t* default_);

color_t ColorFromName8(const int8_t* name);

color_t ColorFromName16(const int16_t* name);

color_t ColorFromName32(const int32_t* name);

/*
 * These functions provide inline string formatting support
 * for TerminalSetF, TerminalPrintF, etc.
 *
 * Using static termporary buffer is okay because terminal API is not
 * required to be multiple-thread safe by design.
 */

#define TERMINAL_VSPRINTF_MAXIMUM_BUFFER_SIZE 65536

inline const char* terminal_vsprintf(const char* s, va_list args)
{
	static int buffer_size = 512;
	static char* buffer = nullptr;
	int rc = 0;

	if (!s)
	{
		return nullptr;
	}
	else if (!buffer)
	{
		buffer = (char*)malloc(buffer_size);
	}

	while (true)
	{
		buffer[buffer_size - 1] = '\0';
		rc = vsnprintf(buffer, buffer_size, s, args);
		if (rc >= buffer_size || buffer[buffer_size - 1] != '\0')
		{
			if (buffer_size >= TERMINAL_VSPRINTF_MAXIMUM_BUFFER_SIZE)
			{
				return nullptr;
			}

			buffer_size *= 2;
			buffer = (char*)realloc(buffer, buffer_size);
		}
		else
		{
			break;
		}
	}

	return rc >= 0 ? buffer : nullptr;
}

inline const wchar_t* terminal_vswprintf(const wchar_t* s, va_list args)
{
	static int buffer_size = 512;
	static wchar_t* buffer = nullptr;
	int rc = 0;

	if (!s)
	{
		return nullptr;
	}
	else if (!buffer)
	{
		buffer = (wchar_t*)malloc(buffer_size * sizeof(wchar_t));
	}

	while (true)
	{
		buffer[buffer_size - 1] = L'\0';
#if defined(_WIN32)
		rc = _vsnwprintf(buffer, buffer_size, s, args);
#else
		rc = vswprintf(buffer, buffer_size, s, args);
#endif
		if (rc >= buffer_size || buffer[buffer_size - 1] != L'\0')
		{
			if (buffer_size >= TERMINAL_VSPRINTF_MAXIMUM_BUFFER_SIZE)
			{
				return nullptr;
			}

			buffer_size *= 2;
			buffer = (wchar_t*)realloc(buffer, buffer_size * sizeof(wchar_t));
		}
		else
		{
			break;
		}
	}

	return rc >= 0 ? buffer : nullptr;
}

#define TERMINAL_FORMATTED_WRAP(type, call) \
    type ret; \
    va_list args; \
    va_start(args, s); \
    ret = call; \
    va_end(args); \
    return ret;

/*
 * This set of inline functions define basic name substitution + type cast:
 * terminal_[w]xxxx -> terminal_xxxx{8|16|32}
 */

inline int TerminalSet(const char* s)
{
	return TerminalSet8((const int8_t*)s);
}

inline int TerminalSetF(const char* s, ...)
{
	TERMINAL_FORMATTED_WRAP(int, TerminalSet(terminal_vsprintf(s, args)))
}

inline int TerminalWSet(const wchar_t* s)
{
	return TerminalSet32((const int32_t*)s);
}

inline int TerminalWSetF(const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(int, TerminalWSet(terminal_vswprintf(s, args)))
}

inline void TerminalFont(const char* name)
{
	TerminalFont8((const int8_t*)name);
}

inline void TerminalWFont(const wchar_t* name)
{
	TerminalFont32((const int32_t*)name);
}

inline dimensions_t TerminalPrint(int x, int y, const char* s)
{
	dimensions_t ret;
	TerminalPrintExt8(x, y, 0, 0, TK_ALIGN_DEFAULT, (const int8_t*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t TerminalPrintF(int x, int y, const char* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalPrint(x, y, terminal_vsprintf(s, args)))
}

inline dimensions_t TerminalWPrint(int x, int y, const wchar_t* s)
{
	dimensions_t ret;
	TerminalPrintExt32(x, y, 0, 0, TK_ALIGN_DEFAULT,
			(const int32_t*)s, &ret.width,
			&ret.height);
	return ret;
}

inline dimensions_t TerminalWPrintF(int x, int y, const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalWPrint(x, y, terminal_vswprintf(s, args)))
}

inline dimensions_t TerminalPrintExt(int x, int y, int w, int h, int align, const char* s)
{
	dimensions_t ret;
	TerminalPrintExt8(x, y, w, h, align, (const int8_t*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t TerminalPrintFExt(int x, int y, int w, int h, int align, const char* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalPrintExt(x, y, w, h, align, terminal_vsprintf(s, args)));
}

inline dimensions_t TerminalWPrintExt(int x, int y, int w, int h, int align, const wchar_t* s)
{
	dimensions_t ret;
	TerminalPrintExt32(x, y, w, h, align, (const int32_t*)s,
			&ret.width, &ret.height);
	return ret;
}

inline dimensions_t TerminalWPrintFExt(int x, int y, int w, int h, int align, const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalWPrintExt(x, y, w, h, align, terminal_vswprintf(s, args)))
}

inline dimensions_t TerminalMeasure(const char* s)
{
	dimensions_t ret;
	TerminalMeasureExt8(0, 0, (const int8_t*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t TerminalMeasureF(const char* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalMeasure(terminal_vsprintf(s, args)))
}

inline dimensions_t TerminalWMeasure(const wchar_t* s)
{
	dimensions_t ret;
	TerminalMeasureExt32(0, 0, (const int32_t*)s, &ret.width,
			&ret.height);
	return ret;
}

inline dimensions_t TerminalWMeasureF(const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalWMeasure(terminal_vswprintf(s, args)))
}

inline dimensions_t TerminalMeasureExt(int w, int h, const char* s)
{
	dimensions_t ret;
	TerminalMeasureExt8(w, h, (const int8_t*)s, &ret.width, &ret.height);
	return ret;
}

inline dimensions_t TerminalMeasureFExt(int w, int h, const char* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalMeasureExt(w, h, terminal_vsprintf(s, args)))
}

inline dimensions_t TerminalWMeasureExt(int w, int h, const wchar_t* s)
{
	dimensions_t ret;
	TerminalMeasureExt32(w, h, (const int32_t*)s, &ret.width,
			&ret.height);
	return ret;
}

inline dimensions_t TerminalWMeasureFExt(int w, int h, const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalWMeasureExt(w, h, terminal_vswprintf(s, args)))
}

inline int TerminalReadStr(int x, int y, char* buffer, int max)
{
	return TerminalReadStr8(x, y, (int8_t*)buffer, max);
}

inline int TerminalReadWStr(int x, int y, wchar_t* buffer, int max)
{
	return TerminalReadStr32(x, y, (int32_t*)buffer, max);
}

inline const char* TerminalGet(const char* key, const char* default_ = (const char*)0)
{
	return (const char*)TerminalGet8((const int8_t*)key, (const int8_t*)default_);
}

inline const wchar_t* TerminalWGet(const wchar_t* key,
		const wchar_t* default_ = (const wchar_t*)0)
{
	return (const wchar_t*)TerminalGet32((const int32_t*)key,
			(const int32_t*)default_);
}

inline color_t ColorFromName(const char* name)
{
	return ColorFromName8((const int8_t*)name);
}

inline color_t ColorFromWName(const wchar_t* name)
{
	return ColorFromName32((const int32_t*)name);
}

#ifdef __cplusplus

/*
 * C++ supports function overloading, should take advantage of it.
 */

inline int TerminalSet(const wchar_t* s)
{
	return TerminalWSet(s);
}

inline int TerminalSetF(const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(int, TerminalWSet(terminal_vswprintf(s, args)));
}

inline void TerminalColor(const char* name)
{
	TerminalColor(ColorFromName(name));
}

inline void TerminalColor(const wchar_t* name)
{
	TerminalColor(ColorFromWName(name));
}

inline void TerminalBackColor(const char* name)
{
	TerminalBackColor(ColorFromName(name));
}

inline void TerminalBackColor(const wchar_t* name)
{
	TerminalBackColor(ColorFromWName(name));
}

inline void TerminalFont(const wchar_t* name)
{
	TerminalWFont(name);
}

inline void TerminalPutExt(int x, int y, int dx, int dy, int code)
{
	TerminalPutExt(x, y, dx, dy, code, nullptr);
}

inline dimensions_t TerminalPrint(int x, int y, const wchar_t* s)
{
	return TerminalWPrint(x, y, s);
}

inline dimensions_t TerminalPrintF(int x, int y, const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalWPrint(x, y, terminal_vswprintf(s, args)))
}

inline dimensions_t TerminalPrintExt(int x, int y, int w, int h, int align, const wchar_t* s)
{
	return TerminalWPrintExt(x, y, w, h, align, s);
}

inline dimensions_t TerminalPrintFExt(int x, int y, int w, int h, int align, const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalWPrintExt(x, y, w, h, align, terminal_vswprintf(s, args)))
}

inline dimensions_t TerminalMeasure(const wchar_t* s)
{
	return TerminalWMeasure(s);
}

inline dimensions_t TerminalMeasureF(const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalWMeasure(terminal_vswprintf(s, args)))
}

inline dimensions_t TerminalMeasureExt(int w, int h, const wchar_t* s)
{
	return TerminalWMeasureExt(w, h, s);
}

inline dimensions_t TerminalMeasureFExt(int w, int h, const wchar_t* s, ...)
{
	TERMINAL_FORMATTED_WRAP(dimensions_t, TerminalWMeasureExt(w, h, terminal_vswprintf(s, args)))
}

inline int TerminalReadStr(int x, int y, wchar_t* buffer, int max)
{
	return TerminalReadWStr(x, y, buffer, max);
}

inline color_t ColorFromName(const wchar_t* name)
{
	return ColorFromWName(name);
}

inline int TerminalPick(int x, int y)
{
	return TerminalPick(x, y, 0);
}

inline color_t TerminalPickColor(int x, int y)
{
	return TerminalPickColor(x, y, 0);
}

inline const wchar_t* TerminalGet(const wchar_t* key, const wchar_t* default_ = (const wchar_t*)0)
{
	return TerminalWGet(key, default_);
}

template <typename T, typename C>
T TerminalGet(const C* key, const T& default_ = T())
{
	const C* result_str = TerminalGet(key, (const C*)0);
	if (result_str[0] == C(0))
	{
		return default_;
	}
	T result;
	return (bool)(std::basic_istringstream <C>(result_str) >> result) ? result : default_;
}

#endif /* __cplusplus */

/*
 * Color routines
 */
inline color_t ColorFromARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	return ((color_t)a << 24) | (r << 16) | (g << 8) | b;
}

/*
 * Other functional sugar
 */
inline int TerminalCheck(int code)
{
	return TerminalState(code) > 0;
}

#endif // BEARLIBTERMINAL_H
