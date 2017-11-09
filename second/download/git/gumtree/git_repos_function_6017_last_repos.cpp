static void show_commit(struct commit *commit, void *data)
{
	struct rev_list_info *info = data;
	struct rev_info *revs = info->revs;

	display_progress(progress, ++progress_counter);

	if (info->flags & REV_LIST_QUIET) {
		finish_commit(commit, data);
		return;
	}

	graph_show_commit(revs->graph);

	if (revs->count) {
		if (commit->object.flags & PATCHSAME)
			revs->count_same++;
		else if (commit->object.flags & SYMMETRIC_LEFT)
			revs->count_left++;
		else
			revs->count_right++;
		finish_commit(commit, data);
		return;
	}

	if (info->show_timestamp)
		printf("%"PRItime" ", commit->date);
	if (info->header_prefix)
		fputs(info->header_prefix, stdout);

	if (!revs->graph)
		fputs(get_revision_mark(revs, commit), stdout);
	if (revs->abbrev_commit && revs->abbrev)
		fputs(find_unique_abbrev(commit->object.oid.hash, revs->abbrev),
		      stdout);
	else
		fputs(oid_to_hex(&commit->object.oid), stdout);
	if (revs->print_parents) {
		struct commit_list *parents = commit->parents;
		while (parents) {
			printf(" %s", oid_to_hex(&parents->item->object.oid));
			parents = parents->next;
		}
	}
	if (revs->children.name) {
		struct commit_list *children;

		children = lookup_decoration(&revs->children, &commit->object);
		while (children) {
			printf(" %s", oid_to_hex(&children->item->object.oid));
			children = children->next;
		}
	}
	show_decorations(revs, commit);
	if (revs->commit_format == CMIT_FMT_ONELINE)
		putchar(' ');
	else
		putchar('\n');

	if (revs->verbose_header && get_cached_commit_buffer(commit, NULL)) {
		struct strbuf buf = STRBUF_INIT;
		struct pretty_print_context ctx = {0};
		ctx.abbrev = revs->abbrev;
		ctx.date_mode = revs->date_mode;
		ctx.date_mode_explicit = revs->date_mode_explicit;
		ctx.fmt = revs->commit_format;
		ctx.output_encoding = get_log_output_encoding();
		ctx.color = revs->diffopt.use_color;
		pretty_print_commit(&ctx, commit, &buf);
		if (buf.len) {
			if (revs->commit_format != CMIT_FMT_ONELINE)
				graph_show_oneline(revs->graph);

			graph_show_commit_msg(revs->graph, stdout, &buf);

			/*
			 * Add a newline after the commit message.
			 *
			 * Usually, this newline produces a blank
			 * padding line between entries, in which case
			 * we need to add graph padding on this line.
			 *
			 * However, the commit message may not end in a
			 * newline.  In this case the newline simply
			 * ends the last line of the commit message,
			 * and we don't need any graph output.  (This
			 * always happens with CMIT_FMT_ONELINE, and it
			 * happens with CMIT_FMT_USERFORMAT when the
			 * format doesn't explicitly end in a newline.)
			 */
			if (buf.len && buf.buf[buf.len - 1] == '\n')
				graph_show_padding(revs->graph);
			putchar(info->hdr_termination);
		} else {
			/*
			 * If the message buffer is empty, just show
			 * the rest of the graph output for this
			 * commit.
			 */
			if (graph_show_remainder(revs->graph))
				putchar('\n');
			if (revs->commit_format == CMIT_FMT_ONELINE)
				putchar('\n');
		}
		strbuf_release(&buf);
	} else {
		if (graph_show_remainder(revs->graph))
			putchar('\n');
	}
	maybe_flush_or_die(stdout, "stdout");
	finish_commit(commit, data);
}