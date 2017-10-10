		 * them to the list following the refspecs resulting
		 * from the tags option so that one of the latter,
		 * which has FETCH_HEAD_NOT_FOR_MERGE, is not removed
		 * by ref_remove_duplicates() in favor of one of these
		 * opportunistic entries with FETCH_HEAD_IGNORE.
		 */
		for (i = 0; i < transport->remote->fetch_refspec_nr; i++)
			get_fetch_map(ref_map, &transport->remote->fetch[i],
				      &oref_tail, 1);

		if (tags == TAGS_SET)
			get_fetch_map(remote_refs, tag_refspec, &tail, 0);
	} else {
		/* Use the defaults */
		struct remote *remote = transport->remote;
		struct branch *branch = branch_get(NULL);
		int has_merge = branch_has_merge_config(branch);
		if (remote &&
