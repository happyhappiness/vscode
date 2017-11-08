static int count_slash(const char *s)
{
	int cnt = 0;
	while (*s)
		if (*s++ == '/')
			cnt++;
	return cnt;
}