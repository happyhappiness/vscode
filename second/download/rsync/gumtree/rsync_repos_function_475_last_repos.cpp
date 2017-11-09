int do_open_nofollow(const char *pathname, int flags)
{
#ifndef O_NOFOLLOW
	STRUCT_STAT f_st, l_st;
#endif
	int fd;

	if (flags != O_RDONLY) {
		RETURN_ERROR_IF(dry_run, 0);
		RETURN_ERROR_IF_RO_OR_LO;
#ifndef O_NOFOLLOW
		/* This function doesn't support write attempts w/o O_NOFOLLOW. */
		errno = EINVAL;
		return -1;
#endif
	}

#ifdef O_NOFOLLOW
	fd = open(pathname, flags|O_NOFOLLOW);
#else
	if (do_lstat(pathname, &l_st) < 0)
		return -1;
	if (S_ISLNK(l_st.st_mode)) {
		errno = ELOOP;
		return -1;
	}
	if ((fd = open(pathname, flags)) < 0)
		return fd;
	if (do_fstat(fd, &f_st) < 0) {
	  close_and_return_error:
		{
			int save_errno = errno;
			close(fd);
			errno = save_errno;
		}
		return -1;
	}
	if (l_st.st_dev != f_st.st_dev || l_st.st_ino != f_st.st_ino) {
		errno = EINVAL;
		goto close_and_return_error;
	}
#endif

	return fd;
}