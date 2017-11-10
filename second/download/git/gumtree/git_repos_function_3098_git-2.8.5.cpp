static void print_submodule_summary(struct rev_info *rev, FILE *f,
		const char *line_prefix,
		const char *del, const char *add, const char *reset)
{
	static const char format[] = "  %m %s";
	struct strbuf sb = STRBUF_INIT;
	struct commit *commit;

	while ((commit = get_revision(rev))) {
		struct pretty_print_context ctx = {0};
		ctx.date_mode = rev->date_mode;
		ctx.output_encoding = get_log_output_encoding();
		strbuf_setlen(&sb, 0);
		strbuf_addstr(&sb, line_prefix);
		if (commit->object.flags & SYMMETRIC_LEFT) {
			if (del)
				strbuf_addstr(&sb, del);
		}
		else if (add)
			strbuf_addstr(&sb, add);
		format_commit_message(commit, format, &sb, &ctx);
		if (reset)
			strbuf_addstr(&sb, reset);
		strbuf_addch(&sb, '\n');
		fprintf(f, "%s", sb.buf);
	}
	strbuf_release(&sb);
}