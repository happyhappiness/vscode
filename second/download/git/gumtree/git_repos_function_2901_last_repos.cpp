int log_tree_diff_flush(struct rev_info *opt)
{
	opt->shown_dashes = 0;
	diffcore_std(&opt->diffopt);

	if (diff_queue_is_empty()) {
		int saved_fmt = opt->diffopt.output_format;
		opt->diffopt.output_format = DIFF_FORMAT_NO_OUTPUT;
		diff_flush(&opt->diffopt);
		opt->diffopt.output_format = saved_fmt;
		return 0;
	}

	if (opt->loginfo && !opt->no_commit_id) {
		show_log(opt);
		if ((opt->diffopt.output_format & ~DIFF_FORMAT_NO_OUTPUT) &&
		    opt->verbose_header &&
		    opt->commit_format != CMIT_FMT_ONELINE &&
		    !commit_format_is_empty(opt->commit_format)) {
			/*
			 * When showing a verbose header (i.e. log message),
			 * and not in --pretty=oneline format, we would want
			 * an extra newline between the end of log and the
			 * diff/diffstat output for readability.
			 */
			int pch = DIFF_FORMAT_DIFFSTAT | DIFF_FORMAT_PATCH;
			if (opt->diffopt.output_prefix) {
				struct strbuf *msg = NULL;
				msg = opt->diffopt.output_prefix(&opt->diffopt,
					opt->diffopt.output_prefix_data);
				fwrite(msg->buf, msg->len, 1, opt->diffopt.file);
			}

			/*
			 * We may have shown three-dashes line early
			 * between notes and the log message, in which
			 * case we only want a blank line after the
			 * notes without (an extra) three-dashes line.
			 * Otherwise, we show the three-dashes line if
			 * we are showing the patch with diffstat, but
			 * in that case, there is no extra blank line
			 * after the three-dashes line.
			 */
			if (!opt->shown_dashes &&
			    (pch & opt->diffopt.output_format) == pch)
				fprintf(opt->diffopt.file, "---");
			putc('\n', opt->diffopt.file);
		}
	}
	diff_flush(&opt->diffopt);
	return 1;
}