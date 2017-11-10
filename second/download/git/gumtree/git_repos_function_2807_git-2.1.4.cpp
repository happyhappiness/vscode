static int merge_recursive_config(const char *var, const char *value, void *cb)
{
	struct merge_options *o = cb;
	if (!strcmp(var, "merge.verbosity")) {
		o->verbosity = git_config_int(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.renamelimit")) {
		o->diff_rename_limit = git_config_int(var, value);
		return 0;
	}
	if (!strcmp(var, "merge.renamelimit")) {
		o->merge_rename_limit = git_config_int(var, value);
		return 0;
	}
	return git_xmerge_config(var, value, cb);
}