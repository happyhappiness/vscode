		 * As a side effect, we make sure to transform only a valid
		 * existing config file.
		 */
		if (git_config_from_file(store_aux, config_filename, NULL)) {
			error("invalid config file %s", config_filename);
			free(store.key);
			if (store.value_regex != NULL &&
			    store.value_regex != CONFIG_REGEX_NONE) {
				regfree(store.value_regex);
				free(store.value_regex);
			}
			ret = CONFIG_INVALID_FILE;
			goto out_free;
		}

		free(store.key);
		if (store.value_regex != NULL &&
		    store.value_regex != CONFIG_REGEX_NONE) {
			regfree(store.value_regex);
			free(store.value_regex);
		}

		/* if nothing to unset, or too many matches, error out */
		if ((store.seen == 0 && value == NULL) ||
