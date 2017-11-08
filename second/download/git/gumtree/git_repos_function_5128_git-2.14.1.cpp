static int get_value(const char *key_, const char *regex_)
{
	int ret = CONFIG_GENERIC_ERROR;
	struct strbuf_list values = {NULL};
	int i;

	if (use_key_regexp) {
		char *tl;

		/*
		 * NEEDSWORK: this naive pattern lowercasing obviously does not
		 * work for more complex patterns like "^[^.]*Foo.*bar".
		 * Perhaps we should deprecate this altogether someday.
		 */

		key = xstrdup(key_);
		for (tl = key + strlen(key) - 1;
		     tl >= key && *tl != '.';
		     tl--)
			*tl = tolower(*tl);
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
			goto free_strings;
		}
	}

	if (regex_) {
		if (regex_[0] == '!') {
			do_not_match = 1;
			regex_++;
		}

		regexp = (regex_t*)xmalloc(sizeof(regex_t));
		if (regcomp(regexp, regex_, REG_EXTENDED)) {
			error("invalid pattern: %s", regex_);
			FREE_AND_NULL(regexp);
			ret = CONFIG_INVALID_PATTERN;
			goto free_strings;
		}
	}

	config_with_options(collect_config, &values,
			    &given_config_source, &config_options);

	ret = !values.nr;

	for (i = 0; i < values.nr; i++) {
		struct strbuf *buf = values.items + i;
		if (do_all || i == values.nr - 1)
			fwrite(buf->buf, 1, buf->len, stdout);
		strbuf_release(buf);
	}
	free(values.items);

free_strings:
	free(key);
	if (key_regexp) {
		regfree(key_regexp);
		free(key_regexp);
	}
	if (regexp) {
		regfree(regexp);
		free(regexp);
	}

	return ret;
}