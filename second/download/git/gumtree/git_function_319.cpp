static void show_raw_diff(struct combine_diff_path *p, int num_parent, struct rev_info *rev)
{
	struct diff_options *opt = &rev->diffopt;
	int line_termination, inter_name_termination, i;
	const char *line_prefix = diff_line_prefix(opt);

	line_termination = opt->line_termination;
	inter_name_termination = '\t';
	if (!line_termination)
		inter_name_termination = 0;

	if (rev->loginfo && !rev->no_commit_id)
		show_log(rev);


	if (opt->output_format & DIFF_FORMAT_RAW) {
		printf("%s", line_prefix);

		/* As many colons as there are parents */
		for (i = 0; i < num_parent; i++)
			putchar(':');

		/* Show the modes */
		for (i = 0; i < num_parent; i++)
			printf("%06o ", p->parent[i].mode);
		printf("%06o", p->mode);

		/* Show sha1's */
		for (i = 0; i < num_parent; i++)
			printf(" %s", diff_unique_abbrev(p->parent[i].oid.hash,
							 opt->abbrev));
		printf(" %s ", diff_unique_abbrev(p->oid.hash, opt->abbrev));
	}

	if (opt->output_format & (DIFF_FORMAT_RAW | DIFF_FORMAT_NAME_STATUS)) {
		for (i = 0; i < num_parent; i++)
			putchar(p->parent[i].status);
		putchar(inter_name_termination);
	}

	write_name_quoted(p->path, stdout, line_termination);
}