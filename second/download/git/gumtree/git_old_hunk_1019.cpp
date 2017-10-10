
	format_commit_message(commit, "%f", &subject, &ctx);
	fmt_output_subject(filename, subject.buf, info);
	strbuf_release(&subject);
}

void log_write_email_headers(struct rev_info *opt, struct commit *commit,
			     const char **subject_p,
			     const char **extra_headers_p,
			     int *need_8bit_cte_p)
{
	const char *subject = NULL;
	const char *extra_headers = opt->extra_headers;
	const char *name = oid_to_hex(opt->zero_commit ?
				      &null_oid : &commit->object.oid);

	*need_8bit_cte_p = 0; /* unknown */
	if (opt->total > 0) {
		static char buffer[64];
		snprintf(buffer, sizeof(buffer),
			 "Subject: [%s%s%0*d/%d] ",
			 opt->subject_prefix,
			 *opt->subject_prefix ? " " : "",
			 digits_in_number(opt->total),
			 opt->nr, opt->total);
		subject = buffer;
	} else if (opt->total == 0 && opt->subject_prefix && *opt->subject_prefix) {
		static char buffer[256];
		snprintf(buffer, sizeof(buffer),
			 "Subject: [%s] ",
			 opt->subject_prefix);
		subject = buffer;
	} else {
		subject = "Subject: ";
	}

	fprintf(opt->diffopt.file, "From %s Mon Sep 17 00:00:00 2001\n", name);
	graph_show_oneline(opt->graph);
	if (opt->message_id) {
		fprintf(opt->diffopt.file, "Message-Id: <%s>\n", opt->message_id);
		graph_show_oneline(opt->graph);
