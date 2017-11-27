static void trim_spaces (char *s)
{
	for (size_t l = strlen (s) - 1; (l > 0) && isspace ((int) s[l]); l--)
		s[l] = '\0';
}