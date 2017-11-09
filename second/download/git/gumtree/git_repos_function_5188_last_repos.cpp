static int git_checkout_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "diff.ignoresubmodules")) {
		struct checkout_opts *opts = cb;
		handle_ignore_submodules_arg(&opts->diff_options, value);
		return 0;
	}

	if (starts_with(var, "submodule."))
		return submodule_config(var, value, NULL);

	return git_xmerge_config(var, value, NULL);
}