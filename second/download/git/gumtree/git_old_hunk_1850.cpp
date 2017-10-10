			    absolute_path(path), strerror(err));
	} else
		strbuf_addf(buf, "Unable to create '%s.lock': %s",
			    absolute_path(path), strerror(err));
}

int unable_to_lock_error(const char *path, int err)
{
	struct strbuf buf = STRBUF_INIT;

	unable_to_lock_message(path, err, &buf);
	error("%s", buf.buf);
	strbuf_release(&buf);
	return -1;
}

NORETURN void unable_to_lock_index_die(const char *path, int err)
{
	struct strbuf buf = STRBUF_INIT;

	unable_to_lock_message(path, err, &buf);
	die("%s", buf.buf);
}

/* This should return a meaningful errno on failure */
int hold_lock_file_for_update(struct lock_file *lk, const char *path, int flags)
{
	int fd = lock_file(lk, path, flags);
	if (fd < 0 && (flags & LOCK_DIE_ON_ERROR))
		unable_to_lock_index_die(path, errno);
	return fd;
}

int hold_lock_file_for_append(struct lock_file *lk, const char *path, int flags)
{
	int fd, orig_fd;

	fd = lock_file(lk, path, flags);
	if (fd < 0) {
		if (flags & LOCK_DIE_ON_ERROR)
			unable_to_lock_index_die(path, errno);
		return fd;
	}

	orig_fd = open(path, O_RDONLY);
	if (orig_fd < 0) {
		if (errno != ENOENT) {
			if (flags & LOCK_DIE_ON_ERROR)
				die("cannot open '%s' for copying", path);
			close(fd);
			return error("cannot open '%s' for copying", path);
		}
	} else if (copy_fd(orig_fd, fd)) {
		if (flags & LOCK_DIE_ON_ERROR)
			exit(128);
		close(fd);
		return -1;
	}
	return fd;
}

int close_lock_file(struct lock_file *lk)
{
	int fd = lk->fd;
	lk->fd = -1;
	return close(fd);
}

int commit_lock_file(struct lock_file *lk)
{
	char result_file[PATH_MAX];
	size_t i;
	if (lk->fd >= 0 && close_lock_file(lk))
		return -1;
	strcpy(result_file, lk->filename);
	i = strlen(result_file) - 5; /* .lock */
	result_file[i] = 0;
	if (rename(lk->filename, result_file))
		return -1;
	lk->filename[0] = 0;
	return 0;
}

int hold_locked_index(struct lock_file *lk, int die_on_error)
{
	return hold_lock_file_for_update(lk, get_index_file(),
					 die_on_error
					 ? LOCK_DIE_ON_ERROR
					 : 0);
}

void rollback_lock_file(struct lock_file *lk)
{
	if (lk->filename[0]) {
		if (lk->fd >= 0)
			close(lk->fd);
		unlink_or_warn(lk->filename);
	}
	lk->filename[0] = 0;
}
