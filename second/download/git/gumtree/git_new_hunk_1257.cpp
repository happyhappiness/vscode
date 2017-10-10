		for (tl = key; *tl && *tl != '.'; tl++)
			*tl = tolower(*tl);

		key_regexp = (regex_t*)xmalloc(sizeof(regex_t));
		if (regcomp(key_regexp, key, REG_EXTENDED)) {
			error("invalid key pattern: %s", key_);
			FREE_AND_NULL(key_regexp);
			ret = CONFIG_INVALID_PATTERN;
			goto free_strings;
		}
	} else {
		if (git_config_parse_key(key_, &key, NULL)) {
			ret = CONFIG_INVALID_KEY;
