
	return 0;
}

static const char *action_name(const struct replay_opts *opts)
{
	return opts->action == REPLAY_REVERT ? N_("revert") : N_("cherry-pick");
}

struct commit_message {
	char *parent_label;
	char *label;
	char *subject;
