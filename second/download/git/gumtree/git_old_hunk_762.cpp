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
	warning("%s:.gitmodules, multiple configurations found for "
			"'submodule.%s.%s'. Skipping second one!",
			commit_string, name, option);
}

struct parse_config_parameter {
	struct submodule_cache *cache;
	const unsigned char *commit_sha1;
	const unsigned char *gitmodules_sha1;
	int overwrite;
};

static int parse_config(const char *var, const char *value, void *data)
{
