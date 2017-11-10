static int process_diff_filepair(struct rev_info *rev,
				 struct diff_filepair *pair,
				 struct line_log_data *range,
				 struct diff_ranges **diff_out)
{
	struct line_log_data *rg = range;
	struct range_set tmp;
	struct diff_ranges diff;
	mmfile_t file_parent, file_target;

	assert(pair->two->path);
	while (rg) {
		assert(rg->path);
		if (!strcmp(rg->path, pair->two->path))
			break;
		rg = rg->next;
	}

	if (!rg)
		return 0;
	if (rg->ranges.nr == 0)
		return 0;

	assert(pair->two->sha1_valid);
	diff_populate_filespec(pair->two, 0);
	file_target.ptr = pair->two->data;
	file_target.size = pair->two->size;

	if (pair->one->sha1_valid) {
		diff_populate_filespec(pair->one, 0);
		file_parent.ptr = pair->one->data;
		file_parent.size = pair->one->size;
	} else {
		file_parent.ptr = "";
		file_parent.size = 0;
	}

	diff_ranges_init(&diff);
	collect_diff(&file_parent, &file_target, &diff);

	/* NEEDSWORK should apply some heuristics to prevent mismatches */
	free(rg->path);
	rg->path = xstrdup(pair->one->path);

	range_set_init(&tmp, 0);
	range_set_map_across_diff(&tmp, &rg->ranges, &diff, diff_out);
	range_set_release(&rg->ranges);
	range_set_move(&rg->ranges, &tmp);

	diff_ranges_release(&diff);

	return ((*diff_out)->parent.nr > 0);
}