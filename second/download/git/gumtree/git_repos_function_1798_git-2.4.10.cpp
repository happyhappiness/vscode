int strcmp_icase(const char *a, const char *b)
{
	return ignore_case ? strcasecmp(a, b) : strcmp(a, b);
}