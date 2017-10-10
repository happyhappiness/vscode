printf(remote_branch
			       ? _("Deleted remote-tracking branch %s (was %s).\n")
			       : _("Deleted branch %s (was %s).\n"),
			       bname.buf,
			       (flags & REF_ISBROKEN) ? "broken"
			       : (flags & REF_ISSYMREF) ? target
			       : find_unique_abbrev(oid.hash, DEFAULT_ABBREV));