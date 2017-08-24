(iter = *global; iter != NULL; iter = iter->next) {
		r = add_option(a, &entry->options, iter->value,
		    strlen(iter->value));
		if (r != ARCHIVE_OK)
			return (r);
	}