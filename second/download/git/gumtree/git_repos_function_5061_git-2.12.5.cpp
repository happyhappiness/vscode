static int git_patch_id_config(const char *var, const char *value, void *cb)
{
	int *stable = cb;

	if (!strcmp(var, "patchid.stable")) {
		*stable = git_config_bool(var, value);
		return 0;
	}

	return git_default_config(var, value, cb);
}