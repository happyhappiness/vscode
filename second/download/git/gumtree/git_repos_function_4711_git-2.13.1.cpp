static int line_contains_alnum(const char *ptr, long size)
{
	while (size--)
		if (isalnum((unsigned char)*(ptr++)))
			return 1;
	return 0;
}