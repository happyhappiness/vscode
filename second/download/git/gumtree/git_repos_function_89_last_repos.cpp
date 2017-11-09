static int needs_rfc822_quoting(const char *s, int len)
{
	int i;
	for (i = 0; i < len; i++)
		if (is_rfc822_special(s[i]))
			return 1;
	return 0;
}