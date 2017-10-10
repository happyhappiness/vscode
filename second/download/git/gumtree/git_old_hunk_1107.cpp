
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
