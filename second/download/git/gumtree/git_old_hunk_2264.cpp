		show_log(rev);

	dump_quoted_path(dense ? "diff --cc " : "diff --combined ",
			 "", elem->path, line_prefix, c_meta, c_reset);
	printf("%s%sindex ", line_prefix, c_meta);
	for (i = 0; i < num_parent; i++) {
		abb = find_unique_abbrev(elem->parent[i].sha1,
					 abbrev);
		printf("%s%s", i ? "," : "", abb);
	}
	abb = find_unique_abbrev(elem->sha1, abbrev);
	printf("..%s%s\n", abb, c_reset);

	if (mode_differs) {
		deleted = !elem->mode;

		/* We say it was added if nobody had it */
