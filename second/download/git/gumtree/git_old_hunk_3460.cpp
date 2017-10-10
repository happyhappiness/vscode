			DIFF_OPT_SET(diffopt, IGNORE_SUBMODULES);
	}
}

int submodule_config(const char *var, const char *value, void *cb)
{
	if (starts_with(var, "submodule."))
		return parse_submodule_config_option(var, value);
	else if (!strcmp(var, "fetch.recursesubmodules")) {
		config_fetch_recurse_submodules = parse_fetch_recurse_submodules_arg(var, value);
		return 0;
	}
	return 0;
