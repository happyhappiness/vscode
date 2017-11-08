void shortlog_add_commit(struct shortlog *log, struct commit *commit)
{
	struct strbuf author = STRBUF_INIT;
	struct strbuf oneline = STRBUF_INIT;
	struct pretty_print_context ctx = {0};
	const char *fmt;

	ctx.fmt = CMIT_FMT_USERFORMAT;
	ctx.abbrev = log->abbrev;
	ctx.print_email_subject = 1;
	ctx.date_mode.type = DATE_NORMAL;
	ctx.output_encoding = get_log_output_encoding();

	fmt = log->committer ? "%cn <%ce>" : "%an <%ae>";

	format_commit_message(commit, fmt, &author, &ctx);
	if (!log->summary) {
		if (log->user_format)
			pretty_print_commit(&ctx, commit, &oneline);
		else
			format_commit_message(commit, "%s", &oneline, &ctx);
	}

	insert_one_record(log, author.buf, oneline.len ? oneline.buf : "<none>");

	strbuf_release(&author);
	strbuf_release(&oneline);
}