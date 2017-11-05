static int buf_cmp(const char *a_begin, const char *a_end,
		   const char *b_begin, const char *b_end)
{
	int a_len = a_end - a_begin;
	int b_len = b_end - b_begin;
	int min = a_len < b_len ? a_len : b_len;
	int cmp;

	cmp = memcmp(a_begin, b_begin, min);
	if (cmp)
		return cmp;

	return a_len - b_len;
}