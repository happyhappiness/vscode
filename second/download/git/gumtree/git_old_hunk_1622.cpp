			info.header_prefix = "commit ";
	}
	else if (revs.verbose_header)
		/* Only --header was specified */
		revs.commit_format = CMIT_FMT_RAW;

	if ((!revs.commits &&
	     (!(revs.tag_objects || revs.tree_objects || revs.blob_objects) &&
	      !revs.pending.nr)) ||
	    revs.diff)
		usage(rev_list_usage);

	if (revs.show_notes)
		die(_("rev-list does not support display of notes"));

