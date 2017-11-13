static int create_symref_locked(struct ref_lock *lock, const char *refname,
				const char *target, const char *logmsg)
{
	if (prefer_symlink_refs && !create_ref_symlink(lock, target)) {
		update_symref_reflog(lock, refname, target, logmsg);
		return 0;
	}

	if (!fdopen_lock_file(lock->lk, "w"))
		return error("unable to fdopen %s: %s",
			     lock->lk->tempfile.filename.buf, strerror(errno));

	update_symref_reflog(lock, refname, target, logmsg);

	/* no error check; commit_ref will check ferror */
	fprintf(lock->lk->tempfile.fp, "ref: %s\n", target);
	if (commit_ref(lock) < 0)
		return error("unable to write symref for %s: %s", refname,
			     strerror(errno));
	return 0;
}