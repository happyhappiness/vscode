			entry->processed = 0;
			break;
		}
	} else if (o_sha && (!a_sha || !b_sha)) {
		/* Case A: Deleted in one */
		if ((!a_sha && !b_sha) ||
		    (!b_sha && blob_unchanged(o_sha, o_mode, a_sha, a_mode, normalize, path)) ||
		    (!a_sha && blob_unchanged(o_sha, o_mode, b_sha, b_mode, normalize, path))) {
			/* Deleted in both or deleted in one and
			 * unchanged in the other */
			if (a_sha)
				output(o, 2, _("Removing %s"), path);
			/* do not touch working file if it did not exist */
			remove_file(o, 1, path, !a_sha);
