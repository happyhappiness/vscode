	if (userdiff_config(var, value) < 0)
		return -1;

	return git_default_config(var, value, cb);
}

static int blame_copy_callback(const struct option *option, const char *arg, int unset)
{
	int *opt = option->value;

	/*
	 * -C enables copy from removed files;
