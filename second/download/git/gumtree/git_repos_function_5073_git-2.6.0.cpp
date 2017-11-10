static int from_callback(const struct option *opt, const char *arg, int unset)
{
	char **from = opt->value;

	free(*from);

	if (unset)
		*from = NULL;
	else if (arg)
		*from = xstrdup(arg);
	else
		*from = xstrdup(git_committer_info(IDENT_NO_DATE));
	return 0;
}