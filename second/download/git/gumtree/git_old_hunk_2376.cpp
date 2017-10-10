		struct stat st;
		const char *rel;

		if (!cache_name_is_other(ent->name, ent->len))
			continue;

		if (lstat(ent->name, &st))
			die_errno("Cannot lstat '%s'", ent->name);

		if (pathspec.nr)
			matches = dir_path_match(ent, &pathspec, 0, NULL);

		if (pathspec.nr && !matches)
			continue;

		if (S_ISDIR(st.st_mode) && !remove_directories &&
		    matches != MATCHED_EXACTLY)
			continue;

		rel = relative_path(ent->name, prefix, &buf);
		string_list_append(&del_list, rel);
