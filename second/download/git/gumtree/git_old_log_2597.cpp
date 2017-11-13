error(_("Commit %s is a merge but no -m option was given."),
				sha1_to_hex(commit->object.sha1));