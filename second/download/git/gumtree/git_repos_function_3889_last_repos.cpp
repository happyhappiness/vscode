int create_tempfile(struct tempfile *tempfile, const char *path)
{
	prepare_tempfile_object(tempfile);

	strbuf_add_absolute_path(&tempfile->filename, path);
	tempfile->fd = open(tempfile->filename.buf,
			    O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC, 0666);
	if (O_CLOEXEC && tempfile->fd < 0 && errno == EINVAL)
		/* Try again w/o O_CLOEXEC: the kernel might not support it */
		tempfile->fd = open(tempfile->filename.buf,
				    O_RDWR | O_CREAT | O_EXCL, 0666);
	if (tempfile->fd < 0) {
		strbuf_reset(&tempfile->filename);
		return -1;
	}
	tempfile->owner = getpid();
	tempfile->active = 1;
	if (adjust_shared_perm(tempfile->filename.buf)) {
		int save_errno = errno;
		error("cannot fix permission bits on %s", tempfile->filename.buf);
		delete_tempfile(tempfile);
		errno = save_errno;
		return -1;
	}
	return tempfile->fd;
}