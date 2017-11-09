static int handle_file(struct merge_options *o,
			struct diff_filespec *rename,
			int stage,
			struct rename_conflict_info *ci)
{
	char *dst_name = rename->path;
	struct stage_data *dst_entry;
	const char *cur_branch, *other_branch;
	struct diff_filespec other;
	struct diff_filespec *add;
	int ret;

	if (stage == 2) {
		dst_entry = ci->dst_entry1;
		cur_branch = ci->branch1;
		other_branch = ci->branch2;
	} else {
		dst_entry = ci->dst_entry2;
		cur_branch = ci->branch2;
		other_branch = ci->branch1;
	}

	add = filespec_from_entry(&other, dst_entry, stage ^ 1);
	if (add) {
		char *add_name = unique_path(o, rename->path, other_branch);
		if (update_file(o, 0, &add->oid, add->mode, add_name))
			return -1;

		remove_file(o, 0, rename->path, 0);
		dst_name = unique_path(o, rename->path, cur_branch);
	} else {
		if (dir_in_way(rename->path, !o->call_depth, 0)) {
			dst_name = unique_path(o, rename->path, cur_branch);
			output(o, 1, _("%s is a directory in %s adding as %s instead"),
			       rename->path, other_branch, dst_name);
		}
	}
	if ((ret = update_file(o, 0, &rename->oid, rename->mode, dst_name)))
		; /* fall through, do allow dst_name to be released */
	else if (stage == 2)
		ret = update_stages(o, rename->path, NULL, rename, add);
	else
		ret = update_stages(o, rename->path, NULL, add, rename);

	if (dst_name != rename->path)
		free(dst_name);

	return ret;
}