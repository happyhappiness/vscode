static int write_ref_to_lockfile(struct ref_lock *lock,
				 const struct object_id *oid, struct strbuf *err)
{
	static char term = '\n';
	struct object *o;
	int fd;

	o = parse_object(oid);
	if (!o) {
		strbuf_addf(err,
			    "trying to write ref '%s' with nonexistent object %s",
			    lock->ref_name, oid_to_hex(oid));
		unlock_ref(lock);
		return -1;
	}
	if (o->type != OBJ_COMMIT && is_branch(lock->ref_name)) {
		strbuf_addf(err,
			    "trying to write non-commit object %s to branch '%s'",
			    oid_to_hex(oid), lock->ref_name);
		unlock_ref(lock);
		return -1;
	}
	fd = get_lock_file_fd(lock->lk);
	if (write_in_full(fd, oid_to_hex(oid), GIT_SHA1_HEXSZ) != GIT_SHA1_HEXSZ ||
	    write_in_full(fd, &term, 1) != 1 ||
	    close_ref(lock) < 0) {
		strbuf_addf(err,
			    "couldn't write '%s'", get_lock_file_path(lock->lk));
		unlock_ref(lock);
		return -1;
	}
	return 0;
}