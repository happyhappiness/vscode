int git_config_from_parameters(config_fn_t fn, void *data)
{
	const char *env = getenv(CONFIG_DATA_ENVIRONMENT);
	int ret = 0;
	char *envw;
	const char **argv = NULL;
	int nr = 0, alloc = 0;
	int i;
	struct config_source source;

	if (!env)
		return 0;

	memset(&source, 0, sizeof(source));
	source.prev = cf;
	source.origin_type = CONFIG_ORIGIN_CMDLINE;
	cf = &source;

	/* sq_dequote will write over it */
	envw = xstrdup(env);

	if (sq_dequote_to_argv(envw, &argv, &nr, &alloc) < 0) {
		ret = error("bogus format in " CONFIG_DATA_ENVIRONMENT);
		goto out;
	}

	for (i = 0; i < nr; i++) {
		if (git_config_parse_parameter(argv[i], fn, data) < 0) {
			ret = -1;
			goto out;
		}
	}

out:
	free(argv);
	free(envw);
	cf = source.prev;
	return ret;
}