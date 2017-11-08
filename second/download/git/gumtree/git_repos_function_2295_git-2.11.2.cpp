static void new_untracked_cache(struct index_state *istate)
{
	struct untracked_cache *uc = xcalloc(1, sizeof(*uc));
	strbuf_init(&uc->ident, 100);
	uc->exclude_per_dir = ".gitignore";
	/* should be the same flags used by git-status */
	uc->dir_flags = DIR_SHOW_OTHER_DIRECTORIES | DIR_HIDE_EMPTY_DIRECTORIES;
	set_untracked_ident(uc);
	istate->untracked = uc;
	istate->cache_changed |= UNTRACKED_CHANGED;
}