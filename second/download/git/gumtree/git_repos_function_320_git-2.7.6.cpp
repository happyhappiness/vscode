int add_to_index(struct index_state *istate, const char *path, struct stat *st, int flags)
{
	int size, namelen, was_same;
	mode_t st_mode = st->st_mode;
	struct cache_entry *ce, *alias;
	unsigned ce_option = CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE|CE_MATCH_RACY_IS_DIRTY;
	int verbose = flags & (ADD_CACHE_VERBOSE | ADD_CACHE_PRETEND);
	int pretend = flags & ADD_CACHE_PRETEND;
	int intent_only = flags & ADD_CACHE_INTENT;
	int add_option = (ADD_CACHE_OK_TO_ADD|ADD_CACHE_OK_TO_REPLACE|
			  (intent_only ? ADD_CACHE_NEW_ONLY : 0));

	if (!S_ISREG(st_mode) && !S_ISLNK(st_mode) && !S_ISDIR(st_mode))
		return error("%s: can only add regular files, symbolic links or git-directories", path);

	namelen = strlen(path);
	if (S_ISDIR(st_mode)) {
		while (namelen && path[namelen-1] == '/')
			namelen--;
	}
	size = cache_entry_size(namelen);
	ce = xcalloc(1, size);
	memcpy(ce->name, path, namelen);
	ce->ce_namelen = namelen;
	if (!intent_only)
		fill_stat_cache_info(ce, st);
	else
		ce->ce_flags |= CE_INTENT_TO_ADD;

	if (trust_executable_bit && has_symlinks)
		ce->ce_mode = create_ce_mode(st_mode);
	else {
		/* If there is an existing entry, pick the mode bits and type
		 * from it, otherwise assume unexecutable regular file.
		 */
		struct cache_entry *ent;
		int pos = index_name_pos_also_unmerged(istate, path, namelen);

		ent = (0 <= pos) ? istate->cache[pos] : NULL;
		ce->ce_mode = ce_mode_from_stat(ent, st_mode);
	}

	/* When core.ignorecase=true, determine if a directory of the same name but differing
	 * case already exists within the Git repository.  If it does, ensure the directory
	 * case of the file being added to the repository matches (is folded into) the existing
	 * entry's directory case.
	 */
	if (ignore_case) {
		adjust_dirname_case(istate, ce->name);
	}

	alias = index_file_exists(istate, ce->name, ce_namelen(ce), ignore_case);
	if (alias && !ce_stage(alias) && !ie_match_stat(istate, alias, st, ce_option)) {
		/* Nothing changed, really */
		if (!S_ISGITLINK(alias->ce_mode))
			ce_mark_uptodate(alias);
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

	if (ignore_case && alias && different_name(ce, alias))
		ce = create_alias_ce(istate, ce, alias);
	ce->ce_flags |= CE_ADDED;

	/* It was suspected to be racily clean, but it turns out to be Ok */
	was_same = (alias &&
		    !ce_stage(alias) &&
		    !hashcmp(alias->sha1, ce->sha1) &&
		    ce->ce_mode == alias->ce_mode);

	if (pretend)
		free(ce);
	else if (add_index_entry(istate, ce, add_option)) {
		free(ce);
		return error("unable to add %s to index", path);
	}
	if (verbose && !was_same)
		printf("add '%s'\n", path);
	return 0;
}