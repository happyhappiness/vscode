printf(_("Updating %s..%s\n"),
			       find_unique_abbrev(head_commit->object.oid.hash,
						  DEFAULT_ABBREV),
			       find_unique_abbrev(remoteheads->item->object.oid.hash,
						  DEFAULT_ABBREV));