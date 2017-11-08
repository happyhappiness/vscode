void shortlog_add_commit(struct shortlog *log, struct commit *commit)
{
	const char *author = NULL, *buffer;
	struct strbuf buf = STRBUF_INIT;
	struct strbuf ufbuf = STRBUF_INIT;

	pp_commit_easy(CMIT_FMT_RAW, commit, &buf);
	buffer = buf.buf;
	while (*buffer && *buffer != '\n') {
		const char *eol = strchr(buffer, '\n');

		if (eol == NULL)
			eol = buffer + strlen(buffer);
		else
			eol++;

		if (starts_with(buffer, "author "))
			author = buffer + 7;
		buffer = eol;
	}
	if (!author) {
		warning(_("Missing author: %s"),
		    oid_to_hex(&commit->object.oid));
		return;
	}
	if (log->user_format) {
		struct pretty_print_context ctx = {0};
		ctx.fmt = CMIT_FMT_USERFORMAT;
		ctx.abbrev = log->abbrev;
		ctx.subject = "";
		ctx.after_subject = "";
		ctx.date_mode.type = DATE_NORMAL;
		ctx.output_encoding = get_log_output_encoding();
		pretty_print_commit(&ctx, commit, &ufbuf);
		buffer = ufbuf.buf;
	} else if (*buffer) {
		buffer++;
	}
	insert_one_record(log, author, !*buffer ? "<none>" : buffer);
	strbuf_release(&ufbuf);
	strbuf_release(&buf);
}