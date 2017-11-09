static void merge_recursive_config(struct merge_options *o)
{
	git_config_get_int("merge.verbosity", &o->verbosity);
	git_config_get_int("diff.renamelimit", &o->diff_rename_limit);
	git_config_get_int("merge.renamelimit", &o->merge_rename_limit);
	git_config(git_xmerge_config, NULL);
}