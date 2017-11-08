static int thread_callback(const struct option *opt, const char *arg, int unset)
{
	int *thread = (int *)opt->value;
	if (unset)
		*thread = 0;
	else if (!arg || !strcmp(arg, "shallow"))
		*thread = THREAD_SHALLOW;
	else if (!strcmp(arg, "deep"))
		*thread = THREAD_DEEP;
	else
		return 1;
	return 0;
}