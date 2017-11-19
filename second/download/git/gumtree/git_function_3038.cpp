void mingw_open_html(const char *unixpath)
{
	const char *htmlpath = make_backslash_path(unixpath);
	typedef HINSTANCE (WINAPI *T)(HWND, const char *,
			const char *, const char *, const char *, INT);
	T ShellExecute;
	HMODULE shell32;
	int r;

	shell32 = LoadLibrary("shell32.dll");
	if (!shell32)
		die("cannot load shell32.dll");
	ShellExecute = (T)GetProcAddress(shell32, "ShellExecuteA");
	if (!ShellExecute)
		die("cannot run browser");

	printf("Launching default browser to display HTML ...\n");
	r = HCAST(int, ShellExecute(NULL, "open", htmlpath,
				NULL, "\\", SW_SHOWNORMAL));
	FreeLibrary(shell32);
	/* see the MSDN documentation referring to the result codes here */
	if (r <= 32) {
		die("failed to launch browser for %.*s", MAX_PATH, unixpath);
	}
}