void strlower(char *s)
{
	while (*s) {
		if (isUpper(s))
			*s = toLower(s);
		s++;
	}
}