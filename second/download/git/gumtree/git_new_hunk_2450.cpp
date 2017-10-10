	 * EXC_CMDL is not considered in the cache. If people set it,
	 * skip the cache.
	 */
	if (dir->exclude_list_group[EXC_CMDL].nr)
		return NULL;

	if (!ident_in_untracked(dir->untracked)) {
		warning(_("Untracked cache is disabled on this system."));
		return NULL;
	}

	if (!dir->untracked->root) {
