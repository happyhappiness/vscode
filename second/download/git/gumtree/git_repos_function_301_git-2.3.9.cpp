int refresh_index(struct index_state *istate, unsigned int flags,
		  const struct pathspec *pathspec,
		  char *seen, const char *header_msg)
{
	int i;
	int has_errors = 0;
	int really = (flags & REFRESH_REALLY) != 0;
	int allow_unmerged = (flags & REFRESH_UNMERGED) != 0;
	int quiet = (flags & REFRESH_QUIET) != 0;
	int not_new = (flags & REFRESH_IGNORE_MISSING) != 0;
	int ignore_submodules = (flags & REFRESH_IGNORE_SUBMODULES) != 0;
	int first = 1;
	int in_porcelain = (flags & REFRESH_IN_PORCELAIN);
	unsigned int options = (CE_MATCH_REFRESH |
				(really ? CE_MATCH_IGNORE_VALID : 0) |
				(not_new ? CE_MATCH_IGNORE_MISSING : 0));
	const char *modified_fmt;
	const char *deleted_fmt;
	const char *typechange_fmt;
	const char *added_fmt;
	const char *unmerged_fmt;

	modified_fmt = (in_porcelain ? "M\t%s\n" : "%s: needs update\n");
	deleted_fmt = (in_porcelain ? "D\t%s\n" : "%s: needs update\n");
	typechange_fmt = (in_porcelain ? "T\t%s\n" : "%s needs update\n");
	added_fmt = (in_porcelain ? "A\t%s\n" : "%s needs update\n");
	unmerged_fmt = (in_porcelain ? "U\t%s\n" : "%s: needs merge\n");
	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce, *new;
		int cache_errno = 0;
		int changed = 0;
		int filtered = 0;

		ce = istate->cache[i];
		if (ignore_submodules && S_ISGITLINK(ce->ce_mode))
			continue;

		if (pathspec && !ce_path_match(ce, pathspec, seen))
			filtered = 1;

		if (ce_stage(ce)) {
			while ((i < istate->cache_nr) &&
			       ! strcmp(istate->cache[i]->name, ce->name))
				i++;
			i--;
			if (allow_unmerged)
				continue;
			if (!filtered)
				show_file(unmerged_fmt, ce->name, in_porcelain,
					  &first, header_msg);
			has_errors = 1;
			continue;
		}

		if (filtered)
			continue;

		new = refresh_cache_ent(istate, ce, options, &cache_errno, &changed);
		if (new == ce)
			continue;
		if (!new) {
			const char *fmt;

			if (really && cache_errno == EINVAL) {
				/* If we are doing --really-refresh that
				 * means the index is not valid anymore.
				 */
				ce->ce_flags &= ~CE_VALID;
				ce->ce_flags |= CE_UPDATE_IN_BASE;
				istate->cache_changed |= CE_ENTRY_CHANGED;
			}
			if (quiet)
				continue;

			if (cache_errno == ENOENT)
				fmt = deleted_fmt;
			else if (ce->ce_flags & CE_INTENT_TO_ADD)
				fmt = added_fmt; /* must be before other checks */
			else if (changed & TYPE_CHANGED)
				fmt = typechange_fmt;
			else
				fmt = modified_fmt;
			show_file(fmt,
				  ce->name, in_porcelain, &first, header_msg);
			has_errors = 1;
			continue;
		}

		replace_index_entry(istate, i, new);
	}
	return has_errors;
}