			ret = 1;
			continue;
		}

		if (delete_ref(name, sha1, REF_NODEREF)) {
			error(remote_branch
			      ? _("Error deleting remote-tracking branch '%s'")
			      : _("Error deleting branch '%s'"),
			      bname.buf);
			ret = 1;
			continue;
		}
		if (!quiet) {
			printf(remote_branch
			       ? _("Deleted remote-tracking branch %s (was %s).\n")
			       : _("Deleted branch %s (was %s).\n"),
			       bname.buf,
			       (flags & REF_ISBROKEN) ? "broken"
			       : (flags & REF_ISSYMREF) ? target
			       : find_unique_abbrev(sha1, DEFAULT_ABBREV));
		}
