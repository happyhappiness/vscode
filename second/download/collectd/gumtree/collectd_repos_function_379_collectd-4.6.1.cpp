int escape_slashes (char *buf, int buf_len)
{
	int i;

	if (strcmp (buf, "/") == 0)
	{
		if (buf_len < 5)
			return (-1);

		strncpy (buf, "root", buf_len);
		return (0);
	}

	if (buf_len <= 1)
		return (0);

	/* Move one to the left */
	if (buf[0] == '/')
		memmove (buf, buf + 1, buf_len - 1);

	for (i = 0; i < buf_len - 1; i++)
	{
		if (buf[i] == '\0')
			break;
		else if (buf[i] == '/')
			buf[i] = '_';
	}
	buf[i] = '\0';

	return (0);
}