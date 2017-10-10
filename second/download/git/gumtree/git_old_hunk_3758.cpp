	const char *c_new = diff_get_color(opt->use_color, DIFF_FILE_NEW);
	const char *c_context = diff_get_color(opt->use_color, DIFF_CONTEXT);

	if (!pair || !diff)
		return;

	if (pair->one->sha1_valid)
		fill_line_ends(pair->one, &p_lines, &p_ends);
	fill_line_ends(pair->two, &t_lines, &t_ends);

	printf("%s%sdiff --git a/%s b/%s%s\n", prefix, c_meta, pair->one->path, pair->two->path, c_reset);
	printf("%s%s--- %s%s%s\n", prefix, c_meta,
	       pair->one->sha1_valid ? "a/" : "",
	       pair->one->sha1_valid ? pair->one->path : "/dev/null",
	       c_reset);
	printf("%s%s+++ b/%s%s\n", prefix, c_meta, pair->two->path, c_reset);
	for (i = 0; i < range->ranges.nr; i++) {
		long p_start, p_end;
		long t_start = range->ranges.ranges[i].start;
		long t_end = range->ranges.ranges[i].end;
		long t_cur = t_start;
		int j_last;
