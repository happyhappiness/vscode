static int matches(const char *key, const char *value)
{
	if (strcmp(key, store.key))
		return 0; /* not ours */
	if (!store.value_regex)
		return 1; /* always matches */
	if (store.value_regex == CONFIG_REGEX_NONE)
		return 0; /* never matches */

	return store.do_not_match ^
		(value && !regexec(store.value_regex, value, 0, NULL, 0));
}