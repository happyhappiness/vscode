static void trim_spaces (char *s)
{
	size_t l;

	for (l = strlen (s) - 1; (l > 0) && isspace (s[l]); l--)
		s[l] = '\0';
}