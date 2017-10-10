
static void update_symref_reflog(struct files_ref_store *refs,
				 struct ref_lock *lock, const char *refname,
				 const char *target, const char *logmsg)
{
	struct strbuf err = STRBUF_INIT;
	struct object_id new_oid;
	if (logmsg &&
	    !refs_read_ref_full(&refs->base, target,
				RESOLVE_REF_READING, new_oid.hash, NULL) &&
	    files_log_ref_write(refs, refname, &lock->old_oid,
				&new_oid, logmsg, 0, &err)) {
		error("%s", err.buf);
		strbuf_release(&err);
	}
}

static int create_symref_locked(struct files_ref_store *refs,
