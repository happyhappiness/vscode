const struct string_list *git_config_get_value_multi(const char *key)
{
	return repo_config_get_value_multi(the_repository, key);
}