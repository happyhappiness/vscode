int git_configset_add_file(struct config_set *cs, const char *filename)
{
	return git_config_from_file(config_set_callback, filename, cs);
}