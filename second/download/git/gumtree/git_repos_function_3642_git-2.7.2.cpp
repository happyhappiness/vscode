static const char *skip_spaces(const char *s)
{
	while (isspace(*s))
		s++;
	return s;
}