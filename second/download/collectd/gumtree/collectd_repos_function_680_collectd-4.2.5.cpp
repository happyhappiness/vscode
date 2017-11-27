static char *unquote (const char *orig)
{
	char *ret = strdup (orig);
	int len;
	int i;

	if (ret == NULL)
		return (NULL);

	len = strlen (ret);

	if ((len < 2) || (ret[0] != '"') || (ret[len - 1] != '"'))
		return (ret);

	ret++;
	len -= 2;
	ret[len] = '\0';

	for (i = 0; i < len; i++)
	{
		if (ret[i] == '\\')
		{
			memmove (ret + i, ret + (i + 1), len - i);
			len--;
		}
	}

	return (ret);
}