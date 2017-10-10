
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

	strbuf_addf(&head_path, "%s/HEAD", absolute_path(gitdir));
	if (hold_lock_file_for_update(&head_lock, head_path.buf,
				      LOCK_NO_DEREF) < 0) {
		struct strbuf err = STRBUF_INIT;
		unable_to_lock_message(head_path.buf, errno, &err);
		error("%s", err.buf);
		strbuf_release(&err);
		strbuf_release(&head_path);
		return -1;
	}

	/* head_rel will be "HEAD" for the main tree, "worktrees/wt/HEAD" for
	   linked trees */
	head_rel = remove_leading_path(head_path.buf,
				       absolute_path(get_git_common_dir()));
	/* to make use of create_symref_locked(), initialize ref_lock */
	lock = xcalloc(1, sizeof(struct ref_lock));
	lock->lk = &head_lock;
	lock->ref_name = xstrdup(head_rel);

	ret = create_symref_locked(refs, lock, head_rel, target, logmsg);

	unlock_ref(lock); /* will free lock */
	strbuf_release(&head_path);
	return ret;
}

static int files_reflog_exists(struct ref_store *ref_store,
			       const char *refname)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ, "reflog_exists");
	struct strbuf sb = STRBUF_INIT;
