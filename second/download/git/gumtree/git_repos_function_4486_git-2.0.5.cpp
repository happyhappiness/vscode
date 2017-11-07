static int git_log_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "format.pretty"))
		return git_config_string(&fmt_pretty, var, value);
	if (!strcmp(var, "format.subjectprefix"))
		return git_config_string(&fmt_patch_subject_prefix, var, value);
	if (!strcmp(var, "log.abbrevcommit")) {
		default_abbrev_commit = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "log.date"))
		return git_config_string(&default_date_mode, var, value);
	if (!strcmp(var, "log.decorate")) {
		decoration_style = parse_decoration_style(var, value);
		if (decoration_style < 0)
			decoration_style = 0; /* maybe warn? */
		return 0;
	}
	if (!strcmp(var, "log.showroot")) {
		default_show_root = git_config_bool(var, value);
		return 0;
	}
	if (starts_with(var, "color.decorate."))
		return parse_decorate_color_config(var, 15, value);
	if (!strcmp(var, "log.mailmap")) {
		use_mailmap_config = git_config_bool(var, value);
		return 0;
	}

	if (grep_config(var, value, cb) < 0)
		return -1;
	if (git_gpg_config(var, value, cb) < 0)
		return -1;
	return git_diff_ui_config(var, value, cb);
}