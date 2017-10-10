		      sha1_to_hex(new_sha1),
		      committer);
	if (msglen)
		len += copy_msg(logrec + len - 1, msg) - 1;
	written = len <= maxlen ? write_in_full(logfd, logrec, len) : -1;
	free(logrec);
	if (written != len) {
		int save_errno = errno;
		close(logfd);
		error("Unable to append to %s", log_file);
		errno = save_errno;
		return -1;
	}
	if (close(logfd)) {
		int save_errno = errno;
		error("Unable to append to %s", log_file);
		errno = save_errno;
		return -1;
	}
	return 0;
}

int is_branch(const char *refname)
{
	return !strcmp(refname, "HEAD") || starts_with(refname, "refs/heads/");
}

/* This function must return a meaningful errno */
int write_ref_sha1(struct ref_lock *lock,
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
		return -1;
	}
	if (o->type != OBJ_COMMIT && is_branch(lock->ref_name)) {
		error("Trying to write non-commit object %s to branch %s",
			sha1_to_hex(sha1), lock->ref_name);
		unlock_ref(lock);
		errno = EINVAL;
		return -1;
	}
	if (write_in_full(lock->lock_fd, sha1_to_hex(sha1), 40) != 40 ||
	    write_in_full(lock->lock_fd, &term, 1) != 1 ||
	    close_ref(lock) < 0) {
		int save_errno = errno;
		error("Couldn't write %s", lock->lk->filename);
		unlock_ref(lock);
		errno = save_errno;
		return -1;
	}
	clear_loose_ref_cache(&ref_cache);
	if (log_ref_write(lock->ref_name, lock->old_sha1, sha1, logmsg) < 0 ||
	    (strcmp(lock->ref_name, lock->orig_ref_name) &&
	     log_ref_write(lock->orig_ref_name, lock->old_sha1, sha1, logmsg) < 0)) {
