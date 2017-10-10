
int parse_fetch_recurse_submodules_arg(const char *opt, const char *arg)
{
	return parse_fetch_recurse(opt, arg, 1);
}

static void warn_multiple_config(const unsigned char *commit_sha1,
				 const char *name, const char *option)
{
	const char *commit_string = "WORKTREE";
	if (commit_sha1)
		commit_string = sha1_to_hex(commit_sha1);
