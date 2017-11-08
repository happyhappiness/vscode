void strlower(char *s)
{
	while (*s) {
		if (isupper(*s)) *s = tolower(*s);
		s++;
	}
}