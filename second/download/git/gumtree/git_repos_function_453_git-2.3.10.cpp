int git_config_from_file(config_fn_t fn, const char *filename, void *data)
{
	int ret = -1;
	FILE *f;

	f = fopen(filename, "r");
	if (f) {
		ret = do_config_from_file(fn, filename, filename, f, data);
		fclose(f);
	}
	return ret;
}