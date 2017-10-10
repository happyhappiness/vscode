static int write_ref_sha1(struct ref_lock *lock,
	const unsigned char *sha1, const char *logmsg)
{
	static char term = '\n';
	struct object *o;

	if (!lock) {
		errno = EINVAL;
		return -1;
	}
	if (!lock->force_write && !hashcmp(lock->old_sha1, sha1)) {
		unlock_ref(lock);
		return 0;
	}
	o = parse_object(sha1);
	if (!o) {
		error("Trying to write ref %s with nonexistent object %s",
			lock->ref_name, sha1_to_hex(sha1));
		unlock_ref(lock);
		errno = EINVAL;
