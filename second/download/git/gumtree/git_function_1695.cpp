static int git_config_get_notes_strategy(const char *key,
					 enum notes_merge_strategy *strategy)
{
	const char *value;

	if (git_config_get_string_const(key, &value))
		return 1;
	if (parse_notes_merge_strategy(value, strategy))
		git_die_config(key, "unknown notes merge strategy %s", value);

	return 0;
}