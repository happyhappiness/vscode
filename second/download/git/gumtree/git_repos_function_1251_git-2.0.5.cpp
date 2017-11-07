static int read_branch_desc_cb(const char *var, const char *value, void *cb)
{
	struct branch_desc_cb *desc = cb;
	if (strcmp(desc->config_name, var))
		return 0;
	free((char *)desc->value);
	return git_config_string(&desc->value, var, value);
}