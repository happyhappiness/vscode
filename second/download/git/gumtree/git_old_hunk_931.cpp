	if (!head_commit) {
		/*
		 * If the merged head is a valid one there is no reason
		 * to forbid "git merge" into a branch yet to be born.
		 * We do the same for "git pull".
		 */
		unsigned char *remote_head_sha1;
		if (squash)
			die(_("Squash commit into empty head not supported yet"));
		if (fast_forward == FF_NO)
			die(_("Non-fast-forward commit does not make sense into "
			    "an empty head"));
		remoteheads = collect_parents(head_commit, &head_subsumed,
					      argc, argv, NULL);
		if (!remoteheads)
			die(_("%s - not something we can merge"), argv[0]);
		if (remoteheads->next)
			die(_("Can merge only exactly one commit into empty head"));
		remote_head_sha1 = remoteheads->item->object.oid.hash;
		read_empty(remote_head_sha1, 0);
		update_ref("initial pull", "HEAD", remote_head_sha1,
			   NULL, 0, UPDATE_REFS_DIE_ON_ERR);
		goto done;
	}

	/*
	 * This could be traditional "merge <msg> HEAD <commit>..."  and
	 * the way we can tell it is to see if the second token is HEAD,
	 * but some people might have misused the interface and used a
	 * commit-ish that is the same as HEAD there instead.
	 * Traditional format never would have "-m" so it is an
	 * additional safety measure to check for it.
	 */
	if (!have_message &&
	    is_old_style_invocation(argc, argv, head_commit->object.oid.hash)) {
		warning("old-style 'git merge <msg> HEAD <commit>' is deprecated.");
		strbuf_addstr(&merge_msg, argv[0]);
		head_arg = argv[1];
		argv += 2;
		argc -= 2;
		remoteheads = collect_parents(head_commit, &head_subsumed,
					      argc, argv, NULL);
	} else {
		/* We are invoked directly as the first-class UI. */
		head_arg = "HEAD";

		/*
		 * All the rest are the commits being merged; prepare
		 * the standard merge summary message to be appended
		 * to the given message.
		 */
		remoteheads = collect_parents(head_commit, &head_subsumed,
					      argc, argv, &merge_msg);
	}

	if (!head_commit || !argc)
		usage_with_options(builtin_merge_usage,
			builtin_merge_options);

	if (verify_signatures) {
		for (p = remoteheads; p; p = p->next) {
			struct commit *commit = p->item;
			char hex[GIT_SHA1_HEXSZ + 1];
			struct signature_check signature_check;
			memset(&signature_check, 0, sizeof(signature_check));

			check_commit_signature(commit, &signature_check);

			find_unique_abbrev_r(hex, commit->object.oid.hash, DEFAULT_ABBREV);
