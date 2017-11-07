static int name_compare(const char *a, int a_len,
			const char *b, int b_len)
{
	int len = (a_len < b_len) ? a_len : b_len;
	int cmp = memcmp(a, b, len);
	if (cmp)
		return cmp;
	return (a_len - b_len);
}