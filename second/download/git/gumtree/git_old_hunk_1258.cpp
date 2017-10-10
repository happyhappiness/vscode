			regex_++;
		}

		regexp = (regex_t*)xmalloc(sizeof(regex_t));
		if (regcomp(regexp, regex_, REG_EXTENDED)) {
			error("invalid pattern: %s", regex_);
			free(regexp);
			regexp = NULL;
			ret = CONFIG_INVALID_PATTERN;
			goto free_strings;
		}
	}

	git_config_with_options(collect_config, &values,
				&given_config_source, &config_options);

	ret = !values.nr;

	for (i = 0; i < values.nr; i++) {
		struct strbuf *buf = values.items + i;
		if (do_all || i == values.nr - 1)
