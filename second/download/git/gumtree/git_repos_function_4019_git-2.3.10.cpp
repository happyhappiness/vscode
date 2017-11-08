static int git_push_config(const char *k, const char *v, void *cb)
{
	struct wt_status *s = cb;
	int status;

	status = git_gpg_config(k, v, NULL);
	if (status)
		return status;
	return git_default_config(k, v, s);
}