static int git_config_from_stdin(config_fn_t fn, void *data)
{
	return do_config_from_file(fn, CONFIG_ORIGIN_STDIN, "", NULL, stdin, data);
}