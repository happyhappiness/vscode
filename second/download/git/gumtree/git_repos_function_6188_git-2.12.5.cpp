static void update_symref_reflog(struct ref_lock *lock, const char *refname,
				 const char *target, const char *logmsg)
{
	struct strbuf err = STRBUF_INIT;
	unsigned char new_sha1[20];
	if (logmsg && !read_ref(target, new_sha1) &&
	    log_ref_write(refname, lock->old_oid.hash, new_sha1, logmsg, 0, &err)) {
		error("%s", err.buf);
		strbuf_release(&err);
	}
}