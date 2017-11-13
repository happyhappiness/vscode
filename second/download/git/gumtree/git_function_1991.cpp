static struct ref_lock *lock_ref_sha1_basic(const char *refname,
					    const unsigned char *old_sha1,
					    const struct string_list *skip,
					    unsigned int flags, int *type_p)
{
	char *ref_file;
	const char *orig_refname = refname;
	struct ref_lock *lock;
	int last_errno = 0;
	int type, lflags;
	int mustexist = (old_sha1 && !is_null_sha1(old_sha1));
	int resolve_flags = 0;
	int attempts_remaining = 3;

	lock = xcalloc(1, sizeof(struct ref_lock));
	lock->lock_fd = -1;

	if (mustexist)
		resolve_flags |= RESOLVE_REF_READING;
	if (flags & REF_DELETING) {
		resolve_flags |= RESOLVE_REF_ALLOW_BAD_NAME;
		if (flags & REF_NODEREF)
			resolve_flags |= RESOLVE_REF_NO_RECURSE;
	}

	refname = resolve_ref_unsafe(refname, resolve_flags,
				     lock->old_sha1, &type);
	if (!refname && errno == EISDIR) {
		/* we are trying to lock foo but we used to
		 * have foo/bar which now does not exist;
		 * it is normal for the empty directory 'foo'
		 * to remain.
		 */
		ref_file = git_path("%s", orig_refname);
		if (remove_empty_directories(ref_file)) {
			last_errno = errno;
			error("there are still refs under '%s'", orig_refname);
			goto error_return;
		}
		refname = resolve_ref_unsafe(orig_refname, resolve_flags,
					     lock->old_sha1, &type);
	}
	if (type_p)
	    *type_p = type;
	if (!refname) {
		last_errno = errno;
		error("unable to resolve reference %s: %s",
			orig_refname, strerror(errno));
		goto error_return;
	}
	/*
	 * If the ref did not exist and we are creating it, make sure
	 * there is no existing packed ref whose name begins with our
	 * refname, nor a packed ref whose name is a proper prefix of
	 * our refname.
	 */
	if (is_null_sha1(lock->old_sha1) &&
	     !is_refname_available(refname, skip, get_packed_refs(&ref_cache))) {
		last_errno = ENOTDIR;
		goto error_return;
	}

	lock->lk = xcalloc(1, sizeof(struct lock_file));

	lflags = 0;
	if (flags & REF_NODEREF) {
		refname = orig_refname;
		lflags |= LOCK_NO_DEREF;
	}
	lock->ref_name = xstrdup(refname);
	lock->orig_ref_name = xstrdup(orig_refname);
	ref_file = git_path("%s", refname);

 retry:
	switch (safe_create_leading_directories(ref_file)) {
	case SCLD_OK:
		break; /* success */
	case SCLD_VANISHED:
		if (--attempts_remaining > 0)
			goto retry;
		/* fall through */
	default:
		last_errno = errno;
		error("unable to create directory for %s", ref_file);
		goto error_return;
	}

	lock->lock_fd = hold_lock_file_for_update(lock->lk, ref_file, lflags);
	if (lock->lock_fd < 0) {
		last_errno = errno;
		if (errno == ENOENT && --attempts_remaining > 0)
			/*
			 * Maybe somebody just deleted one of the
			 * directories leading to ref_file.  Try
			 * again:
			 */
			goto retry;
		else {
			struct strbuf err = STRBUF_INIT;
			unable_to_lock_message(ref_file, errno, &err);
			error("%s", err.buf);
			strbuf_release(&err);
			goto error_return;
		}
	}
	return old_sha1 ? verify_lock(lock, old_sha1, mustexist) : lock;

 error_return:
	unlock_ref(lock);
	errno = last_errno;
	return NULL;
}