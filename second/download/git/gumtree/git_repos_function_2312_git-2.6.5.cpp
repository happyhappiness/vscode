void show_log(struct rev_info *opt)
{
	struct strbuf msgbuf = STRBUF_INIT;
	struct log_info *log = opt->loginfo;
	struct commit *commit = log->commit, *parent = log->parent;
	int abbrev_commit = opt->abbrev_commit ? opt->abbrev : 40;
	const char *extra_headers = opt->extra_headers;
	struct pretty_print_context ctx = {0};

	opt->loginfo = NULL;
	if (!opt->verbose_header) {
		graph_show_commit(opt->graph);

		if (!opt->graph)
			put_revision_mark(opt, commit);
		fputs(find_unique_abbrev(commit->object.sha1, abbrev_commit), stdout);
		if (opt->print_parents)
			show_parents(commit, abbrev_commit);
		if (opt->children.name)
			show_children(opt, commit, abbrev_commit);
		show_decorations(opt, commit);
		if (opt->graph && !graph_is_commit_finished(opt->graph)) {
			putchar('\n');
			graph_show_remainder(opt->graph);
		}
		putchar(opt->diffopt.line_termination);
		return;
	}

	/*
	 * If use_terminator is set, we already handled any record termination
	 * at the end of the last record.
	 * Otherwise, add a diffopt.line_termination character before all
	 * entries but the first.  (IOW, as a separator between entries)
	 */
	if (opt->shown_one && !opt->use_terminator) {
		/*
		 * If entries are separated by a newline, the output
		 * should look human-readable.  If the last entry ended
		 * with a newline, print the graph output before this
		 * newline.  Otherwise it will end up as a completely blank
		 * line and will look like a gap in the graph.
		 *
		 * If the entry separator is not a newline, the output is
		 * primarily intended for programmatic consumption, and we
		 * never want the extra graph output before the entry
		 * separator.
		 */
		if (opt->diffopt.line_termination == '\n' &&
		    !opt->missing_newline)
			graph_show_padding(opt->graph);
		putchar(opt->diffopt.line_termination);
	}
	opt->shown_one = 1;

	/*
	 * If the history graph was requested,
	 * print the graph, up to this commit's line
	 */
	graph_show_commit(opt->graph);

	/*
	 * Print header line of header..
	 */

	if (opt->commit_format == CMIT_FMT_EMAIL) {
		log_write_email_headers(opt, commit, &ctx.subject, &extra_headers,
					&ctx.need_8bit_cte);
	} else if (opt->commit_format != CMIT_FMT_USERFORMAT) {
		fputs(diff_get_color_opt(&opt->diffopt, DIFF_COMMIT), stdout);
		if (opt->commit_format != CMIT_FMT_ONELINE)
			fputs("commit ", stdout);

		if (!opt->graph)
			put_revision_mark(opt, commit);
		fputs(find_unique_abbrev(commit->object.sha1, abbrev_commit),
		      stdout);
		if (opt->print_parents)
			show_parents(commit, abbrev_commit);
		if (opt->children.name)
			show_children(opt, commit, abbrev_commit);
		if (parent)
			printf(" (from %s)",
			       find_unique_abbrev(parent->object.sha1,
						  abbrev_commit));
		fputs(diff_get_color_opt(&opt->diffopt, DIFF_RESET), stdout);
		show_decorations(opt, commit);
		if (opt->commit_format == CMIT_FMT_ONELINE) {
			putchar(' ');
		} else {
			putchar('\n');
			graph_show_oneline(opt->graph);
		}
		if (opt->reflog_info) {
			/*
			 * setup_revisions() ensures that opt->reflog_info
			 * and opt->graph cannot both be set,
			 * so we don't need to worry about printing the
			 * graph info here.
			 */
			show_reflog_message(opt->reflog_info,
					    opt->commit_format == CMIT_FMT_ONELINE,
					    &opt->date_mode,
					    opt->date_mode_explicit);
			if (opt->commit_format == CMIT_FMT_ONELINE)
				return;
		}
	}

	if (opt->show_signature) {
		show_signature(opt, commit);
		show_mergetag(opt, commit);
	}

	if (!get_cached_commit_buffer(commit, NULL))
		return;

	if (opt->show_notes) {
		int raw;
		struct strbuf notebuf = STRBUF_INIT;

		raw = (opt->commit_format == CMIT_FMT_USERFORMAT);
		format_display_notes(commit->object.sha1, &notebuf,
				     get_log_output_encoding(), raw);
		ctx.notes_message = notebuf.len
			? strbuf_detach(&notebuf, NULL)
			: xcalloc(1, 1);
	}

	/*
	 * And then the pretty-printed message itself
	 */
	if (ctx.need_8bit_cte >= 0 && opt->add_signoff)
		ctx.need_8bit_cte =
			has_non_ascii(fmt_name(getenv("GIT_COMMITTER_NAME"),
					       getenv("GIT_COMMITTER_EMAIL")));
	ct