
	format_commit_message(commit, "%f", &subject, &ctx);
	fmt_output_subject(filename, subject.buf, info);
	strbuf_release(&subject);
}

void fmt_output_email_subject(struct strbuf *sb, struct rev_info *opt)
{
	if (opt->total > 0) {
		strbuf_addf(sb, "Subject: [%s%s%0*d/%d] ",
			    opt->subject_prefix,
			    *opt->subject_prefix ? " " : "",
			    digits_in_number(opt->total),
			    opt->nr, opt->total);
	} else if (opt->total == 0 && opt->subject_prefix && *opt->subject_prefix) {
		strbuf_addf(sb, "Subject: [%s] ",
			    opt->subject_prefix);
	} else {
		strbuf_addstr(sb, "Subject: ");
	}
}

void log_write_email_headers(struct rev_info *opt, struct commit *commit,
			     const char **extra_headers_p,
			     int *need_8bit_cte_p)
{
	const char *extra_headers = opt->extra_headers;
	const char *name = oid_to_hex(opt->zero_commit ?
				      &null_oid : &commit->object.oid);

	*need_8bit_cte_p = 0; /* unknown */

	fprintf(opt->diffopt.file, "From %s Mon Sep 17 00:00:00 2001\n", name);
	graph_show_oneline(opt->graph);
	if (opt->message_id) {
		fprintf(opt->diffopt.file, "Message-Id: <%s>\n", opt->message_id);
		graph_show_oneline(opt->graph);
