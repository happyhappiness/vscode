static char *null_strdup(const char *s)
{
	return s ? xstrdup(s) : NULL;
}