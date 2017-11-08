static int remove_all_fetch_refspecs(const char *remote, const char *key)
{
	return git_config_set_multivar_gently(key, NULL, NULL, 1);
}