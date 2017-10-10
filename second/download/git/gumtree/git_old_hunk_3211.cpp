	 * skip the cache.
	 */
	if (dir->exclude_list_group[EXC_CMDL].nr)
		return NULL;

	if (!ident_in_untracked(dir->untracked)) {
		warning(_("Untracked cache is disabled on this system."));
		return NULL;
	}

	if (!dir->untracked->root) {
		const int len = sizeof(*dir->untracked->root);
		dir->untracked->root = xmalloc(len);
