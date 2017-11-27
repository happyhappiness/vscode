static char *unquote (const char *orig)
{
	char *ret = strdup (orig);
	int len;

	if (ret == NULL)
		return (NULL);

	len = strlen (ret);

	if ((len < 2) || (ret[0] != '"') || (ret[len - 1] != '"'))
		return (ret);

	len -= 2;
	memmove (ret, ret + 1, len);
	ret[len] = '\0';

	for (int i = 0; i < len; i++)
	{
		if (ret[i] == '\\')
		{
			memmove (ret + i, ret + (i + 1), len - i);
			len--;
		}
	}

	return (ret);
}