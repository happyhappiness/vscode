const struct string_list *git_configset_get_value_multi(struct config_set *cs, const char *key)
{
	struct config_set_element *e = configset_find_element(cs, key);
	return e ? &e->value_list : NULL;
}