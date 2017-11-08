const struct string_list *git_config_get_value_multi(const char *key)
{
	git_config_check_init();
	return git_configset_get_value_multi(&the_config_set, key);
}