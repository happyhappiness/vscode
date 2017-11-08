static inline int ps_strcmp(const struct pathspec_item *item,
			    const char *s1, const char *s2)
{
	if (item->magic & PATHSPEC_ICASE)
		return strcasecmp(s1, s2);
	else
		return strcmp(s1, s2);
}