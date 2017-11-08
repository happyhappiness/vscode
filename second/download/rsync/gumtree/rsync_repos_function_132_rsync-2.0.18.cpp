void strlcat(char *d, char *s, int maxlen)
{
	int len1 = strlen(d);
	int len2 = strlen(s);
	if (len1+len2 > maxlen) {
		len2 = maxlen-len1;
	}
	if (len2 > 0) {
		memcpy(d+len1, s, len2);
		d[len1+len2] = 0;
	}
}