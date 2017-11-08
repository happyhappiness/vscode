static int write_ref_to_lockfile(struct ref_lock *lock,
				 const unsigned char *sha1, struct strbuf *err)
{
	static char term = '\n';
	struct object *o;
	int fd;

	o = parse_object(sha1);
	if (!o) {
		strbuf_addf(err,
			    "Trying to write ref %s with nonexistent object %s",
			    lock->ref_name, sha1_to_hex(sha1));
		unlock_ref(lock);
		return -1;
	}
	if (o->type != OBJ_COMMIT && is_branch(lock->ref_name)) {
		strbuf_addf(err,
			    "Trying to write non-commit object %s to branch %s",
			    sha1_to_hex(sha1), lock->ref_name);
		unlock_ref(lock);
		return -1;
	}
	fd = get_lock_file_fd(lock->lk);
	if (write_in_full(fd, sha1_to_hex(sha1), 40) != 40 ||
	    write_in_full(fd, &term, 1) != 1 ||
	    close_ref(lock) < 0) {
		strbuf_addf(err,
			    "Couldn't write %s", get_lock_file_path(lock->lk));
		unlock_ref(lock);
		return -1;
	}
	return 0;
}