void strlcpy(char *d, char *s, int maxlen)
{
	int len = strlen(s);
	if (len > maxlen) len = maxlen;
	memcpy(d, s, len);
	d[len] = 0;
}