static void show_list(const char *debug, int counted, int nr,
		      struct commit_list *list)
{
	struct commit_list *p;

	fprintf(stderr, "%s (%d/%d)\n", debug, counted, nr);

	for (p = list; p; p = p->next) {
		struct commit_list *pp;
		struct commit *commit = p->item;
		unsigned flags = commit->object.flags;
		enum object_type type;
		unsigned long size;
		char *buf = read_sha1_file(commit->object.sha1, &type, &size);
		const char *subject_start;
		int subject_len;

		fprintf(stderr, "%c%c%c ",
			(flags & TREESAME) ? ' ' : 'T',
			(flags & UNINTERESTING) ? 'U' : ' ',
			(flags & COUNTED) ? 'C' : ' ');
		if (commit->util)
			fprintf(stderr, "%3d", weight(p));
		else
			fprintf(stderr, "---");
		fprintf(stderr, " %.*s", 8, sha1_to_hex(commit->object.sha1));
		for (pp = commit->parents; pp; pp = pp->next)
			fprintf(stderr, " %.*s", 8,
				sha1_to_hex(pp->item->object.sha1));

		subject_len = find_commit_subject(buf, &subject_start);
		if (subject_len)
			fprintf(stderr, " %.*s", subject_len, subject_start);
		fprintf(stderr, "\n");
	}
}