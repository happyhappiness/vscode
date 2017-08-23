static int
set_fflags_platform(struct archive_write_disk *a, int fd, const char *name,
    mode_t mode, unsigned long set, unsigned long clear)
{
	int r;

	(void)mode; /* UNUSED */
	if (set == 0  && clear == 0)
		return (ARCHIVE_OK);

	/*
	 * XXX Is the stat here really necessary?  Or can I just use
	 * the 'set' flags directly?  In particular, I'm not sure
	 * about the correct approach if we're overwriting an existing
	 * file that already has flags on it. XXX
	 */
	if ((r = lazy_stat(a)) != ARCHIVE_OK)
		return (r);

	a->st.st_flags &= ~clear;
	a->st.st_flags |= set;
#ifdef HAVE_FCHFLAGS
	/* If platform has fchflags() and we were given an fd, use it. */
	if (fd >= 0 && fchflags(fd, a->st.st_flags) == 0)
		return (ARCHIVE_OK);
#endif
	/*
	 * If we can't use the fd to set the flags, we'll use the
	 * pathname to set flags.  We prefer lchflags() but will use
	 * chflags() if we must.
	 */
#ifdef HAVE_LCHFLAGS
	if (lchflags(name, a->st.st_flags) == 0)
		return (ARCHIVE_OK);
#elif defined(HAVE_CHFLAGS)
	if (S_ISLNK(a->st.st_mode)) {
		archive_set_error(&a->archive, errno,
		    "Can't set file flags on symlink.");
		return (ARCHIVE_WARN);
	}
	if (chflags(name, a->st.st_flags) == 0)
		return (ARCHIVE_OK);
#endif
	archive_set_error(&a->archive, errno,
	    "Failed to set file flags");
	return (ARCHIVE_WARN);
}