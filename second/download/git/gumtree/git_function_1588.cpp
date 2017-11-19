static int update_branch(struct branch *b)
{
	static const char *msg = "fast-import";
	struct ref_lock *lock;
	unsigned char old_sha1[20];

	if (read_ref(b->name, old_sha1))
		hashclr(old_sha1);
	if (is_null_sha1(b->sha1)) {
		if (b->delete)
			delete_ref(b->name, old_sha1, 0);
		return 0;
	}
	lock = lock_any_ref_for_update(b->name, old_sha1, 0, NULL);
	if (!lock)
		return error("Unable to lock %s", b->name);
	if (!force_update && !is_null_sha1(old_sha1)) {
		struct commit *old_cmit, *new_cmit;

		old_cmit = lookup_commit_reference_gently(old_sha1, 0);
		new_cmit = lookup_commit_reference_gently(b->sha1, 0);
		if (!old_cmit || !new_cmit) {
			unlock_ref(lock);
			return error("Branch %s is missing commits.", b->name);
		}

		if (!in_merge_bases(old_cmit, new_cmit)) {
			unlock_ref(lock);
			warning("Not updating %s"
				" (new tip %s does not contain %s)",
				b->name, sha1_to_hex(b->sha1), sha1_to_hex(old_sha1));
			return -1;
		}
	}
	if (write_ref_sha1(lock, b->sha1, msg) < 0)
		return error("Unable to update %s", b->name);
	return 0;
}