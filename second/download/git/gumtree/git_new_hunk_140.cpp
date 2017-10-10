	}
	CloseHandle(h);

	errno = EINVAL;
	return -1;
}

int mingw_offset_1st_component(const char *path)
{
	int offset = 0;
	if (has_dos_drive_prefix(path))
		offset = 2;

	/* unc paths */
	else if (is_dir_sep(path[0]) && is_dir_sep(path[1])) {

		/* skip server name */
		char *pos = strpbrk(path + 2, "\\/");
		if (!pos)
			return 0; /* Error: malformed unc path */

		do {
			pos++;
		} while (*pos && !is_dir_sep(*pos));

		offset = pos - path;
	}

	return offset + is_dir_sep(path[offset]);
}

int xutftowcsn(wchar_t *wcs, const char *utfs, size_t wcslen, int utflen)
{
	int upos = 0, wpos = 0;
	const unsigned char *utf = (const unsigned char*) utfs;
	if (!utf || !wcs || wcslen < 1) {
		errno = EINVAL;
		return -1;
	}
	/* reserve space for \0 */
	wcslen--;
	if (utflen < 0)
		utflen = INT_MAX;

	while (upos < utflen) {
		int c = utf[upos++] & 0xff;
		if (utflen == INT_MAX && c == 0)
			break;

		if (wpos >= wcslen) {
			wcs[wpos] = 0;
			errno = ERANGE;
			return -1;
		}

		if (c < 0x80) {
			/* ASCII */
			wcs[wpos++] = c;
		} else if (c >= 0xc2 && c < 0xe0 && upos < utflen &&
				(utf[upos] & 0xc0) == 0x80) {
			/* 2-byte utf-8 */
			c = ((c & 0x1f) << 6);
			c |= (utf[upos++] & 0x3f);
			wcs[wpos++] = c;
		} else if (c >= 0xe0 && c < 0xf0 && upos + 1 < utflen &&
				!(c == 0xe0 && utf[upos] < 0xa0) && /* over-long encoding */
				(utf[upos] & 0xc0) == 0x80 &&
				(utf[upos + 1] & 0xc0) == 0x80) {
			/* 3-byte utf-8 */
			c = ((c & 0x0f) << 12);
			c |= ((utf[upos++] & 0x3f) << 6);
			c |= (utf[upos++] & 0x3f);
			wcs[wpos++] = c;
		} else if (c >= 0xf0 && c < 0xf5 && upos + 2 < utflen &&
				wpos + 1 < wcslen &&
				!(c == 0xf0 && utf[upos] < 0x90) && /* over-long encoding */
				!(c == 0xf4 && utf[upos] >= 0x90) && /* > \u10ffff */
				(utf[upos] & 0xc0) == 0x80 &&
				(utf[upos + 1] & 0xc0) == 0x80 &&
				(utf[upos + 2] & 0xc0) == 0x80) {
			/* 4-byte utf-8: convert to \ud8xx \udcxx surrogate pair */
			c = ((c & 0x07) << 18);
			c |= ((utf[upos++] & 0x3f) << 12);
			c |= ((utf[upos++] & 0x3f) << 6);
			c |= (utf[upos++] & 0x3f);
			c -= 0x10000;
			wcs[wpos++] = 0xd800 | (c >> 10);
			wcs[wpos++] = 0xdc00 | (c & 0x3ff);
		} else if (c >= 0xa0) {
			/* invalid utf-8 byte, printable unicode char: convert 1:1 */
			wcs[wpos++] = c;
		} else {
			/* invalid utf-8 byte, non-printable unicode: convert to hex */
			static const char *hex = "0123456789abcdef";
			wcs[wpos++] = hex[c >> 4];
			if (wpos < wcslen)
				wcs[wpos++] = hex[c & 0x0f];
		}
	}
	wcs[wpos] = 0;
	return wpos;
}

