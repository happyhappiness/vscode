static inline char *xstrdup_or_null(const char *str)
{
	return str ? xstrdup(str) : NULL;
}