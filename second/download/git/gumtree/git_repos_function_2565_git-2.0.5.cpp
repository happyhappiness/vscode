static int is_rerere_enabled(void)
{
	const char *rr_cache;
	int rr_cache_exists;

	if (!rerere_enabled)
		return 0;

	rr_cache = git_path("rr-cache");
	rr_cache_exists = is_directory(rr_cache);
	if (rerere_enabled < 0)
		return rr_cache_exists;

	if (!rr_cache_exists && mkdir_in_gitdir(rr_cache))
		die("Could not create directory %s", rr_cache);
	return 1;
}