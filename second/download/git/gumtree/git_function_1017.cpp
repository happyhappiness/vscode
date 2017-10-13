static int option_parse_m(const struct option *opt,
			  const char *arg, int unset)
{
	struct replay_opts *replay = opt->value;
	char *end;

	if (unset) {
		replay->mainline = 0;
		return 0;
	}

	replay->mainline = strtol(arg, &end, 10);
	if (*end || replay->mainline <= 0)
		return opterror(opt, "expects a number greater than zero", 0);

	return 0;
}