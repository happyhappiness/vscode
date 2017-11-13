error(_("commit %s is a merge but no -m option was given."),
				oid_to_hex(&commit->object.oid));