 	 * EXC_CMDL is not considered in the cache. If people set it,
 	 * skip the cache.
 	 */
 	if (dir->exclude_list_group[EXC_CMDL].nr)
 		return NULL;
 
-	/*
-	 * An optimization in prep_exclude() does not play well with
-	 * CE_SKIP_WORKTREE. It's a rare case anyway, if a single
-	 * entry has that bit set, disable the whole untracked cache.
-	 */
-	for (i = 0; i < active_nr; i++)
-		if (ce_skip_worktree(active_cache[i]))
-			return NULL;
-
 	if (!ident_in_untracked(dir->untracked)) {
 		warning(_("Untracked cache is disabled on this system."));
 		return NULL;
 	}
 
 	if (!dir->untracked->root) {
