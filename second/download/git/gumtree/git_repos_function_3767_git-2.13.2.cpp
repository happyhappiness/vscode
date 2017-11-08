int close_tempfile(struct tempfile *tempfile)
{
	int fd = tempfile->fd;
	FILE *fp = tempfile->fp;
	int err;

	if (fd < 0)
		return 0;

	tempfile->fd = -1;
	if (fp) {
		tempfile->fp = NULL;
		if (ferror(fp)) {
			err = -1;
			if (!fclose(fp))
				errno = EIO;
		} else {
			err = fclose(fp);
		}
	} else {
		err = close(fd);
	}

	if (err) {
		int save_errno = errno;
		delete_tempfile(tempfile);
		errno = save_errno;
		return -1;
	}

	return 0;
}