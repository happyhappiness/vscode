error(opts->action == REPLAY_REVERT
		      ? _("could not revert %s... %s")
		      : _("could not apply %s... %s"),
		      find_unique_abbrev(commit->object.oid.hash, DEFAULT_ABBREV),
		      msg.subject);