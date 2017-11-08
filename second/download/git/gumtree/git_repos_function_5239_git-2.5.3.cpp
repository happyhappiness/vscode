static int commit_tree_config(const char *var, const char *value, void *cb)
{
	int status = git_gpg_config(var, value, NULL);
	if (status)
		return status;
	if (!strcmp(var, "commit.gpgsign")) {
		sign_commit = git_config_bool(var, value) ? "" : NULL;
		return 0;
	}
	return git_default_config(var, value, cb);
}