{
	git_config_get_bool("rerere.enabled", &rerere_enabled);
	git_config_get_bool("rerere.autoupdate", &rerere_autoupdate);
	git_config(git_default_config, NULL);
}

static GIT_PATH_FUNC(git_path_rr_cache, "rr-cache")

static int is_rerere_enabled(void)
{
	int rr_cache_exists;

	if (!rerere_enabled)
		return 0;

	rr_cache_exists = is_directory(git_path_rr_cache());
	if (rerere_enabled < 0)
		return rr_cache_exists;

	if (!rr_cache_exists && mkdir_in_gitdir(git_path_rr_cache()))
		die("Could not create directory %s", git_path_rr_cache());
	return 1;
}

int setup_rerere(struct string_list *merge_rr, int flags)
{
	int fd;
