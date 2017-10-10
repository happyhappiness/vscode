	va_end(ap);

	if (this_opt)
		die(_("%s: %s cannot be used with %s"), me, this_opt, base_opt);
}

static int run_sequencer(int argc, const char **argv, struct replay_opts *opts)
{
	const char * const * usage_str = revert_or_cherry_pick_usage(opts);
	const char *me = action_name(opts);
	int cmd = 0;
	struct option base_options[] = {
		OPT_CMDMODE(0, "quit", &cmd, N_("end revert or cherry-pick sequence"), 'q'),
