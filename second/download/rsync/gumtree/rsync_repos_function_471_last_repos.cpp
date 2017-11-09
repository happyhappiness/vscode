int do_utimensat(const char *fname, time_t modtime, uint32 mod_nsec)
{
	struct timespec t[2];

	if (dry_run) return 0;
	RETURN_ERROR_IF_RO_OR_LO;

	t[0].tv_sec = 0;
	t[0].tv_nsec = UTIME_NOW;
	t[1].tv_sec = modtime;
	t[1].tv_nsec = mod_nsec;
	return utimensat(AT_FDCWD, fname, t, AT_SYMLINK_NOFOLLOW);
}