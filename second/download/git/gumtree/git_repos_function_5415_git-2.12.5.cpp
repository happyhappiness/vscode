static int git_log_config(const char *var, const char *value, void *cb)
{
	const char *slot_name;

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
	if (!strcmp(var, "log.follow")) {
		default_follow = git_config_bool(var, value);
		return 0;
	}
	if (skip_prefix(var, "color.decorate.", &slot_name))
		return parse_decorate_color_config(var, slot_name, value);
	if (!strcmp(var, "log.mailmap")) {
		use_mailmap_config = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "log.showsignature")) {
		default_show_signature = git_config_bool(var, value);
		return 0;
	}

	if (grep_config(var, value, cb) < 0)
		return -1;
	if (git_gpg_config(var, value, cb) < 0)
		return -1;
	return git_diff_ui_config(var, value, cb);
}