int fmt_merge_msg(struct strbuf *in, struct strbuf *out,
		  struct fmt_merge_msg_opts *opts)
{
	int i = 0, pos = 0;
	unsigned char head_sha1[20];
	const char *current_branch;
	void *current_branch_to_free;
	struct merge_parents merge_parents;

	memset(&merge_parents, 0, sizeof(merge_parents));

	/* get current branch */
	current_branch = current_branch_to_free =
		resolve_refdup("HEAD", RESOLVE_REF_READING, head_sha1, NULL);
	if (!current_branch)
		die("No current branch");
	if (starts_with(current_branch, "refs/heads/"))
		current_branch += 11;

	find_merge_parents(&merge_parents, in, head_sha1);

	/* get a line */
	while (pos < in->len) {
		int len;
		char *newline, *p = in->buf + pos;

		newline = strchr(p, '\n');
		len = newline ? newline - p : strlen(p);
		pos += len + !!newline;
		i++;
		p[len] = 0;
		if (handle_line(p, &merge_parents))
			die ("Error in line %d: %.*s", i, len, p);
	}

	if (opts->add_title && srcs.nr)
		fmt_merge_msg_title(out, current_branch);

	if (origins.nr)
		fmt_merge_msg_sigs(out);

	if (opts->shortlog_len) {
		struct commit *head;
		struct rev_info rev;

		head = lookup_commit_or_die(head_sha1, "HEAD");
		init_revisions(&rev, NULL);
		rev.commit_format = CMIT_FMT_ONELINE;
		rev.ignore_merges = 1;
		rev.limited = 1;

		strbuf_complete_line(out);

		for (i = 0; i < origins.nr; i++)
			shortlog(origins.items[i].string,
				 origins.items[i].util,
				 head, &rev, opts, out);
	}

	strbuf_complete_line(out);
	free(current_branch_to_free);
	free(merge_parents.item);
	return 0;
}