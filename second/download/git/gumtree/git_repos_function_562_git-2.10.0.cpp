int git_env_bool(const char *k, int def)
{
	const char *v = getenv(k);
	return v ? git_config_bool(k, v) : def;
}