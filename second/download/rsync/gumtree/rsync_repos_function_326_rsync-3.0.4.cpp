int set_modtime(const char *fname, time_t modtime, mode_t mode)
{
#if !defined HAVE_LUTIMES || !defined HAVE_UTIMES
	if (S_ISLNK(mode))
		return 1;
#endif

	if (verbose > 2) {
		rprintf(FINFO, "set modtime of %s to (%ld) %s",
			fname, (long)modtime,
			asctime(localtime(&modtime)));
	}

	if (dry_run)
		return 0;

	{
#ifdef HAVE_UTIMES
		struct timeval t[2];
		t[0].tv_sec = time(NULL);
		t[0].tv_usec = 0;
		t[1].tv_sec = modtime;
		t[1].tv_usec = 0;
# ifdef HAVE_LUTIMES
		if (S_ISLNK(mode)) {
			if (lutimes(fname, t) < 0)
				return errno == ENOSYS ? 1 : -1;
			return 0;
		}
# endif
		return utimes(fname, t);
#elif defined HAVE_STRUCT_UTIMBUF
		struct utimbuf tbuf;
		tbuf.actime = time(NULL);
		tbuf.modtime = modtime;
		return utime(fname,&tbuf);
#elif defined HAVE_UTIME
		time_t t[2];
		t[0] = time(NULL);
		t[1] = modtime;
		return utime(fname,t);
#else
#error No file-time-modification routine found!
#endif
	}
}