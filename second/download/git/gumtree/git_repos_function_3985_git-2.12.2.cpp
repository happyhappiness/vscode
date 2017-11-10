static inline int at_mark(const char *string, int len,
			  const char **suffix, int nr)
{
	int i;

	for (i = 0; i < nr; i++) {
		int suffix_len = strlen(suffix[i]);
		if (suffix_len <= len
		    && !memcmp(string, suffix[i], suffix_len))
			return suffix_len;
	}
	return 0;
}