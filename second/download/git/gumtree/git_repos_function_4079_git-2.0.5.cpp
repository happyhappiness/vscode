static unsigned long linelen(const char *buffer, unsigned long size)
{
	unsigned long len = 0;
	while (size--) {
		len++;
		if (*buffer++ == '\n')
			break;
	}
	return len;
}