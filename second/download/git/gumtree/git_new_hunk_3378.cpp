
static const char * const verify_tag_usage[] = {
		N_("git verify-tag [-v | --verbose] <tag>..."),
		NULL
};

static int git_verify_tag_config(const char *var, const char *value, void *cb)
{
	int status = git_gpg_config(var, value, cb);
	if (status)
		return status;
	return git_default_config(var, value, cb);
