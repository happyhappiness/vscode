int git_config_key_is_valid(const char *key)
{
	return !git_config_parse_key_1(key, NULL, NULL, 1);
}