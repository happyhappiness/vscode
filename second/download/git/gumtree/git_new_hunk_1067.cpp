	if (!lock) {
		error("%s", err.buf);
		strbuf_release(&err);
		return -1;
	}

	ret = create_symref_locked(refs, lock, refname, target, logmsg);
	unlock_ref(lock);
	return ret;
}

int set_worktree_head_symref(const char *gitdir, const char *target, const char *logmsg)
{
	/*
	 * FIXME: this obviously will not work well for future refs
	 * backends. This function needs to die.
	 */
	struct files_ref_store *refs =
		files_downcast(get_main_ref_store(),
			       REF_STORE_WRITE,
			       "set_head_symref");

	static struct lock_file head_lock;
	struct ref_lock *lock;
	struct strbuf head_path = STRBUF_INIT;
	const char *head_rel;
	int ret;

