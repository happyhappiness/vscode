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
