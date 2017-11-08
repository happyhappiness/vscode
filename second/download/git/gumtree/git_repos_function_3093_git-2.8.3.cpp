void set_diffopt_flags_from_submodule_config(struct diff_options *diffopt,
					     const char *path)
{
	const struct submodule *submodule = submodule_from_path(null_sha1, path);
	if (submodule) {
		if (submodule->ignore)
			handle_ignore_submodules_arg(diffopt, submodule->ignore);
		else if (gitmodules_is_unmerged)
			DIFF_OPT_SET(diffopt, IGNORE_SUBMODULES);
	}
}