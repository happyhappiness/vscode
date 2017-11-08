static int git_config_from_stdin(config_fn_t fn, void *data)
{
	return do_config_from_file(fn, "<stdin>", NULL, stdin, data);
}