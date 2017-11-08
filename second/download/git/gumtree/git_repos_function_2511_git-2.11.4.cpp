char *xstrdup_tolower(const char *string)
{
	char *result;
	size_t len, i;

	len = strlen(string);
	result = xmallocz(len);
	for (i = 0; i < len; i++)
		result[i] = tolower(string[i]);
	result[i] = '\0';
	return result;
}