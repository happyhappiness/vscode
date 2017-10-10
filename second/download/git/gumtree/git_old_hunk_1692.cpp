	av[++ac] = buf.buf;
	av[++ac] = NULL;
	setup_revisions(ac, av, &revs, NULL);
	revs.mailmap = &mailmap;
	read_mailmap(revs.mailmap, NULL);

	prepare_revision_walk(&revs);
	commit = get_revision(&revs);
	if (commit) {
		struct pretty_print_context ctx = {0};
		ctx.date_mode = DATE_NORMAL;
		strbuf_release(&buf);
		format_commit_message(commit, "%aN <%aE>", &buf, &ctx);
