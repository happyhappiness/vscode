size_t pathjoin(char *dest, size_t destsize, const char *p1, const char *p2)
{
	size_t len = strlcpy(dest, p1, destsize);
	if (len < destsize - 1) {
		if (!len || dest[len-1] != '/')
			dest[len++] = '/';
		if (len < destsize - 1)
			len += strlcpy(dest + len, p2, destsize - len);
		else {
			dest[len] = '\0';
			len += strlen(p2);
		}
	}
	else
		len += strlen(p2) + 1; /* Assume we'd insert a '/'. */
	return len;
}