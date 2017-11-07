int git_config(config_fn_t fn, void *data)
{
	return git_config_with_options(fn, data, NULL, 1);
}