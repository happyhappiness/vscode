	if (!force) {
		head_rev = lookup_commit_reference(head_sha1);
		if (!head_rev)
			die(_("Couldn't look up commit object for HEAD"));
	}
	for (i = 0; i < argc; i++, strbuf_release(&bname)) {
		const char *target;
		int flags = 0;

		strbuf_branchname(&bname, argv[i]);
		free(name);
		name = mkpathdup(fmt, bname.buf);

