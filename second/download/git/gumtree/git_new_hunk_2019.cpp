extern int odb_mkstemp(char *template, size_t limit, const char *pattern);
extern int odb_pack_keep(char *name, size_t namesz, const unsigned char *sha1);
extern char *xgetcwd(void);

#define REALLOC_ARRAY(x, alloc) (x) = xrealloc((x), (alloc) * sizeof(*(x)))

static inline char *xstrdup_or_null(const char *str)
{
	return str ? xstrdup(str) : NULL;
}

static inline size_t xsize_t(off_t len)
{
	if (len > (size_t) len)
		die("Cannot handle files this big");
	return (size_t)len;
}
