static struct ref_lock *lock_ref_sha1_basic(const char *refname,
					    const unsigned char *old_sha1,
					    const struct string_list *extras,
					    const struct string_list *skip,
					    unsigned int flags, int *type_p,
					    struct strbuf *err)
{
	struct strbuf ref_file = STRBUF_INIT;
	struct strbuf orig_ref_file = STRBUF_INIT;
	const char *orig_refname = refname;
	struct ref_lock *lock;
	int last_errno = 0;
	int type, lflags;
	int mustexist = (old_sha1 && !is_null_sha1(old_sha1));
	int resolve_flags = 0;
	int attempts_remaining = 3;

	assert(err);

	lock = xcalloc(1, sizeof(struct ref_lock));

	if (mustexist)
		resolve_flags |= RESOLVE_REF_READING;
	if (flags & REF_DELETING) {
		resolve_flags |= RESOLVE_REF_ALLOW_BAD_NAME;
		if (flags & REF_NODEREF)
			resolve_flags |= RESOLVE_REF_NO_RECURSE;
	}

	refname = resolve_ref_unsafe(refname, resolve_flags,
				     lock->old_oid.hash, &type);
	if (!refname && errno == EISDIR) {
		/*
		 * we are trying to lock foo but we used to
		 * have foo/bar which now does not exist;
		 * it is normal for the empty directory 'foo'
		 * to remain.
		 */
		strbuf_git_path(&orig_ref_file, "%s", orig_refname);
		if (remove_empty_directories(&orig_ref_file)) {
			last_errno = errno;
			if (!verify_refname_available_dir(orig_refname, extras, skip,
							  get_loose_refs(&ref_cache), err))
				strbuf_addf(err, "there are still refs under '%s'",
					    orig_refname);
			goto error_return;
		}
		refname = resolve_ref_unsafe(orig_refname, resolve_flags,
					     lock->old_oid.hash, &type);
	}
	if (type_p)
	    *type_p = type;
	if (!refname) {
		last_errno = errno;
		if (last_errno != ENOTDIR ||
		    !verify_refname_available_dir(orig_refname, extras, skip,
						  get_loose_refs(&ref_cache), err))
			strbuf_addf(err, "unable to resolve reference %s: %s",
				    orig_refname, strerror(last_errno));

		goto error_return;
	}
	/*
	 * If the ref did not exist and we are creating it, make sure
	 * there is no existing packed ref whose name begins with our
	 * refname, nor a packed ref whose name is a proper prefix of
	 * our refname.
	 */
	if (is_null_oid(&lock->old_oid) &&
	    verify_refname_available_dir(refname, extras, skip,
					 get_packed_refs(&ref_cache), err)) {
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
	strbuf_git_path(&ref_file, "%s", refname);

 retry:
	switch (safe_create_leading_directories_const(ref_file.buf)) {
	case SCLD_OK:
		break; /* success */
	case SCLD_VANISHED:
		if (--attempts_remaining > 0)
			goto retry;
		/* fall through */
	default:
		last_errno = errno;
		strbuf_addf(err, "unable to create directory for %s",
			    ref_file.buf);
		goto error_return;
	}

	if (hold_lock_file_for_update(lock->lk, ref_file.buf, lflags) < 0) {
		last_errno = errno;
		if (errno == ENOENT && --attempts_remaining > 0)
			/*
			 * Maybe somebody just deleted one of the
			 * directories leading to ref_file.  Try
			 * again:
			 */
			goto retry;
		else {
			unable_to_lock_message(ref_file.buf, errno, err);
			goto error_return;
		}
	}
	if (old_sha1 && verify_lock(lock, old_sha1, mustexist, err)) {
		last_errno = errno;
		goto error_return;
	}
	goto out;

 error_return:
	unlock_ref(lock);
	lock = NULL;

 out:
	strbuf_release(&ref_file);
	strbuf_release(&orig_ref_file);
	errno = last_errno;
	return lock;
}