int git_config_from_file(config_fn_t fn, const char *filename, void *data)
{
	int ret = -1;
	FILE *f;

	f = fopen_or_warn(filename, "r");
	if (f) {
		flockfile(f);
		ret = do_config_from_file(fn, CONFIG_ORIGIN_FILE, filename, filename, f, data);
		funlockfile(f);
		fclose(f);
	}
	return ret;
}