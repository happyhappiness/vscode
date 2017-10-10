			 * Maybe somebody just deleted one of the
			 * directories leading to ref_file.  Try
			 * again:
			 */
			goto retry;
		else
			unable_to_lock_die(ref_file, errno);
	}
	return old_sha1 ? verify_lock(lock, old_sha1, mustexist) : lock;

 error_return:
	unlock_ref(lock);
	errno = last_errno;
	return NULL;
}

struct ref_lock *lock_any_ref_for_update(const char *refname,
					 const unsigned char *old_sha1,
					 int flags, int *type_p)
{
	return lock_ref_sha1_basic(refname, old_sha1, NULL, flags, type_p);
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
	write_packed_entry(cb_data, entry->name, entry->u.value.sha1,
			   peel_status == PEEL_PEELED ?
			   entry->u.value.peeled : NULL);
	return 0;
}

/* This should return a meaningful errno on failure */
