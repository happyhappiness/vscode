static int write_one_config(const char *key, const char *value, void *data)
{
	return git_config_set_multivar(key, value ? value : "true", "^$", 0);
}