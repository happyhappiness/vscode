static const char *skipspaces(const char *s)
{
	while (isspace(*s))
		s++;
	return s;
}