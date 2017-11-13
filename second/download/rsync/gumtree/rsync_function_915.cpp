static struct passwd *want_all_groups(int f_out, uid_t uid)
{
	struct passwd *pw;
	if ((pw = getpwuid(uid)) == NULL) {
		rsyserr(FLOG, errno, "getpwuid failed");
		io_printf(f_out, "@ERROR: getpwuid failed\n");
		return NULL;
	}
	/* Start with the default group and initgroups() will add the reset. */
	gid_count = 1;
	gid_list[0] = pw->pw_gid;
	return pw;
}