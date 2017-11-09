static int pager_command_config(const char *var, const char *value, void *vdata)
{
	struct pager_command_config_data *data = vdata;
	const char *cmd;

	if (skip_prefix(var, "pager.", &cmd) && !strcmp(cmd, data->cmd)) {
		int b = git_config_maybe_bool(var, value);
		if (b >= 0)
			data->want = b;
		else {
			data->want = 1;
			data->value = xstrdup(value);
		}
	}

	return 0;
}