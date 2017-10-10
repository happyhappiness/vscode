	 * but some people might have misused the interface and used a
	 * commit-ish that is the same as HEAD there instead.
	 * Traditional format never would have "-m" so it is an
	 * additional safety measure to check for it.
	 */
	if (!have_message &&
	    is_old_style_invocation(argc, argv, head_commit->object.sha1)) {
		warning("old-style 'git merge <msg> HEAD <commit>' is deprecated.");
		strbuf_addstr(&merge_msg, argv[0]);
		head_arg = argv[1];
		argv += 2;
		argc -= 2;
		remoteheads = collect_parents(head_commit, &head_subsumed,
