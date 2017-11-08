int copy_file(const char *source, const char *dest, int ofd,
	      mode_t mode, int create_bak_dir)
{
	int ifd;
	char buf[1024 * 8];
	int len;   /* Number of bytes read into `buf'. */

	if ((ifd = do_open(source, O_RDONLY, 0)) < 0) {
		int save_errno = errno;
		rsyserr(FERROR_XFER, errno, "open %s", full_fname(source));
		errno = save_errno;
		return -1;
	}

	if (ofd < 0) {
		if (robust_unlink(dest) && errno != ENOENT) {
			int save_errno = errno;
			rsyserr(FERROR_XFER, errno, "unlink %s", full_fname(dest));
			errno = save_errno;
			return -1;
		}

		if ((ofd = do_open(dest, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, mode)) < 0) {
			int save_errno = errno ? errno : EINVAL; /* 0 paranoia */
			if (create_bak_dir && errno == ENOENT && make_bak_dir(dest) == 0) {
				if ((ofd = do_open(dest, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, mode)) < 0)
					save_errno = errno ? errno : save_errno;
				else
					save_errno = 0;
			}
			if (save_errno) {
				rsyserr(FERROR_XFER, save_errno, "open %s", full_fname(dest));
				close(ifd);
				errno = save_errno;
				return -1;
			}
		}
	}

	while ((len = safe_read(ifd, buf, sizeof buf)) > 0) {
		if (full_write(ofd, buf, len) < 0) {
			int save_errno = errno;
			rsyserr(FERROR_XFER, errno, "write %s", full_fname(dest));
			close(ifd);
			close(ofd);
			errno = save_errno;
			return -1;
		}
	}

	if (len < 0) {
		int save_errno = errno;
		rsyserr(FERROR_XFER, errno, "read %s", full_fname(source));
		close(ifd);
		close(ofd);
		errno = save_errno;
		return -1;
	}

	if (close(ifd) < 0) {
		rsyserr(FWARNING, errno, "close failed on %s",
			full_fname(source));
	}

	if (close(ofd) < 0) {
		int save_errno = errno;
		rsyserr(FERROR_XFER, errno, "close failed on %s",
			full_fname(dest));
		errno = save_errno;
		return -1;
	}

#ifdef SUPPORT_XATTRS
	if (preserve_xattrs)
		copy_xattrs(source, dest);
#endif

	return 0;
}