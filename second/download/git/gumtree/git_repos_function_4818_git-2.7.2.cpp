static int git_am_config(const char *k, const char *v, void *cb)
{
	int status;

	status = git_gpg_config(k, v, NULL);
	if (status)
		return status;

	return git_default_config(k, v, NULL);
}