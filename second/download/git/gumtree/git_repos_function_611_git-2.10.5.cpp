int git_config_parse_key(const char *key, char **store_key, int *baselen)
{
	return git_config_parse_key_1(key, store_key, baselen, 0);
}