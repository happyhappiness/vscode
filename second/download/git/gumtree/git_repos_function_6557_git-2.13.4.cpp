static void write_console(unsigned char *str, size_t len)
{
	/* only called from console_thread, so a static buffer will do */
	static wchar_t wbuf[2 * BUFFER_SIZE + 1];
	DWORD dummy;

	/* convert utf-8 to utf-16 */
	int wlen = xutftowcsn(wbuf, (char*) str, ARRAY_SIZE(wbuf), len);
	if (wlen < 0) {
		wchar_t *err = L"[invalid]";
		WriteConsoleW(console, err, wcslen(err), &dummy, NULL);
		return;
	}

	/* write directly to console */
	WriteConsoleW(console, wbuf, wlen, &dummy, NULL);

	/* remember if non-ascii characters are printed */
	if (wlen != len)
		non_ascii_used = 1;
}