
	/*
	 * Verify that the action matches up with the one in
	 * opts; we don't support arbitrary instructions
	 */
	if (action != opts->action) {
		if (action == REPLAY_REVERT)
		      error((opts->action == REPLAY_REVERT)
			    ? _("Cannot revert during another revert.")
			    : _("Cannot revert during a cherry-pick."));
		else
		      error((opts->action == REPLAY_REVERT)
			    ? _("Cannot cherry-pick during a revert.")
			    : _("Cannot cherry-pick during another cherry-pick."));
		return NULL;
	}

	if (status < 0)
		return NULL;

