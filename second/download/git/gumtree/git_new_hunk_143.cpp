/*
 * Copyright 2008 Peter Harris <git@peter.is-a-geek.org>
 */

#undef NOGDI
#include "../git-compat-util.h"
#include <wingdi.h>
#include <winreg.h>

/*
 ANSI codes used by git: m, K

 This file is git-specific. Therefore, this file does not attempt
 to implement any codes that are not used by git.
*/

static HANDLE console;
static WORD plain_attr;
static WORD attr;
static int negative;
static int non_ascii_used = 0;
static HANDLE hthread, hread, hwrite;
static HANDLE hconsole1, hconsole2;

#ifdef __MINGW32__
typedef struct _CONSOLE_FONT_INFOEX {
	ULONG cbSize;
	DWORD nFont;
	COORD dwFontSize;
	UINT FontFamily;
	UINT FontWeight;
	WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
#endif

typedef BOOL (WINAPI *PGETCURRENTCONSOLEFONTEX)(HANDLE, BOOL,
		PCONSOLE_FONT_INFOEX);

static void warn_if_raster_font(void)
{
	DWORD fontFamily = 0;
	PGETCURRENTCONSOLEFONTEX pGetCurrentConsoleFontEx;

	/* don't bother if output was ascii only */
	if (!non_ascii_used)
		return;

	/* GetCurrentConsoleFontEx is available since Vista */
	pGetCurrentConsoleFontEx = (PGETCURRENTCONSOLEFONTEX) GetProcAddress(
			GetModuleHandle("kernel32.dll"),
			"GetCurrentConsoleFontEx");
	if (pGetCurrentConsoleFontEx) {
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		if (pGetCurrentConsoleFontEx(console, 0, &cfi))
			fontFamily = cfi.FontFamily;
	} else {
		/* pre-Vista: check default console font in registry */
		HKEY hkey;
		if (ERROR_SUCCESS == RegOpenKeyExA(HKEY_CURRENT_USER, "Console",
				0, KEY_READ, &hkey)) {
			DWORD size = sizeof(fontFamily);
			RegQueryValueExA(hkey, "FontFamily", NULL, NULL,
					(LPVOID) &fontFamily, &size);
			RegCloseKey(hkey);
		}
	}

	if (!(fontFamily & TMPF_TRUETYPE)) {
		const wchar_t *msg = L"\nWarning: Your console font probably "
			L"doesn\'t support Unicode. If you experience strange "
			L"characters in the output, consider switching to a "
			L"TrueType font such as Consolas!\n";
		DWORD dummy;
		WriteConsoleW(console, msg, wcslen(msg), &dummy, NULL);
	}
}

static int is_console(int fd)
{
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	HANDLE hcon;

	static int initialized = 0;

	/* get OS handle of the file descriptor */
	hcon = (HANDLE) _get_osfhandle(fd);
	if (hcon == INVALID_HANDLE_VALUE)
		return 0;

	/* check if its a device (i.e. console, printer, serial port) */
	if (GetFileType(hcon) != FILE_TYPE_CHAR)
		return 0;

	/* check if its a handle to a console output screen buffer */
	if (!GetConsoleScreenBufferInfo(hcon, &sbi))
		return 0;

	/* initialize attributes */
	if (!initialized) {
		console = hcon;
		attr = plain_attr = sbi.wAttributes;
		negative = 0;
		initialized = 1;
	}

	return 1;
}

#define BUFFER_SIZE 4096
#define MAX_PARAMS 16

static void write_console(unsigned char *str, size_t len)
{
	/* only called from console_thread, so a static buffer will do */
	static wchar_t wbuf[2 * BUFFER_SIZE + 1];
	DWORD dummy;

	/* convert utf-8 to utf-16 */
	int wlen = xutftowcsn(wbuf, (char*) str, ARRAY_SIZE(wbuf), len);

	/* write directly to console */
	WriteConsoleW(console, wbuf, wlen, &dummy, NULL);

	/* remember if non-ascii characters are printed */
	if (wlen != len)
		non_ascii_used = 1;
}

#define FOREGROUND_ALL (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define BACKGROUND_ALL (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)

static void set_console_attr(void)
{
