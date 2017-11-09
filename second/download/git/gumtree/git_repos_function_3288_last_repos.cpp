static struct line_log_data *
parse_lines(struct commit *commit, const char *prefix, struct string_list *args)
{
	long lines = 0;
	unsigned long *ends = NULL;
	struct nth_line_cb cb_data;
	struct string_list_item *item;
	struct line_log_data *ranges = NULL;
	struct line_log_data *p;

	for_each_string_list_item(item, args) {
		const char *name_part, *range_part;
		char *full_name;
		struct diff_filespec *spec;
		long begin = 0, end = 0;
		long anchor;

		name_part = skip_range_arg(item->string);
		if (!name_part || *name_part != ':' || !name_part[1])
			die("-L argument not 'start,end:file' or ':funcname:file': %s",
			    item->string);
		range_part = xstrndup(item->string, name_part - item->string);
		name_part++;

		full_name = prefix_path(prefix, prefix ? strlen(prefix) : 0,
					name_part);

		spec = alloc_filespec(full_name);
		fill_blob_sha1(commit, spec);
		fill_line_ends(spec, &lines, &ends);
		cb_data.spec = spec;
		cb_data.lines = lines;
		cb_data.line_ends = ends;

		p = search_line_log_data(ranges, full_name, NULL);
		if (p && p->ranges.nr)
			anchor = p->ranges.ranges[p->ranges.nr - 1].end + 1;
		else
			anchor = 1;

		if (parse_range_arg(range_part, nth_line, &cb_data,
				    lines, anchor, &begin, &end,
				    full_name))
			die("malformed -L argument '%s'", range_part);
		if (lines < end || ((lines || begin) && lines < begin))
			die("file %s has only %lu lines", name_part, lines);
		if (begin < 1)
			begin = 1;
		if (end < 1)
			end = lines;
		begin--;
		line_log_data_insert(&ranges, full_name, begin, end);

		free_filespec(spec);
		FREE_AND_NULL(ends);
	}

	for (p = ranges; p; p = p->next)
		sort_and_merge_range_set(&p->ranges);

	return ranges;
}