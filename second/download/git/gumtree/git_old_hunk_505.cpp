		alias->ce_flags |= CE_ADDED;

		free(ce);
		return 0;
	}
	if (!intent_only) {
		if (index_path(ce->sha1, path, st, HASH_WRITE_OBJECT)) {
			free(ce);
			return error("unable to index file %s", path);
		}
	} else
		set_object_name_for_intent_to_add_entry(ce);

