int no_wildcard(const char *string)
{
	return string[simple_length(string)] == '\0';
}