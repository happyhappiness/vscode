
int parse_fetch_recurse_submodules_arg(const char *opt, const char *arg)
{
	return parse_fetch_recurse(opt, arg, 1);
}

static int parse_push_recurse(const char *opt, const char *arg,
			       int die_on_error)
{
	switch (git_config_maybe_bool(opt, arg)) {
	case 1:
		/* There's no simple "on" value when pushing */
		if (die_on_error)
			die("bad %s argument: %s", opt, arg);
		else
			return RECURSE_SUBMODULES_ERROR;
	case 0:
		return RECURSE_SUBMODULES_OFF;
	default:
		if (!strcmp(arg, "on-demand"))
			return RECURSE_SUBMODULES_ON_DEMAND;
		else if (!strcmp(arg, "check"))
			return RECURSE_SUBMODULES_CHECK;
		else if (die_on_error)
			die("bad %s argument: %s", opt, arg);
		else
			return RECURSE_SUBMODULES_ERROR;
	}
}

int parse_push_recurse_submodules_arg(const char *opt, const char *arg)
{
	return parse_push_recurse(opt, arg, 1);
}

static void warn_multiple_config(const unsigned char *commit_sha1,
				 const char *name, const char *option)
{
	const char *commit_string = "WORKTREE";
	if (commit_sha1)
		commit_string = sha1_to_hex(commit_sha1);
