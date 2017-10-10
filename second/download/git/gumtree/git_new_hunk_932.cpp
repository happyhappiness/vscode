		 */
		refresh_cache(REFRESH_QUIET);
		if (allow_trivial && fast_forward != FF_ONLY) {
			/* See if it is really trivial. */
			git_committer_info(IDENT_STRICT);
			printf(_("Trying really trivial in-index merge...\n"));
			if (!read_tree_trivial(&common->item->object.oid,
					       &head_commit->object.oid,
					       &remoteheads->item->object.oid)) {
				ret = merge_trivial(head_commit, remoteheads);
				goto done;
			}
			printf(_("Nope.\n"));
		}
	} else {
