static int get_sha1_with_context_1(const char *name,
				   unsigned flags,
				   const char *prefix,
				   unsigned char *sha1,
				   struct object_context *oc)
{
	int ret, bracket_depth;
	int namelen = strlen(name);
	const char *cp;
	int only_to_die = flags & GET_SHA1_ONLY_TO_DIE;

	if (only_to_die)
		flags |= GET_SHA1_QUIETLY;

	memset(oc, 0, sizeof(*oc));
	oc->mode = S_IFINVALID;
	ret = get_sha1_1(name, namelen, sha1, flags);
	if (!ret)
		return ret;
	/*
	 * sha1:path --> object name of path in ent sha1
	 * :path -> object name of absolute path in index
	 * :./path -> object name of path relative to cwd in index
	 * :[0-3]:path -> object name of path in index at stage
	 * :/foo -> recent commit matching foo
	 */
	if (name[0] == ':') {
		int stage = 0;
		const struct cache_entry *ce;
		char *new_path = NULL;
		int pos;
		if (!only_to_die && namelen > 2 && name[1] == '/') {
			struct commit_list *list = NULL;

			for_each_ref(handle_one_ref, &list);
			commit_list_sort_by_date(&list);
			return get_sha1_oneline(name + 2, sha1, list);
		}
		if (namelen < 3 ||
		    name[2] != ':' ||
		    name[1] < '0' || '3' < name[1])
			cp = name + 1;
		else {
			stage = name[1] - '0';
			cp = name + 3;
		}
		new_path = resolve_relative_path(cp);
		if (!new_path) {
			namelen = namelen - (cp - name);
		} else {
			cp = new_path;
			namelen = strlen(cp);
		}

		strlcpy(oc->path, cp, sizeof(oc->path));

		if (!active_cache)
			read_cache();
		pos = cache_name_pos(cp, namelen);
		if (pos < 0)
			pos = -pos - 1;
		while (pos < active_nr) {
			ce = active_cache[pos];
			if (ce_namelen(ce) != namelen ||
			    memcmp(ce->name, cp, namelen))
				break;
			if (ce_stage(ce) == stage) {
				hashcpy(sha1, ce->oid.hash);
				oc->mode = ce->ce_mode;
				free(new_path);
				return 0;
			}
			pos++;
		}
		if (only_to_die && name[1] && name[1] != '/')
			diagnose_invalid_index_path(stage, prefix, cp);
		free(new_path);
		return -1;
	}
	for (cp = name, bracket_depth = 0; *cp; cp++) {
		if (*cp == '{')
			bracket_depth++;
		else if (bracket_depth && *cp == '}')
			bracket_depth--;
		else if (!bracket_depth && *cp == ':')
			break;
	}
	if (*cp == ':') {
		unsigned char tree_sha1[20];
		int len = cp - name;
		unsigned sub_flags = flags;

		sub_flags &= ~GET_SHA1_DISAMBIGUATORS;
		sub_flags |= GET_SHA1_TREEISH;

		if (!get_sha1_1(name, len, tree_sha1, sub_flags)) {
			const char *filename = cp+1;
			char *new_filename = NULL;

			new_filename = resolve_relative_path(filename);
			if (new_filename)
				filename = new_filename;
			if (flags & GET_SHA1_FOLLOW_SYMLINKS) {
				ret = get_tree_entry_follow_symlinks(tree_sha1,
					filename, sha1, &oc->symlink_path,
					&oc->mode);
			} else {
				ret = get_tree_entry(tree_sha1, filename,
						     sha1, &oc->mode);
				if (ret && only_to_die) {
					diagnose_invalid_sha1_path(prefix,
								   filename,
								   tree_sha1,
								   name, len);
				}
			}
			hashcpy(oc->tree, tree_sha1);
			strlcpy(oc->path, filename, sizeof(oc->path));

			free(new_filename);
			return ret;
		} else {
			if (only_to_die)
				die("Invalid object name '%.*s'.", len, name);
		}
	}
	return ret;
}