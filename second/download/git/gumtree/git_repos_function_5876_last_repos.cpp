static const char * const *revert_or_cherry_pick_usage(struct replay_opts *opts)
{
	return opts->action == REPLAY_REVERT ? revert_usage : cherry_pick_usage;
}