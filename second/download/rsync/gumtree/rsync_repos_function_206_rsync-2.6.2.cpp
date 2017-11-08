int copy_file(char *source, char *dest, mode_t mode)
{
	int ifd;
	int ofd;
	char buf[1024 * 8];
	int len;   /* Number of bytes read into `buf'. */

	ifd = do_open(source, O_RDONLY, 0);
	if (ifd == -1) {
		rprintf(FERROR,"open %s: %s\n",
			full_fname(source), strerror(errno));
		return -1;
	}

	if (robust_unlink(dest) && errno != ENOENT) {
		rprintf(FERROR,"unlink %s: %s\n",
			full_fname(dest), strerror(errno));
		return -1;
	}

	ofd = do_open(dest, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, mode);
	if (ofd == -1) {
		rprintf(FERROR,"open %s: %s\n",
			full_fname(dest), strerror(errno));
		close(ifd);
		return -1;
	}

	while ((len = safe_read(ifd, buf, sizeof buf)) > 0) {
		if (full_write(ofd, buf, len) < 0) {
			rprintf(FERROR,"write %s: %s\n",
				full_fname(dest), strerror(errno));
			close(ifd);
			close(ofd);
			return -1;
		}
	}

	if (len < 0) {
		rprintf(FERROR, "read %s: %s\n",
			full_fname(source), strerror(errno));
		close(ifd);
		close(ofd);
		return -1;
	}

	if (close(ifd) < 0) {
		rprintf(FINFO, "close failed on %s: %s\n",
			full_fname(source), strerror(errno));
	}

	if (close(ofd) < 0) {
		rprintf(FERROR, "close failed on %s: %s\n",
			full_fname(dest), strerror(errno));
		return -1;
	}

	return 0;
}