char *subst (char *buf, size_t buflen, const char *string, int off1, int off2,
		const char *replacement)
{
	char  *buf_ptr = buf;
	size_t len     = buflen;

	if ((NULL == buf) || (0 >= buflen) || (NULL == string)
			|| (0 > off1) || (0 > off2) || (off1 > off2)
			|| (NULL == replacement))
		return NULL;

	sstrncpy (buf_ptr, string,
			((size_t)off1 + 1 > buflen) ? buflen : (size_t)off1 + 1);
	buf_ptr += off1;
	len     -= off1;

	if (0 >= len)
		return buf;

	sstrncpy (buf_ptr, replacement, len);
	buf_ptr += strlen (replacement);
	len     -= strlen (replacement);

	if (0 >= len)
		return buf;

	sstrncpy (buf_ptr, string + off2, len);
	return buf;
}