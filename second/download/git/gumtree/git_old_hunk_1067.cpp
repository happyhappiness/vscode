	if (!lock) {
		error("%s", err.buf);
		strbuf_release(&err);
		return -1;
	}

	ret = create_symref_locked(lock, refname, target, logmsg);
	unlock_ref(lock);
	return ret;
}

int set_worktree_head_symref(const char *gitdir, const char *target)
{
	static struct lock_file head_lock;
	struct ref_lock *lock;
	struct strbuf head_path = STRBUF_INIT;
	const char *head_rel;
	int ret;

