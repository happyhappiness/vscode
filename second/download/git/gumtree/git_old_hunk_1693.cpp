	get_commit_format(format.buf, &rev);
	rev.always_show_header = 0;
	rev.diffopt.detect_rename = 1;
	rev.diffopt.break_opt = 0;
	diff_setup_done(&rev.diffopt);

	head = resolve_ref_unsafe("HEAD", junk_sha1, 0, NULL);
	printf("[%s%s ",
		starts_with(head, "refs/heads/") ?
			head + 11 :
			!strcmp(head, "HEAD") ?
				_("detached HEAD") :
				head,
		initial_commit ? _(" (root-commit)") : "");

	if (!log_tree_commit(&rev, commit)) {
		rev.always_show_header = 1;
		rev.use_terminator = 1;
		log_tree_commit(&rev, commit);
	}
