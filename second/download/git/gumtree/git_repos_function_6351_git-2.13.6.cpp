static int files_create_symref(struct ref_store *ref_store,
			       const char *refname, const char *target,
			       const char *logmsg)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "create_symref");
	struct strbuf err = STRBUF_INIT;
	struct ref_lock *lock;
	int ret;

	lock = lock_ref_sha1_basic(refs, refname, NULL,
				   NULL, NULL, REF_NODEREF, NULL,
				   &err);
	if (!lock) {
		error("%s", err.buf);
		strbuf_release(&err);
		return -1;
	}

	ret = create_symref_locked(refs, lock, refname, target, logmsg);
	unlock_ref(lock);
	return ret;
}