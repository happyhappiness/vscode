static const char *ident_default_date(void)
{
	if (!git_default_date.len)
		datestamp(&git_default_date);
	return git_default_date.buf;
}