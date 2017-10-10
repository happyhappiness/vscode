		*from = xstrdup(arg);
	else
		*from = xstrdup(git_committer_info(IDENT_NO_DATE));
	return 0;
}

int cmd_format_patch(int argc, const char **argv, const char *prefix)
{
	struct commit *commit;
	struct commit **list = NULL;
	struct rev_info rev;
	struct setup_revision_opt s_r_opt;
