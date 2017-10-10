			DIFF_OPT_SET(diffopt, IGNORE_SUBMODULES);
	}
}

int submodule_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "submodule.fetchjobs")) {
		parallel_jobs = git_config_int(var, value);
		if (parallel_jobs < 0)
			die(_("negative values not allowed for submodule.fetchJobs"));
		return 0;
	} else if (starts_with(var, "submodule."))
		return parse_submodule_config_option(var, value);
	else if (!strcmp(var, "fetch.recursesubmodules")) {
		config_fetch_recurse_submodules = parse_fetch_recurse_submodules_arg(var, value);
		return 0;
	}
	return 0;
