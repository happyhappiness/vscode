static int read_from_tree(const struct pathspec *pathspec,
			  struct object_id *tree_oid,
			  int intent_to_add)
{
	struct diff_options opt;

	memset(&opt, 0, sizeof(opt));
	copy_pathspec(&opt.pathspec, pathspec);
	opt.output_format = DIFF_FORMAT_CALLBACK;
	opt.format_callback = update_index_from_diff;
	opt.format_callback_data = &intent_to_add;

	if (do_diff_cache(tree_oid, &opt))
		return 1;
	diffcore_std(&opt);
	diff_flush(&opt);
	clear_pathspec(&opt.pathspec);

	return 0;
}