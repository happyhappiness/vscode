}

/*
 * Write an entry to the packed-refs file for the specified refname.
 * If peeled is non-NULL, write it as the entry's peeled value.
 */
static void write_packed_entry(FILE *fh, const char *refname,
			       const unsigned char *sha1,
			       const unsigned char *peeled)
{
	fprintf_or_die(fh, "%s %s\n", sha1_to_hex(sha1), refname);
	if (peeled)
		fprintf_or_die(fh, "^%s\n", sha1_to_hex(peeled));
}

/*
 * Lock the packed-refs file for writing. Flags is passed to
 * hold_lock_file_for_update(). Return 0 on success. On errors, set
 * errno appropriately and return a nonzero value.
 */
static int lock_packed_refs(struct files_ref_store *refs, int flags)
{
	static int timeout_configured = 0;
	static int timeout_value = 1000;
	struct packed_ref_cache *packed_ref_cache;

	files_assert_main_repository(refs, "lock_packed_refs");

	if (!timeout_configured) {
		git_config_get_int("core.packedrefstimeout", &timeout_value);
		timeout_configured = 1;
	}

	if (hold_lock_file_for_update_timeout(
			    &packlock, files_packed_refs_path(refs),
			    flags, timeout_value) < 0)
		return -1;
	/*
	 * Get the current packed-refs while holding the lock.  If the
	 * packed-refs file has been modified since we last read it,
	 * this will automatically invalidate the cache and re-read
