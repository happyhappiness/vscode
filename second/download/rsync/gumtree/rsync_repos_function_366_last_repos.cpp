int copy_file(const char *source, const char *dest, int ofd, mode_t mode)
{
	int ifd;
	char buf[1024 * 8];
	int len;   /* Number of bytes read into `buf'. */
#ifdef PREALLOCATE_NEEDS_TRUNCATE
	OFF_T preallocated_len = 0, offset = 0;
#endif

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

#ifdef SUPPORT_XATTRS
		if (preserve_xattrs)
			mode |= S_IWUSR;
#endif
		mode &= INITACCESSPERMS;
		if ((ofd = do_open(dest, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, mode)) < 0) {
			int save_errno = errno;
			rsyserr(FERROR_XFER, save_errno, "open %s", full_fname(dest));
			close(ifd);
			errno = save_errno;
			return -1;
		}
	}

#ifdef SUPPORT_PREALLOCATION
	if (preallocate_files) {
		STRUCT_STAT srcst;

		/* Try to preallocate enough space for file's eventual length.  Can
		 * reduce fragmentation on filesystems like ext4, xfs, and NTFS. */
		if (do_fstat(ifd, &srcst) < 0)
			rsyserr(FWARNING, errno, "fstat %s", full_fname(source));
		else if (srcst.st_size > 0) {
			if (do_fallocate(ofd, 0, srcst.st_size) == 0) {
#ifdef PREALLOCATE_NEEDS_TRUNCATE
				preallocated_len = srcst.st_size;
#endif
			} else
				rsyserr(FWARNING, errno, "do_fallocate %s", full_fname(dest));
		}
	}
#endif

	while ((len = safe_read(ifd, buf, sizeof buf)) > 0) {
		if (full_write(ofd, buf, len) < 0) {
			int save_errno = errno;
			rsyserr(FERROR_XFER, errno, "write %s", full_fname(dest));
			close(ifd);
			close(ofd);
			errno = save_errno;
			return -1;
		}
#ifdef PREALLOCATE_NEEDS_TRUNCATE
		offset += len;
#endif
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

#ifdef PREALLOCATE_NEEDS_TRUNCATE
	/* Source file might have shrunk since we fstatted it.
	 * Cut off any extra preallocated zeros from dest file. */
	if (offset < preallocated_len && do_ftruncate(ofd, offset) < 0) {
		/* If we fail to truncate, the dest file may be wrong, so we
		 * must trigger the "partial transfer" error. */
		rsyserr(FERROR_XFER, errno, "ftruncate %s", full_fname(dest));
	}
#endif

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