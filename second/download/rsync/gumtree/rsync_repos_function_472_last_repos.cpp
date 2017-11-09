int do_lutimes(const char *fname, time_t modtime, uint32 mod_nsec)
{
	struct timeval t[2];

	if (dry_run) return 0;
	RETURN_ERROR_IF_RO_OR_LO;

	t[0].tv_sec = time(NULL);
	t[0].tv_usec = 0;
	t[1].tv_sec = modtime;
	t[1].tv_usec = mod_nsec / 1000;
	return lutimes(fname, t);
}