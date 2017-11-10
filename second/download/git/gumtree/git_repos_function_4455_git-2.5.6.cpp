static int count_slashes(const char *cp)
{
	int cnt = 0;
	char ch;

	while ((ch = *cp++))
		if (ch == '/')
			cnt++;
	return cnt;
}