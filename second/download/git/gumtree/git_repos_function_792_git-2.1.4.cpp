char *alias_lookup(const char *alias)
{
	alias_key = alias;
	alias_val = NULL;
	git_config(alias_lookup_cb, NULL);
	return alias_val;
}