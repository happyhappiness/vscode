int fspathncmp(const char *a, const char *b, size_t count)
{
	return ignore_case ? strncasecmp(a, b, count) : strncmp(a, b, count);
}