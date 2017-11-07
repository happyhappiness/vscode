static char *dup_downcase(const char *string)
{
	char *result;
	size_t len, i;

	len = strlen(string);
	result = xmalloc(len + 1);
	for (i = 0; i < len; i++)
		result[i] = tolower(string[i]);
	result[i] = '\0';
	return result;
}