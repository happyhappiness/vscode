void git_config_set(const char *key, const char *value)
{
	git_config_set_multivar(key, value, NULL, 0);
}

/*
 * If value==NULL, unset in (remove from) config,
 * if value_regex!=NULL, disregard key/value pairs where value does not match.
 * if value_regex==CONFIG_REGEX_NONE, do not match any existing values
 *     (only add a new one)
 * if multi_replace==0, nothing, or only one matching key/value is replaced,
 *     else all matching key/values (regardless how many) are removed,
