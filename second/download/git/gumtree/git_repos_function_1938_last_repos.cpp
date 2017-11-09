static inline int strtoul_ui(char const *s, int base, unsigned int *result)
{
	unsigned long ul;
	char *p;

	errno = 0;
	/* negative values would be accepted by strtoul */
	if (strchr(s, '-'))
		return -1;
	ul = strtoul(s, &p, base);
	if (errno || *p || p == s || (unsigned int) ul != ul)
		return -1;
	*result = ul;
	return 0;
}