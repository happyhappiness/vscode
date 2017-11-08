static int is_empty_line(const char *bol, const char *eol)
{
	while (bol < eol && isspace(*bol))
		bol++;
	return bol == eol;
}