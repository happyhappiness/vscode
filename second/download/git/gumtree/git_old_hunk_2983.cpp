	*log = NULL;
	for (p = ref_rev_parse_rules; *p; p++) {
		unsigned char hash[20];
		char path[PATH_MAX];
		const char *ref, *it;

		mksnpath(path, sizeof(path), *p, len, str);
		ref = resolve_ref_unsafe(path, RESOLVE_REF_READING,
					 hash, NULL);
		if (!ref)
			continue;
		if (reflog_exists(path))
			it = path;
		else if (strcmp(ref, path) && reflog_exists(ref))
			it = ref;
		else
			continue;
		if (!logs_found++) {
			*log = xstrdup(it);
			hashcpy(sha1, hash);
		}
		if (!warn_ambiguous_refs)
			break;
	}
	free(last_branch);
	return logs_found;
}

/*
 * Locks a ref returning the lock on success and NULL on failure.
 * On failure errno is set to something meaningful.
 */
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
			if (!verify_refname_available(orig_refname, extras, skip,
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
		    !verify_refname_available(orig_refname, extras, skip,
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
	    verify_refname_available(refname, extras, skip,
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

/*
 * Write an entry to the packed-refs file for the specified refname.
 * If peeled is non-NULL, write it as the entry's peeled value.
 */
static void write_packed_entry(FILE *fh, char *refname, unsigned char *sha1,
			       unsigned char *peeled)
{
	fprintf_or_die(fh, "%s %s\n", sha1_to_hex(sha1), refname);
	if (peeled)
		fprintf_or_die(fh, "^%s\n", sha1_to_hex(peeled));
}

/*
 * An each_ref_entry_fn that writes the entry to a packed-refs file.
 */
static int write_packed_entry_fn(struct ref_entry *entry, void *cb_data)
{
	enum peel_status peel_status = peel_entry(entry, 0);

	if (peel_status != PEEL_PEELED && peel_status != PEEL_NON_TAG)
		error("internal error: %s is not a valid packed reference!",
		      entry->name);
	write_packed_entry(cb_data, entry->name, entry->u.value.oid.hash,
			   peel_status == PEEL_PEELED ?
			   entry->u.value.peeled.hash : NULL);
	return 0;
}

/*
 * Lock the packed-refs file for writing. Flags is passed to
 * hold_lock_file_for_update(). Return 0 on success. On errors, set
 * errno appropriately and return a nonzero value.
 */
static int lock_packed_refs(int flags)
{
	static int timeout_configured = 0;
	static int timeout_value = 1000;

	struct packed_ref_cache *packed_ref_cache;

	if (!timeout_configured) {
		git_config_get_int("core.packedrefstimeout", &timeout_value);
		timeout_configured = 1;
	}

	if (hold_lock_file_for_update_timeout(
			    &packlock, git_path("packed-refs"),
			    flags, timeout_value) < 0)
		return -1;
	/*
	 * Get the current packed-refs while holding the lock.  If the
	 * packed-refs file has been modified since we last read it,
	 * this will automatically invalidate the cache and re-read
	 * the packed-refs file.
	 */
	packed_ref_cache = get_packed_ref_cache(&ref_cache);
	packed_ref_cache->lock = &packlock;
	/* Increment the reference count to prevent it from being freed: */
	acquire_packed_ref_cache(packed_ref_cache);
	return 0;
}

/*
 * Write the current version of the packed refs cache from memory to
 * disk. The packed-refs file must already be locked for writing (see
 * lock_packed_refs()). Return zero on success. On errors, set errno
 * and return a nonzero value
 */
static int commit_packed_refs(void)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(&ref_cache);
	int error = 0;
	int save_errno = 0;
	FILE *out;

	if (!packed_ref_cache->lock)
		die("internal error: packed-refs not locked");

	out = fdopen_lock_file(packed_ref_cache->lock, "w");
	if (!out)
		die_errno("unable to fdopen packed-refs descriptor");

	fprintf_or_die(out, "%s", PACKED_REFS_HEADER);
	do_for_each_entry_in_dir(get_packed_ref_dir(packed_ref_cache),
				 0, write_packed_entry_fn, out);

	if (commit_lock_file(packed_ref_cache->lock)) {
		save_errno = errno;
		error = -1;
	}
	packed_ref_cache->lock = NULL;
	release_packed_ref_cache(packed_ref_cache);
	errno = save_errno;
	return error;
}

/*
 * Rollback the lockfile for the packed-refs file, and discard the
 * in-memory packed reference cache.  (The packed-refs file will be
 * read anew if it is needed again after this function is called.)
 */
static void rollback_packed_refs(void)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(&ref_cache);

	if (!packed_ref_cache->lock)
		die("internal error: packed-refs not locked");
	rollback_lock_file(packed_ref_cache->lock);
	packed_ref_cache->lock = NULL;
	release_packed_ref_cache(packed_ref_cache);
	clear_packed_ref_cache(&ref_cache);
}

struct ref_to_prune {
	struct ref_to_prune *next;
	unsigned char sha1[20];
	char name[FLEX_ARRAY];
};

struct pack_refs_cb_data {
	unsigned int flags;
	struct ref_dir *packed_refs;
	struct ref_to_prune *ref_to_prune;
};

/*
 * An each_ref_entry_fn that is run over loose references only.  If
 * the loose reference can be packed, add an entry in the packed ref
 * cache.  If the reference should be pruned, also add it to
 * ref_to_prune in the pack_refs_cb_data.
 */
static int pack_if_possible_fn(struct ref_entry *entry, void *cb_data)
{
	struct pack_refs_cb_data *cb = cb_data;
	enum peel_status peel_status;
	struct ref_entry *packed_entry;
	int is_tag_ref = starts_with(entry->name, "refs/tags/");

	/* ALWAYS pack tags */
	if (!(cb->flags & PACK_REFS_ALL) && !is_tag_ref)
		return 0;

	/* Do not pack symbolic or broken refs: */
	if ((entry->flag & REF_ISSYMREF) || !ref_resolves_to_object(entry))
		return 0;

	/* Add a packed ref cache entry equivalent to the loose entry. */
	peel_status = peel_entry(entry, 1);
	if (peel_status != PEEL_PEELED && peel_status != PEEL_NON_TAG)
		die("internal error peeling reference %s (%s)",
		    entry->name, oid_to_hex(&entry->u.value.oid));
	packed_entry = find_ref(cb->packed_refs, entry->name);
	if (packed_entry) {
		/* Overwrite existing packed entry with info from loose entry */
		packed_entry->flag = REF_ISPACKED | REF_KNOWS_PEELED;
		oidcpy(&packed_entry->u.value.oid, &entry->u.value.oid);
	} else {
		packed_entry = create_ref_entry(entry->name, entry->u.value.oid.hash,
						REF_ISPACKED | REF_KNOWS_PEELED, 0);
		add_ref(cb->packed_refs, packed_entry);
	}
	oidcpy(&packed_entry->u.value.peeled, &entry->u.value.peeled);

	/* Schedule the loose reference for pruning if requested. */
	if ((cb->flags & PACK_REFS_PRUNE)) {
		int namelen = strlen(entry->name) + 1;
		struct ref_to_prune *n = xcalloc(1, sizeof(*n) + namelen);
		hashcpy(n->sha1, entry->u.value.oid.hash);
		strcpy(n->name, entry->name);
		n->next = cb->ref_to_prune;
		cb->ref_to_prune = n;
	}
	return 0;
}

/*
 * Remove empty parents, but spare refs/ and immediate subdirs.
 * Note: munges *name.
 */
static void try_remove_empty_parents(char *name)
{
	char *p, *q;
	int i;
	p = name;
	for (i = 0; i < 2; i++) { /* refs/{heads,tags,...}/ */
		while (*p && *p != '/')
			p++;
		/* tolerate duplicate slashes; see check_refname_format() */
		while (*p == '/')
			p++;
	}
	for (q = p; *q; q++)
		;
	while (1) {
		while (q > p && *q != '/')
			q--;
		while (q > p && *(q-1) == '/')
			q--;
		if (q == p)
			break;
		*q = '\0';
		if (rmdir(git_path("%s", name)))
			break;
	}
}

/* make sure nobody touched the ref, and unlink */
static void prune_ref(struct ref_to_prune *r)
{
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	if (check_refname_format(r->name, 0))
		return;

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_delete(transaction, r->name, r->sha1,
				   REF_ISPRUNING, NULL, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		ref_transaction_free(transaction);
		error("%s", err.buf);
		strbuf_release(&err);
		return;
	}
	ref_transaction_free(transaction);
	strbuf_release(&err);
	try_remove_empty_parents(r->name);
}

static void prune_refs(struct ref_to_prune *r)
{
	while (r) {
		prune_ref(r);
		r = r->next;
	}
}

int pack_refs(unsigned int flags)
{
	struct pack_refs_cb_data cbdata;

	memset(&cbdata, 0, sizeof(cbdata));
	cbdata.flags = flags;

	lock_packed_refs(LOCK_DIE_ON_ERROR);
	cbdata.packed_refs = get_packed_refs(&ref_cache);

	do_for_each_entry_in_dir(get_loose_refs(&ref_cache), 0,
				 pack_if_possible_fn, &cbdata);

	if (commit_packed_refs())
		die_errno("unable to overwrite old ref-pack file");

	prune_refs(cbdata.ref_to_prune);
	return 0;
}

/*
 * Rewrite the packed-refs file, omitting any refs listed in
 * 'refnames'. On error, leave packed-refs unchanged, write an error
 * message to 'err', and return a nonzero value.
 *
 * The refs in 'refnames' needn't be sorted. `err` must not be NULL.
 */
static int repack_without_refs(struct string_list *refnames, struct strbuf *err)
{
	struct ref_dir *packed;
	struct string_list_item *refname;
	int ret, needs_repacking = 0, removed = 0;

	assert(err);

	/* Look for a packed ref */
	for_each_string_list_item(refname, refnames) {
		if (get_packed_ref(refname->string)) {
			needs_repacking = 1;
			break;
		}
	}

	/* Avoid locking if we have nothing to do */
	if (!needs_repacking)
		return 0; /* no refname exists in packed refs */

	if (lock_packed_refs(0)) {
		unable_to_lock_message(git_path("packed-refs"), errno, err);
		return -1;
	}
	packed = get_packed_refs(&ref_cache);

	/* Remove refnames from the cache */
	for_each_string_list_item(refname, refnames)
		if (remove_entry(packed, refname->string) != -1)
			removed = 1;
	if (!removed) {
		/*
		 * All packed entries disappeared while we were
		 * acquiring the lock.
		 */
		rollback_packed_refs();
		return 0;
	}

	/* Write what remains */
	ret = commit_packed_refs();
	if (ret)
		strbuf_addf(err, "unable to overwrite old ref-pack file: %s",
			    strerror(errno));
	return ret;
}

static int delete_ref_loose(struct ref_lock *lock, int flag, struct strbuf *err)
{
	assert(err);

	if (!(flag & REF_ISPACKED) || flag & REF_ISSYMREF) {
		/*
		 * loose.  The loose file name is the same as the
		 * lockfile name, minus ".lock":
		 */
		char *loose_filename = get_locked_file_path(lock->lk);
		int res = unlink_or_msg(loose_filename, err);
		free(loose_filename);
		if (res)
			return 1;
	}
	return 0;
}

static int is_per_worktree_ref(const char *refname)
{
	return !strcmp(refname, "HEAD");
}

static int is_pseudoref_syntax(const char *refname)
{
	const char *c;

