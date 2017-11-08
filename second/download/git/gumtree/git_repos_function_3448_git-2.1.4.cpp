static const char *ident_default_date(void)
{
	if (!git_default_date[0])
		datestamp(git_default_date, sizeof(git_default_date));
	return git_default_date;
}