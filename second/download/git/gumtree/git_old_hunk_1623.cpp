	return 0;
}

static int push_check(int argc, const char **argv, const char *prefix)
{
	struct remote *remote;

	if (argc < 2)
		die("submodule--helper push-check requires at least 1 argument");

	/*
	 * The remote must be configured.
	 * This is to avoid pushing to the exact same URL as the parent.
	 */
	remote = pushremote_get(argv[1]);
