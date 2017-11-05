static int git_config_parse_key_1(const char *key, char **store_key, int *baselen_, int quiet)
{
	int i, dot, baselen;
	const char *last_dot = strrchr(key, '.');

	/*
	 * Since "key" actually contains the section name and the real
	 * key name separated by a dot, we have to know where the dot is.
	 */

	if (last_dot == NULL || last_dot == key) {
		if (!quiet)
			error("key does not contain a section: %s", key);
		return -CONFIG_NO_SECTION_OR_NAME;
	}

	if (!last_dot[1]) {
		if (!quiet)
			error("key does not contain variable name: %s", key);
		return -CONFIG_NO_SECTION_OR_NAME;
	}

	baselen = last_dot - key;
	if (baselen_)
		*baselen_ = baselen;

	/*
	 * Validate the key and while at it, lower case it for matching.
	 */
	if (store_key)
		*store_key = xmallocz(strlen(key));

	dot = 0;
	for (i = 0; key[i]; i++) {
		unsigned char c = key[i];
		if (c == '.')
			dot = 1;
		/* Leave the extended basename untouched.. */
		if (!dot || i > baselen) {
			if (!iskeychar(c) ||
			    (i == baselen + 1 && !isalpha(c))) {
				if (!quiet)
					error("invalid key: %s", key);
				goto out_free_ret_1;
			}
			c = tolower(c);
		} else if (c == '\n') {
			if (!quiet)
				error("invalid key (newline): %s", key);
			goto out_free_ret_1;
		}
		if (store_key)
			(*store_key)[i] = c;
	}

	return 0;

out_free_ret_1:
	if (store_key) {
		free(*store_key);
		*store_key = NULL;
	}
	return -CONFIG_INVALID_KEY;
}