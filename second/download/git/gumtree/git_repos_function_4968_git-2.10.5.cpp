static int parse_opt_patchformat(const struct option *opt, const char *arg, int unset)
{
	int *opt_value = opt->value;

	if (!strcmp(arg, "mbox"))
		*opt_value = PATCH_FORMAT_MBOX;
	else if (!strcmp(arg, "stgit"))
		*opt_value = PATCH_FORMAT_STGIT;
	else if (!strcmp(arg, "stgit-series"))
		*opt_value = PATCH_FORMAT_STGIT_SERIES;
	else if (!strcmp(arg, "hg"))
		*opt_value = PATCH_FORMAT_HG;
	else if (!strcmp(arg, "mboxrd"))
		*opt_value = PATCH_FORMAT_MBOXRD;
	else
		return error(_("Invalid value for --patch-format: %s"), arg);
	return 0;
}