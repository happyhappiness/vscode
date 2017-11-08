static const char *find_encoding(const char *begin, const char *end)
{
	const char *needle = "\nencoding ";
	char *bol, *eol;

	bol = memmem(begin, end ? end - begin : strlen(begin),
		     needle, strlen(needle));
	if (!bol)
		return git_commit_encoding;
	bol += strlen(needle);
	eol = strchrnul(bol, '\n');
	*eol = '\0';
	return bol;
}