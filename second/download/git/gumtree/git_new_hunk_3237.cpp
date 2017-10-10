	}

	unlock_ref(lock);
	return 0;
}

static int create_ref_symlink(struct ref_lock *lock, const char *target)
{
	int ret = -1;
#ifndef NO_SYMLINK_HEAD
	char *ref_path = get_locked_file_path(lock->lk);
	unlink(ref_path);
	ret = symlink(target, ref_path);
	free(ref_path);

	if (ret)
		fprintf(stderr, "no symlink - falling back to symbolic ref\n");
#endif
	return ret;
}

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

	ret = create_symref_locked(lock, refname, target, logmsg);
	unlock_ref(lock);
	return ret;
}

int reflog_exists(const char *refname)
{
	struct stat st;

