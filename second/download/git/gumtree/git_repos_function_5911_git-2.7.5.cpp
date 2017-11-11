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