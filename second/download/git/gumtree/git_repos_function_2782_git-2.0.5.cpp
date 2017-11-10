static int pager_command_config(const char *var, const char *value, void *data)
{
	struct pager_config *c = data;
	if (starts_with(var, "pager.") && !strcmp(var + 6, c->cmd)) {
		int b = git_config_maybe_bool(var, value);
		if (b >= 0)
			c->want = b;
		else {
			c->want = 1;
			c->value = xstrdup(value);
		}
	}
	return 0;
}