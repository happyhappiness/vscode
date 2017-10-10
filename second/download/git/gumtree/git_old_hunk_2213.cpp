			do_not_match = 1;
			regex_++;
		}

		regexp = (regex_t*)xmalloc(sizeof(regex_t));
		if (regcomp(regexp, regex_, REG_EXTENDED)) {
			fprintf(stderr, "Invalid pattern: %s\n", regex_);
			free(regexp);
			regexp = NULL;
			ret = CONFIG_INVALID_PATTERN;
			goto free_strings;
		}
	}
