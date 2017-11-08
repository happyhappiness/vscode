static int option_parse_x(const struct option *opt,
			  const char *arg, int unset)
{
	struct replay_opts **opts_ptr = opt->value;
	struct replay_opts *opts = *opts_ptr;

	if (unset)
		return 0;

	ALLOC_GROW(opts->xopts, opts->xopts_nr + 1, opts->xopts_alloc);
	opts->xopts[opts->xopts_nr++] = xstrdup(arg);
	return 0;
}