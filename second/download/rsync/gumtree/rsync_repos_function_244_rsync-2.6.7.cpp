int copy_file(const char *source, const char *dest, mode_t mode)
{
	int ifd;
	int ofd;
	char buf[1024 * 8];
	int len;   /* Number of bytes read into `buf'. */

	ifd = do_open(source, O_RDONLY, 0);
	if (ifd == -1) {
		rsyserr(FERROR, errno, "open %s", full_fname(source));
		return -1;
	}

	if (robust_unlink(dest) && errno != ENOENT) {
		rsyserr(FERROR, errno, "unlink %s", full_fname(dest));
		return -1;
	}

	ofd = do_open(dest, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, mode);
	if (ofd == -1) {
		rsyserr(FERROR, errno, "open %s", full_fname(dest));
		close(ifd);
		return -1;
	}

	while ((len = safe_read(ifd, buf, sizeof buf)) > 0) {
		if (full_write(ofd, buf, len) < 0) {
			rsyserr(FERROR, errno, "write %s", full_fname(dest));
			close(ifd);
			close(ofd);
			return -1;
		}
	}

	if (len < 0) {
		rsyserr(FERROR, errno, "read %s", full_fname(source));
		close(ifd);
		close(ofd);
		return -1;
	}

	if (close(ifd) < 0) {
		rsyserr(FINFO, errno, "close failed on %s",
			full_fname(source));
	}

	if (close(ofd) < 0) {
		rsyserr(FERROR, errno, "close failed on %s",
			full_fname(dest));
		return -1;
	}

	return 0;
}