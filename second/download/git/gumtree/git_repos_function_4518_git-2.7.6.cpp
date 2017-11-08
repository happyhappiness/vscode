static int git_commit_config(const char *k, const char *v, void *cb)
{
	struct wt_status *s = cb;
	int status;

	if (!strcmp(k, "commit.template"))
		return git_config_pathname(&template_file, k, v);
	if (!strcmp(k, "commit.status")) {
		include_status = git_config_bool(k, v);
		return 0;
	}
	if (!strcmp(k, "commit.cleanup"))
		return git_config_string(&cleanup_arg, k, v);
	if (!strcmp(k, "commit.gpgsign")) {
		sign_commit = git_config_bool(k, v) ? "" : NULL;
		return 0;
	}

	status = git_gpg_config(k, v, NULL);
	if (status)
		return status;
	return git_status_config(k, v, s);
}