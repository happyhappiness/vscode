		}
	}

	alias = index_file_exists(istate, ce->name, ce_namelen(ce), ignore_case);
	if (alias && !ce_stage(alias) && !ie_match_stat(istate, alias, st, ce_option)) {
		/* Nothing changed, really */
		free(ce);
		if (!S_ISGITLINK(alias->ce_mode))
			ce_mark_uptodate(alias);
		alias->ce_flags |= CE_ADDED;
		return 0;
	}
	if (!intent_only) {
		if (index_path(ce->sha1, path, st, HASH_WRITE_OBJECT))
			return error("unable to index file %s", path);
	} else
		set_object_name_for_intent_to_add_entry(ce);

	if (ignore_case && alias && different_name(ce, alias))
		ce = create_alias_ce(istate, ce, alias);
	ce->ce_flags |= CE_ADDED;
