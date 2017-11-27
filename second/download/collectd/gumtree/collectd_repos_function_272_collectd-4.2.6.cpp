void sstrncpy (char *d, const char *s, int len)
{
	strncpy (d, s, len);
	d[len - 1] = '\0';
}