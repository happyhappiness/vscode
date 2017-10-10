{
	if (len > (size_t) len)
		die("Cannot handle files this big");
	return (size_t)len;
}

__attribute__((format (printf, 3, 4)))
extern int xsnprintf(char *dst, size_t max, const char *fmt, ...);

/* in ctype.c, for kwset users */
extern const unsigned char tolower_trans_tbl[256];

/* Sane ctype - no locale, and works with signed chars */
#undef isascii
#undef isspace
