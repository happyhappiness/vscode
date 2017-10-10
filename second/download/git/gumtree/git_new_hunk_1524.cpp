
	ret = create_symref_locked(refs, lock, refname, target, logmsg);
	unlock_ref(lock);
	return ret;
}

static int files_reflog_exists(struct ref_store *ref_store,
			       const char *refname)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ, "reflog_exists");
	struct strbuf sb = STRBUF_INIT;
