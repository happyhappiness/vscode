	for (; *path; ++path)
		if (is_dir_sep(*path))
			ret = (char *)path;
	return ret;
}
#define find_last_dir_sep mingw_find_last_dir_sep
int mingw_offset_1st_component(const char *path);
#define offset_1st_component mingw_offset_1st_component
#define PATH_SEP ';'
#define PRIuMAX "I64u"
#define PRId64 "I64d"

void mingw_open_html(const char *path);
#define open_html mingw_open_html

void mingw_mark_as_git_dir(const char *dir);
#define mark_as_git_dir mingw_mark_as_git_dir

/**
 * Converts UTF-8 encoded string to UTF-16LE.
 *
 * To support repositories with legacy-encoded file names, invalid UTF-8 bytes
 * 0xa0 - 0xff are converted to corresponding printable Unicode chars \u00a0 -
 * \u00ff, and invalid UTF-8 bytes 0x80 - 0x9f (which would make non-printable
 * Unicode) are converted to hex-code.
 *
 * Lead-bytes not followed by an appropriate number of trail-bytes, over-long
 * encodings and 4-byte encodings > \u10ffff are detected as invalid UTF-8.
 *
 * Maximum space requirement for the target buffer is two wide chars per UTF-8
 * char (((strlen(utf) * 2) + 1) [* sizeof(wchar_t)]).
 *
 * The maximum space is needed only if the entire input string consists of
 * invalid UTF-8 bytes in range 0x80-0x9f, as per the following table:
 *
 *               |                   | UTF-8 | UTF-16 |
 *   Code point  |  UTF-8 sequence   | bytes | words  | ratio
 * --------------+-------------------+-------+--------+-------
 * 000000-00007f | 0-7f              |   1   |   1    |  1
 * 000080-0007ff | c2-df + 80-bf     |   2   |   1    |  0.5
 * 000800-00ffff | e0-ef + 2 * 80-bf |   3   |   1    |  0.33
 * 010000-10ffff | f0-f4 + 3 * 80-bf |   4   |  2 (a) |  0.5
 * invalid       | 80-9f             |   1   |  2 (b) |  2
 * invalid       | a0-ff             |   1   |   1    |  1
 *
 * (a) encoded as UTF-16 surrogate pair
 * (b) encoded as two hex digits
 *
 * Note that, while the UTF-8 encoding scheme can be extended to 5-byte, 6-byte
 * or even indefinite-byte sequences, the largest valid code point \u10ffff
 * encodes as only 4 UTF-8 bytes.
 *
 * Parameters:
 * wcs: wide char target buffer
 * utf: string to convert
 * wcslen: size of target buffer (in wchar_t's)
 * utflen: size of string to convert, or -1 if 0-terminated
 *
 * Returns:
 * length of converted string (_wcslen(wcs)), or -1 on failure
 *
 * Errors:
 * EINVAL: one of the input parameters is invalid (e.g. NULL)
 * ERANGE: the output buffer is too small
 */
int xutftowcsn(wchar_t *wcs, const char *utf, size_t wcslen, int utflen);

/**
 * Simplified variant of xutftowcsn, assumes input string is \0-terminated.
 */
static inline int xutftowcs(wchar_t *wcs, const char *utf, size_t wcslen)
{
	return xutftowcsn(wcs, utf, wcslen, -1);
}

/**
 * Simplified file system specific variant of xutftowcsn, assumes output
 * buffer size is MAX_PATH wide chars and input string is \0-terminated,
 * fails with ENAMETOOLONG if input string is too long.
 */
static inline int xutftowcs_path(wchar_t *wcs, const char *utf)
{
	int result = xutftowcsn(wcs, utf, MAX_PATH, -1);
	if (result < 0 && errno == ERANGE)
		errno = ENAMETOOLONG;
	return result;
}

/**
 * Converts UTF-16LE encoded string to UTF-8.
 *
 * Maximum space requirement for the target buffer is three UTF-8 chars per
 * wide char ((_wcslen(wcs) * 3) + 1).
 *
 * The maximum space is needed only if the entire input string consists of
 * UTF-16 words in range 0x0800-0xd7ff or 0xe000-0xffff (i.e. \u0800-\uffff
 * modulo surrogate pairs), as per the following table:
 *
 *               |                       | UTF-16 | UTF-8 |
 *   Code point  |  UTF-16 sequence      | words  | bytes | ratio
 * --------------+-----------------------+--------+-------+-------
 * 000000-00007f | 0000-007f             |   1    |   1   |  1
 * 000080-0007ff | 0080-07ff             |   1    |   2   |  2
 * 000800-00ffff | 0800-d7ff / e000-ffff |   1    |   3   |  3
 * 010000-10ffff | d800-dbff + dc00-dfff |   2    |   4   |  2
 *
 * Note that invalid code points > 10ffff cannot be represented in UTF-16.
 *
 * Parameters:
 * utf: target buffer
 * wcs: wide string to convert
 * utflen: size of target buffer
 *
 * Returns:
 * length of converted string, or -1 on failure
 *
 * Errors:
 * EINVAL: one of the input parameters is invalid (e.g. NULL)
 * ERANGE: the output buffer is too small
 */
int xwcstoutf(char *utf, const wchar_t *wcs, size_t utflen);

/*
 * A critical section used in the implementation of the spawn
 * functions (mingw_spawnv[p]e()) and waitpid(). Intialised in
 * the replacement main() macro below.
 */
extern CRITICAL_SECTION pinfo_cs;

/*
 * A replacement of main() that adds win32 specific initialization.
 */

void mingw_startup();
#define main(c,v) dummy_decl_mingw_main(); \
static int mingw_main(c,v); \
int main(int argc, char **argv) \
{ \
	mingw_startup(); \
	return mingw_main(__argc, (void *)__argv); \
} \
static int mingw_main(c,v)

/*
 * Used by Pthread API implementation for Windows
 */
