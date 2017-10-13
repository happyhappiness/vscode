static const char *action_name(const struct replay_opts *opts)
{
	switch (opts->action) {
	case REPLAY_REVERT:
		return N_("revert");
	case REPLAY_PICK:
		return N_("cherry-pick");
	case REPLAY_INTERACTIVE_REBASE:
		return N_("rebase -i");
	}
	die(_("Unknown action: %d"), opts->action);
}