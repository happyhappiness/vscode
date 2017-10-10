	if (!commit)
		return error("no such commit %s", arg);
	commit_list_insert(commit, opt->value);
	return 0;
}

int parse_opt_tertiary(const struct option *opt, const char *arg, int unset)
{
	int *target = opt->value;
	*target = unset ? 2 : 1;
	return 0;
}
