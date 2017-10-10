
	/*
	 * Verify that the action matches up with the one in
	 * opts; we don't support arbitrary instructions
	 */
	if (action != opts->action) {
		const char *action_str;
		action_str = action == REPLAY_REVERT ? "revert" : "cherry-pick";
		error(_("Cannot %s during a %s"), action_str, action_name(opts));
		return NULL;
	}

	if (status < 0)
		return NULL;

