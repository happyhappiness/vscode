static int is_rfc2822_line(const char *buf, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		int ch = buf[i];
		if (ch == ':')
			return 1;
		if (!isalnum(ch) && ch != '-')
			break;
	}

	return 0;
}