
	/*
	 * Print header line of header..
	 */

	if (cmit_fmt_is_mail(opt->commit_format)) {
		log_write_email_headers(opt, commit, &ctx.subject, &extra_headers,
					&ctx.need_8bit_cte);
	} else if (opt->commit_format != CMIT_FMT_USERFORMAT) {
		fputs(diff_get_color_opt(&opt->diffopt, DIFF_COMMIT), opt->diffopt.file);
		if (opt->commit_format != CMIT_FMT_ONELINE)
			fputs("commit ", opt->diffopt.file);

		if (!opt->graph)