int xwcstoutf(char *utf, const wchar_t *wcs, size_t utflen)
{
	if (!wcs || !utf || utflen < 1) {
		errno = EINVAL;
		return -1;
	}
	utflen = WideCharToMultiByte(CP_UTF8, 0, wcs, -1, utf, utflen, NULL, NULL);
	if (utflen)
		return utflen - 1;
	errno = ERANGE;
	return -1;
}

/*
 * Disable MSVCRT command line wildcard expansion (__getmainargs called from
 * mingw startup code, see init.c in mingw runtime).
 */
int _CRT_glob = 0;

typedef struct {
	int newmode;
} _startupinfo;

extern int __wgetmainargs(int *argc, wchar_t ***argv, wchar_t ***env, int glob,
		_startupinfo *si);

static NORETURN void die_startup()
{
	fputs("fatal: not enough memory for initialization", stderr);
	exit(128);
}

static void *malloc_startup(size_t size)
{
	void *result = malloc(size);
	if (!result)
		die_startup();
	return result;
}

static char *wcstoutfdup_startup(char *buffer, const wchar_t *wcs, size_t len)
{
	len = xwcstoutf(buffer, wcs, len) + 1;
	return memcpy(malloc_startup(len), buffer, len);
}

void mingw_startup()
{
	int i, maxlen, argc;
	char *buffer;
	wchar_t **wenv, **wargv;
	_startupinfo si;

	/* get wide char arguments and environment */
	si.newmode = 0;
	if (__wgetmainargs(&argc, &wargv, &wenv, _CRT_glob, &si) < 0)
		die_startup();

	/* determine size of argv and environ conversion buffer */
	maxlen = wcslen(_wpgmptr);
	for (i = 1; i < argc; i++)
		maxlen = max(maxlen, wcslen(wargv[i]));
	for (i = 0; wenv[i]; i++)
		maxlen = max(maxlen, wcslen(wenv[i]));

	/*
	 * nedmalloc can't free CRT memory, allocate resizable environment
	 * list. Note that xmalloc / xmemdupz etc. call getenv, so we cannot
	 * use it while initializing the environment itself.
	 */
	environ_size = i + 1;
	environ_alloc = alloc_nr(environ_size * sizeof(char*));
	environ = malloc_startup(environ_alloc);

	/* allocate buffer (wchar_t encodes to max 3 UTF-8 bytes) */
	maxlen = 3 * maxlen + 1;
	buffer = malloc_startup(maxlen);

	/* convert command line arguments and environment to UTF-8 */
	__argv[0] = wcstoutfdup_startup(buffer, _wpgmptr, maxlen);
	for (i = 1; i < argc; i++)
		__argv[i] = wcstoutfdup_startup(buffer, wargv[i], maxlen);
	for (i = 0; wenv[i]; i++)
		environ[i] = wcstoutfdup_startup(buffer, wenv[i], maxlen);
	environ[i] = NULL;
	free(buffer);

	/* sort environment for O(log n) getenv / putenv */
	qsort(environ, i, sizeof(char*), compareenv);

	/* fix Windows specific environment settings */

	/* on Windows it is TMP and TEMP */
	if (!mingw_getenv("TMPDIR")) {
		const char *tmp = mingw_getenv("TMP");
		if (!tmp)
			tmp = mingw_getenv("TEMP");
		if (tmp)
			setenv("TMPDIR", tmp, 1);
	}

	/* simulate TERM to enable auto-color (see color.c) */
	if (!getenv("TERM"))
		setenv("TERM", "cygwin", 1);

	/* initialize critical section for waitpid pinfo_t list */
	InitializeCriticalSection(&pinfo_cs);

	/* set up default file mode and file modes for stdin/out/err */
	_fmode = _O_BINARY;
	_setmode(_fileno(stdin), _O_BINARY);
	_setmode(_fileno(stdout), _O_BINARY);
	_setmode(_fileno(stderr), _O_BINARY);

	/* initialize Unicode console */
	winansi_init();
}
