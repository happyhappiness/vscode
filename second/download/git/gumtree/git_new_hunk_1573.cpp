			handle_ignore_submodules_arg(diffopt, submodule->ignore);
		else if (gitmodules_is_unmerged)
			DIFF_OPT_SET(diffopt, IGNORE_SUBMODULES);
	}
}

/* For loading from the .gitmodules file. */
static int git_modules_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "submodule.fetchjobs")) {
		parallel_jobs = git_config_int(var, value);
		if (parallel_jobs < 0)
			die(_("negative values not allowed for submodule.fetchJobs"));
		return 0;
