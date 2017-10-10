error((opts->action == REPLAY_REVERT)
			    ? _("Cannot revert during another revert.")
			    : _("Cannot revert during a cherry-pick."));