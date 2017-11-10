static int is_submodule_ignored(const char *path, struct diff_options *options)
{
	int ignored = 0;
	unsigned orig_flags = options->flags;
	if (!DIFF_OPT_TST(options, OVERRIDE_SUBMODULE_CONFIG))
		set_diffopt_flags_from_submodule_config(options, path);
	if (DIFF_OPT_TST(options, IGNORE_SUBMODULES))
		ignored = 1;
	options->flags = orig_flags;
	return ignored;
}