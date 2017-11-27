int strunescape (char *buf, size_t buf_len)
{
	size_t i;

	for (i = 0; (i < buf_len) && (buf[i] != '\0'); ++i)
	{
		if (buf[i] != '\\')
			continue;

		if ((i >= buf_len) || (buf[i + 1] == '\0')) {
			ERROR ("string unescape: backslash found at end of string.");
			return (-1);
		}

		switch (buf[i + 1]) {
			case 't':
				buf[i] = '\t';
				break;
			case 'n':
				buf[i] = '\n';
				break;
			case 'r':
				buf[i] = '\r';
				break;
			default:
				buf[i] = buf[i + 1];
				break;
		}

		memmove (buf + i + 1, buf + i + 2, buf_len - i - 2);
	}
	return (0);
}