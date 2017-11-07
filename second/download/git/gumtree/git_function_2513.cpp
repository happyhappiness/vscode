static void make_cover_letter(struct rev_info *rev, int use_stdout,
			      struct commit *origin,
			      int nr, struct commit **list,
			      const char *branch_name,
			      int quiet)
{
	const char *committer;
	const char *body = "*** SUBJECT HERE ***\n\n*** BLURB HERE ***\n";
	const char *msg;
	struct shortlog log;
	struct strbuf sb = STRBUF_INIT;
	int i;
	const char *encoding = "UTF-8";
	struct diff_options opts;
	int need_8bit_cte = 0;
	struct pretty_print_context pp = {0};
	struct commit *head = list[0];

	if (rev->commit_format != CMIT_FMT_EMAIL)
		die(_("Cover letter needs email format"));

	committer = git_committer_info(0);

	if (!use_stdout &&
	    reopen_stdout(NULL, rev->numbered_files ? NULL : "cover-letter", rev, quiet))
		return;

	log_write_email_headers(rev, head, &pp.subject, &pp.after_subject,
				&need_8bit_cte);

	for (i = 0; !need_8bit_cte && i < nr; i++) {
		const char *buf = get_commit_buffer(list[i], NULL);
		if (has_non_ascii(buf))
			need_8bit_cte = 1;
		unuse_commit_buffer(list[i], buf);
	}

	if (!branch_name)
		branch_name = find_branch_name(rev);

	msg = body;
	pp.fmt = CMIT_FMT_EMAIL;
	pp.date_mode.type = DATE_RFC2822;
	pp_user_info(&pp, NULL, &sb, committer, encoding);
	pp_title_line(&pp, &msg, &sb, encoding, need_8bit_cte);
	pp_remainder(&pp, &msg, &sb, 0);
	add_branch_description(&sb, branch_name);
	printf("%s\n", sb.buf);

	strbuf_release(&sb);

	shortlog_init(&log);
	log.wrap_lines = 1;
	log.wrap = 72;
	log.in1 = 2;
	log.in2 = 4;
	for (i = 0; i < nr; i++)
		shortlog_add_commit(&log, list[i]);

	shortlog_output(&log);

	/*
	 * We can only do diffstat with a unique reference point
	 */
	if (!origin)
		return;

	memcpy(&opts, &rev->diffopt, sizeof(opts));
	opts.output_format = DIFF_FORMAT_SUMMARY | DIFF_FORMAT_DIFFSTAT;

	diff_setup_done(&opts);

	diff_tree_sha1(origin->tree->object.oid.hash,
		       head->tree->object.oid.hash,
		       "", &opts);
	diffcore_std(&opts);
	diff_flush(&opts);

	printf("\n");
	print_signature();
}