			continue;

		if (S_ISGITLINK(patch->old_mode)) {
			if (!preimage_sha1_in_gitlink_patch(patch, sha1))
				; /* ok, the textual part looks sane */
			else
				die("sha1 information is lacking or useless for submoule %s",
				    name);
		} else if (!get_sha1_blob(patch->old_sha1_prefix, sha1)) {
			; /* ok */
		} else if (!patch->lines_added && !patch->lines_deleted) {
			/* mode-only change: update the current */
			if (get_current_sha1(patch->old_name, sha1))
