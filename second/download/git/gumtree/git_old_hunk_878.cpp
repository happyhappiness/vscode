	get_commit_format(format.buf, &rev);
	rev.always_show_header = 0;
	rev.diffopt.detect_rename = 1;
	rev.diffopt.break_opt = 0;
	diff_setup_done(&rev.diffopt);

	head = resolve_ref_unsafe("HEAD", 0, junk_sha1, NULL);
	if (!strcmp(head, "HEAD"))
		head = _("detached HEAD");
	else
		skip_prefix(head, "refs/heads/", &head);
	printf("[%s%s ", head, initial_commit ? _(" (root-commit)") : "");

