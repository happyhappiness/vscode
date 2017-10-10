		die("option %s needs an argument (check|on-demand)",
				opt->long_name);

	return 0;
}

int cmd_push(int argc, const char **argv, const char *prefix)
{
	int flags = 0;
	int tags = 0;
	int rc;
	const char *repo = NULL;	/* default repository */
