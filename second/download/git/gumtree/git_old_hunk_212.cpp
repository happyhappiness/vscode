		if (index_path(ce->sha1, path, st, HASH_WRITE_OBJECT))
			return error("unable to index file %s", path);
	} else
		set_object_name_for_intent_to_add_entry(ce);

	if (ignore_case && alias && different_name(ce, alias))
		ce = create_alias_ce(ce, alias);
	ce->ce_flags |= CE_ADDED;

	/* It was suspected to be racily clean, but it turns out to be Ok */
	was_same = (alias &&
		    !ce_stage(alias) &&
		    !hashcmp(alias->sha1, ce->sha1) &&
