	show_log_first = !!rev->loginfo && !rev->no_commit_id;
	needsep = 0;
	if (show_log_first) {
		show_log(rev);

		if (rev->verbose_header && opt->output_format &&
		    opt->output_format != DIFF_FORMAT_NO_OUTPUT &&
		    !commit_format_is_empty(rev->commit_format))
			printf("%s%c", diff_line_prefix(opt),
			       opt->line_termination);
	}

	diffopts = *opt;
	copy_pathspec(&diffopts.pathspec, &opt->pathspec);
