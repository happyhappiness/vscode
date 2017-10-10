	if (commit_ref(lock) < 0)
		return error("unable to write symref for %s: %s", refname,
			     strerror(errno));
	return 0;
}

int create_symref(const char *refname, const char *target, const char *logmsg)
{
	struct strbuf err = STRBUF_INIT;
	struct ref_lock *lock;
	int ret;

	lock = lock_ref_sha1_basic(refname, NULL, NULL, NULL, REF_NODEREF, NULL,
				   &err);
	if (!lock) {
		error("%s", err.buf);
		strbuf_release(&err);
		return -1;
	}
