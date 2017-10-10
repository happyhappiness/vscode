
	unable_to_lock_message(path, err, &buf);
	die("%s", buf.buf);
}

/* This should return a meaningful errno on failure */
int hold_lock_file_for_update(struct lock_file *lk, const char *path, int flags)
{
	int fd = lock_file(lk, path, flags);
	if (fd < 0 && (flags & LOCK_DIE_ON_ERROR))
		unable_to_lock_die(path, errno);
	return fd;
}

int hold_lock_file_for_append(struct lock_file *lk, const char *path, int flags)
