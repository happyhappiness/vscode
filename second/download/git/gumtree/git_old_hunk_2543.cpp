		die("option %s needs an argument (check|on-demand)",
				opt->long_name);

	return 0;
}

static int git_push_config(const char *k, const char *v, void *cb)
{
	int *flags = cb;
	int status;

	status = git_gpg_config(k, v, NULL);
