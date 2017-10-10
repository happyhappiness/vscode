		error("unable to restore logfile %s from "TMP_RENAMED_LOG": %s",
			oldrefname, strerror(errno));

	return 1;
}

static int close_ref(struct ref_lock *lock)
{
	if (close_lock_file(lock->lk))
		return -1;
	lock->lock_fd = -1;
	return 0;
}

static int commit_ref(struct ref_lock *lock)
{
	if (commit_lock_file(lock->lk))
		return -1;
	lock->lock_fd = -1;
	return 0;
}

/*
 * copy the reflog message msg to buf, which has been allocated sufficiently
 * large, while cleaning up the whitespaces.  Especially, convert LF to space,
 * because reflog file is one line per entry.
 */
static int copy_msg(char *buf, const char *msg)
