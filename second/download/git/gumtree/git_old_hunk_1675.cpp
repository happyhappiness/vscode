		}
		if (!quiet) {
			printf(remote_branch
			       ? _("Deleted remote branch %s (was %s).\n")
			       : _("Deleted branch %s (was %s).\n"),
			       bname.buf,
			       (flags & REF_ISSYMREF)
			       ? target
			       : find_unique_abbrev(sha1, DEFAULT_ABBREV));
		}
		delete_branch_config(bname.buf);
	}

	free(name);
