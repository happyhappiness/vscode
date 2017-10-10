	int ret = 0;

	/* this also ensures that we only parse submodule entries */
	if (!name_and_item_from_var(var, &name, &item))
		return 0;

	submodule = lookup_or_create_by_name(me->cache,
					     me->gitmodules_sha1,
					     name.buf);

	if (!strcmp(item.buf, "path")) {
		if (!value)
			ret = config_error_nonbool(var);
		else if (!me->overwrite && submodule->path != NULL)
			warn_multiple_config(me->commit_sha1, submodule->name,
					"path");
		else {
			if (submodule->path)
				cache_remove_path(me->cache, submodule);
			free((void *) submodule->path);
			submodule->path = xstrdup(value);
			cache_put_path(me->cache, submodule);
		}
	} else if (!strcmp(item.buf, "fetchrecursesubmodules")) {
		/* when parsing worktree configurations we can die early */
		int die_on_error = is_null_sha1(me->gitmodules_sha1);
		if (!me->overwrite &&
		    submodule->fetch_recurse != RECURSE_SUBMODULES_NONE)
			warn_multiple_config(me->commit_sha1, submodule->name,
					"fetchrecursesubmodules");
		else
			submodule->fetch_recurse = parse_fetch_recurse(
								var, value,
								die_on_error);
	} else if (!strcmp(item.buf, "ignore")) {
		if (!value)
			ret = config_error_nonbool(var);
		else if (!me->overwrite && submodule->ignore != NULL)
			warn_multiple_config(me->commit_sha1, submodule->name,
					"ignore");
		else if (strcmp(value, "untracked") &&
			 strcmp(value, "dirty") &&
			 strcmp(value, "all") &&
			 strcmp(value, "none"))
			warning("Invalid parameter '%s' for config option "
					"'submodule.%s.ignore'", value, var);
		else {
			free((void *) submodule->ignore);
			submodule->ignore = xstrdup(value);
		}
	} else if (!strcmp(item.buf, "url")) {
		if (!value) {
			ret = config_error_nonbool(var);
		} else if (!me->overwrite && submodule->url != NULL) {
			warn_multiple_config(me->commit_sha1, submodule->name,
					"url");
		} else {
			free((void *) submodule->url);
			submodule->url = xstrdup(value);
		}
	}

	strbuf_release(&name);
	strbuf_release(&item);

	return ret;
}

