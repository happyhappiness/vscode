static inline int ps_strncmp(const struct pathspec_item *item,
			     const char *s1, const char *s2, size_t n)
{
	if (item->magic & PATHSPEC_ICASE)
		return strncasecmp(s1, s2, n);
	else
		return strncmp(s1, s2, n);
}