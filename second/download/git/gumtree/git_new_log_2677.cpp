error((opts->action == REPLAY_REVERT)
			    ? _("Cannot cherry-pick during a revert.")
			    : _("Cannot cherry-pick during another cherry-pick."));