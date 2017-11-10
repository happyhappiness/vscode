int do_diff_cache(const struct object_id *tree_oid, struct diff_options *opt)
{
	struct rev_info revs;

	init_revisions(&revs, NULL);
	copy_pathspec(&revs.prune_data, &opt->pathspec);
	revs.diffopt = *opt;

	if (diff_cache(&revs, tree_oid, NULL, 1))
		exit(128);
	return 0;
}