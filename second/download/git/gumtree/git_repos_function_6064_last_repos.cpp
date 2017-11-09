static int difftool_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "diff.guitool")) {
		diff_gui_tool = xstrdup(value);
		return 0;
	}

	if (!strcmp(var, "difftool.trustexitcode")) {
		trust_exit_code = git_config_bool(var, value);
		return 0;
	}

	return git_default_config(var, value, cb);
}